#!/usr/bin/perl
use strict;

my $baseID = 0x053D0000;
my $counter = 0;
my $ID = 0;
my ($match, $answer);
my $retries = 0;

local $/ = undef;
open DEFS, "BSB_lan_defs.h";
my $defs = <DEFS>;

for ($counter; $counter < 65536; $counter++) {
  $retries = 0;
  $answer = "";
  $ID = sprintf("%08X", $baseID + $counter);
  if ($defs !~ /$ID/) {
    while ($answer le " " && $retries < 3) {
      print STDERR "$ID\n";
      $answer = `wget -q -O - http://192.168.1.50/4444/Y06,0x$ID | grep "DC 80 0."`;
      if ($answer !~ /DC 80 0. 0C 08/ && $answer gt " ") {
        print "$ID\n";
        print $answer . "\n";
        print STDERR "$answer" . "\n";
      }
      sleep 0.25;
      $retries++;
      if ($retries > 1) {
        print STDERR "Retrying...\n";
      }
    }
  }
}
