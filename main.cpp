#include <fstream>
#include <cstdlib>
#include <iostream>
#include "myfns.h"

using namespace std;

int main(int args, char* argv[]) {

    string codons = argv[2]; //Reading in arguments from the command line
    string genetest = argv[3];
    int alphabet_num = atoi(argv[1]); //Char to int

    ifstream inData1, inData2;
    string rules, data, x, y;

    inData1.open(codons); //open files
    if(!inData1){
        cerr<<"Error Opening File"<<endl; //standard errs if file doesnt open
        return -1;
    }

    inData2.open(genetest);

    if(!inData2){
        cerr<<"Error Opening File"<<endl;
        return -1;
    }

    while(inData1 >> x){ //add to rules string
        rules += x;
        rules += " ";
    }
    while(inData2 >> y){ //add to data string
        data += y;
    }

    inData1.close(); inData2.close();

    if(alphabet_num == 3) { //if the cmd line arg is 3, use the 3 letter alphabet class
        Alphabet3 alpha3(rules, data);
        alpha3.setRules();
        alpha3.displayResults();
    }
    else if(alphabet_num == 4){ //the inverse of above
        Alphabet4 alpha4(rules, data);
        alpha4.setRules();
        alpha4.displayResults();
    }

    return 0;
}

