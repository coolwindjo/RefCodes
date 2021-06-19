load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
	name = "01_test",
	size = "small",
	srcs = [
		"01_ExtractMethod_unittest.cc",
		"01_ExtractMethod.cc",
		"01_ExtractMethod.h",
	],
	deps = [
		"@gtest//:gtest",
		"@gtest//:gtest_main"	# Only if srcs have no main()
		# "@com_google_googletest//:gtest_main"
	],
)