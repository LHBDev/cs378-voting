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
	string x = voting_eval(&candidates, 1);

	ASSERT_EQ("", x);
}

TEST(Voting, eval_2){
	vector<Candidate> candidates;
	std::istringstream r("3 \nRuben Lujan\nCristhian Escobar\nEmaly Martinez\n1 2 3 \n");
	int count = Voting_read(r, &candidates);
	string val;
	val = voting_eval(&candidates, (count/2)+1);
	ASSERT_EQ("Ruben Lujan", candidates[0].get_name());
	ASSERT_EQ("Ruben Lujan\n", val);
}

TEST(Voting, eval_3){
	string in = "3 \nRuben Lujan\nCristhian Escobar\nEmaly Martinez\n1 2 3 \n2 1 3\n1 3 2\n2 3 1\n3 1 2\n";
	std::istringstream r(in);
	vector<Candidate> candidates;
	int count = Voting_read(r, &candidates);
	string val;
	val = voting_eval(&candidates, (count/2)+1);
	ASSERT_EQ("Ruben Lujan", val);
}

// ------
// losers
// ------
TEST(Voting, losers){
	Candidate x("ruben");
	for(int i = 0; i < 4; ++i){
		x.inc_votes();
	}
	vector<Candidate> cand;
	cand.push_back(x);
	vector<Candidate> losers;
	voting_losers(&cand, &losers, 3);
	ASSERT_EQ(0, losers.size());
	ASSERT_EQ(1, cand.size());
}

TEST(Voting, losers_2){
	vector<Candidate> cand;
	vector<Candidate> loser;
	voting_losers(&cand, &loser, 0);
	ASSERT_EQ(0, loser.size());
	ASSERT_EQ(0, cand.size());
}

TEST(Voting, losers_3){
	vector<Candidate> cand;
	vector<Candidate> loser;
	Candidate x("Ruben");
	Candidate y("Edgar");
	Candidate z("Peter");
	cand.push_back(x);
	cand.push_back(y);
	cand.push_back(z);
	for(int i = 0; i < 3; ++i){
		if(!i)
			cand[i].inc_votes();
		cand[i].inc_votes();
	}
	voting_losers(&cand, &loser, 1);
	ASSERT_EQ(3, cand.size());
	ASSERT_EQ(2, loser.size());
	ASSERT_EQ("Edgar", loser.front().get_name());
	ASSERT_EQ("Peter", loser[1].get_name());
}

// -----------
// printWinner
// -----------
TEST(Voting, printWinner){

}

TEST(Voting, printWinner_2){

}

TEST(Voting, printWinner_3){

}

// --------
// checkTie
// --------
TEST(Voting, checkTie){

}

TEST(Voting, checkTie_2){

}

TEST(Voting, checkTie_3){

}

// -----------------
// voting_distribute
// -----------------
TEST(Voting, voting_distribute){

}

TEST(Voting, voting_distribute_2){
	
}

TEST(Voting, voting_distribute_3){
	
}

// ------------
// voting_solve
// ------------
TEST(Voting, solve){

}

TEST(Voting, solve_2){
	
}

TEST(Voting, solve_3){
	
}