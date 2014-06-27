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
	vector<Candidate> candidates;
	int count = 0;
	count = Voting_read(r, &candidates);
    ASSERT_EQ(0, count);
	ASSERT_EQ(0, candidates.size());
}


TEST(Voting, read_2) {
	std::istringstream r("3 \nRuben Lujan\nCristhian Escobar\nEmaly Martinez\n");
	vector<Candidate> candidates;
	int count = Voting_read(r, &candidates);
	ASSERT_EQ(0, count);
	ASSERT_EQ(3, candidates.size());
	ASSERT_EQ("Ruben Lujan", candidates[0].get_name());
	ASSERT_EQ("Cristhian Escobar", candidates[1].get_name());
	ASSERT_EQ("Emaly Martinez", candidates[2].get_name());
}

TEST(Voting, read_3) {
	std::istringstream r("3 \nRuben Lujan\nCristhian Escobar\nEmaly Martinez\n1 2 3 \n");
	vector<Candidate> candidates;
	int count = Voting_read(r, &candidates);
	ASSERT_EQ(1, count);
	ASSERT_EQ(3, candidates.size());
	ASSERT_EQ("Ruben Lujan", candidates[0].get_name());
	ASSERT_EQ("Cristhian Escobar", candidates[1].get_name());
	ASSERT_EQ("Emaly Martinez", candidates[2].get_name());
	ASSERT_EQ(1, candidates[0].get_numvotes());
}

// ----
// eval
// ----
TEST(Voting, eval){
	vector<Candidate> candidates;
	string x = voting_eval(&candidates);

	ASSERT_EQ("", x);
}

// // ----
// // eval
// // ----

// TEST(Voting, eval) {
// 	}

// ------
// solve
// ------
// TEST(Collatz, solve) {
//     std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
//     std::ostringstream w;
//     collatz_solve(r, w);
//     ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

// TEST(Collatz, solve_2) {
//     std::istringstream r("0 0\n");
//     std::ostringstream w;
//     collatz_solve(r, w);
//     ASSERT_EQ("", w.str());}

// TEST(Collatz, solve_3) {
//     std::istringstream r("1 2\n");
//     std::ostringstream w;
//     collatz_solve(r, w);
//     ASSERT_EQ("1 2 2\n", w.str());}
