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
#include <utility>

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(Voting, read) {
	std::istringstream r("0\n");
	vector<string, int> candidates;
	int count = 0;
	Vote votes[1000];
	count = Voting_read(r, candidates, votes);
    ASSERT_EQ(0, count);
	ASSERT_EQ(0, names.size);
	ASSERT_EQ()}

TEST(Voting, read2) {
    ASSERT_EQ();}

TEST(Voting, read3) {
    ASSERT_EQ();}


// ----
// eval
// ----

TEST(Voting, eval) {
	}
