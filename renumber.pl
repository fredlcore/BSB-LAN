#!/usr/bin/perl

# Reads BSB_lan_defs.h-style file from first command-line parameter and 
# renumbers entries in the CAT_USER_DEFINED category, starting from $startID.

open (IN, $ARGV[0]);

$startID = 10200;

while ($line = <IN>) {
  if ($line =~ /(.*CAT_USER_DEFINED.*VT_UNKNOWN,.*?)([0-9]+)(.*)(STR10200)(.*)/g) {
    print "$1$startID$3$4$5\n";
    $startID++;
  } else {
    print $line;
  }
}    
