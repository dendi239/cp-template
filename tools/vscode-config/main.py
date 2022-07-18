#! /usr/bin/env python3

import pathlib
import typing as tp

import click
import json5
from pydantic import BaseModel


def to_camel(string: str) -> str:
    camel_case = "".join(word.capitalize() for word in string.split("_"))
    return camel_case[0].lower() + camel_case[1:]


class Group(BaseModel):
    kind: str = "build"
    isDefault: bool = False


class Task(BaseModel):
    label: str
    type: str = "shell"
    command: str
    group: Group = Group()


class TasksConfig(BaseModel):
    version: str = "2.0.0"
    tasks: tp.List[Task] = []

    def add_task(self, task: Task) -> None:
        for i, t in enumerate(self.tasks):
            if t.label == task.label:
                self.tasks[i] = task
                return
        self.tasks.append(task)

    class Config:
        json_loads = json5.loads


class Configuration(BaseModel):
    name: str
    type: str = "cppdbg"
    preLaunchTask: str
    request: str = "launch"
    program: str
    cwd: str = "${workspaceFolder}"
    MIMode: str = "lldb"
    externalConsole: bool = True
    sourceFileMap: tp.Dict[str, str] = {}


def build_configuration(bazel_target: str, build_task_name: str) -> Configuration:
    prefix = bazel_target.split("/")[0] + "/"
    return Configuration(
        name=bazel_target,
        preLaunchTask=build_task_name,
        program=f"${{workspaceFolder}}/bazel-out/darwin-dbg/bin/{bazel_target.replace(':', '/')}",
        sourceFileMap={
            prefix: f"${{workspaceFolder}}/{prefix}",
        },
    )


class LaunchConfig(BaseModel):
    version: str = "0.2.0"
    configurations: tp.List[Configuration] = []

    def add_configuration(self, configuration: Configuration) -> None:
        for i, c in enumerate(self.configurations):
            if c.name == configuration.name:
                self.configurations[i] = configuration
                return
        self.configurations.append(configuration)

    class Config:
        json_loads = json5.loads


def try_parse(cls: tp.Type[BaseModel], path: pathlib.Path) -> tp.Optional[BaseModel]:
    try:
        return cls.parse_file(path)
    except FileNotFoundError:
        return cls()


@click.group()
@click.option("--debug/--no-debug", default=False)
def cli(debug):
    pass


@cli.command()  # @cli, not @click!
@click.argument("bazel_target")
@click.option("--config-dir", type=pathlib.Path, default=pathlib.Path(".vscode"))
def add_debug(bazel_target, config_dir):
    bazel_target = bazel_target.strip("/")

    tasks_config = try_parse(TasksConfig, config_dir / "tasks.json")
    launch_config = try_parse(LaunchConfig, config_dir / "launch.json")

    task = Task(
        label=f"build {bazel_target}",
        command=f"bazel build --compilation_mode=dbg --spawn_strategy=standalone {bazel_target}",
    )
    tasks_config.add_taks(task)
    launch_config.add_configuration(build_configuration(bazel_target, task.label))

    config_dir.mkdir(exist_ok=True)
    with open(config_dir / "tasks.json", "w") as f:
        f.write(tasks_config.json(indent=2))
    with open(config_dir / "launch.json", "w") as f:
        f.write(launch_config.json(indent=2))


@cli.command()
@click.argument("config_file", type=str)
def parse_tasks(config_file):
    tasks_config = TasksConfig.parse_file(config_file)
    click.echo(tasks_config.json(indent=2))


@cli.command()
@click.argument("config_file", type=str)
def parse_launch(config_file):
    launch_config = LaunchConfig.parse_file(config_file)
    click.echo(launch_config.json(indent=2))


if __name__ == "__main__":
    cli(obj={})
