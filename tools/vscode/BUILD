load("@rules_python//python:defs.bzl", "py_binary", "py_library")
load("@local_tools_deps//:requirements.bzl", "requirement")

py_library(
    name = "vscode-lib",
    srcs = ["vscode.py"],
    deps = [
        requirement("click"),
        requirement("json5"),
        requirement("pydantic"),
    ],
    visibility = [
        "//tools:__subpackages__",
    ]
)

py_binary(
    name = "vscode",
    srcs = ["cli.py"],
    main = "cli.py",
    python_version = "PY3",
    deps = [
        "vscode-lib",
    ],
)
