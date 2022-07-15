new_local_repository(
    name = "ac-library",
    build_file = "3rdparty/ac-library.bzl",
    path = "3rdparty/ac-library",
)

local_repository(
    name = "hedron_compile_commands",
    path = "3rdparty/bazel-compile-commands-extractor",
    repo_mapping = {"": ""},
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()
