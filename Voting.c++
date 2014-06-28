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

// ----------
// vote class
// ----------
Vote::Vote(const Vote &other){
    ballot = other.ballot;
}

Vote::Vote(){}

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
        voting_losers(candidates, &losers, lowest);
        voting_distribute(candidates, &losers);
    }
    return winner;
}

// -------------
// collatz_solve
// -------------

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
            if(winner.back() != '\n')
                winner += "\n";
            w<<winner;
        }
        if(i > 1)
            w<<endl;

    }
}