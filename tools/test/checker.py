#! /usr/bin/env python

import argparse
from asyncio import subprocess


def main() -> None:
  parser = argparse.ArgumentParser()
  parser.add_argument('executable', help='Executable to test')
  args = parser.parse_args()

  subprocess.check_call([args.executable])


if __name__ == '__main__':
  main()
