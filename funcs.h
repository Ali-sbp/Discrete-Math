#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

class MultisetProgram {
private:
    int bitWidth;
    vector<string> universe;
    map<string, int> multiset1;
    map<string, int> multiset2;
    
public:
    MultisetProgram();
    
    // Gray code generation
    vector<string> generateGrayCode(int n);
    void initializeUniverse();
    void displayUniverse();
    
    // Multiset creation and display
    void createMultisetManually(map<string, int>& multiset, const string& name);
    void createMultisetAutomatically(map<string, int>& multiset, const string& name, int cardinality);
    void displayMultiset(const map<string, int>& multiset, const string& name);
    
    // Set operations
    map<string, int> unionMultisets(const map<string, int>& m1, const map<string, int>& m2);
    map<string, int> intersectionMultisets(const map<string, int>& m1, const map<string, int>& m2);
    map<string, int> differenceMultisets(const map<string, int>& m1, const map<string, int>& m2);
    map<string, int> symmetricDifferenceMultisets(const map<string, int>& m1, const map<string, int>& m2);
    map<string, int> complementMultiset(const map<string, int>& multiset);
    
    // Arithmetic operations
    int sumMultisets(const map<string, int>& multiset);
    int arithmeticDifferenceMultisets(const map<string, int>& m1, const map<string, int>& m2);
    int productMultisets(const map<string, int>& multiset);
    double divisionMultisets(const map<string, int>& m1, const map<string, int>& m2);

    // Gray-weighted arithmetic
    static int grayToInt(const string& grayBits);
    long long weightedSum(const map<string, int>& multiset) const;
    long long weightedDifference(const map<string, int>& m1, const map<string, int>& m2) const;
    long double weightedProduct(const map<string, int>& multiset) const;
    double weightedDivision(const map<string, int>& m1, const map<string, int>& m2) const;
    
    // Main program flow
    void run();
    
    // Getters for testing
    const vector<string>& getUniverse() const { return universe; }
    const map<string, int>& getMultiset1() const { return multiset1; }
    const map<string, int>& getMultiset2() const { return multiset2; }
    int getBitWidth() const { return bitWidth; }
};

// Test functions
void runTests();
void testGrayCodeGeneration();
void testMultisetOperations();
void testArithmeticOperations();

#endif // FUNCS_H
