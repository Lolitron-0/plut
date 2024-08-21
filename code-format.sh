#!/bin/sh

find .  \( -path "./*/thirdparty/*" -prune -o -path "./build/*" -prune \) -iname "*.hpp" -o -iname "*.cc" | xargs clang-format-18 -i --verbose
