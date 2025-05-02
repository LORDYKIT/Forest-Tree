/**
 * @file ForestTree.cpp
 * @brief Implementation file for the ForestTree class.
 *
 * @details
 * Course : CSIS217 - Advanced Data Structures
 * Purpose : Implements a tree-like structure for managing accounts and their hierarchical relationships.
 *           Supports account creation, transaction management, balance propagation, and reporting.
 *
 * Features:
 * - Adding and removing accounts in a hierarchical structure
 * - Managing transactions and updating balances, including balance propagation to parent accounts
 * - Generating detailed account reports and saving them to a file
 * - Recursive traversal for printing account details and transactions
 *
 * @authors Mia
 *          Carmen
 * @date November 24th, 2024
 */

#include "ForestTree.h"
#include <fstream>
#include <iomanip>

/**
 * @brief Default constructor for ForestTree. Initializes an empty tree with no root.
 */
ForestTree::ForestTree() : root(nullptr) {}


/**
 * @brief Destructor for ForestTree. Cleans up dynamically allocated resources.
 *
 * @note Recursive deletion logic can be added here if necessary.
 */
ForestTree::~ForestTree() {
	deleteSubtree(root);
}


/**
 * @brief Recursively deletes a subtree starting from the given node.
 *
 * This helper function is used to clean up dynamically allocated memory
 * in the tree. It ensures that all children and sibling nodes of the
 * provided node are properly deleted before the node itself.
 *
 * @param node The root node of the subtree to delete. If `nullptr`, the function does nothing.
 *
 * @note Called by the destructor to deallocate the entire tree structure.
 */
void ForestTree::deleteSubtree(Node* node) {
	if (!node) return;

	deleteSubtree(node->firstChild);
	deleteSubtree(node->nextSibling);

	delete node;
}


/**
 * @brief Adds an account to the forest tree, either as a root-level or child account.
 *
 * @param accountNumber The unique identifier for the account.
 * @param description A brief description of the account.
 * @pre The accountNumber must not already exist in the tree.
 * @post A new account node is created and added to the tree, either as a root node or as a child under the appropriate parent.
 */
void ForestTree::addAccount(int accountNumber, const std::string& description) {
	if (accountMap.find(accountNumber) != accountMap.end()) {
		return;
	}

	auto newAccount = std::make_shared<Account>(accountNumber, description, 0);
	Node* newNode = new Node(newAccount);

	if (accountNumber < 10) {
		if (!root) {
			root = newNode;
		} else {
			Node* current = root;
			while (current->nextSibling) {
				current = current->nextSibling;
			}
			current->nextSibling = newNode;
		}
		accountMap[accountNumber] = newNode;
		return;
	}

	Node* parent = findParent(accountNumber);
	if (!parent) {
		std::cerr << "Parent not found for account " << accountNumber << ".\n";
		delete newNode;
		return;
	}

	if (!parent->firstChild) {
		parent->firstChild = newNode;
	} else {
		Node* sibling = parent->firstChild;
		Node* prevSibling = nullptr;
		while (sibling && sibling->account->getNumber() < accountNumber) {
			prevSibling = sibling;
			sibling = sibling->nextSibling;
		}

		if (prevSibling) {
			prevSibling->nextSibling = newNode;
		} else {
			parent->firstChild = newNode;
		}
		newNode->nextSibling = sibling;
	}

	accountMap[accountNumber] = newNode;
}


/**
 * @brief Prints the entire forest tree structure to a specified file.
 *
 * @param filename The name of the file to save the tree structure.
 * @post The tree's structure and accounts are written to the specified file.
 */
void ForestTree::printTreeToFile(const std::string& filename) const {
	std::ofstream file(filename);
	if (!file) {
		std::cerr << "Error creating file: " << filename << "\n";
		return;
	}


	Node* current = root;
	while (current) {
		printNode(current, file, 0, current->account->getNumber());
		current = current->nextSibling;
	}

	std::cout << "Tree successfully saved to " << filename << "\n";
}

/**
 * @brief Finds the parent node for a given account number.
 *
 * @param accountNumber The account number whose parent is to be found.
 * @return A pointer to the parent Node if found; otherwise, nullptr.
 *
 * @details Uses the account number hierarchy to identify the immediate parent.
 */
ForestTree::Node* ForestTree::findParent(int accountNumber) {
	if (accountNumber < 10) {

		return nullptr;
	}

	int parentNumber = accountNumber / 10;
	while (parentNumber > 0) {
		auto it = accountMap.find(parentNumber);
		if (it != accountMap.end()) {
			return it->second;
		}
		parentNumber /= 10;
	}

	return nullptr;
}

/**
 * @brief Finds an account in the tree by its account number.
 *
 * @param accountNumber The account number to search for.
 * @return A shared pointer to the Account if found; otherwise, nullptr.
 */
std::shared_ptr<Account> ForestTree::findAccount(int accountNumber) const {
	auto it = accountMap.find(accountNumber);
	if (it != accountMap.end()) {
		return it->second->account;
	}
	return nullptr;
}

/**
 * @brief Adds a transaction to a specified account and propagates the balance change to parent accounts.
 *
 * @param accountNumber The account number to which the transaction is added.
 * @param t The transaction details.
 * @pre The account must exist in the tree.
 * @post The transaction is added, the account balance is updated, and the balance change is propagated to parent accounts.
 */
void ForestTree::addTransaction(int accountNumber, const Transaction& t) {
	auto it = accountMap.find(accountNumber);
	if (it != accountMap.end()) {

		Node* node = it->second;
		node->account->addTransaction(t);


		double amt = (t.getType() == 'D' ? t.getAmount() : -t.getAmount());


		Node* parentNode = findParent(node->account->getNumber());
		while (parentNode) {
			parentNode->account->updateBalance(amt, t.getType());
			parentNode = findParent(parentNode->account->getNumber());
		}
	} else {

		std::cout << "Account not found. Please check the account number and try again.\n";
	}
}


