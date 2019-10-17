#!/bin/bash
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1

export LD_PRELOAD="$(pwd)/libft_malloc.so"
export LD_DEBUG="libs"
$@

# strace -ff -o strace.dump.log $@
# ltrace -l ./libft_malloc.so -o ltrace.dump.log $@
# ltrace $@

#valgrind --trace-children=yes env \
#  DYLD_LIBRARY_PATH=. \
#  DYLD_INSERT_LIBRARIES="libft_malloc.so" \
#  DYLD_FORCE_FLAT_NAMESPACE=1 \
#  $@
