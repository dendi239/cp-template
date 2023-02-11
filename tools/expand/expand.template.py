#! /usr/bin/env python3

import os
import pathlib
import subprocess
import typing as tp

from tools.expand.expand import expand


def get_target(label: str) -> str:
    return (
        subprocess.check_output(
            [
                f"bazel",
                f"query",
                f"attr('srcs', {label}, '//...')",
            ]
        )
        .decode("utf-8")
        .split("\n")[0]
    )


def get_defines(target: str) -> tp.List[pathlib.Path]:
    return [
        pathlib.Path(path)
        for path in subprocess.check_output(
            [
                "bazel",
                "cquery",
                "--output=starlark",
                "--starlark:expr=' '.join(providers(target)['CcInfo'].compilation_context.local_defines.to_list())",
                target,
            ]
        )
        .decode("utf-8")
        .split()
    ]

def get_libs(target: str) -> tp.List[pathlib.Path]:
    return [
        pathlib.Path(path)
        for path in subprocess.check_output(
            [
                "bazel",
                "cquery",
                "--output=starlark",
                "--starlark:expr=' '.join(providers(target)['CcInfo'].compilation_context.includes.to_list())",
                target,
            ]
        )
        .decode("utf-8")
        .split()
    ]


def main() -> None:
    source_label = "{SOURCE_LABEL}"
    source_path = pathlib.Path("{SOURCE_PATH}")

    workspace_root = pathlib.Path(os.environ["BUILD_WORKSPACE_DIRECTORY"])
    os.chdir(workspace_root)

    target = get_target(source_label)

    subprocess.check_call(["bazel", "build", target])
    libs = [workspace_root / lib for lib in get_libs(target)]

    for line in expand(
        source_path,
        system_libraries=[],
        libraries=libs,
    ):
        print(line)


if __name__ == "__main__":
    main()
