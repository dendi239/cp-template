#! /usr/bin/env python3

import argparse
import logging
import pathlib
import typing as tp
import re


def remove_comments(s: str, m=re.compile("(//.*$|/\*.*\*/)")) -> str:
    matched = m.search(s)
    if matched:
        (l, r) = matched.span()
        s = s[:l] + s[r:]
    return s


class MacroStorage:
    def __init__(self) -> None:
        self.defines: tp.Dict[str, tp.Optional[str]] = {}

    def define(self, macro: str, value: tp.Optional[str] = None) -> None:
        self.defines[macro] = value

    def undef(self, macro: str) -> None:
        del self.defines[macro]

    def defined(self, macro: str) -> bool:
        return macro in self.defines


class MacroScope:
    def __init__(self, macro: str, target: bool, storage: MacroStorage) -> None:
        self.macro = macro
        self.active = target == storage.defined(macro)

    def ifdef(macro: str, storage: MacroStorage) -> "MacroScope":
        return MacroScope(macro, True, storage)

    def ifndef(macro: str, storage: MacroStorage) -> "MacroScope":
        return MacroScope(macro, False, storage)

    def is_active(self) -> bool:
        return self.active

    def flip(self) -> None:
        self.active = not self.active


class MacroMachine:
    def __init__(
        self,
        known_macro_regexp="(ATCODER.*|DENDI239)",
    ) -> None:
        self.define_macro = re.compile(known_macro_regexp)
        self.storage = MacroStorage()
        self.stack = []
        self.managed_stack = []

    def managed(self, macro: str) -> bool:
        return bool(self.define_macro.fullmatch(macro))

    def consume(self, line: str) -> bool:
        line = remove_comments(line)

        if line.startswith("#if"):
            macro = line.split()[1]
            scope = (
                MacroScope.ifdef(macro, self.storage)
                if line.startswith("#ifdef")
                else MacroScope.ifndef(macro, self.storage)
            )

            self.stack.append(scope)
            if self.managed(macro):
                self.managed_stack.append(scope)
                return True
            return False

        if line.startswith("#else"):
            self.stack[-1].flip()
            return self.managed_stack and self.managed_stack[-1] == self.stack[-1]

        if line.startswith("#endif"):
            scope = self.stack.pop()
            if self.managed_stack and self.managed_stack[-1] == scope:
                self.managed_stack.pop()
                return True
            return False

        if line.startswith("#define"):
            words = line.split()[1:]
            macro = words[0]

            if len(words) == 1:
                self.storage.define(words[0])
            else:
                self.storage.define(words[0], words[1])

            if self.managed(macro):
                return True
            return False

        return False

    def is_active(self) -> bool:
        return all(scope.is_active() for scope in self.managed_stack)


class Preprocessor:
    def __init__(
        self,
        system_libraries: tp.List[pathlib.Path],
        libraries: tp.List[pathlib.Path],
        seen: tp.Optional[tp.Set[pathlib.Path]] = None,
    ) -> None:
        self.libraries = libraries
        self.system = system_libraries
        self.seen = seen or set()
        self.seen_system = set()
        self.defines = MacroMachine()

    def is_pragma(self, line: str) -> bool:
        return remove_comments(line).strip() == "#pragma once"

    def is_system_include(self, line: str) -> bool:
        path = line[len("#include") :].strip().split(" ")[0]
        if path.startswith("<"):
            return True

        path = pathlib.Path(path[1:-1])
        for system_lib in self.system:
            if (system_lib / path).exists():
                return True

        return False

    def parse_include_path(self, line: str) -> pathlib.Path:
        path = line[len("#include") :].strip().split(" ")[0]
        if not path.startswith('"'):
            raise ValueError(f"'${line.strip()}' is not a valid include")
        return pathlib.Path(path[1:-1])

    def find(self, path: pathlib.Path, source: pathlib.Path) -> pathlib.Path:
        for lib in self.libraries + [source.parent]:
            if (lib / path).exists():
                return lib / path
        raise ValueError(f"can't find {path}")

    def expand(self, source: pathlib.Path) -> tp.Generator[str, None, None]:
        if source in self.seen:
            return

        for line in open(source, "r"):
            if self.is_pragma(line):
                self.seen.add(source)
                continue

            if self.defines.consume(line):
                continue

            if line.startswith("#include "):
                if self.is_system_include(line):
                    if line not in self.seen_system:
                        yield line
                        self.seen_system.add(line)
                    continue
                path = self.parse_include_path(line)
                location = self.find(path, source)
                yield from self.expand(location)
                continue

            if self.defines.is_active():
                yield line


def expand(
    source: pathlib.Path,
    system_libraries: tp.List[pathlib.Path],
    libraries: tp.List[pathlib.Path],
    seen: tp.Optional[tp.Set[pathlib.Path]] = None,
) -> tp.Generator[str, None, None]:
    prev_empty = True
    for line in Preprocessor(system_libraries, libraries, seen).expand(source):
        if not prev_empty or line.strip():
            yield line.rstrip()
        prev_empty = not line.strip()


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("source")
    parser.add_argument("-isystem", action="append")
    parser.add_argument("-I", action="append")
    parser.add_argument("-D", action="append")
    parser.add_argument("-o", "--output", default="/dev/stdout")
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("--cwd")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)
    else:
        logging.basicConfig(level=logging.INFO)

    output = args.output

    libs = []
    if args.I is not None:
        libs = [pathlib.Path(path) for path in args.I]

    system_libs = []
    if args.isystem is not None:
        system_libs = [pathlib.Path(path) for path in args.isystem]

    source = pathlib.Path(args.source)
    if args.cwd is not None:
        cwd = pathlib.Path(args.cwd)
        source = cwd / source
        libs = [cwd / lib for lib in libs]
        system_libs = [cwd / lib for lib in system_libs]

    with open(output, "w") as f:
        for line in expand(
            source=source,
            system_libraries=system_libs,
            libraries=libs,
        ):
            print(line, file=f)


if __name__ == "__main__":
    main()
