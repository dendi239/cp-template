"""rules for testing competitive programming solutions.
"""

def _single_test(ctx, runner, executable, checker, interactor, files):
    checker_content = "./{runner} {executable} {checker} {interactor} {tests}"

    runfiles = ctx.runfiles(files = files)
    runfiles = runfiles.merge(runner.default_runfiles)
    runfiles = runfiles.merge(executable.default_runfiles)
    runfiles = runfiles.merge(checker.default_runfiles)
    runfiles = runfiles.merge(interactor.default_runfiles)
 
    run_me = ctx.actions.declare_file(ctx.label.name)
    ctx.actions.write(
        output = run_me,
        content = checker_content.format(
            runner = runner.files_to_run.executable.short_path,
            executable = executable.files_to_run.executable.short_path,
            checker = checker.files_to_run.executable.short_path,
            interactor = interactor.files_to_run.executable.short_path,
            tests = " ".join([file.path for file in files]),
        ),
    )

    return DefaultInfo(
        executable = run_me,
        runfiles = runfiles,
    )


def _cp_test_impl(ctx):
    return [
        _single_test(
            ctx = ctx,
            runner = ctx.attr._runner,
            executable = ctx.attr.target,
            checker = ctx.attr.checker,
            interactor = ctx.attr.interactor,
            files = [
                file
                for file_list in ctx.attr.files
                for file in file_list.files.to_list()
            ],
        ),
    ]

cp_test = rule(
    test = True,
    implementation = _cp_test_impl,
    attrs = {
        "username": attr.string(),
        "target": attr.label(executable = True, cfg = "exec"),
        "interactor": attr.label(executable = True, cfg = "exec", default = "//tools/test:cat"),
        "checker": attr.label(executable = True, cfg = "exec", default = "//tools/test:checker"),
        "files": attr.label_list(allow_files = True),
        "_runner": attr.label(executable = True, cfg = "exec", default = "//tools/test:run-tests"),
    },
)
