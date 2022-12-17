load("//tools/test:test.bzl", "cp_test")

cc_binary(
    name = "{name}",
    srcs = ["{name}.cpp"] + glob(["*.hpp"]),
    deps = [
        "//include:stdlib",
    ],
)

cp_test(
    name = "{name}-test",
    files = glob(["*.txt"]),
    target = ":{name}",
)
