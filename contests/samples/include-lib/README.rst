Include lib
-----------

In this sample we'll take a look at embeding library code into single source.
We'll use tourist's approach to do modular arifmetics, so we created some library stubs at ``include/tourist`` which we'll use.

Note that we referenced it inside our ``BUILD`` file:

.. code-block:: bazel
  
  cc_binary(
      name = "include-lib",
      srcs = ["include-lib.cpp"] + glob(["*.hpp"]),
      deps = [
          "//include:stdlib",
          "//include:tourist",  # <--- HERE
      ],
  )

It's used in the 7-th line of our cpp code:

.. code-block:: cpp

  #include "bits/stdc++.h"
  #include "tourist/modular.hpp"

Now all it takes to generate full file is following:

.. code-block:: bash

  contests/samples/include-lib $ bazel run :expand
  # Prints entire expanded file.

**Pro tip**: you can either direct output to file, or to clipboard (on mac at least):

.. code-block:: bash

  contests/samples/include-lib $ bazel run :expand > expanded.cpp
  contests/samples/include-lib $ bazel run :expand | pbcopy  # mac users only
