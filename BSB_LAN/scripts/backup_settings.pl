#!/usr/bin/perl

# This script retrieves all settings from the heater (optionally limted to a
# range limited by the first two command line arguments) and stores them in a
# CSV-style file.
# All you need to do is adjust the URL of BSB-LAN in the line below (including
# any potential credentials/passcode). Do NOT end the URL with a slash!

my $URL = "http://192.168.1.50/4444";

my $from = $ARGV[0];
my $to = $ARGV[1];
if ($from le " " ) {
  $from = 0;
}
if ($to le " " ) {
  $to = 9999;
}

print "Creating backup for parameters $from to $to, this may take several minutes...\n";
my $date = `date "+%Y%m%d"`;
chomp ($date);

open (OUT, ">backup_settings-$from-$to-$date.csv");
open (WGET, "wget -q -O - $URL/$from-$to|");
while (my $line=<WGET>) {
  if ($line =~ /^\s*(\d+)\s+.*: (.*)/) {
    my $param_no = $1;
    my $param_val = $2;
    if ($param_val =~ /error/) {
      next;
    }
    print "$param_no;$param_val\n";
    print OUT "$param_no;$param_val\n";
  }
}
