#"""Defines test rule for competive programming.
#"""
#
#TestInfo = provider(
#    doc = "Creates test case.",
#    fields = {
#        "input": "Input data.",
#        "output": "Output data.",
#    },
#)
#
#def _cp_test_impl(ctx):
#    prog = ctx.attr.prog.files_to_run.executable
#    ctx.actions.run(executable = ctx.executable.prog, arguments = [prog.path], outputs = [ctx.outputs.out])
#
#    return DefaultInfo(
#        executable = simple_checker,
#    )
#
#cp_test = rule(
#    implementation = _cp_test_impl,
#    test = True,
#    attrs = {
#        "prog": attr.label(executable = True, cfg = "exec"),
#        "checker": attr.label(),
#        "tests": attr.label_list(providers=[TestInfo]),
#    },
#    outputs = {
#        "out": "%{name}.out",
#    },
#)
