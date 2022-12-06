load("@rules_python//python:defs.bzl", "py_binary")
load("@local_tools_deps//:requirements.bzl", "requirement")

cc_binary(
    name = "cpp-test",
    srcs = ["template.cpp"],
    deps = ["//include:stdlib"],
)

py_binary(
    name = "create",
    srcs = ["cli.py"],
    data = [
        "template.cpp",
        "template.BUILD",
    ],
    main = "cli.py",
    python_version = "PY3",
    deps = [
        "//tools/vscode:vscode-lib",
        requirement("click"),
    ],
)
