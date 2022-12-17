load("@local_tools_deps//:requirements.bzl", "requirement")

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
    deps = [
        requirement("psutil"),
    ],
    main = "run-tests.py",
    visibility = ["//visibility:public"],
)

py_binary(
    name = "cat",
    srcs = ["cat.py"],
    main = "cat.py",
    visibility = ["//visibility:public"],
)
