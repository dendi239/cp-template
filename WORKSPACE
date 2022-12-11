local_repository(
    name = "hedron_compile_commands",
    path = "3rdparty/bazel-compile-commands-extractor",
    repo_mapping = {"": ""},
)

local_repository(
    name = "rules_python",
    path = "3rdparty/rules_python",
    repo_mapping = {"": ""},
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

load("@rules_python//python:repositories.bzl", "python_register_toolchains")

python_register_toolchains(
    name = "python3_9",
    python_version = "3.9",
)

load("@python3_9//:defs.bzl", "interpreter")
load("@rules_python//python:pip.bzl", "pip_parse")

pip_parse(
    name = "local_tools_deps",
    python_interpreter_target = interpreter,
    requirements_lock = "//tools/py-deps:requirements.txt",
)

load("@local_tools_deps//:requirements.bzl", "install_deps")

install_deps()
