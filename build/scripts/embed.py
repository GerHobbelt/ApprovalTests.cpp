#!/bin/env python3

# ==============================================================================
#  SPY - C++ Informations Broker
#  Copyright 2020 Joel FALCOU
#
# Licensed under the MIT License <http://opensource.org/licenses/MIT>.
# SPDX-License-Identifier: MIT
# ==============================================================================


"""
This script pre-processes files to aggregate every matching includes to
create a single file by removing extra includes guard, C comments and other noises.
"""

import re
import sys
import os.path
import argparse

# defaults paths to look for includes
from io import TextIOWrapper
from argparse import Namespace
from typing import Callable, List
default_includes_path = ['.']

# pp tokens regexp
r_escape_line = re.compile(r'^.*\\\n$')
r_empty_line = re.compile('^[ \t]*\n$')
r_pp_include = re.compile(r'^\s*#\s*include\s+["](.*)["]$')
r_pp_ifndef = re.compile(r'^\s*#\s*ifndef\s+(.*)\s*$')
r_pp_if_defined = re.compile(r'^\s*#\s*if\s+defined\(\s*(.*)\s*\)\s*$')
r_pp_if = re.compile(r'^\s*#\s*if.*$')
r_pp_endif = re.compile(r'^\s*#\s*endif.*$')
r_pp_define = re.compile(r'^\s*#\s*define\s+(.*)\s*$')
r_pp_pragma_once = re.compile(r'^\s*#\s*pragma\s+once\s*$')

# globals
will_escape = False
guard_stack = []
included_files = []
keep_guard = True

"""
Parse options. Here is the list of supported options:
    see `help`(s)
"""


def parse_opts(args: List[str]) -> Namespace:
    p = argparse.ArgumentParser(
        description='Aggregates headers into one single file')
    p.add_argument('-I', type=str, action='append', metavar='<dir>', default=[], dest='includes_path',
                   help='Add the specified directory to the search path for include files')
    p.add_argument('-v', dest='verbose', action='store_true', default=False,
                   help='Enable verbose mode, useful for debugging')
    p.add_argument('--include-match', type=str, metavar='<regexp>', default='.*', dest='r_include',
                   help='The regexp to match includes that will be expanded')
    p.add_argument('--guard-match', type=str, metavar='<regexp>', default='^.*_INCLUDED$', dest='r_guard',
                   help='The regexp to match includes guard')
    p.add_argument('-o', type=argparse.FileType('w'), metavar='<output-file>', dest='output', default=sys.stdout,
                   help='The output file')
    p.add_argument('filename', type=str, metavar='<input-file>',
                   help='The file to preprocess')

    opts = p.parse_args(args)
    opts.r_guard = re.compile(opts.r_guard)
    opts.r_include = re.compile(opts.r_include)
    return opts


"""
Print only if 'verbose' option is enabled
"""


def vprint(opts: Namespace, what: str) -> None:
    if opts.verbose:
        sys.stderr.write('verbose: {}\n'.format(what))


"""
Try to find a valid path for the given filename, if not found then exit
"""


def get_path_for(f: str, opts: Namespace) -> str:
    for path in opts.includes_path:
        path = os.path.join(path, f)
        vprint(opts, 'try to include: {}'.format(path))
        if os.path.isfile(path):
            return path
    sys.stderr.write('{}: file not found! aborting.\n'.format(f))
    sys.exit(1)


"""
Preprocess a single line
"""


def pp_line(line: str, output: TextIOWrapper, opts: Namespace) -> None:
    global will_escape
    global keep_guard

    is_escaped = will_escape
    will_escape = False
    if r_empty_line.match(line):
        output.write(line)
        return
    # #include
    m = r_pp_include.match(line)
    if m and opts.r_include.match(m.group(1)):
        keep_guard = False
        path = get_path_for(m.group(1), opts)
        pp_file(path, output, opts)
        return
    # we keep the guard only for the very first preprocessed file
    if not keep_guard:
        # #pragma once
        if r_pp_pragma_once.match(line):
            return
        # #ifndef / #if defined(...)
        m = r_pp_ifndef.match(line) or r_pp_if_defined.match(line)
        if m and opts.r_guard.match(m.group(1)):
            # we've found a new include guard, add a new counter to
            # keep track of it!
            guard_stack.append(1)
            return
        # #{if,ifndef} / #endif (pairs)
        if len(guard_stack):
            if r_pp_if.match(line):
                guard_stack[-1] += 1
            elif r_pp_endif.match(line):
                guard_stack[-1] -= 1
                if guard_stack[-1] < 0:
                    sys.stderr.write('non matching #endif found! aborting.')
                    sys.exit(1)
                if guard_stack[-1] == 0:
                    # we hit the 'endif' part of the guard, so pop it from
                    # the stack counter and do not print it!
                    guard_stack.pop()
                    return
            # define (guard)
            # we do check this one only if we have a valid stack counter
            # DO NOT PUT IT OUTSIDE OF THE `if len(guard_stack):`
            m = r_pp_define.match(line)
            if m and opts.r_guard.match(m.group(1)):
                return
    for i in opts.discardables:
        if i(line):
            return
    # add missing '\n' if needed, for example:
    #
    # '/* foo */\n'
    # gets turned into:
    # ''
    #
    # also:
    #
    # #define foo\
    # /**/
    # gets turned into:
    # #define foo
    # '\n'
    #
    if (is_escaped or len(line) > 0) and '\n' not in line:
        line += '\n'
    # check if the current line escape the next one
    if r_escape_line.match(line):
        will_escape = True
    # everything has been checked now! so we can print the current line
    output.write(line)


"""
Preprocess the file here!
"""


def pp_file(file_name: str, output: TextIOWrapper, opts: Namespace) -> None:
    # use the absolute version of the filename to always get the same path
    # e.g. ./foo.h == foo.h == bar/../foo.h
    abs_file_name = os.path.abspath(file_name)
    if abs_file_name in included_files:
        # if included, then do not process it!
        return
    included_files.append(abs_file_name)
    vprint(opts, 'preprocessing: {}'.format(abs_file_name))
    try:
        with open(abs_file_name, 'r') as f:
            dirname = os.path.dirname(f.name)
            opts.includes_path.append(dirname)
            filename = os.path.split(f.name)[1]
            pp_line('\n', output, opts)
            pp_line(f'// ******************** From: {filename}', output, opts)
            for line in f.readlines():
                pp_line(line, output, opts)
            opts.includes_path.remove(dirname)
    except IOError as e:
        sys.stderr.write(str(e) + '\n')
        sys.exit(1)


"""
The top-level function
"""


def embed(args: List[str], discardables: List[Callable] = []) -> None:
    for path in default_includes_path:
        args.append('-I')
        args.append(path)
    opts = parse_opts(args)
    opts.discardables = discardables
    pp_file(opts.filename, opts.output, opts)
    if opts.output != sys.stdout:
        opts.output.close()

def create_single_header_file(initial_file: str, output_file: str, include_search_path1: str, include_search_path2: str, discardables: List[Callable] = []) -> None:
    embed([
        initial_file,
        "-I",
        include_search_path1,
        "-I",
        include_search_path2,
        "-o",
        output_file
    ], discardables)


# The entry point!
if __name__ == '__main__':
    embed(sys.argv[1:])
