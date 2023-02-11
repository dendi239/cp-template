load("//tools/expand:expand.bzl", "cp_expand")
load("//tools/test:test.bzl", "cp_test")

cc_binary(
    name = "include-lib",
    srcs = ["include-lib.cpp"] + glob(["*.hpp"]),
    deps = [
        "//include:stdlib",
        "//include:tourist",
    ],
)

cp_expand(
    name = "expand",
    source = "include-lib.cpp",
)

cp_test(
    name = "test",
    files = glob(["*.txt"]),
    target = ":include-lib",
)
