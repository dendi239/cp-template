#! /usr/bin/env python

import argparse
import sys


def tokens(filename: str):
    with open(filename, "r") as f:
        for line in f:
            yield from line.strip().split()


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("answer")
    parser.add_argument("output")
    args = parser.parse_args()

    expected = list(tokens(args.answer))
    actual = list(tokens(args.output))

    if expected != actual:
        sys.exit(1)


if __name__ == "__main__":
    main()
