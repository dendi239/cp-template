#! /usr/bin/env python

import argparse
import pathlib


BUILD_TEMPLATE = \
"""cc_binary(
  name = "{name}",
  srcs = ["{name}.cpp"],
  deps = ["//include:stdlib"],
)
"""

CPP_TEMPLATE = \
"""#include "bits/stdc++.h"

using namespace std;

int main() {

  return 0;
}
"""


def create(name: str) -> None:
  full_path = pathlib.Path(name)
  
  assert full_path.is_absolute(), f"Please, provide an absolute path. $(pwd)/{name} would work."
  assert not full_path.exists(), f"Path {name} already exists."

  full_path.mkdir(parents=True)
  name = full_path.stem

  build_path = full_path / 'BUILD'
  source_path = full_path / f"{name}.cpp"

  build_path.write_text(BUILD_TEMPLATE.format(name=name))
  source_path.write_text(CPP_TEMPLATE)


def main() -> None:
  parser = argparse.ArgumentParser()
  parser.add_argument('name', help='Name of the new problem')
  
  args = parser.parse_args()
  create(args.name)


if __name__ == '__main__':
  main()
