/*

To compile the test:
	% g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread

To run the test:
	% valgrind TestVoting

To obtain coverage of the test:
	%gcov-4.7 -b Voting.c++ TestVoting.c++
*/

//--------
//includes
//--------

#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Collatz.h"

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read) {
    ASSERT_EQ();}

TEST(Voting, read2) {
    ASSERT_EQ();}

TEST(Voting, read3) {
    ASSERT_EQ();}


// ----
// eval
// ----

TEST(Voting, eval) {
	}
