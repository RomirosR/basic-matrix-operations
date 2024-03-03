load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test_lib",
    srcs = ["test.cpp"],
    deps = [
        "//lib:matrix_lib",
        "//tools/catch:catch2",
    ],
)