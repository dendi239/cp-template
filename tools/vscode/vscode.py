import pathlib
import typing as tp

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
    type: str = "lldb"
    preLaunchTask: str
    request: str = "launch"
    program: str
    cwd: str = "${workspaceFolder}"
    console: str = "externalTerminal"
    sourceMap: tp.Dict[str, str] = {}


def build_configuration(bazel_target: str, build_task_name: str) -> Configuration:
    prefix = bazel_target.split("/")[0] + "/"
    return Configuration(
        name=bazel_target,
        preLaunchTask=build_task_name,
        program=f"${{workspaceFolder}}/bazel-bin/{bazel_target.replace(':', '/')}",
        sourceMap={
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
        self.configurations.sort(key=lambda x: x.name)

    class Config:
        json_loads = json5.loads


def try_parse(cls: tp.Type[BaseModel], path: pathlib.Path) -> tp.Optional[BaseModel]:
    try:
        return cls.parse_file(path)
    except FileNotFoundError:
        return cls()


def add_debug(bazel_target: str, config_dir: pathlib.Path) -> None:
    bazel_target = bazel_target.strip("/")

    tasks_config = try_parse(TasksConfig, config_dir / "tasks.json")
    launch_config = try_parse(LaunchConfig, config_dir / "launch.json")

    task = Task(
        label=f"build {bazel_target}",
        command=f"bazel build --compilation_mode=dbg --spawn_strategy=standalone {bazel_target}",
    )
    tasks_config.add_task(task)
    launch_config.add_configuration(build_configuration(bazel_target, task.label))

    config_dir.mkdir(exist_ok=True)
    with open(config_dir / "tasks.json", "w") as f:
        f.write(tasks_config.json(indent=2))
    with open(config_dir / "launch.json", "w") as f:
        f.write(launch_config.json(indent=2))
