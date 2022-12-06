load("@local_tools_deps//:requirements.bzl", "all_requirements")
load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "python",
    srcs = glob(["**/*.py"]),
    main = "python.py",
    deps = all_requirements,
)
