#! /usr/bin/env perl

use strict;
use POSIX;
use Test;

require "test-common.pl";

my $type = 0;
if(@ARGV == 1)
{
    $type = 1;
}

my @tests;
my @todo;
my $test_exec="./framework_test";

my $inline_finish;
my $buffer_size=2048;
my $test_name="framework";

# setup different chunk sizes
my @chunk_sizes;
push(@chunk_sizes, "1024");
push(@chunk_sizes, "1924");
push(@chunk_sizes, "2048");

#setup different driver combinations
my @drivers;
push(@drivers, "");
push(@drivers, "-D debug");
push(@drivers, "-D bounce");
push(@drivers, "-D debug -D bounce");
push(@drivers, "-D null -D null");
push(@drivers, "-D bounce -D debug");
push(@drivers, "-D null -D bounce -D debug");
push(@drivers, "-D bounce -D null_pass -D bounce");

sub basic_tests
{
    my $inline_finish="-i";
    my $delay="";

    for(my $i = 0; $i < 2; $i++)
    {
        foreach(@drivers)
        {
            my $d=$_;
            foreach(@chunk_sizes)
            {
                my $c = $_;
                push(@tests, "$test_name -w 1 -r 0 -c $c -b $buffer_size $inline_finish $d $delay");
                push(@tests, "$test_name -w 0 -r 1 -c $c -b $buffer_size $inline_finish $d $delay");
                push(@tests, "$test_name -w 0 -r 0 -c $c -b $buffer_size $inline_finish $d $delay");
                for(my $write_count = 1; $write_count <= 16; $write_count *= 4)
                {
                    for(my $read_count = 1; $read_count <= 16; $read_count *= 4)
                    {
                        push(@tests, "$test_name -w $write_count -r $read_count -c $c -b $buffer_size $inline_finish $d $delay");
                    }
                }
            }
        }
        $inline_finish="";
    }
}

&basic_tests();

if($type == 1)
{
    foreach(@tests)
    {
        print "$_\n";
    }
}
else
{
    my $cnt=0;
    plan tests => scalar(@tests), todo => \@todo;
    foreach(@tests)
    {
        my $test_str="$test_name.$cnt";
        &run_test("$test_exec $_", $test_str);
        $cnt++;
    }
}
