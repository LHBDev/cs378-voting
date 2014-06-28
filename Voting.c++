// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <string>
#include <sstream>

#include "Voting.h"

using namespace std;

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

    while(!r.eof()){
        Vote v;
        string line;
        getline(r, line);
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
        Vote v(it->votes.front());
        v.ballot.pop_front();
        (*candidates)[v.ballot.front() -1].add_vote(v);
        (*candidates)[v.ballot.front() - 1].inc_votes();
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
    int i = candidates->front().get_numvotes();
    for(vector<Candidate>::iterator it = candidates->begin(); it != candidates->end();++it){
        if(it->get_numvotes() != i && it->get_numvotes() != 0)
            return false;
    }
    return true;
}

// -----------
// voting_eval
// -----------
string voting_eval (vector<Candidate>* candidates, int wins) {
    string winner;
    vector<Candidate> losers;
    int lowest = 1000;
    int highest = 0;
    int highCount=0;

    if(wins == 0)
        return winner;
    if(candidates->empty())
        return winner;

    while(winner == ""){
        highCount = 0;
        for(vector<Candidate>::iterator it = candidates->begin(); it != candidates->end();++it){
            if(it->get_numvotes() >= wins)
                winner = it->get_name();
            else if(it->get_numvotes() == wins -1){
                if(checkTie(candidates))
                    return printWinner(candidates);
            }
            else if(checkTie(candidates))
                return printWinner(candidates);
            else if(it->get_numvotes() < lowest && it->get_numvotes() != 0)
                lowest = it->get_numvotes();
            else{
                if(it->get_numvotes() > highest){
                    highest = it->get_numvotes();
                    highCount = 1;
                }
                if(it->get_numvotes() == highest)
                    ++highCount;
                if((int)candidates->size() == highCount){
                    return printWinner(candidates);
                }
            }
        }
        voting_losers(candidates, &losers, lowest);
        voting_distribute(candidates, &losers);
    }
    return winner;
}

// -------------
// collatz_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
    // while (true) {
        vector<Candidate> candidates;
        int count = Voting_read(r, &candidates);
        string winner =  voting_eval(&candidates, (count/2) + 1);
        if(winner.back() != '\n')
            winner += "\n";
        w<<winner;
}