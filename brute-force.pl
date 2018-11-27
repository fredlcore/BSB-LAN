#!/usr/bin/perl
use strict;

# This script calls BSB-LAN and queries all possible cominations within one
# major command area (defined in the fist byte of $baseID. The second byte
# seems to be static or irrelevant and is mostly used as 3D which is why it is
# hardcoded here.
# To query other major command areas, change the 0x05... in $baseID to 
# 0x2D (HK1), 0x31 (TWW) or others and report the results back to us.
# 
# Log output will be (overwritten) into brute-force-log.txt
# Please note that BSB_lan_defs.h has to be in the same folder as this script.
#
# Set $URL to point to your BSB-LAN installation, including an active passkey.

my $URL = "http://192.168.1.50/4444";
my $baseID = 0x053D0000;

my $counter = 0;
my $ID = 0;
my ($match, $answer);
my $retries = 0;

local $/ = undef;
open DEFS, "BSB_lan_defs.h";
my $defs = <DEFS>;
close DEFS;

open LOG, ">./brute-force-log.txt";

for ($counter; $counter < 65536; $counter++) {
  $retries = 0;
  $answer = "";
  $ID = sprintf("%08X", $baseID + $counter);
  if ($defs !~ /$ID/) {
    while ($answer le " " && $retries < 3) {
      print "$ID\n";
      $answer = `wget -q -O - $URL/Y06,0x$ID | grep "DC 80 0."`;
      if ($answer !~ /DC 80 0. 0C 08/ && $answer gt " ") {
        print LOG "$ID\n";
        print LOG $answer . "\n";
        print "$answer" . "\n";
      }
      sleep 0.25;
      $retries++;
      if ($retries > 1) {
        print "Retrying...\n";
      }
    }
  }
}
close LOG;
