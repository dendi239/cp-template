Competitive Programming
-----------------------

This repository will have competitive programming solutions and tools I'm using for.
Chosen build system is Bazel, editor — vs code.

Setup
=====

This project uses its dependencies as git submodules, so you'll likely need to run following right after cloning this repository:

.. code-block:: bash

	git submodule update --init --recursive


``compile_commands.json``
*************************

For various editors bazel is something unknown: yet clion claims support to it, but I haven't managed to run even debugger there.
If you have your favorite code editor for cpp, you'll probably have option to run ``clangd`` there for code completion, inspection and all that stuff.
Thanks to bazel-compile-commands-extractor_, to generate ``compile_commands.json`` you need just run following:

.. code-block:: bash

	bazel run @hedron_compile_commands//:refresh_all


.. _bazel-compile-commands-extractor:
	https://github.com/hedronvision/bazel-compile-commands-extractor

vscode debugger
***************

It isn't that easy to setup debugger when you're working with cpp in Bazel.
Even CLion doesn't have it working right out of the box: let alone that they charge money for it.
To do it in vscode with existing setup, you'll need to provide bazel target which you wanna debug (assuming it's target ``//eolymp/khto-round-5/c-clusters:c-clusters``):

.. code-block:: bash

	bazel run -- //tools/vscode-config add-debug eolymp/khto-round-5/c-clusters:c-clusters
