load("//tools/expand:expand.bzl", "cp_expand")
load("//tools/test:test.bzl", "cp_test")

cc_binary(
    name = "{name}",
    srcs = ["{name}.cpp"] + glob(["*.hpp"]),
    deps = [
        "//include:stdlib",
    ],
)

cp_expand(
    name = "expand",
    source = "{name}.cpp",
)

cp_test(
    name = "test",
    files = glob(["*.txt"]),
    target = ":{name}",
)
