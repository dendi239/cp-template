py_library(
    name = "expand-lib",
    srcs = ["expand.py"],
    visibility = ["//visibility:public"],
)

py_binary(
    name = "expander",
    srcs = ["expand.py"],
    main = "expand.py",
)

exports_files([
    "expand.template.py",
])
