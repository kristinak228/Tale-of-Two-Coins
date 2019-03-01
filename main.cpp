/*
Kristina R Kolibab
Professor Tamon
Algorithms - Assignment 2
Oct. 30th 2018

Compile: g++ Main.cpp -std=c++11
Execute: ./a.out

Files: chain.txt, emit.txt, obs.txt, out.txt
The names are not hard coded, but the order of the files is

For my output file, the 0's represent state X, the 1's represent state Y
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using std::endl;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cerr;
using std::vector;
using std::sqrt;

// Used for testing my program 
void printTT(vector<vector<float>> tt){
	cout << "Testing...\n";
	for(int i = 0; i < tt.size(); i++){
		for(int j = 0; j < tt[i].size(); j++) 
			cout << tt[i][j] << ' ';
		cout << endl;
	}
}

// Util function used in findSequence function 
vector<float> getColumn(vector<vector<float>> tt, int cc){
	vector<float> col;
	for(int i = 0; i < tt.size(); i++) col.push_back(tt[i][cc]);
	return col;
}

// tt is transition table, heads is prob of heads for each coin, seq is observed sequence, n is num of coins
vector<int> findSequence(vector<vector<float>> tt, float heads[], vector<int> seq, int &n){

	// Data to be used
	double maxProb = 1.0;
	int cc = 0; // current coin/state
	vector<float> col; // column of current coin
	vector<int> stateSeq; // will hold the final sequence with max prob
	stateSeq.push_back(0); // start at state 1

	// Calculate first value at start state
	vector<int>::iterator it = seq.begin();
	if(*it) maxProb *= 1*heads[0];
	else maxProb *= 1*(1-heads[0]);
	it++;

	// step through observable sequence
	while(it != seq.end()){
		col = getColumn(tt, cc);			
		float finalMaxProb = 0.0;
		float tempProb = 0.0;
		vector<float>::iterator i = col.begin();
		int headsTracker = 0;
		while(i != col.end()){
			if(*it){ // 1 if Heads
				tempProb = (*i)*heads[headsTracker]; 		
			} else { // 0 if Tails
				tempProb = (*i)*(1-heads[headsTracker]);
			}
			// find the move that offers the max prob
			if(tempProb > finalMaxProb){
				cc = headsTracker;
				finalMaxProb = tempProb;
			}
			headsTracker++;
			i++;
		}
		maxProb *= finalMaxProb;
		stateSeq.push_back(cc);
		it++;
	}
	return stateSeq;
}

// Driver Code
int main(){
	// read in prob. transition matrix file
	cout << "Name of probability transition matrix file: ";
	string ptmFile;
	getline(cin, ptmFile);

	ifstream ptm(ptmFile);
	if(!ptm){
		cerr << "Could not open file\n";
		exit(1);
	}

	// create table of transition probabilities
	vector<float> stateProb;
	float prob;
	while(ptm >> prob) stateProb.push_back(prob);

	// calculate n*n table size
	int tSize = sqrt(stateProb.size());
	vector<vector<float>> tt;
	vector<float>::iterator it = stateProb.begin();

	// hold values in 2d vector instead of array
	for(int i = 0; i < tSize; i++){
		tt.push_back(vector<float>());
		for(int j = 0; j < tSize; j++){
			tt[i].push_back(*it);
			it++;
		}
	}

	// read in bias of showing heads file
	cout << "Name of heads probability file: ";
	string htpFile;
	getline(cin, htpFile);

	ifstream htp(htpFile);
	if(!htp){
		cerr << "Could not open file\n";
		exit(1);
	}
	
	float headBias[tSize];
	float bias;
	int i = 0;
	while(htp >> bias){
		headBias[i] = bias;
		i++;
	}

/* 	T E S T I N G
	cout << "Printing the biases for flipping a heads:\n";
	for(int i = 0; i < tSize; i++) cout << headBias[i] << ' ';
	cout << endl;
*/	

	// read in outcome sequence
	cout << "Name of output sequence file: ";
	string osFile;
	getline(cin, osFile);
	
	ifstream os(osFile);
	if(!os){
		cerr << "Could not open file\n";
		exit(1);
	}

	vector<int> observedSeq;
	int seq;
	while(os >> seq) observedSeq.push_back(seq);

/*  T E S T I N G
	cout << "Printing the observed sequence:\n";
	for(int i : observedSeq) cout << i << ' ';
	cout << endl;
*/

	// ask user for name of output file
	cout << "Name of output file: ";
	string outputFile;
	getline(cin, outputFile);

	ofstream out(outputFile);
	if(!out){
		cerr << "Could not open output file\n";
		exit(1);
	}

	// All my work in 4 lines
	vector<int> sequence;
	sequence = findSequence(tt, headBias, observedSeq, tSize);
	for(int x : sequence) out << x << ' ';	
	out.close();

	return 0;
}
