#! /usr/bin/env python3

import argparse
import logging
import pathlib
import typing as tp


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
        self.defines = {}

    def is_pragma(self, line: str) -> bool:
        return line.strip() == "#pragma once"
    
    def is_system_include(self, line: str) -> bool:
        path = line[len("#include"):].strip().split(' ')[0]
        if path.startswith("<"):
            return True
        
        path = pathlib.Path(path[1:-1])        
        for system_lib in self.system:
            if (system_lib / path).exists():
                return True

        return False
    
    def parse_include_path(self, line: str) -> pathlib.Path:
        path = line[len("#include"):].strip().split(' ')[0]
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

            yield line
            

def expand(
    source: pathlib.Path,
    system_libraries: tp.List[pathlib.Path],
    libraries: tp.List[pathlib.Path],
    seen: tp.Optional[tp.Set[pathlib.Path]] = None,
) -> tp.Generator[str, None, None]:
    yield from Preprocessor(system_libraries, libraries, seen).expand(source)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("source")
    parser.add_argument("-isystem", action="append")
    parser.add_argument("-I", action="append")
    parser.add_argument("-o", "--output", default="/dev/stdout")
    parser.add_argument("-v", "--verbose", action="store_true")
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

    with open(output, "w") as f:
        prev_empty = True
        for line in expand(
            source=pathlib.Path(args.source),
            system_libraries=system_libs,
            libraries=libs,
        ):
            if not prev_empty or line.strip():
                print(line, end="", file=f)
            prev_empty = not line.strip()


if __name__ == '__main__':
    main()
