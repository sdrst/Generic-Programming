#include <iostream>
#include "myfns.h"

using namespace std;

template <typename keyType, typename valueType> // key value pair (string, string)
void keyValueMultimap<keyType,valueType>::reportLength(string letters) {
    int count = 0;
    for(auto &i: letters){
        count++;
    }
    if(count%3 != 0){
        cout<<"\nBad Chain, Aborting!"; // validates that the chain is divisible by 3, and exits if not
        exit(1);
    }
    else{
        cout<<"\nContains "<<count<<" elements, or "<<count/3<<" codons."<<endl; // displays element count
    }
}

template <typename keyType, typename valueType>
void keyValueMultimap<keyType,valueType>::displayContainer(string letters) {
    string mapping = "\n";
    int count = 0;
    for(auto &i: letters){
        mapping += i;
        count++;
        if(count%60 == 0){
            mapping+="\n";
        }
    }
    cout<<mapping<<endl; // displays entire chain, with a new line separating every 60 elements
}

template <typename keyType, typename valueType>
void keyValueMultimap<keyType,valueType>::distributionCount(string letters, int alpha) {
    int Acount = 0; int Bcount = 0; int Ccount = 0; int Tcount = 0; int Gcount = 0;
    if(alpha == 3){
        for(auto &i: letters){
            if(i == 'A'){
                Acount++;
            }
            else if(i == 'B'){ // self explanatory, counts amount of characters in chain, reports
                Bcount++;
            }
            else if(i == 'C'){
                Ccount++;
            }
            else{
                cout<<"\nInvalid symbol in data file, aborting!"<<endl; // if character isnt one of those in the
                exit(1);                                                // predeclared alphabet, abort.
            }
        }
        cout<<"\nNumber of 'A' symbols: "<<Acount<<"\nNumber of 'B' symbols: "<<Bcount<<"\nNumber of 'C' symbols: "<<Ccount<<endl;
    }
    else{
        for(auto &i: letters) {
            if(i == 'A'){
                Acount++;
            }
            else if(i == 'T'){
                Tcount++;
            }
            else if(i == 'G'){ // same as above
                Gcount++;
            }
            else if(i == 'C'){
                Ccount++;
            }
            else{
                cout<<"\nInvalid symbol in data file, aborting!"<<endl;
                exit(1);
            }
        }
        cout<<"\nNumber of 'A' symbols: "<<Acount<<"\nNumber of 'T' symbols: "<<Tcount<<"\nNumber of 'C' symbols: "<<Ccount<<"\nNumber of 'G symbols: "<<Gcount<<endl;
    }

}

template <typename keyType, typename valueType>
void keyValueMultimap<keyType,valueType>::calculateChain(string letters) {
    string sequence;
    int count = 0; // 3 element count per codon
    int ignore_counter = 0; // amount of codons ignored between each active chain
    int i = 0; // position in the chain
    bool ended = true; // for testing to see if chain ended during active sequence
    int sequenceNumber = 0;
    string amino;
    string chain;
    while (i < letters.size()) {
        while (amino != "Start" && i < letters.size()) { // looking for the start and incrementing the ignore counter
            if (count < 3) {                             // until it is found
                chain += letters[i];

                if (count == 2) {
                    amino = mm.find(chain)->second; // if the characters have formed a codon, find its value within the container
                    count = 0; // restart the count
                    chain = "";
                    if(amino != "Start") {
                        ignore_counter++;
                    }
                }
                else {
                    count++;
                }
            }
            i++;
        }
        if(amino == "Start") {
            ended = false;
        }
        int codon_counter = 0; // counts codons in active sequence

        sequence += "Start";
        while (amino != "Stop" && i < letters.size()) { // looking for stop codon, codon count increases until that point
            if (count < 3) {
                chain += letters[i];

                if (count == 2) {
                    amino = mm.find(chain)->second;
                    count = 0;
                    chain = "";
                    codon_counter++;
                    sequence += "-" + amino;
                }
                else {
                    count++;
                }
            }
            i++;
        }
        if (amino == "Stop") {
            ended = true;
        }
        if(sequence.find("Stop") != string::npos) { // if the chain hasnt ended during an active sequence

            sequenceNumber++;
            cout << ignore_counter << " codons read and ignored" << endl;
            cout << "Sequence " << sequenceNumber << ": " << sequence << endl;
            cout << "Contains " << codon_counter - 1 << " amino acids" << endl; // report data
            sequence = "";
            ignore_counter = 0;
            cout<<endl;

        }
        if(!ended){
            cout<<"Reached end of data during an active sequence"<<endl;
        }
    }
}


void Alphabet3::setRules() {
    for(int i = 0; i < rules.size(); i++){
        size_t pos1 = rules.find(':'); // finding each rule
        string aa = rules.substr(0, pos1);
        rules.erase(0,pos1+2);
        size_t pos2 = 0;
        bool x = true; // x is true until the next codon mapping is found
        char comma = ',';
        while(x){
            pos2 = rules.find(' ');
            char letter = rules[pos2-1];
            if(letter == comma){
                string codon = rules.substr(0,pos2-1);
                rules.erase(0,pos2+1);
                map.mm.insert(make_pair(codon, aa)); // inserting the mapping into the container and looking for the next
            }
            else{
                string codon = rules.substr(0,pos2);
                rules.erase(0,pos2+1);
                map.mm.insert(make_pair(codon, aa)); // inserting the mapping into the container and moving on to the next aa
                x = false;
            }
        }
    }
}

void Alphabet3::permutations(){ // all possible combinations of A,B,C are 3^3 which is 27, so therefore if the
    const int perm = 27;        // the container has fewer mappings then we know not all the possibilities have been covered
    if(map.mm.size()<perm){
        cout<<"\nWARNING: Not all possible codons covered in mapping! May cause errors"<<endl;
    }
        // only displays an error rather than aborting because theoretically the program could still function properly
}       // as long as the left out codon combination(s) is not in the chain. If it is the program may have unknown behavior

void Alphabet3::displayResults(){
    map.reportLength(data); // display all the functionality of the container as well as the permutations
    permutations();
    map.distributionCount(data,3);
    map.displayContainer(data);
    map.calculateChain(data);
}



void Alphabet4::setRules() {
    for(int i = 0; i < rules.size(); i++){
        size_t pos1 = rules.find(':');
        string aa = rules.substr(0, pos1); // same functionality as Alphabet3 but with an extra character
        rules.erase(0,pos1+2);
        size_t pos2 = 0;
        bool x = true;
        char comma = ',';
        while(x){
            pos2 = rules.find(' ');
            char letter = rules[pos2-1];
            if(letter == comma){
                string codon = rules.substr(0,pos2-1);
                rules.erase(0,pos2+1);
                map.mm.insert(make_pair(codon, aa));
            }
            else{
                string codon = rules.substr(0,pos2);
                rules.erase(0,pos2+1);
                map.mm.insert(make_pair(codon, aa));
                x = false;
            }
        }
    }
}

void Alphabet4::permutations(){ // same as alpha3 but 4^3 = 64 total possibilities
    const int perm = 64;
    if(map.mm.size()<perm){
        cout<<"\nWARNING: Not all possible codons covered in mapping! May cause errors"<<endl;
    }

}
void Alphabet4::displayResults() {
    map.reportLength(data);
    permutations();
    map.distributionCount(data,4);
    map.displayContainer(data);
    map.calculateChain(data);
}

