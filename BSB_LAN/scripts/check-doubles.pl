#!/usr/bin/perl

# This script tests whether the data payload of command ids in related fields 
# are similar and thus point to the same paraameter.
# For example 0x2D3D0574 and 0x2E3D0574 are heating mode in heat circuit 1 and 2
# respectively.
# Define baseID1 and baseID2 before running this script. Results will be 
# appended to doubles.txt

use strict;

my $URL = "http://192.168.1.50/4444";
my $baseID1 = "2D3D";
my $baseID2 = "2F3D";

my $counter = 0;
my ($match, $answer, $answer2, $line, $ID1, $ID2);
my $retries = 0;

open DEFS, "BSB_lan_defs.h";
open LOG, ">>./doubles.txt";

while ($line = <DEFS>) {
  if ($line =~ /0x$baseID2(....).*STR10200/) {
    $ID1 = $baseID1 . $1;
    $ID2 = $baseID2 . $1;

    $retries = 0;
    $answer = "";
    while ($answer le " " && $retries < 3) {
      print "$ID2\n";
      $answer = `wget -q -O - $URL/Y06,0x$ID2 | grep "DC 80 0."`;
      if ($answer !~ /DC 80 0. 0C 08/ && $answer !~ /DC 80 0A/ && $answer gt " ") {
#        print LOG $answer . "\n";
#        print "$answer" . "\n";
      }
      sleep 0.25;
      $retries++;
      if ($retries > 1) {
        print "Retrying...\n";
      }
    }

    $retries = 0;
    $answer2 = "";
    while ($answer2 le " " && $retries < 3) {
      print "$ID1\n";
      $answer2 = `wget -q -O - $URL/Y06,0x$ID1 | grep "DC 80 0."`;
      if ($answer2 !~ /DC 80 0. 0C 08/ && $answer2 !~ /DC 80 0A/ && $answer2 gt " ") {
#        print LOG $answer2 . "\n";
#        print "$answer2" . "\n";
        my $payload1 = substr($answer, 27, -9);
        my $payload2 = substr($answer2, 27, -9);
        if ($payload1 eq $payload2) {
          print "0x$ID2 and 0x$ID1 have same payload: $payload1\n";
          print LOG "0x$ID2 and 0x$ID1 have same payload: $payload1\n";
        }
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
close DEFS;
