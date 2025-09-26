#include "funcs.h"
#include <cassert>

MultisetProgram::MultisetProgram() : bitWidth(0) {}

// Generate binary Gray code
vector<string> MultisetProgram::generateGrayCode(int n) {
    if (n <= 0) return {""};
    if (n == 1) return {"0", "1"};
    
    vector<string> prev = generateGrayCode(n - 1);
    vector<string> result;
    
    // Add 0 prefix to previous codes
    for (const string& code : prev) {
        result.push_back("0" + code);
    }
    
    // Add 1 prefix to reversed previous codes
    for (int i = prev.size() - 1; i >= 0; i--) {
        result.push_back("1" + prev[i]);
    }
    
    return result;
}

// Initialize universe with Gray codes and cardinality
void MultisetProgram::initializeUniverse() {
    universe = generateGrayCode(bitWidth);
    universeCardinality.clear();
    
    // Ask for maximum cardinality for the universe
    int maxUniverseCardinality;
    cout << "Enter maximum cardinality for universe elements (1-10): ";
    while (!(cin >> maxUniverseCardinality) || maxUniverseCardinality < 1 || maxUniverseCardinality > 10) {
        cout << "Invalid input! Enter a number between 1 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Assign random cardinality (1 to maxUniverseCardinality) to each universe element
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> cardinalityDist(1, maxUniverseCardinality);
    
    for (const string& element : universe) {
        universeCardinality[element] = cardinalityDist(g);
    }
}

// Display universe
void MultisetProgram::displayUniverse() {
    cout << "\nUniverse (Gray codes with max cardinality):\n";
    for (size_t i = 0; i < universe.size(); i++) {
        cout << i + 1 << ". " << universe[i] << " (" << universeCardinality[universe[i]] << ")" << endl;
    }
}

// Manual multiset creation
void MultisetProgram::createMultisetManually(map<string, int>& multiset, const string& name) {
    cout << "\nCreating " << name << " manually:\n";
    multiset.clear();
    
    // First, set cardinality for each universe element
    cout << "First, set the maximum cardinality for each universe element:\n";
    for (size_t i = 0; i < universe.size(); i++) {
        int cardinality;
        cout << "Enter max cardinality for " << universe[i] << " (1-10): ";
        while (!(cin >> cardinality) || cardinality < 1 || cardinality > 10) {
            cout << "Invalid input! Enter a number between 1 and 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        universeCardinality[universe[i]] = cardinality;
    }
    
    // Then, set multiplicity for each element
    cout << "\nNow, set the multiplicity for each universe element:\n";
    for (size_t i = 0; i < universe.size(); i++) {
        int multiplicity;
        cout << "Enter multiplicity for " << universe[i] << " (0 to " << universeCardinality[universe[i]] << ", 0 to skip): ";
        while (!(cin >> multiplicity) || multiplicity < 0 || multiplicity > universeCardinality[universe[i]]) {
            cout << "Invalid input! Enter a number between 0 and " << universeCardinality[universe[i]] << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (multiplicity > 0) {
            multiset[universe[i]] = multiplicity;
        }
    }
}

// Automatic multiset creation
void MultisetProgram::createMultisetAutomatically(map<string, int>& multiset, const string& name, int cardinality) {
    cout << "\nCreating " << name << " automatically with cardinality " << cardinality << ":\n";
    multiset.clear();
    
    // First, set random cardinality (1-10) for each universe element
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> cardinalityDist(1, 10);
    
    for (const string& element : universe) {
        universeCardinality[element] = cardinalityDist(g);
    }
    
    // Randomly distribute cardinality among universe elements
    vector<int> indices(universe.size());
    iota(indices.begin(), indices.end(), 0);
    shuffle(indices.begin(), indices.end(), g);
    
    int remaining = cardinality;
    for (size_t i = 0; i < indices.size() && remaining > 0; i++) {
        int maxMultiplicity = universeCardinality[universe[indices[i]]];
        int multiplicity = (i == indices.size() - 1) ? min(remaining, maxMultiplicity) : 
                          min(rand() % (remaining + 1), maxMultiplicity);
        if (multiplicity > 0) {
            multiset[universe[indices[i]]] = multiplicity;
        }
        remaining -= multiplicity;
    }
}

// Display multiset
void MultisetProgram::displayMultiset(const map<string, int>& multiset, const string& name) {
    cout << "\n" << name << ":\n";
    if (multiset.empty()) {
        cout << "Empty multiset\n";
        return;
    }
    for (const auto& pair : multiset) {
        cout << pair.first << ": " << pair.second << " (" << universeCardinality[pair.first] << ")" << endl;
    }
}

// Set operations
map<string, int> MultisetProgram::unionMultisets(const map<string, int>& m1, const map<string, int>& m2) {
    map<string, int> result;
    set<string> allKeys;
    
    for (const auto& pair : m1) allKeys.insert(pair.first);
    for (const auto& pair : m2) allKeys.insert(pair.first);
    
    for (const string& key : allKeys) {
        int maxCardinality = universeCardinality[key];
        int unionValue = max(m1.count(key) ? m1.at(key) : 0, m2.count(key) ? m2.at(key) : 0);
        result[key] = min(unionValue, maxCardinality); // Respect cardinality limit
    }
    return result;
}

map<string, int> MultisetProgram::intersectionMultisets(const map<string, int>& m1, const map<string, int>& m2) {
    map<string, int> result;
    for (const auto& pair : m1) {
        if (m2.count(pair.first)) {
            int maxCardinality = universeCardinality[pair.first];
            int intersectionValue = min(pair.second, m2.at(pair.first));
            result[pair.first] = min(intersectionValue, maxCardinality); // Respect cardinality limit
        }
    }
    return result;
}

map<string, int> MultisetProgram::differenceMultisets(const map<string, int>& m1, const map<string, int>& m2) {
    map<string, int> result;
    for (const auto& pair : m1) {
        int maxCardinality = universeCardinality[pair.first];
        int diff = pair.second - (m2.count(pair.first) ? m2.at(pair.first) : 0);
        if (diff > 0) {
            result[pair.first] = min(diff, maxCardinality); // Respect cardinality limit
        }
    }
    return result;
}

map<string, int> MultisetProgram::symmetricDifferenceMultisets(const map<string, int>& m1, const map<string, int>& m2) {
    map<string, int> diff1 = differenceMultisets(m1, m2);
    map<string, int> diff2 = differenceMultisets(m2, m1);
    return unionMultisets(diff1, diff2);
}

map<string, int> MultisetProgram::complementMultiset(const map<string, int>& multiset) {
    map<string, int> result;
    for (const string& element : universe) {
        int multiplicity = multiset.count(element) ? multiset.at(element) : 0;
        int maxCardinality = universeCardinality[element];
        if (multiplicity == 0) {
            result[element] = maxCardinality; // Complement uses actual max cardinality
        }
    }
    return result;
}

// Arithmetic operations
int MultisetProgram::sumMultisets(const map<string, int>& multiset) {
    int sum = 0;
    for (const auto& pair : multiset) {
        sum += pair.second;
    }
    return sum;
}

int MultisetProgram::arithmeticDifferenceMultisets(const map<string, int>& m1, const map<string, int>& m2) {
    int diff = sumMultisets(m1) - sumMultisets(m2);
    return max(0, diff); // Ensure non-negative result
}

int MultisetProgram::productMultisets(const map<string, int>& multiset) {
    int product = 1;
    for (const auto& pair : multiset) {
        product *= pair.second;
    }
    return product;
}

int MultisetProgram::divisionMultisets(const map<string, int>& m1, const map<string, int>& m2) {
    int sum2 = sumMultisets(m2);
    if (sum2 == 0) {
        cout << "Division by zero error!\n";
        return 0;
    }
    return sumMultisets(m1) / sum2; // Integer division
}

// Gray-weighted arithmetic helpers
int MultisetProgram::grayToInt(const string& grayBits) {
    //Gray code string to integer: prefix XOR method
    int result = 0;
    int bitAccumulator = 0; // current binary bit value as we scan MSB->LSB
    for (char c : grayBits) {
        int g = (c == '1') ? 1 : 0;
        bitAccumulator ^= g;               // next binary bit = previous XOR gray
        result = (result << 1) | bitAccumulator;
    }
    return result;
}

long long MultisetProgram::weightedSum(const map<string, int>& multiset) const {
    long long total = 0;
    for (const auto& kv : multiset) {
        const string& gray = kv.first;
        int multiplicity = kv.second;
        total += static_cast<long long>(multiplicity) * grayToInt(gray);
    }
    return total;
}

long long MultisetProgram::weightedDifference(const map<string, int>& m1, const map<string, int>& m2) const {
    return weightedSum(m1) - weightedSum(m2);
}

long double MultisetProgram::weightedProduct(const map<string, int>& multiset) const {
    // Product over (value(gray) ^ multiplicity). Use long double to handle growth.
    long double product = 1.0L;
    for (const auto& kv : multiset) {
        const string& gray = kv.first;
        int multiplicity = kv.second;
        int value = grayToInt(gray);
        if (value == 0 && multiplicity > 0) {
            return 0.0L; // any zero value to positive power makes whole product zero
        }
        for (int i = 0; i < multiplicity; i++) {
            product *= static_cast<long double>(value);
        }
    }
    return product;
}

double MultisetProgram::weightedDivision(const map<string, int>& m1, const map<string, int>& m2) const {
    long long denom = weightedSum(m2);
    if (denom == 0) {
        cout << "Division by zero error!\n";
        return 0.0;
    }
    long long numer = weightedSum(m1);
    return static_cast<double>(numer) / static_cast<double>(denom);
}

// Main menu
void MultisetProgram::run() {
    cout << "=== Multiset Operations Program ===\n";
    
    // Get bit width
    cout << "Enter bit width for Gray code (1-10): ";
    while (!(cin >> bitWidth) || bitWidth < 1 || bitWidth > 10) {
        cout << "Invalid input! Enter a number between 1 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    initializeUniverse();
    displayUniverse();
    
    // Create multisets
    int choice;
    cout << "\nChoose creation method for Multiset 1:\n";
    cout << "1. Manual\n2. Automatic\n";
    cout << "Enter choice (1-2): ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (choice == 1) {
        createMultisetManually(multiset1, "Multiset 1");
    } else {
        int cardinality;
        cout << "Enter cardinality for Multiset 1: ";
        while (!(cin >> cardinality) || cardinality < 0) {
            cout << "Invalid input! Enter a non-negative integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        createMultisetAutomatically(multiset1, "Multiset 1", cardinality);
    }
    
    cout << "\nChoose creation method for Multiset 2:\n";
    cout << "1. Manual\n2. Automatic\n";
    cout << "Enter choice (1-2): ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (choice == 1) {
        createMultisetManually(multiset2, "Multiset 2");
    } else {
        int cardinality;
        cout << "Enter cardinality for Multiset 2: ";
        while (!(cin >> cardinality) || cardinality < 0) {
            cout << "Invalid input! Enter a non-negative integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        createMultisetAutomatically(multiset2, "Multiset 2", cardinality);
    }
    
    // Display multisets
    displayMultiset(multiset1, "Multiset 1");
    displayMultiset(multiset2, "Multiset 2");
    
    // Perform operations
    cout << "\n=== Set Operations ===\n";
    
    map<string, int> unionResult = unionMultisets(multiset1, multiset2);
    displayMultiset(unionResult, "Union");
    
    map<string, int> intersectionResult = intersectionMultisets(multiset1, multiset2);
    displayMultiset(intersectionResult, "Intersection");
    
    map<string, int> diff1Result = differenceMultisets(multiset1, multiset2);
    displayMultiset(diff1Result, "Difference (M1 - M2)");
    
    map<string, int> diff2Result = differenceMultisets(multiset2, multiset1);
    displayMultiset(diff2Result, "Difference (M2 - M1)");
    
    map<string, int> symDiffResult = symmetricDifferenceMultisets(multiset1, multiset2);
    displayMultiset(symDiffResult, "Symmetric Difference");
    
    map<string, int> comp1Result = complementMultiset(multiset1);
    displayMultiset(comp1Result, "Complement of M1");
    
    map<string, int> comp2Result = complementMultiset(multiset2);
    displayMultiset(comp2Result, "Complement of M2");
    
    cout << "\n=== Arithmetic Operations ===\n";
    cout << "Sum of M1: " << sumMultisets(multiset1) << endl;
    cout << "Sum of M2: " << sumMultisets(multiset2) << endl;
    cout << "Arithmetic Difference (M1 - M2): " << arithmeticDifferenceMultisets(multiset1, multiset2) << endl;
    cout << "Arithmetic Difference (M2 - M1): " << arithmeticDifferenceMultisets(multiset2, multiset1) << endl;
    cout << "Product of M1: " << productMultisets(multiset1) << endl;
    cout << "Product of M2: " << productMultisets(multiset2) << endl;
    cout << "Division (M1 / M2): " << divisionMultisets(multiset1, multiset2) << endl;
    cout << "Division (M2 / M1): " << divisionMultisets(multiset2, multiset1) << endl;

    // Gray-weighted arithmetic section
    cout << "\n=== Gray-weighted Arithmetic (values derived from Gray → integer) ===\n";
    cout << "Weighted Sum of M1: " << weightedSum(multiset1) << endl;
    cout << "Weighted Sum of M2: " << weightedSum(multiset2) << endl;
    cout << "Weighted Difference (M1 - M2): " << weightedDifference(multiset1, multiset2) << endl;
    cout << "Weighted Difference (M2 - M1): " << weightedDifference(multiset2, multiset1) << endl;
    cout << "Weighted Product of M1: " << fixed << setprecision(2) << (double)weightedProduct(multiset1) << endl;
    cout << "Weighted Product of M2: " << fixed << setprecision(2) << (double)weightedProduct(multiset2) << endl;
    cout << "Weighted Division (M1 / M2): " << fixed << setprecision(2) << weightedDivision(multiset1, multiset2) << endl;
    cout << "Weighted Division (M2 / M1): " << fixed << setprecision(2) << weightedDivision(multiset2, multiset1) << endl;
}

// Test functions
void runTests() {
    cout << "=== Running Tests ===\n\n";
    testGrayCodeGeneration();
    testMultisetOperations();
    testArithmeticOperations();
    cout << "\n=== All Tests Completed ===\n";
}

void testGrayCodeGeneration() {
    cout << "Testing Gray Code Generation...\n";
    
    MultisetProgram program;
    
    // Test 1-bit Gray code
    vector<string> gray1 = program.generateGrayCode(1);
    assert(gray1.size() == 2);
    assert(gray1[0] == "0");
    assert(gray1[1] == "1");
    cout << "✓ 1-bit Gray code: " << gray1[0] << ", " << gray1[1] << endl;
    
    // Test 2-bit Gray code
    vector<string> gray2 = program.generateGrayCode(2);
    assert(gray2.size() == 4);
    assert(gray2[0] == "00");
    assert(gray2[1] == "01");
    assert(gray2[2] == "11");
    assert(gray2[3] == "10");
    cout << "✓ 2-bit Gray code: " << gray2[0] << ", " << gray2[1] << ", " << gray2[2] << ", " << gray2[3] << endl;
    
    // Test 3-bit Gray code
    vector<string> gray3 = program.generateGrayCode(3);
    assert(gray3.size() == 8);
    cout << "✓ 3-bit Gray code has " << gray3.size() << " elements" << endl;
    
    cout << "Gray Code Generation Tests: PASSED\n\n";
}

void testMultisetOperations() {
    cout << "Testing Multiset Operations...\n";
    
    MultisetProgram program;
    
    // Create test multisets
    map<string, int> m1 = {{"00", 2}, {"01", 1}};
    map<string, int> m2 = {{"01", 3}, {"10", 1}};
    
    // Test union
    map<string, int> unionResult = program.unionMultisets(m1, m2);
    assert(unionResult["00"] == 2);
    assert(unionResult["01"] == 3);
    assert(unionResult["10"] == 1);
    cout << "✓ Union operation works correctly" << endl;
    
    // Test intersection
    map<string, int> intersectionResult = program.intersectionMultisets(m1, m2);
    assert(intersectionResult["01"] == 1);
    assert(intersectionResult.size() == 1);
    cout << "✓ Intersection operation works correctly" << endl;
    
    // Test difference
    map<string, int> diffResult = program.differenceMultisets(m1, m2);
    assert(diffResult["00"] == 2);
    assert(diffResult.size() == 1);
    cout << "✓ Difference operation works correctly" << endl;
    
    cout << "Multiset Operations Tests: PASSED\n\n";
}

void testArithmeticOperations() {
    cout << "Testing Arithmetic Operations...\n";
    
    MultisetProgram program;
    
    // Create test multiset
    map<string, int> m = {{"00", 2}, {"01", 3}, {"10", 1}};
    
    // Test sum
    int sum = program.sumMultisets(m);
    assert(sum == 6);
    cout << "✓ Sum operation: " << sum << endl;
    
    // Test product
    int product = program.productMultisets(m);
    assert(product == 6);
    cout << "✓ Product operation: " << product << endl;
    
    // Test arithmetic difference
    map<string, int> m1 = {{"00", 5}};
    map<string, int> m2 = {{"01", 2}};
    int diff = program.arithmeticDifferenceMultisets(m1, m2);
    assert(diff == 3);
    cout << "✓ Arithmetic difference operation: " << diff << endl;
    
    cout << "Arithmetic Operations Tests: PASSED\n\n";
}
