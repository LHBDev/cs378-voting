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

class Vote{
	public:
		deque<int> ballot;
		Vote(const Vote &);
		Vote(){};
};


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
