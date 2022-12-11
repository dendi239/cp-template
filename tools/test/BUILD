load("//tools/test:test.bzl", "cp_test")

py_binary(
    name = "a-plus-b",
    srcs = ["a-plus-b.py"],
    main = "a-plus-b.py",
)

py_binary(
    name = "checker",
    srcs = ["checker.py"],
    main = "checker.py",
    visibility = ["//visibility:public"],
)

py_binary(
    name = "run-tests",
    srcs = ["run-tests.py"],
    main = "run-tests.py",
    visibility = ["//visibility:public"],
)

cp_test(
    name = "a-plus-b-test",
    target = ":a-plus-b",
    files = glob(["*.txt"]),
)
