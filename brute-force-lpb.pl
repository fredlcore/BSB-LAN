#!/usr/bin/perl
use strict;

# This script calls BSB-LAN and queries all possible combinations within one
# major command area (defined in the fist byte of $baseID. The second byte
# seems to be static or irrelevant and is mostly used as 3D which is why it is
# hardcoded here.
# To query other major command areas, change the 0x05... in $baseID to 
# 0x2D (HK1), 0x31 (TWW) or others and report the results back to us.
# Following major IDs exit: 05, 06, 07, 09, 0D, 11, 15, 19, 21, 22, 25, 29, 
# 2A, 2B, 2D, 2E, 2F, 31, 49, 51, 59, 65, 69
# Check in BSB_lan_defs.h first if a major group does apply to your heater
# before running tests. Some of them are specific to certain features (such
# as solar or cooling), so it won't make sense for you to test this group.
# 
# Log output will be appended to brute-force-log.txt
# Please note that BSB_lan_defs.h has to be in the same folder as this script.
# Testing one major category will take approx. 18 hours, more if you increase
# the delay between queries via the sleep command (now at 1/4 second).

# Set $URL to point to your BSB-LAN installation, including (optional) passkey.
# Note: No trailing slash!

my $URL = "http://192.168.1.50/4444";
my $baseID = 0x2D;

my $counter = 0;
my $ID = 0;
my ($match, $answer);
my $retries = 0;
$baseID = $baseID * 0x1000000 + 0x3D0000;

local $/ = undef;
open DEFS, "BSB_lan_defs.h";
my $defs = <DEFS>;
close DEFS;

open LOG, ">>./brute-force-log.txt";

for ($counter; $counter < 65536; $counter++) {
  $retries = 0;
  $answer = "";
  $ID = sprintf("%08X", $baseID + $counter);
  if ($defs !~ /$ID/) {
    while ($answer le " " && $retries < 3) {
      print "$ID\n";
      $answer = `wget -q -O - $URL/Y06,0x$ID | grep "0C 02 00 14"`;
      if ($answer gt " " && $answer =~ /02 00 14 .7/) {
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
