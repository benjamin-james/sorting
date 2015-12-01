#!/usr/bin/perl

use strict;
use warnings;

sub avg {
    my $sum = 0;
    my $n = 0;
    foreach (@_) {
	$sum += $_;
	$n++;
    }
    return $sum/$n;
}

sub main {
    my $die_str = "Usage: $0 [sort type] [number of elements] [number of times]\n";
    my $sort = shift @_;
    die "$die_str" unless defined($sort);
    my $number = shift @_;
    die "$die_str" unless defined($number);
    my $times = shift @_;
    die "$die_str" unless defined($times);
    my @list;
    for (my $i = 0; $i < $times; $i++) {
	push(@list, `gen $number | sorting -qts $sort | sed 's/time:\t//'`)
    }
    my $average = avg(@list);
    print $average, "\n";
    return 0;
}

main @ARGV
