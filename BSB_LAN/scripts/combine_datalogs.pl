#!/usr/bin/perl -w \

##
# bsb-lan utility to combine multiple /D outputs
# use with arguments [-NUM] [FILE]...
# NUM can be used to declare a minimum sample interval [s]; if given, more
# frequent parameter updates will not be included in the output.
# E.g. -590 would keep parameter updates of about every ten minutes only,
# to reduce the datalog size.

use strict;
use warnings;

my $min_sample_interval = 0;
if (@ARGV && $ARGV[0] =~ /^-(\d+)$/) {
  $min_sample_interval = $1;
  shift;
}

my %t;
my @data;
while (<>) {
  if ($. == 1) { print; next; }  # very first line is header
  next unless /(\d\d):(\d\d):(\d\d);(\d+)/;
  my $t = (($1 * 60) + $2) * 60 + $3;
  next if defined $t{$4} && $t > $t{$4} && $t - $t{$4} < $min_sample_interval;
  $t{$4} = $t;
  push @data, $_;
}
print $_->[0] foreach
  sort { $a->[1] cmp $b->[1] or $a->[0] cmp $b->[0] }
  map { [$_, f($_)] }
  @data;

sub f {
  $_[0] =~ /(\d+)\.(\d+)\.(\d+)([^;]+)/;
  return "$3-$2-$1$4";
}

__END__
Milliseconds;Date;Parameter;Description;Value;Unit
601171;19.03.2023 20:06:27;8700;Aussentemperatur;11.2;°C
601375;19.03.2023 20:06:27;8770;Raumtemperatur-Istwert 2;20.3;°C
