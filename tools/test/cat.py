#! /usr/bin/env python3

import argparse
import sys


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('input')
    parser.add_argument('answer')
    
    args = parser.parse_args()
    for line in open(args.input, 'r'):
        sys.stdout.write(line)
        sys.stdout.close()
    
    with open(args.answer, 'w') as f:
        for line in sys.stdin.readlines():
            f.write(line)        


if __name__ == '__main__':
    main()
