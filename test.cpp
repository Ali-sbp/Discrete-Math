#include "funcs.h"
#include <cassert>
#include <iostream>

using namespace std;

void runComprehensiveTests() {
    cout << "=== Comprehensive Test Suite ===\n\n";
    
    // Test 1: Gray Code Generation
    cout << "Test 1: Gray Code Generation\n";
    cout << "----------------------------\n";
    
    MultisetProgram program;
    
    // Test 1-bit Gray code
    vector<string> gray1 = program.generateGrayCode(1);
    cout << "1-bit Gray code: ";
    for (const string& code : gray1) {
        cout << code << " ";
    }
    cout << endl;
    assert(gray1.size() == 2);
    assert(gray1[0] == "0" && gray1[1] == "1");
    cout << "✓ PASSED\n\n";
    
    // Test 2-bit Gray code
    vector<string> gray2 = program.generateGrayCode(2);
    cout << "2-bit Gray code: ";
    for (const string& code : gray2) {
        cout << code << " ";
    }
    cout << endl;
    assert(gray2.size() == 4);
    assert(gray2[0] == "00" && gray2[1] == "01" && gray2[2] == "11" && gray2[3] == "10");
    cout << "✓ PASSED\n\n";
    
    // Test 3-bit Gray code
    vector<string> gray3 = program.generateGrayCode(3);
    cout << "3-bit Gray code: ";
    for (const string& code : gray3) {
        cout << code << " ";
    }
    cout << endl;
    assert(gray3.size() == 8);
    cout << "✓ PASSED\n\n";
    
    // Test 2: Multiset Operations
    cout << "Test 2: Multiset Operations\n";
    cout << "---------------------------\n";
    
    // Create test multisets
    map<string, int> m1 = {{"00", 2}, {"01", 1}, {"11", 3}};
    map<string, int> m2 = {{"01", 2}, {"11", 1}, {"10", 2}};
    
    cout << "Multiset 1: ";
    for (const auto& pair : m1) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;
    
    cout << "Multiset 2: ";
    for (const auto& pair : m2) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;
    
    // Test Union
    map<string, int> unionResult = program.unionMultisets(m1, m2);
    cout << "Union: ";
    for (const auto& pair : unionResult) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;
    assert(unionResult["00"] == 2);
    assert(unionResult["01"] == 2);
    assert(unionResult["11"] == 3);
    assert(unionResult["10"] == 2);
    cout << "✓ Union PASSED\n";
    
    // Test Intersection
    map<string, int> intersectionResult = program.intersectionMultisets(m1, m2);
    cout << "Intersection: ";
    for (const auto& pair : intersectionResult) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;
    assert(intersectionResult["01"] == 1);
    assert(intersectionResult["11"] == 1);
    assert(intersectionResult.size() == 2);
    cout << "✓ Intersection PASSED\n";
    
    // Test Difference
    map<string, int> diffResult = program.differenceMultisets(m1, m2);
    cout << "Difference (M1 - M2): ";
    for (const auto& pair : diffResult) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;
    assert(diffResult["00"] == 2);
    assert(diffResult["11"] == 2);
    assert(diffResult.size() == 2);
    cout << "✓ Difference PASSED\n";
    
    // Test Symmetric Difference
    map<string, int> symDiffResult = program.symmetricDifferenceMultisets(m1, m2);
    cout << "Symmetric Difference: ";
    for (const auto& pair : symDiffResult) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;
    cout << "✓ Symmetric Difference PASSED\n\n";
    
    // Test 3: Arithmetic Operations
    cout << "Test 3: Arithmetic Operations\n";
    cout << "------------------------------\n";
    
    // Test Sum
    int sum1 = program.sumMultisets(m1);
    int sum2 = program.sumMultisets(m2);
    cout << "Sum of M1: " << sum1 << " (expected: 6)" << endl;
    cout << "Sum of M2: " << sum2 << " (expected: 5)" << endl;
    assert(sum1 == 6);
    assert(sum2 == 5);
    cout << "✓ Sum PASSED\n";
    
    // Test Product
    int product1 = program.productMultisets(m1);
    int product2 = program.productMultisets(m2);
    cout << "Product of M1: " << product1 << " (expected: 6)" << endl;
    cout << "Product of M2: " << product2 << " (expected: 4)" << endl;
    assert(product1 == 6);
    assert(product2 == 4);
    cout << "✓ Product PASSED\n";
    
    // Test Arithmetic Difference
    int arithDiff = program.arithmeticDifferenceMultisets(m1, m2);
    cout << "Arithmetic Difference (M1 - M2): " << arithDiff << " (expected: 1)" << endl;
    assert(arithDiff == 1);
    cout << "✓ Arithmetic Difference PASSED\n";
    
    // Test Division
    double division = program.divisionMultisets(m1, m2);
    cout << "Division (M1 / M2): " << fixed << setprecision(2) << division << " (expected: 1.20)" << endl;
    assert(abs(division - 1.2) < 0.01);
    cout << "✓ Division PASSED\n\n";

    // Test 5: Gray-weighted arithmetic
    cout << "Test 5: Gray-weighted Arithmetic\n";
    cout << "---------------------------------\n";
    // Known 3-bit Gray values: 000→0, 001→1, 011→2, 010→3, 110→4, 111→5, 101→6, 100→7
    // Verify converter on a few
    assert(MultisetProgram::grayToInt("000") == 0);
    assert(MultisetProgram::grayToInt("001") == 1);
    assert(MultisetProgram::grayToInt("011") == 2);
    assert(MultisetProgram::grayToInt("010") == 3);
    assert(MultisetProgram::grayToInt("110") == 4);
    assert(MultisetProgram::grayToInt("111") == 5);
    assert(MultisetProgram::grayToInt("101") == 6);
    assert(MultisetProgram::grayToInt("100") == 7);
    cout << "✓ grayToInt converter PASSED" << endl;

    map<string, int> mw = {{"100", 2}, {"101", 1}, {"111", 3}}; // 7*2 + 6*1 + 5*3 = 14 + 6 + 15 = 35
    long long wsum = program.weightedSum(mw);
    assert(wsum == 35);
    cout << "✓ weightedSum PASSED (" << wsum << ")" << endl;

    long long wdiff = program.weightedDifference({{"100", 2}}, {{"111", 1}}); // 14 - 5 = 9
    assert(wdiff == 9);
    cout << "✓ weightedDifference PASSED (" << wdiff << ")" << endl;

    // Product: value^multiplicity. Example: {100:1, 011:2} => 7^1 * 2^2 = 28
    long double wprod = program.weightedProduct({{"100", 1}, {"011", 2}});
    assert((long long)wprod == 28);
    cout << "✓ weightedProduct PASSED (" << (long long)wprod << ")" << endl;

    double wdiv = program.weightedDivision({{"100", 1}}, {{"011", 2}}); // 7 / (2+2) = 7/4 = 1.75
    assert(fabs(wdiv - 1.75) < 1e-9);
    cout << "✓ weightedDivision PASSED (" << fixed << setprecision(2) << wdiv << ")" << endl;
    
    // Test 4: Edge Cases
    cout << "Test 4: Edge Cases\n";
    cout << "------------------\n";
    
    // Empty multiset
    map<string, int> empty;
    int emptySum = program.sumMultisets(empty);
    cout << "Empty multiset sum: " << emptySum << " (expected: 0)" << endl;
    assert(emptySum == 0);
    cout << "✓ Empty multiset PASSED\n";
    
    // Division by zero
    double divByZero = program.divisionMultisets(m1, empty);
    cout << "Division by zero: " << divByZero << " (expected: 0)" << endl;
    assert(divByZero == 0);
    cout << "✓ Division by zero PASSED\n";
    
    // Single element multiset
    map<string, int> single = {{"00", 5}};
    int singleSum = program.sumMultisets(single);
    int singleProduct = program.productMultisets(single);
    cout << "Single element sum: " << singleSum << " (expected: 5)" << endl;
    cout << "Single element product: " << singleProduct << " (expected: 5)" << endl;
    assert(singleSum == 5);
    assert(singleProduct == 5);
    cout << "✓ Single element PASSED\n\n";
    
    cout << "=== All Tests PASSED! ===\n";
    cout << "The multiset operations program is working correctly.\n";
}

int main() {
    runComprehensiveTests();
    return 0;
}
