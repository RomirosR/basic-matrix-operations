load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "matrix_lib",
    srcs = ["matrix.cpp"],
    hdrs = ["matrix.h"],
    visibility = [
        "//main:__pkg__",
        "//tests/lib:__pkg__",
    ],
)
