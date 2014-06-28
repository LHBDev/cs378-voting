#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <ctime>
#include <cstdlib>


//number of elections to generate
#define num_tests 5

//if you want to use a set number of candidates with a set number of ballots,
//use the below values. 
#define num_candidates 9
#define num_ballots 300
// 0 to random values, 1 to use above values
#define set_num 1

//voila, now just compile and run that shit.
//make sure to pipe it to RunVoting.in!

using namespace std;


string  first_name[] = { 
	"Jowana", "Leave it to", "Nevergonna Give", "Systematic", "Loyal",
	"Mature", "Kit", "Blackand", "Linkin", "Yellow", 
	"Dizzy", "The", "Pu", "Karma", 
	"Trophy", "Jack", "Thirsty", "Blind", "Maggie",
	"Weird", "Tripping", "Acid", "Smoking", "Jointing", 
	"Vibing", "Rolling", "I", "Just", "Wanna",
	"Party", "Mama", "There's", "No", "Need",
	"For", "A", "Drama", "Mexicanos", "Al", "Grito",
	"De", "Guerra", "El Acero", "Aprestad Y", "El Bridon",
	"Y Retiemble", "En Sus", "Centros", "La Tierra", "Al", "Sonoro",
	"Rugir", "Del Canon", "Un", "Soldado", "En Cada",
	"Hijo", "De Dios", "Uuuuuun", "Soldado En", "Cada",
	"Hijo De", "Dios", "Cthuulu", "Mystogan", "Y Volver Volver", "Volver",
	"Y Hechenle", "Mis", "Rieleros", "Aha",
};

string last_name[] = {
	"Man", "Beaver", "YouUp", "Shutdown", "SSH", "Pointer",
	"Kat", "Yellow", "Park", "Submarine", "Rooster", "Library",
	"Re", "Lounge", "Room", "A-lope", "Nickel", "Pig",
	"Mae's", "A", "B", "C", "D", "E",
	"F", "G", "H", "I", "J", "K",
	"LMNOP", "Q", "R", "S", "T", "U", //
	"V", "W", "X", "Y", "And", "Z", 
	"Now", "I", "Know", "My", "ABC's", "Next",
	"Time", "Wont", "You", "Sing", "With",
	"Me", "Cuz", "I'm", "Down", "With", "the",
	"Sickness", "And", "I'm", "Breaking", "The ", "Habit", 
	"Turn", "Down", "For", "What", "Dubstepper", 
	"I", "Love", "It"
};


int main() {
	int i, j, c, b, t, x, a;

	//seed the randomizer for funniest test cases
	srand((unsigned)time(0)); 

	cout << num_tests << endl << endl;
	for (i = 0; i < num_tests; i++) {
		//generate number of candidates
		c = (set_num ? num_candidates : rand()%19+1);
		cout << c << endl;

		//generate their names
		vector<string> names;
		vector<int> votes;
		vector<int> votest;
		for (j = 0; j < c; j++) {
			names.push_back(first_name[rand()%71] + " " + last_name[rand()%73]);
			cout << names.back() << endl;
			votes.push_back(j+1);
		}
		//generate a random number of ballots
		b = (set_num ? num_ballots : rand()%999+1);
		//b = num_ballots;
		votest = votes;
		for (j = 0; j < b; j++) {
			for (a = 0; a < c; a++) {
				x = rand()%(c-a);
				t = votes.at(x);
				cout << t << " ";
				votes.erase(votes.begin()+x);
			}
			votes = votest;
			cout << endl;
		}

		cout << endl;
	}

}
