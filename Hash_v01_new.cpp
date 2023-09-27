#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int value(string input) {
    int ASCII_VALUE = 0;
    for (char c : input) {
        ASCII_VALUE += c;
    }
    return ASCII_VALUE;
}

string generateHash(string input) {
    string Hash, unique_number = to_string(value(input));
    static const char symbols[] = "0abc1def2ghi3jkl4mno5pqr6st7uvw8xyz9";
    for (char c : unique_number) {
        Hash += symbols[c % 31];
    }
    int i = 0;
    while (Hash.length() != 32) {
        Hash += symbols[Hash[i] % 31];
        i++;
    }
    return Hash;
}

string stringToHex(const string& input) {
    stringstream hexStream;
    for (char c : input) {
        hexStream << hex << setw(2) << setfill('0') << static_cast<int>(c);
    }

    string hexString = hexStream.str();
    return hexString;
}

int main(int argc, char* argv[]) {
    string input;

    if (argc == 2) {
        ifstream inFile(argv[1]);
        if (!inFile) {
            cerr << "Error: Could not open input file " << argv[1] << "\n";
            return 1;
        }

        char x;
        while (inFile.get(x)) {
            input += x;
        }

        inFile.close();
    }
    else if (argc == 1) {
        cout << "Enter your input: ";
        getline(cin, input);
    }
    else {
        cerr << "Usage: " << argv[0] << " [input_file]\n";
        return 1; 
    }

    string output = generateHash(input);
    cout << "Hash: " << stringToHex(output);
    return 0;
}







