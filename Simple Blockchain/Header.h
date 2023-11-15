#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "MyLib.h"


struct users {
    string name, public_key;
    int balance;
};

struct transactions {
    string ID, sender_key, receiver_key;
    int value;

};

struct block {
    string candidateNr;
    int index;
    std::chrono::system_clock::time_point timestamp;
    string prev_hash, MerkleRootHash;
    string version = "1.0";
    string Difficulty_Target = "68";
    int nonce = 0;
    vector<transactions> transactionPool;
};

class Blockchain {
public:
    Blockchain() {
        // Genesis block
        addBlock(vector<transactions>{transactions{ "GenesisID", "GenesisSender", "GenesisReceiver", 0 }});
    }

    void addBlock(const vector<transactions>& txPool) {
        string candidateNr = "1A";
        int index = chain.size();
        string prevHash = index > 0 ? calculateHash(chain[index - 1]) : "0";
        string MerkleRootHash = index > 0 ? calculateMerkleRootHash(txPool) : "GenesisMerkleRootHash";

        block newBlock;
        newBlock.index = index;
        newBlock.timestamp = std::chrono::system_clock::now();
        newBlock.prev_hash = prevHash;
        newBlock.MerkleRootHash = MerkleRootHash;
        newBlock.version = "1.0";
        newBlock.Difficulty_Target = "6868";
        newBlock.transactionPool = txPool;
        newBlock.nonce = index > 0 ? calculateNonce(newBlock) : 0;

        chain.push_back(newBlock);
    }

    void addBlockCandidate(const vector<transactions>& txPool) {
        string candidateNr = candidates.size() + "A";
        int index = chain.size();
        string prevHash = candidates.size() > 0 ? calculateHash(candidates[candidates.size() - 1]) : "0";
        string MerkleRootHash = calculateMerkleRootHash(txPool);

        block newBlock;
        newBlock.index = index;
        newBlock.timestamp = std::chrono::system_clock::now();
        newBlock.prev_hash = prevHash;
        newBlock.MerkleRootHash = MerkleRootHash;
        newBlock.version = "1.0";
        newBlock.Difficulty_Target = "68";
        newBlock.transactionPool = txPool;
        candidates.push_back(newBlock);
    }

    bool miningForCandidates(int index) {
        int nonce;
        block& blk = candidates[index];
        nonce = calculateNonceForCandidates(blk);
        if (nonce != -1) {
            blk.nonce = nonce;
            return true;
        }
        else {
            return false;
        }
    };

    void displaySingleBlock(int index) const {
        if (index < 0 || index >= chain.size()) {
            cout << "Invalid block index\n";
            return;
        }

        const block& blk = chain[index];

        cout << "Block #" << blk.index << "\n";
        cout << "Timestamp: " << std::chrono::system_clock::to_time_t(blk.timestamp) << "\n";
        cout << "Previous Hash: " << blk.prev_hash << "\n";
        cout << "Merkle Root Hash: " << blk.MerkleRootHash << "\n";
        cout << "Version: " << blk.version << "\n";
        cout << "Difficulty Target: " << blk.Difficulty_Target << "\n";
        cout << "Nonce: " << blk.nonce << "\n";
        cout << "Transactions:\n";
        for (const transactions& tx : blk.transactionPool) {
            std::cout << "  Transaction ID: " << tx.ID << "\n";
            std::cout << "  Sender: " << tx.sender_key << "\n";
            std::cout << "  Recipient: " << tx.receiver_key << "\n";
            std::cout << "  Value: " << tx.value << "\n";
            std::cout << "----------------\n";
        }
        std::cout << "Hash: " << calculateHash(blk) << "\n";
        std::cout << "----------------\n";
    }

    void addCandidateToChain(int index) {
        chain.push_back(candidates[index]);
    }

    void clearCandidates() {
        candidates.clear();
    }

private:
    vector<block> chain;
    vector<block> candidates;

    int value(const string& input) const {
        int ASCII_VALUE = 0;
        for (char c : input) {
            ASCII_VALUE += c;
        }
        return ASCII_VALUE;
    }

    string generateHash(const string& input) const {
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

    string stringToHex(const std::string& input) const {
        stringstream hexStream;
        for (char c : input) {
            hexStream << std::hex << setw(2) << setfill('0') << static_cast<int>(c);
        }

        string hexString = hexStream.str();
        return hexString;
    }

    string calculateHash(const block& blk) const {
        stringstream ss;
        ss << blk.index << blk.timestamp.time_since_epoch().count() << blk.prev_hash
            << blk.version << blk.Difficulty_Target << blk.nonce;

        for (const transactions& tx : blk.transactionPool) {
            ss << tx.ID << tx.sender_key << tx.receiver_key << tx.value;
        }

        string input = ss.str();
        string hash = generateHash(input);
        return stringToHex(hash);
    }

    string calculateMerkleRootHash(const vector<transactions>& txPool) {
        vector<transactions> pair_hashes = txPool;
        transactions IDs;
        while (pair_hashes.size() > 1) {
            vector<transactions>temp_vector;
            for (size_t i = 0; i < pair_hashes.size(); i += 2) {
                if (i + 1 < pair_hashes.size()) {
                    IDs.ID = stringToHex(generateHash(pair_hashes[i].ID + pair_hashes[i + 1].ID));
                    temp_vector.push_back(IDs);
                }
                else {
                    IDs.ID = stringToHex(generateHash(pair_hashes[i].ID + pair_hashes[i].ID));
                    temp_vector.push_back(IDs);
                }
            }
            pair_hashes = temp_vector;
        }
        return pair_hashes[0].ID;
    }

    int calculateNonce(block& blk) {
        int calculatedNonce = 0;

        while (true) {
            blk.nonce = calculatedNonce;
            string input = to_string(calculatedNonce);
            string hash = stringToHex(generateHash(input));

            if (hash.substr(0, blk.Difficulty_Target.length()) == blk.Difficulty_Target) {
                break;
            }

            calculatedNonce++;
        }

        return calculatedNonce;
    }

    int calculateNonceForCandidates(block& blk) {
        int calculatedNonce = 0;
        bool found = false;

        while (calculatedNonce < 1000000) {
            blk.nonce = calculatedNonce;
            string input = to_string(calculatedNonce);
            string hash = stringToHex(generateHash(input));

            if (hash.substr(0, blk.Difficulty_Target.length()) == blk.Difficulty_Target) {
                found = true;
                break;
            }

            calculatedNonce++;
        }
        if (found == false) {
            return -1;
        }
        else {
            return calculatedNonce;
        }
    }
};

void generator(vector<users>& list);
int value(string input);
string generateHash(const string& input);
string stringToHex(string input);
void transaction_list(vector<transactions>& list, vector<users>& usr);
void file_read(vector<users>& usr, vector<transactions>& list);
bool validateTransactionHash(const transactions& tx);

#endif
