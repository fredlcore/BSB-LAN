#!/usr/bin/perl
use strict;

# This script calls BSB-LAN and queries all possible combinations within one
# major command area (defined in the fist byte of $baseID. The second byte
# seems to be static or irrelevant and is mostly used as 3D which is why it is
# hardcoded here.
# To query other major command areas, change the 0x05... in $baseID to 
# 0x2D (HK1), 0x31 (TWW) or others and report the results back to us.
# Following major IDs are know to exist, but there may be more in rather
# special settings: 05, 06, 07, 09, 0D, 11, 15, 19, 21, 22, 25, 29, 2A, 2B, 2D,
# 2E, 2F, 31, 49, 51, 59, 65, 69
# Check in BSB_lan_defs.h first if a major group does apply to your heater
# before running tests. Some of them are specific to certain features (such
# as solar or cooling), so it won't make sense for you to test this group.
# 
# Log output will be appended to defs-brute-force-<Heater-ID>.h
# Please note that BSB_lan_defs.h has to be in the same folder as this script.
# Testing one major category will take approx. 18 hours, more if you increase
# the delay between queries via the sleep command (now at 1/4 second).

# Set $URL to point to your BSB-LAN installation, including (optional) passkey.
# Note: No trailing slash!

my $URL = "http://192.168.1.50/4444";
my $baseID = 0x05;
my $param_nr = 11000;

my $counter = 0;
my $counter_padded = 0;
my $ID = 0;
my ($match, $answer);
my $retries = 0;
$ID = $baseID * 0x1000000 + 0x3D0000;

my $COID=0;
my $len=0;
my $payload_start=0;


my $bus = `wget -q -O - $URL/JI | grep "\"bus\""`;
$bus =~ /.*: "(.*)"/;
$bus = $1;
my $orig = sprintf("%02X", $2);;
my $dest = sprintf("%02X", $3+0x80);
if ($bus ne "BSB" && $bus ne "LPB") {
  print "Brute-force querying only works on BSB and LPB.\n";
  exit;
}

my $heater = `wget -q -O - $URL/JQ=6224 | grep "value"`;
$heater =~ /.*: "(.*)"/;
$heater = $1;
$heater =~ s/\//-/g;
print "Running scan on $bus (source: 0x$orig, dest: 0x$dest) for Command ID range ";
printf("%02X", $baseID);
print " on $heater...\n";

local $/ = undef;
open DEFS, "BSB_lan_defs.h";
my $defs = <DEFS>;
close DEFS;
$/ = "\n";

open LOG, ">>./defs-brute-force-$heater.h";

for ($counter; $counter < 65536; $counter++) {
  $retries = 0;
  $answer = "";
  $ID = sprintf("%08X", $baseID * 0x1000000 + 0x3D0000 + $counter);
  $counter_padded = sprintf("%04X", $counter);
  if ($defs !~ /$baseID..$counter_padded/) {
    while ($answer le " " && $retries < 3) {
      print "$ID\n";
      if ($bus eq "BSB") {
        $answer = `wget -q -O - $URL/Y06,0x$ID | grep "DC $dest $orig"`;
      } else {
        $answer = `wget -q -O - $URL/Y06,0x$ID | grep "0C 02 00 14"`;
      }
      if ((($bus eq "BSB" && $answer !~ /DC $dest $orig 0C 08/ && $answer !~ /DC 8. 0A/) || ($bus eq "LPB" && $answer =~ /02 00 14 .7/)) && $answer gt " ") {

        my @msg = split(" ", $answer);
        if ($bus eq "BSB") {
          $len = hex($msg[3]) - 11;;
          $COID = "$msg[5]$msg[6]$msg[7]$msg[8]";
          $payload_start = 9;
        } else {
          $len = hex($msg[1]) - 14;
          $COID = "$msg[9]$msg[10]$msg[11]$msg[12]";
          $payload_start = 13;
        }

        my $payload = "";
        my $x = 0;
        for ($x=$payload_start;$x<$payload_start+$len;$x++) {
          $payload .= " " . $msg[$x];
        }

        my $val = "";
        my $temp = 0;
        if ($len < 5) {
          for ($x=$payload_start+1;$x<$payload_start+$len;$x++) {
            $val .= $msg[$x];
          }
          $val = hex($val);
          $temp = $val / 64;
        }

        print LOG "{0x$ID,  CAT_USER_DEFINED,     VT_UNKNOWN,       $param_nr, STR10200, 0,                    NULL,         FL_RONLY, DEV_ALL}, // Brute force detected Command ID via $bus, data payload on $heater:$payload (decimal: $val; temp: $temp)\n";

        print $answer . "\n";
        $param_nr++;
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
