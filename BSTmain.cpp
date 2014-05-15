#include "BinNode.h"
#include "BST.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

// Done by Emily
int main(int argc, char * argv []) {

	//struct timeval start, finish;
	//int REPS = 3;
	string iptree = "iptree-small.txt";
	string ddos = "ddos-small.txt";
	string address;
	ifstream inFile1;
	ifstream inFile2;
	ofstream badFile;
	ofstream goodFile;
	int goodTotal = 0;
	int badTotal = 0;
	string number;
	int num;
	int position;
	istringstream ss;

	badFile.open("bad.txt");
	goodFile.open("good.txt");

/**
	cout << "First file name: " << endl;
	cin >> fileName1;
	cout << "Second file name: " << endl;
	cin >> fileName2;
	cout << "Which node to walk to?" << endl;
	cin >> ithNode; */

	BST* myBST1 = new BST();
	BST* myBST2 = new BST();

	//gettimeofday(&start, NULL);

	//for(int i = 0; i < REPS; i++) {

	// opens the 2 input files
	inFile1.open("iptree-small.txt"); // this is iptree.txt
	//inFile1.open(iptree.c_str()); // this is iptree.txt
	//inFile2.open(ddos.c_str()); // this is ddos.txt
	inFile2.open("ddos-small.txt"); // this is ddos.txt

	// while there was no problem opening iptree.txt
	cout << "!" << endl;
	if(!(inFile1.fail())){
		cout << "4" << endl;

		while(!inFile1.eof()){
			cout << "!" << endl;

			// get each line/ip address in file
			while(getline(inFile1, address)){
				// insert into the first BST
				myBST1->insertNode(address);
			}
		}
	}
	inFile1.close();


	// while there was no problem opening ddos.txt
	if(!(inFile2.fail())){

		while(!inFile2.eof()){

			// get each line/ip address in file
			while(getline(inFile2, address)){
				// search iptree BST to find address
				cout << "hi" << endl;
				bool isBadAddress = myBST1->searchBST(address, myBST1->getRoot());
				cout << "hi2" << endl;
				cout << isBadAddress << endl;
				string address2 = address;

				if (isBadAddress == true) {


					while(position = address2.find(".")){
						string myString = address2.substr(0, position);
						//ss(myString);
						//ss >> num;
						num = atoi(myString)
						//istringstream (myString) >> num;
						badTotal += num;
						address2 = address2.substr(position+1);
						if(address2.find(".") == string::npos){
							//ss(myString);
						//	istringstream (myString) >> num;
							//ss >> num;
							badTotal += num;
							break;
						}
					}
					//write address to bad file
					badFile << address << endl;
					
				} else if (isBadAddress == false) {

					while(position = address2.find(".")){
						string myString = address2.substr(0, position);
						//ss(myString);
						//ss >> num;
						//istringstream (myString) >> num;
						goodTotal += num;
						address2 = address2.substr(position+1);
						if(address2.find(".") == string::npos){
							//ss(myString);
						//	istringstream (myString) >> num;
							goodTotal += num;
						}
					//write address to good file
					goodFile << address << endl;


					}
					
				}
			}
		}
	}
	inFile2.close();

	cout << "The good-sum value is " << goodTotal << "." << endl;
	cout << "The bad-sum value is " << badTotal << "." << endl;

	//gettimeofday(&finish, NULL);
   // double totalTime = 
	//(double)((double)(finish.tv_sec - start.tv_sec) * 1000000 + 
	//	 (double)(finish.tv_usec - start.tv_usec)) / 
	//(double)REPS;
    //cout << "Total time: " << totalTime << " microseconds" << endl; 

	badFile.close();
	goodFile.close();

	delete myBST1;
	delete myBST2;

}

