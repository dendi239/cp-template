#! /usr/bin/env python3

import argparse
import dataclasses
import datetime
import enum
import io
import math
import pathlib
import psutil
import subprocess
import tempfile
import typing as tp
import sys


class TestStatus(enum.Enum):
    NA = "N/A"
    OK = "OK"
    WA = "Wrong Answer"
    RE = "Runtime Error"
    ML = "Memory Limit"
    TL = "Time Limit"

    def short(self) -> str:
        if self == TestStatus.OK:
            return "OK"
        elif self == TestStatus.WA:
            return "WA"
        elif self == TestStatus.RE:
            return "RE"
        elif self == TestStatus.ML:
            return "ML"
        elif self == TestStatus.TL:
            return "TL"
        else:
            raise NotImplementedError


@dataclasses.dataclass
class TestRun:
    status: TestStatus
    time: datetime.timedelta
    memory: int

    input: pathlib.Path
    answer: pathlib.Path

    def passed(self) -> bool:
        return self.status == TestStatus.OK

    def short_description(self) -> str:
        return "  ".join(
            (
                self.status.short(),
                f"{self.input.name}/{self.answer.name}",
                f"Time: {format_time(self.time).ljust(5, ' ')}",
                f"Memory: {convert_size(self.memory).ljust(5, ' ')}",
            )
        )

    def print_failure(self, f) -> None:
        pass


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


def print_fileobj(name: str, file) -> None:
    print(name)
    for line in file:
        print(f"  {line.decode('utf-8').rstrip()}")
    print("-" * 77)


def convert_size(size_bytes):
    if size_bytes == 0:
        return "0B"
    size_name = ("B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB")
    i = int(math.floor(math.log(size_bytes, 1024)))
    p = math.pow(1024, i)
    s = round(size_bytes / p, 2)
    return f"{size_bytes / p:.2f}{size_name[i]}"


def format_time(t: datetime.timedelta) -> str:
    if t < datetime.timedelta(milliseconds=1):
        microseconds = t.microseconds
        return f"{microseconds:4.1f}ns"
    if t < datetime.timedelta(seconds=1):
        miliseconds = t.microseconds / 1000
        return f"{miliseconds:4.1f}ms"
    else:
        return f"{t.total_seconds():5.3f}s"


@dataclasses.dataclass
class Test:
    executable: pathlib.Path
    checker: pathlib.Path
    interactor: pathlib.Path

    input: pathlib.Path
    answer: pathlib.Path


def poll(proc: subprocess.Popen) -> tp.Tuple[datetime.timedelta, int]:
    max_memory = 0
    start = datetime.datetime.now()
    deadline = start + datetime.timedelta(seconds=180)

    while True:
        res = proc.poll()
        try:
            memory_info = psutil.Process(proc.pid).memory_info()
            max_memory = max(max_memory, memory_info.rss)
        except psutil.NoSuchProcess:
            pass
        if res is not None:
            break
        if datetime.datetime.now() > deadline:
            proc.kill()
            res = proc.returncode

    now = datetime.datetime.now()
    return (now - start, max_memory)


def new_run_test(t: Test) -> TestRun:
    with tempfile.NamedTemporaryFile() as tf:
        interactor_proc = subprocess.Popen(
            [t.interactor, t.input, tf.name],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )

        proc = subprocess.Popen(
            [t.executable],
            stdin=interactor_proc.stdout,
            stdout=interactor_proc.stdin,
            stderr=subprocess.PIPE,
        )

        time, memory = poll(proc)
        result = TestRun(
            status=TestStatus.OK,
            time=time,
            memory=memory,
            input=t.input,
            answer=t.answer,
        )

        if proc.returncode:
            result.status = TestStatus.RE
            return result

        checker_proc = subprocess.Popen(
            [t.checker, t.input, tf.name, t.answer], stderr=subprocess.PIPE
        )

        retcode = checker_proc.wait()
        if retcode:
            result.status = TestStatus.WA

        return result


def run_test(t: Test) -> bool:
    with tempfile.NamedTemporaryFile(delete=True) as tf:
        proc = subprocess.Popen(
            [t.executable],
            stdin=open(t.input, "rb"),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )

        time, memory = poll(proc)
        res = proc.returncode

        if res:
            print(f"Runtime error: {res}")
            print_fileobj("stderr", proc.stderr)
            return True

        with open(tf.name, "wb") as f:
            for line in proc.stdout:
                f.write(line)

        checker_res = subprocess.run(
            [t.checker, t.answer, tf.name], capture_output=True
        )
        print(
            f"{t.input.name}  Time: {format_time(time)}  Memory: {convert_size(memory)}"
        )

        if checker_res.returncode:
            print_filecontents("checker", checker_res.stdout)
            print_file(f"input({t.input.name})", t.input)
            print_file(f"expected({t.answer.name})", t.answer)
            print_file("actual", tf.name)
            print_fileobj("stderr", proc.stderr)
            return True

        return False


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("executable")
    parser.add_argument("checker")
    parser.add_argument("interactor")
    parser.add_argument("test_files", nargs="*")

    args = parser.parse_args()
    inputs, outputs = {}, {}

    for file in args.test_files:
        path = pathlib.Path(file)
        if path.name.startswith("in") and path.suffix == ".txt":
            inputs[path.name[2:-4]] = path

        if path.name.startswith("ans") and path.suffix == ".txt":
            outputs[path.name[3:-4]] = path

    failed = False
    for k, v in inputs.items():
        if k in outputs:
            t = Test(
                executable=pathlib.Path(args.executable),
                checker=pathlib.Path(args.checker),
                interactor=pathlib.Path(args.interactor),
                input=v,
                answer=outputs[k],
            )
            # TODO: replace with new_run_test
            if run_test(t):
                failed = True

    if failed:
        sys.exit(1)


if __name__ == "__main__":
    main()
