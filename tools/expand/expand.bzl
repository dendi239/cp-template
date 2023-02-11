"""Bundles all internal libraries to a single source.
"""

def _cp_expand_impl(ctx):
    script = ctx.actions.declare_file(ctx.attr.name)
    ctx.actions.expand_template(
        output = script,
        is_executable = True,
        template = ctx.file._script_template,
        substitutions = {
            "{SOURCE_LABEL}": str(ctx.attr.source.label),
            "{SOURCE_PATH}": str(ctx.attr.source.files.to_list()[0].path),
        },
    )
    return DefaultInfo(files = depset([script]))

_cp_expand = rule(
    implementation = _cp_expand_impl,
    attrs = {
        "source": attr.label(allow_single_file = True),
        "_script_template": attr.label(
            allow_single_file = True,
            default = "//tools/expand:expand.template.py",
        ),
    },
)

def cp_expand(name, source, **kwargs):
    script_name = "script-" + name + ".py"

    _cp_expand(
        name = script_name,
        source = source,
    )

    native.py_binary(
        name = name,
        srcs = [script_name],
        deps = [
            "//tools/expand:expand-lib",
        ],
        main = script_name,
        **kwargs
    )
