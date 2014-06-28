// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

// #ifndef Voting_h
// #define Voting_h

// --------
// includes
// --------

/*
g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall UVaVoting.c++ -o UVa
*/

#include <iostream> // istream, ostream
#include <utility>  // pair
#include <vector>
#include <string>
#include <deque>
#include <cassert>  // assert
// #include <iostream> // endl, istream, ostream
// #include <utility>  // make_pair, pair
#include <string>
#include <sstream>

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

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

// #endif // Voting_h
// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------



// #include "Voting.h"

// using namespace std;

// vector<Candidate> candidates;
// ----------------
// Candidate class
// ----------------

void Candidate::set_name(string x){
    name = x;
}

string Candidate::get_name(){
    return name;
}

void Candidate::inc_votes(){
    ++numvotes;
}

int Candidate::get_numvotes(){
    return numvotes;
}

void Candidate::add_vote(Vote v){
    votes.push_back(v);
}

void Candidate::clear_vote(){
    numvotes = 0;
}

Candidate::Candidate(const Candidate &other){
    name = other.name;
    numvotes = other.numvotes;
    votes = other.votes;
}

Candidate::Candidate(string s){
    name = s;
}

Vote::Vote(const Vote &other){
    ballot = other.ballot;
}

Vote::Vote(){}


void state(vector<Candidate>*);
// ----------
// Vote class
// ----------

// void Vote::set_vote(int x){
//     *filler = x;
//     ++filler;
// }

// int* Vote::get_setter(){
//     return filler;
// }

// int* Vote::get_reader(){
//     return reader;
// }

// int Vote::move(){
//     return *++reader;
// }

// int Vote::peek(){
//     return *votes;
// }

// ------------
// collatz_read
// ------------

int Voting_read(std::istream& r, vector<Candidate>* candidates) {
    int count, runners;
    count = 0;
    r >> runners;
    if(runners == 0)
        return runners;
    r.ignore(1, '\n'); //used to move the position so we don't read in a newline character

    for(int i = runners; i > 0; --i){
        string line;
        getline(r, line);
        Candidate x(line);
        (*candidates).push_back(x);
    }

    while(r){
        if(!r)
            return count;
        string line;
        getline(r, line);
        Vote v;
        
        
        if(line == "")
            return count;

        istringstream iss(line);
        for(int i = runners; i>0; --i){
            int x;
            iss >> x;
            while(x == ' ')
                iss >> x;
            v.ballot.push_back(x);
        }
        Candidate* y = &(*candidates)[v.ballot.front() - 1];
        y->inc_votes();
        y->add_vote(v);

        ++count;
    }
    return count;
}

// -----------------
// voting_distribute
// -----------------

void voting_distribute(vector<Candidate>* candidates, vector<Candidate>* losers){
   for(vector<Candidate>::iterator it = losers->begin(); it != losers->end();++it){
        while(!(it->votes.empty())){

            Vote v(it->votes.front());
            while((*candidates)[v.ballot.front()-1].get_numvotes() == 0){
                v.ballot.pop_front();
            }
            it->votes.pop_front();
            (*candidates)[v.ballot.front() -1].add_vote(v);
            (*candidates)[v.ballot.front() - 1].inc_votes();
        }
   }
   losers->clear();
}

// -------------
// voting_losers
// -------------

void voting_losers(vector<Candidate>* candidates, vector<Candidate>* losers, int lowest){
    for(vector<Candidate>::iterator it = candidates->begin(); it != candidates->end();++it){
        if(it->get_numvotes() == lowest){
            Candidate x(*it);
            losers->push_back(x);
            it->clear_vote();
        }
    }
}

// ------------
// printWinner
// ------------
string printWinner(vector<Candidate>* candidates){
    string winners = "";
    bool checked = false;
    int count = 0;
    for(vector<Candidate>::iterator it = candidates->begin();it != candidates->end(); ++it){

        if(it->get_numvotes() != 0){
            if(checked)
                winners += "\n";
            else
                checked = !checked;

            winners += it->get_name();
            ++count;
        }
    }
    if(winners != "")
        winners += "\n";
    if(winners.back() != '\n' && winners != "")
        winners += "\n";
    return winners;
}

// --------
// checkTie
// --------
bool checkTie(vector<Candidate>* candidates){
    int j = 0;
    for(int i = 0; i < (int)candidates->size() && j == 0;++i){
        if((*candidates)[i].get_numvotes() != 0)
            j = (*candidates)[i].get_numvotes();

    }
    for(vector<Candidate>::iterator it = candidates->begin(); it != candidates->end();++it){
        if(it->get_numvotes() != j && it->get_numvotes() != 0)
            return false;
    }
    return true;
}

string printAll(vector<Candidate>* candidates){
    string all = "";
    bool checked = false;
    int count = 0;
    for(vector<Candidate>::iterator it = candidates->begin();it != candidates->end(); ++it){
 
        if(checked)
            all += "\n";
        else
            checked = !checked;

        all += it->get_name();
        ++count;

    }
    if(all != "")
        all += "\n";
    if(all.back() != '\n' && all != "")
        all += "\n";
    return all;
}

// -----------
// voting_eval
// -----------
string voting_eval (vector<Candidate>* candidates, int wins) {
    string winner;
    vector<Candidate> losers;
    int lowest = 1000;

    if(wins == 0)
        return printAll(candidates);
    if(candidates->empty())
        return winner;

    while(winner == ""){
        lowest = 1000;
        if(checkTie(candidates))
            return printWinner(candidates);
        for(vector<Candidate>::iterator it = candidates->begin(); it != candidates->end();++it){
            int i = it->get_numvotes();
            if(i >= wins){
                winner = it->get_name();
                return winner;}
            if(i == 0)
                it->votes.clear();
            else if(i<lowest && i != 0)
                lowest = i;
        }
        // cout<<"HERE"<<endl;
        voting_losers(candidates, &losers, lowest);
        voting_distribute(candidates, &losers);
        // state(candidates);
        // int i = 0;
        // int j = 0;
        // for(vector<Candidate>::iterator it = candidates->begin();it != candidates->end();++it)
        // {
        //     cout<<it->get_name()<<": "<<it->get_numvotes()<<endl;
        // }
        // cout<<i<<endl;
        // cout<<j<<endl;
    }
    return winner;
}

// -------------
// collatz_solve
// -------------

void state(vector<Candidate>* candidates)
{
    cout<<"STATE:"<<endl;
    for(vector<Candidate>::iterator it = candidates->begin(); it != candidates->end();++it)
        {
            cout<< it->get_name()<<" " << it->get_numvotes()<<endl;
            deque<Vote> v = it->votes;
            for(deque<Vote>::iterator i = v.begin(); i != v.end(); ++i)
            {
                deque<int> b = i->ballot;
                for(deque<int>::iterator x = b.begin(); x != b.end();++x)
                {
                    cout<<*x<<" ";
                }
                cout<<endl;
            }
        }
        cout<<endl;
}

void voting_solve (std::istream& r, std::ostream& w) {
    int i;
    r>>i;
    for(;i>0;--i){
        vector<Candidate> candidates;
        int count = Voting_read(r, &candidates);
        if(count == 0)
            w<<printAll(&candidates);
        else{
            string winner =  voting_eval(&candidates, (count/2) + 1);
            // cout<<"HERE"<<endl;
            if(winner.back() != '\n')
                winner += "\n";

            w<<winner;
        }
        if(i > 1)
            w<<endl;

    }
}



// --------
// includes
// --------

// #include <iostream> // cin, cout

// #include "Voting.h"

// ----
// main
// ----

int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}