#!/bin/bash

# This file checks whether parameters that have been moved from CAT_USER_DEFINED
# to the regular categories can be removed from CAT_USER_DEFINED to save space.

grep "^{0x" BSB_lan_defs.h | \
sed -e 's/^{0x\(..\)..\(....\).*/\1\.\.\2/;' | \
sort | \
uniq -d | \
while read -r line ; do
  grep "$line.*CAT_USER_DEFINED.*STR10200" BSB_lan_defs.h
done
