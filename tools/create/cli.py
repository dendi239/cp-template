#! /usr/bin/env python

import datetime
import pathlib
import shutil
import typing as tp

import click

import tools.vscode.vscode as vscode


BUILD_TEMPLATE_PATH = pathlib.Path(__file__).parent / "template.BUILD"
CPP_TEMPLATE_PATH = pathlib.Path(__file__).parent / "template.cpp"


def split_target(full_path: pathlib.Path) -> tp.Tuple[pathlib.Path, str]:
    path = full_path
    while not (path / "WORKSPACE").exists():
        path = path.parent
        if path.parent == path:
            raise

    return (path, full_path.relative_to(path))


@click.command()
@click.option("--debug/--no-debug", default=True)
@click.argument("name")
def create(name: str, debug: bool) -> None:
    full_path = pathlib.Path(name)

    assert (
        full_path.is_absolute()
    ), f"Please, provide an absolute path. $(pwd)/{name} would work."
    assert not full_path.exists(), f"Path {name} already exists."

    full_path.mkdir(parents=True)
    name = full_path.stem

    build_path = full_path / "BUILD"
    source_path = full_path / f"{name}.cpp"

    with open(CPP_TEMPLATE_PATH, "r") as source_template_f:
        with open(source_path, "w") as source_f:
            for source_line in source_template_f:
                now = datetime.datetime.now()
                source_f.write(source_line
                    .replace("{date}", now.strftime("%Y-%m-%d"))
                    .replace("{time}", now.strftime("%H:%M:%S"))
                )

    with open(BUILD_TEMPLATE_PATH, "r") as build_f:
        build_template = build_f.read()
        build_path.write_text(build_template.format(name=name))

    if debug:
        root, target = split_target(full_path)
        vscode.add_debug(str(target), root / ".vscode")


if __name__ == "__main__":
    create()
