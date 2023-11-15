#include "MyLib.h"
#include "Header.h"

int main() {
	vector<users> list_of_users;
	vector<transactions> list_of_transactions;
	vector<transactions>txpool;
	Blockchain blockchain;
	int q = 0;
	bool found = false;
	file_read(list_of_users, list_of_transactions);
	//generator(list_of_users);
	//transaction_list(list_of_transactions, list_of_users);
	for (int i = 0; i < list_of_transactions.size(); i++) {
		if (!validateTransactionHash(list_of_transactions[i])) {
			cout << "Invalid transaction hash for transaction ID skipping transaction: " << list_of_transactions[i].ID << endl;
			list_of_transactions.erase(list_of_transactions.begin() + i);
		}
	}
	blockchain.displaySingleBlock(q);
	q++;
	while (list_of_transactions.size() > 0) {
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < 100; i++) {
				txpool.push_back(list_of_transactions[i]);
			}
			blockchain.addBlockCandidate(txpool);
			txpool.clear();
		}
		for (int i = 0; i < 5; i++) {
			found = blockchain.miningForCandidates(i);
			if (found == true) {
				blockchain.addCandidateToChain(i);
				list_of_transactions.erase(list_of_transactions.begin(), list_of_transactions.begin() + 100);
				blockchain.displaySingleBlock(q);
				q++;
				break;
			}
		}
		if (found == false) {
			cout << "Failed to mine a block!" << endl;
		}
		blockchain.clearCandidates();
	}
}