#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;
using namespace chrono;

int value(string input) {
    int ASCII_VALUE = 0;
    for (char c : input) {
        ASCII_VALUE += c;
    }
    return ASCII_VALUE;
}

string generateHash(string input) {
    string Hash = "", unique_number = to_string(value(input));
    static const char symbols[] = "0abc1def2ghi3jkl4mno5pqr6st7uvw8xyz9";
    for (char c : unique_number) {
        Hash += symbols[c % 13];
    }
    int i = 0;
    while (Hash.length() != 32) {
        Hash += symbols[Hash[i] % 31];
        i++;
    }
    return Hash;
}

string stringToHex(string input) {
    stringstream hexStream;
    for (char c : input) {
        hexStream << hex << setw(2) << setfill('0') << static_cast<int>(c);
    }

    string hexString = hexStream.str();
    return hexString;
}

int countHexDifference(string hex1, string hex2) {
    int difference = 0;

    for (size_t i = 0; i < hex1.length(); i++) {
        char c1 = hex1[i];
        char c2 = hex2[i];
        if (c1 != c2) {
            difference++;
        }
    }
    return difference;
}

int countBitDifference(string hex1, string hex2) {
    int difference = 0;
    for (size_t i = 0; i < hex1.length(); ++i) {
        int int1 = stoi(hex1.substr(i, 2), nullptr, 16); 
        int int2 = stoi(hex2.substr(i, 2), nullptr, 16);

        bitset<8> binary1(int1);
        bitset<8> binary2(int2);

        for (int j = 0; j < 8; ++j) {
            if (binary1[j] != binary2[j]) {
                difference++;
            }
        }
        i++;
    }
    return difference;
}

void task_nr_6(string name) {
    string symbols;
    vector<string> pair_1, pair_2, hash_pair_1, hash_pair_2;
    char x;
    ifstream inFile(name);
    while (inFile.get(x)) {
        if (x != ',' && x != '\n') {
            if (x != ' ') {
                symbols += x;
            } 
        }
        else {
            if (x == ',') {
                pair_1.push_back(symbols);
            }
            else {
                pair_2.push_back(symbols);
            }
            symbols = "";
        }
    }
    for (int i = 0; i < pair_1.size(); i++) {
        hash_pair_1.push_back(stringToHex(generateHash(pair_1[i])));
        hash_pair_2.push_back(stringToHex(generateHash(pair_2[i])));
    }

    vector<int> bitDifferences;
    vector<int> hexDifferences;

    for (int i = 0; i < hash_pair_1.size(); i++) {
        int bitDifference = countBitDifference(hash_pair_1[i], hash_pair_2[i]);
        int hexDifference = countHexDifference(hash_pair_1[i], hash_pair_2[i]);
        if (hexDifference == 0) {
            cout << pair_1[i] << " " << pair_2[i] << endl
                << hash_pair_1[i] << " " << hash_pair_2[i] << endl;
        }

        bitDifferences.push_back(bitDifference);
        hexDifferences.push_back(hexDifference);
    }

    sort(bitDifferences.begin(), bitDifferences.end());
    sort(hexDifferences.begin(), hexDifferences.end());

    double minBitDifference = bitDifferences.front();
    double maxBitDifference = bitDifferences.back();
    double minHexDifference = hexDifferences.front();
    double maxHexDifference = hexDifferences.back();

    double totalBitDifference = 0;
    double totalHexDifference = 0;

    for (int i = 0; i < bitDifferences.size(); i++) {
        totalBitDifference += bitDifferences[i];
    }

    for (int i = 0; i < hexDifferences.size(); i++) {
        totalHexDifference += hexDifferences[i];
    }

    double avgBitDifference = totalBitDifference / (double)bitDifferences.size();
    double avgHexDifference = totalHexDifference / (double)hexDifferences.size();

    double percentageAvgBitDifference = (avgBitDifference / maxBitDifference) * 100;
    double percentageAvgHexDifference = (avgHexDifference / maxHexDifference) * 100;

    cout << "Bits difference stats:" << endl;
    cout << "Min difference: " << minBitDifference << " bits" << endl;
    cout << "Max difference: " << maxBitDifference << " bits" << endl;
    cout << "Average difference: " << avgBitDifference << " bits" << endl;
    cout << "Percentage of average difference: " << percentageAvgBitDifference << "%" << endl;

    cout << "Hex difference stats:" << endl;
    cout << "Min difference: " << minHexDifference << " hex" << endl;
    cout << "Max difference: " << maxHexDifference << " hex" << endl;
    cout << "Average difference: " << avgHexDifference << " hex" << endl;
    cout << "Percentage of average difference: " << percentageAvgHexDifference << "%" << endl;
}

int main(int argc, char* argv[]) {
    string input;
    bool task = false;

    if (argc == 3) {
        int linesToRead = atoi(argv[2]);
        ifstream inFile(argv[1]);
        if (!inFile) {
            cerr << "Error: Could not open input file " << argv[1] << endl;
            return 1;
        }

        string line;
        for (int i = 0; i < linesToRead && getline(inFile, line); i++) {
            input += line;
        }

        inFile.close();
    }
    else if (argc == 2) {
        ifstream inFile(argv[1]);
        if (!inFile) {
            cerr << "Error: Could not open input file " << argv[1] << endl;
            return 1;
        }
        string name = argv[1];
        if (name == "random_pairs_1_diff.txt") {
            task = true;
            task_nr_6(name);
        }
        else {
            char x;
            while (inFile.get(x)) {
                input += x;
            }
        } 
        inFile.close();
    }
    else if (argc == 1) {
        cout << "Enter your input: ";
        getline(cin, input);
    }
    else {
        cerr << "Usage: " << argv[0] << " [input_file] [lines_to_read] " << endl;
        return 1;
    }

    if (!task) {
        time_point<high_resolution_clock> start, end;
        duration<double> time;
        double hashing_time = 0;

        start = high_resolution_clock::now();

        string output = generateHash(input);
        cout << "Hash: " << stringToHex(output) << endl;

        end = high_resolution_clock::now();
        time = end - start;
        hashing_time = time.count();

        cout << "Hashing took: " << setprecision(2) << hashing_time << " seconds" << endl;
    }

    return 0;
}

