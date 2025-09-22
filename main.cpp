#include "funcs.h"

int main() {
    srand(time(0));
    
    cout << "Choose mode:\n";
    cout << "1. Run main program\n";
    cout << "2. Run tests\n";
    cout << "Enter choice (1-2): ";
    
    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (choice == 1) {
        MultisetProgram program;
        program.run();
    } else {
        runTests();
    }
    
    return 0;
}
