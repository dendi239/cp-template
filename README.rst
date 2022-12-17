Competitive Programming
-----------------------

This repository will have competitive programming solutions and tools I'm using for.
Chosen build system is Bazel, editor — vs code.

Setup
=====

This project uses its dependencies as git submodules, so you'll likely need to run following right after cloning this repository:

.. code-block:: bash

	git submodule update --init --recursive


Here're available a few useful tools, come take a look.
All of them intended to be useful for developing (mostly) cpp-based sources for competitive programming.
The editor of choice is vscode, build system is Bazel.
Here you can find tools I'm willing to share for everyone to be useful and those can be dropped in without necessity to dealing with stuff like my own library.

create source
_____________

Creates directory for given problem.
Accepts full path to target directory, will create all parent once, however you must ensure that target directory does not exist.
It creates debugging target for vscode as well as ``BUILD`` file to be used for building and testing.
You can configure templates of those in ``tools/create/template*``.

.. code-block:: bash

	# creates directory with problem at path/to/source 
	bazel run //tools/create -- $(pwd)/path/to/source

tests
_____

If you want to opt-in to automatic testing, feel free to use ``//tools/test``, it already set up by ``//tools/create``.
You can tweak checker and interactor there if you wish.
Tests considered to be pairs of files of form ``inK.txt`` and ``ansK.txt``.

.. code-block:: bash
  
	cd path/to/source
	# let's add some tests (assume that you copied them from judge system
	pbpaste > in1.txt
	pbpaste > ans1.txt
	# let's run these tests
	bazel test :...

expand source
_____________

If you choose to reuse some existing code, you can find useful to put those in ``include/`` directory and use ``expander``.
You can pass multiple include directories, it will accept them as ``gcc`` does, convention mentioned earlier proven to be convenient. 

.. code-block:: bash

	bazel run //tools/expander -- -I=$(bazel info workspace)/include $(pwd)/your-source.cpp

vscode support
______________

There're plenty of tools to work with vscode configuration, take a look:

.. code-block:: bash
  
	bazel run //tools/vscode -- --help

``compile_commands.json``
*************************

For various editors bazel is something unknown: yet clion claims support to it, but I haven't managed to run even debugger there.
If you have your favorite code editor for cpp, you'll probably have option to run ``clangd`` there for code completion, inspection and all that stuff.
Thanks to bazel-compile-commands-extractor_, to generate ``compile_commands.json`` you need just run following:

.. code-block:: bash
  
	bazel run @hedron_compile_commands//:refresh_all


.. _bazel-compile-commands-extractor:
	https://github.com/hedronvision/bazel-compile-commands-extractor

