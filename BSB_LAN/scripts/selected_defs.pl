#!/usr/bin/perl

# This script filters BSB_LAN_defs.h and removes all device family/variant
# specific lines which are not matching the device family specified as 
# an argument to this script and outputs it to standard output.
#
# ./selected_defs.pl 162 165 > BSB_LAN_defs_filtered.h
# would therefore output the whole definition file to BSB_LAN_defs_filtered.h
# except all device family/variant specific lines, unless they are for 
# device families 162 and 165.
#
# The original BSB_LAN_defs.h file can then be backed up and the newly
# generated file can be renamed to BSB_LAN_defs.h
# This will save between 10-20kB of flash memory which may be especially
# useful for Arduino Mega2560 users with tighter memory constraints.

open (DEFS, "../BSB_LAN_defs.h") || die "BSB_LAN_defs.h not found in parent directory!\n";
while ($line = <DEFS>) {
  $line_printed = 0;
  if ($line !~ /, *DEV\_\d\d\d\_/) {
    print $line;
  } else {
    foreach $devfam (@ARGV) {
      $devfam = sprintf("%03d", $devfam);
      if ($line =~ /, *DEV\_$devfam\_/) {
        print $line;
        $line_printed = 1;
      }
    }
    if ($line_printed == 0) {
      $lines_removed = $lines_removed + 1;
      $bytes_saved = $bytes_saved + 17;
    }
  }
}
$bytes_saved = $bytes_saved / 1000;
print "// $lines_removed lines have been removed, saving approx. $bytes_saved kB.\n";
