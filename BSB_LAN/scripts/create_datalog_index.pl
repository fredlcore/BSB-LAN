#!/usr/bin/perl -w \

##
# bsb-lan utility to re-build datalog.idx from datalog.txt,
# to be used to replace the existing datalog on a bsb-lan's SD card
# (or for ESP32 w/o SD card: from the Arduino IDE via
# Tools -> ESP32 Sketch Data Upload)

use strict;
use warnings;

die "Usage: $0 datalog.txt > datalog.idx\n"
  if @ARGV > 1 || -t STDOUT;

binmode STDOUT;
my $pos = 0;
my $prev = "";
while (<>) {
  next unless /(\d+)\.(\d+)\.(\d+)/;
  my $date = pack "CCv", $1, $2, $3;
  next if $date eq $prev;
  print $date, pack "V", $pos;
  $prev = $date;
} continue {
  $pos += length;
}

__END__
Milliseconds;Date;Parameter;Description;Value;Unit
601171;19.03.2023 20:06:27;8700;Aussentemperatur;11.2;°C
601375;19.03.2023 20:06:27;8770;Raumtemperatur-Istwert 2;20.3;°C
