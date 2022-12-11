#! /usr/bin/env python3

import argparse
import pathlib
import subprocess
import tempfile
import sys


def print_file(name: str, filename: str) -> None:
    print(name)
    for line in open(filename, "r"):
        print(f"  {line.rstrip()}")
    print("-" * 77)


def print_filecontents(name: str, content: bytes) -> None:
    print(name)
    for line in content.decode("utf-8").split("\n"):
        print(f"  {line.rstrip()}")
    print("-" * 77)


def run_test(executable, checker, input, output) -> None:
    assert pathlib.Path(executable).exists()
    assert input.exists()
    assert output.exists()

    with tempfile.NamedTemporaryFile(delete=False) as t:
        res = subprocess.run(
            [executable],
            input=open(input, "rb").read(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        if res.returncode:
            print(f"Runtime error: {res.returncode}")
            print_filecontents("stderr", res.stderr)
            sys.exit(1)

        with open(t.name, "wb") as f:
            f.write(res.stdout)

        checker_res = subprocess.run([checker, output, t.name], capture_output=True)
        if checker_res.returncode:
            print_filecontents("checker", checker_res.stdout)
            print_file("input", input)
            print_file(f"expected({output})", output)
            print_file("actual", t.name)
            print_filecontents("stderr", res.stderr)
            sys.exit(1)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("executable")
    parser.add_argument("checker")
    parser.add_argument("test_files", nargs="+")

    args = parser.parse_args()
    inputs, outputs = {}, {}

    for file in args.test_files:
        path = pathlib.Path(file)
        if path.name.startswith("in") and path.suffix == ".txt":
            inputs[path.name[2:-4]] = path

        if path.name.startswith("ans") and path.suffix == ".txt":
            outputs[path.name[3:-4]] = path

    for k, v in inputs.items():
        if k in outputs:
            run_test(args.executable, args.checker, v, outputs[k])


if __name__ == "__main__":
    main()
