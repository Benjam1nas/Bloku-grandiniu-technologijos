#include "Header.h"
#include "MyLib.h"

void generator(vector<users>& list) {
    users list_r;
    srand(static_cast<unsigned>(time(nullptr)));

    ofstream output_file("vartotojai.txt");

    static const char characters[] = "0123456789abcdef";
    vector<string> names = { "Alice", "Bob", "John", "Ben", "Bradley", "Terry", "Johnathan", "Kris", "Kate", "Jeremy", "Joshua", "Hannah", "Grace" };
    string public_key;


    for (int i = 0; i < 1000; i++) {
        list_r.name = names[rand() % names.size()];
        for (int i = 0; i < 64; ++i) {
            public_key += characters[std::rand() % 16];
        }
        public_key = stringToHex(generateHash(public_key));
        list_r.public_key = public_key;
        public_key = "";
        list_r.balance = rand() % rand() % 999901 + 100;
        output_file << list_r.name << " " << list_r.public_key << " " << list_r.balance << endl;
        list.push_back(list_r);
    }
    output_file.close();
}

void transaction_list(vector<transactions>& list, vector<users>& usr) {
    transactions list_r;
    users usr_r;
    ofstream output_file("transakcijos.txt");
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < 10000; i++) {
        list_r.sender_key = usr[rand() % 1000].public_key;
        list_r.receiver_key = usr[rand() % 1000].public_key;
        do {
            list_r.receiver_key = usr[rand() % 1000].public_key;

        } while (list_r.receiver_key == list_r.sender_key);
        list.push_back(list_r);
        for (int q = 0; q < 1000; q++) {
            if (list[i].sender_key == usr[q].public_key) {
                list[i].value = usr[q].balance - rand() % (usr[q].balance + 1);
                if (usr[q].balance < 0 || usr[q].balance < list[i].value) {
                    cout << "User doesn't have enough balance to make this trasaction" << endl;
                }
                usr[q].balance = usr[q].balance - list[i].value;
                list[i].ID = stringToHex(generateHash(list[i].sender_key + list[i].receiver_key + to_string(list[i].value)));
            }
        }
        output_file << list[i].ID << " " << list[i].sender_key << " " << list[i].receiver_key << " " << list[i].value << endl;
    }
    output_file.close();
}
