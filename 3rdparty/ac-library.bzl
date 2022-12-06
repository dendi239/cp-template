"""Basic wrapper for ac-library.
ac-library supplied as a header only library, so we supply it.
It also supplies expander.py for expanding solutions, however, we don't yet use it.
"""

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "atcoder",
    hdrs = glob(["atcoder/**/*"]),
    alwayslink = False,
    include_prefix = "",
)
