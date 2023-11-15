#include "MyLib.h"
#include "Header.h"

int value(string input) {
    int ASCII_VALUE = 0;
    for (char c : input) {
        ASCII_VALUE += c;
    }
    return ASCII_VALUE;
}

string generateHash(const string& input) {
    string Hash = "";
    string unique_number = to_string(value(input));
    static const char symbols[] = "0abc1def2ghi3jkl4mno5pqr6st7uvw8xyz9";

    for (char c : unique_number) {
        Hash += symbols[c % 13];
    }

    int i = 0;
    while (Hash.length() < 32) {
        Hash += symbols[Hash[i] % 31];
        i++;
    }

    return Hash.substr(0, 32);
}


string stringToHex(string input) {
    stringstream hexStream;
    for (char c : input) {
        hexStream << std::hex << setw(2) << setfill('0') << static_cast<int>(c);
    }

    string hexString = hexStream.str();
    return hexString;
}

void file_read(vector<users>& usr, vector<transactions>& list) {
    users user_r;
    transactions transactions_r;
    ifstream input_file("vartotojai.txt");
    for (int i = 0; i < 1000; i++) {
        input_file >> user_r.name >> user_r.public_key >> user_r.balance;
        usr.push_back(user_r);
    }
    input_file.close();
    ifstream transaction_file("transakcijos.txt");
    for (int i = 0; i < 10000; i++) {
        transaction_file >> transactions_r.ID >> transactions_r.sender_key >> transactions_r.receiver_key >> transactions_r.value;
        list.push_back(transactions_r);
    }
    transaction_file.close();
}

bool validateTransactionHash(const transactions& tx) {
    string calculatedHash = stringToHex(generateHash(tx.sender_key + tx.receiver_key + to_string(tx.value)));
    return calculatedHash == tx.ID;
}