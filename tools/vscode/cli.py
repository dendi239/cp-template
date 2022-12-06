#! /usr/bin/env python3

import pathlib
import typing as tp

import click

import vscode


@click.group()
@click.option("--debug/--no-debug", default=False)
def cli(debug):
    pass


@cli.command()  # @cli, not @click!
@click.argument("bazel_target")
@click.option("--config-dir", type=pathlib.Path, default=pathlib.Path(".vscode"))
def add_debug(bazel_target, config_dir):
    vscode.add_debug(bazel_target, config_dir)


@cli.command()
@click.argument("config_file", type=str)
def parse_tasks(config_file):
    tasks_config = vscode.TasksConfig.parse_file(config_file)
    click.echo(tasks_config.json(indent=2))


@cli.command()
@click.argument("config_file", type=str)
def parse_launch(config_file):
    launch_config = vscode.LaunchConfig.parse_file(config_file)
    click.echo(launch_config.json(indent=2))


if __name__ == "__main__":
    cli(obj={})
