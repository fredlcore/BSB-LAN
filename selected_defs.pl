#!/usr/bin/perl

# This script filters BSB_lan_defs.h and removes all device family/variant
# specific lines which are not matching the device family specified as 
# an argument to this script and outputs it to standard output.
#
# ./selected_defs.pl 162 165 > BSB_lan_defs_filtered.h
# would therefore output the whole definition file to BSB_lan_defs_filtered.h
# except all device family/variant specific lines, unless they are for 
# device families 162 and 165.
#
# The original BSB_lan_defs.h file can then be backed up and the newly
# generated file can be renamed to BSB_lan_defs.h
# This will save between 10-20kB of flash memory which may be especially
# useful for Arduino Mega2560 users with tighter memory constraints.

open (DEFS, "BSB_lan_defs.h");
while ($line = <DEFS>) {
  if ($line !~ /, *DEV\_\d\d\d\_/) {
    print $line;
  } else {
    foreach $devfam (@ARGV) {
      $devfam = sprintf("%03d", $devfam);
      if ($line =~ /, *DEV\_$devfam\_/) {
        print $line;
      }
    }
  }
}
