// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <utility>  // pair
#include <vector>
#include <string>
#include <deque>

using namespace std;

// ---------
// Vote class
// ---------
/*
 *class for each ballot
 * @member ballot, deque that holds all the info on the ballot
 * @member Vote(const Vote &), copy constructor
 * @member Vote(), default constructor
 */
class Vote{
	public:
		deque<int> ballot;
		Vote(const Vote &);
		Vote();
};

// ---------------
// Candidate class
// ---------------
/**
 * class that holds all the information for each candidate
 * @member private name, string of candidate's name
 * @member private numvotes, number of votes for candidate
 * @member public votes, deque holding all votes for candidate
 * @member set_name(string)
 * @member get_name()
 * @member inc_votes() increments vote for candidate by 1
 * @member clear_vote() sets votes for candidate to 0
 * @member get_numvotes() returns number of votes for candidate
 * @member add_vote() add vote to votes
 * @member Candidate(const Candidate &) copy constructor
 * @member Candidate(string) creates candidate with name string
 */
class Candidate{
		string name;
		int numvotes = 0;
		
	public:
		deque<Vote> votes;
		void set_name(string);
		string get_name();
		void inc_votes();
		void clear_vote();
		int get_numvotes();
		void add_vote(Vote);
		Candidate(const Candidate &);
		Candidate(string);
};

// ------------
// printWinner
// ------------
/**
 *create the string of winners' names
 *@param candidates a vector pointer to all the candidates
 *@return string of formatted names of winners
 */
string printWinner(vector<Candidate>*);

//---------
// checkTie
//---------
/**
 * check if there is a tie in the election
 * @param candidates a vector pointer to all the candidates
 * @return bool, true if there is a tie, false otherwise
 */
bool checkTie(vector<Candidate>*);

// ------------
// voting_read
// ------------

/**
 * read in all candidates and ballots
 * @param  r a  std::istream
 * @param candidates vector to hold all the candidates of the election
 * @return a pair of the two ints, otherwise a pair of zeros
 */
int Voting_read (std::istream&, vector<Candidate>*);

// -----------------
// voting_distribute
// -----------------

/**
 * Distribute the loser's votes to the other candidates
 * @param candidates a vector pointer to all the candidates
 * @param losers a vector pointer to all the losers from the current iteration
 */
void voting_distribute(vector<Candidate>*, vector<Candidate>*);


// -------------
// voting_losers
// -------------

/**
 *filter out the losers from eligible candidates
 * @param candidates vector of eligible candidates
 * @param losers vector to hold the losers filtered out
 * @param lowest number of votes the losers have
 */
void voting_losers(vector<Candidate>*, vector<Candidate>* , int );


// ------------
// voting_eval
// ------------

/**
 * determine the election winner
 * @param candidates vector of all the eligible candidates
 * @param wins votes needed to be declared winner
 * @return name of the winner(s)
 */
string voting_eval (vector<Candidate>*, int);

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void voting_solve (std::istream&, std::ostream&);

#endif // Voting_h
