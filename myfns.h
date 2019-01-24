#include <map>

using namespace std;

template <typename keyType, typename valueType>  // template container class that uses a key value pairing of undecided types
class keyValueMultimap{
public:
    multimap<keyType, valueType> mm; //multimap allows for there to be multiple values for every key
    keyValueMultimap() = default;
    void reportLength(string); // gets the length of total elements as well as total codons
    void displayContainer(string); // displays the entire chain, new line after 60 elements, must be divisible by 3
    void distributionCount(string, int); // reports on how many of each character exists
    void calculateChain(string); // main calculation function, see myfns.cpp for more detail
};

class Alphabet3 {
private:
    keyValueMultimap<string, string> map; // first instance of the container class with two strings
    string rules;
    string data;
public:
    Alphabet3(string &mapping, string &chain) : rules(mapping), data(chain) {}
    void setRules(); // set the mapping between codons and their respective amino acids
    void permutations(); // checks to see if all permutations have been covered, if not a warning is issued
    void displayResults(); // runs all the functionality from the container
};


class Alphabet4 { // shares the same functionality as Alphabet3 but with different rules set and permutaions
private:
    string rules;
    string data;
    keyValueMultimap<string, string> map;
public:
    Alphabet4(string &mapping, string &chain) : rules(mapping), data(chain) {}
    void setRules();
    void permutations();
    void displayResults();
};
