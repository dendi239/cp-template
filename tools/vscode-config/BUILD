load("@rules_python//python:defs.bzl", "py_binary")
load("@local_tools_deps//:requirements.bzl", "requirement")

py_binary(
    name = "vscode-config",
    srcs = ["main.py"],
    main = "main.py",
    python_version = "PY3",
    deps = [
        requirement("click"),
        requirement("json5"),
        requirement("pydantic"),
    ],
)