/**
 * @brief Removes a transaction from a specified account and reverses the balance update.
 *
 * @param accountNumber The account number from which the transaction is removed.
 * @param transactionIndex The index of the transaction to remove.
 * @pre The account and transaction index must be valid.
 * @post The transaction is removed, and the reversed balance update is propagated to parent accounts.
 */
void ForestTree::removeTransaction(int accountNumber, int transactionIndex) {
	auto it = accountMap.find(accountNumber);
	if (it != accountMap.end()) {
		Node* node = it->second;
		std::shared_ptr<Account> account = node->account;


		if (transactionIndex >= 0 && transactionIndex < account->getTransactions().size()) {

			const Transaction& t = account->getTransactions()[transactionIndex];
			double amt = t.getAmount();
			char reversedType = (t.getType() == 'D') ? 'C' : 'D';


			account->removeTransaction(transactionIndex);


			while (node) {
				node->account->updateBalance(amt, reversedType);
				node = findParent(node->account->getNumber());
			}
		} else {
			std::cerr << "Invalid transaction index provided.\n";
		}
	} else {
		std::cerr << "Account number not found in the tree.\n";
	}
}


/**
 * @brief Prints a single node's details, including its account and transactions, recursively.
 *
 * @param node The node to print.
 * @param os The output stream to write to.
 * @param level The current level in the tree for formatting indentation.
 * @param accountNumber The account number for filtering.
 *
 * @details This method is used internally for recursive tree traversal.
 */
void ForestTree::printNode(Node* node, std::ostream& os, int level, int accountNumber) const {
	if (!node) return;


	os << std::string(level * 4, ' ') << *node->account << "\n";


	printNode(node->firstChild, os, level + 1, accountNumber);


	printNode(node->nextSibling, os, level, accountNumber);
}

/**
 * @brief Prints the entire forest tree to an output stream.
 *
 * @param os The output stream to write the tree structure to.
 * @post The tree's structure is written to the specified stream.
 */
void ForestTree::printTree(std::ostream& os) const {
	Node* current = root;
	while (current) {
		printNode(current, os, 0, current->account->getNumber());
		current = current->nextSibling;
	}
}


/**
 * @brief Generates a detailed report for a specific account and saves it to a file.
 *
 * @param accountNumber The account number for which the report is generated.
 * @param filename The name of the file to save the report.
 * @post The account report is written to the specified file.
 */
void ForestTree::printAccountReport(int accountNumber, const std::string& filename) {
	std::ofstream file(filename);
	if (!file) {
		std::cerr << "Error creating file: " << filename << "\n";
		return;
	}


	auto it = accountMap.find(accountNumber);
	if (it == accountMap.end()) {
		std::cerr << "Account not found: " << accountNumber << "\n";
		return;
	}


	printAccountDetails(it->second, file, 0, accountNumber);
	std::cout << "Report saved to " << filename << "\n";
}


/**
 * @brief Prints detailed information for a specific account to the console.
 *
 * @param accountNumber The account number whose details are printed.
 * @post The account details are displayed on the console.
 */
void ForestTree::printAccountInformation(int accountNumber) const {

	auto it = accountMap.find(accountNumber);
	if (it == accountMap.end()) {
		std::cout << "Account not found: " << accountNumber << "\n";
		return;
	}


	printAccountDetails(it->second, std::cout, 0, accountNumber);
}


/**
 * @brief Prints account details and transactions recursively for a specific account.
 *
 * @param node The starting node for printing.
 * @param os The output stream to write to.
 * @param level The current level in the tree for formatting indentation.
 * @param accountNumber The account number for filtering.
 */
void ForestTree::printAccountDetails(Node* node, std::ostream& os, int level, int accountNumber) const {
	if (!node) return;


	std::string accountNumberStr = std::to_string(accountNumber);
	std::string nodeAccountNumberStr = std::to_string(node->account->getNumber());


	if (nodeAccountNumberStr.find(accountNumberStr) == 0) {

		os << std::string(level * 4, ' ');


		os << *node->account << "\n";


		const auto& transactions = node->account->getTransactions();
		for (const auto& transaction : transactions) {
			os << std::string(level * 4 + 2, ' ') << transaction << "\n";
		}


		printAccountDetails(node->firstChild, os, level + 1, accountNumber);
		printAccountDetails(node->nextSibling, os, level, accountNumber);
	}
}


/**
 * @brief Removes an amount from an account balance and propagates the change to parent accounts.
 *
 * @param accountNumber The account number whose balance is updated.
 * @param t The transaction details representing the amount to remove.
 * @pre The account and transaction amount must be valid.
 * @post The balance is updated, and the change is propagated to parent accounts.
 */
void ForestTree::removeFromBalance(int accountNumber, const Transaction& t) {
	auto it = accountMap.find(accountNumber);
	if (it != accountMap.end()) {
		Node* node = it->second;
		node->account->addTransaction(t);


		if (t.getAmount() <= 0) {
			std::cerr << "Invalid amount to remove for account " << accountNumber << "\n";
			return;
		}

		double amountToRemove = t.getAmount();


		node->account->updateBalance(amountToRemove, 'C');


		Node* parentNode = findParent(node->account->getNumber());
		while (parentNode) {
			parentNode->account->updateBalance(amountToRemove, 'C');
			parentNode = findParent(parentNode->account->getNumber());
		}

		std::cout << "Amount removed from account " << accountNumber << " and propagated to parent accounts.\n";
	} else {
		std::cerr << "Account not found: " << accountNumber << "\n";
	}
}

