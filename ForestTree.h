/**
 * @file ForestTree.h
 * @brief Header file for the ForestTree class.
 *
 * @details
 * Course : CSIS217 - Advanced Data Structures
 * Purpose : Declares the ForestTree class, a hierarchical tree structure for managing accounts
 *           and their relationships. Provides methods for account creation, transaction management,
 *           balance propagation, and reporting.
 *
 * Features:
 * - Adds accounts as root-level or child nodes in the hierarchy
 * - Supports balance updates and transaction management
 * - Provides detailed reports of account hierarchies and transactions
 * - Saves the tree structure and reports to files
 *
 * Authors : Mia
 *           Carmen
 * @date November 24th, 2024
 */

#ifndef FORESTTREE_H
#define FORESTTREE_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include "Account.h"

/**
 * @class ForestTree
 * @brief Represents a hierarchical tree structure for accounts.
 *
 * @details
 * Accounts are stored as nodes in a tree, with each node representing an account.
 * Root nodes represent high-level accounts, while child nodes represent sub-accounts.
 * Includes features for adding/removing accounts, managing transactions, and generating reports.
 */
class ForestTree {
private:
	/**
	 * @struct Node
	 * @brief Represents a single node in the ForestTree.
	 *
	 * @details Each node stores an account and pointers to its first child and next sibling.
	 */
	struct Node {
		std::shared_ptr<Account> account; /**< Shared pointer to the account represented by this node */
		Node* firstChild;                 /**< Pointer to the first child of this node */
		Node* nextSibling;                /**< Pointer to the next sibling of this node */

		/**
		 * @brief Constructor for Node.
		 * @param acc Shared pointer to the Account associated with this node.
		 */
		Node(std::shared_ptr<Account> acc)
			: account(acc), firstChild(nullptr), nextSibling(nullptr) {}
	};

	Node* root; /**< Root node of the ForestTree */

	std::unordered_map<int, Node*> accountMap; /**< Map for fast lookup of accounts by number */

	/**
	 * @brief Finds the parent node for a given account number.
	 * @param accountNumber The account number whose parent is to be found.
	 * @return Pointer to the parent Node, or nullptr if not found.
	 */
	Node* findParent(int accountNumber);

	/**
	 * @brief Recursively prints a node's details to an output stream.
	 * @param node The current node to print.
	 * @param os The output stream to write to.
	 * @param level The depth level for indentation.
	 * @param accountNumber The account number for filtering.
	 */
	void printNode(Node* node, std::ostream& os, int level, int accountNumber) const;

public:
	/**
	 * @brief Default constructor for ForestTree. Initializes an empty tree.
	 */
	ForestTree();

	/**
	 * @brief Destructor for ForestTree. Cleans up dynamically allocated resources.
	 */
	~ForestTree();

	/**
	 * @brief Recursively deletes a subtree starting from the given node.
	 *
	 * @details
	 * This method is responsible for deleting all nodes in a subtree, starting from the provided
	 * `node` and continuing recursively for each child and sibling. It ensures that all resources
	 * allocated for the nodes and their associated accounts are properly cleaned up.
	 *
	 * @param node The starting node of the subtree to be deleted. This node and all of its descendants
	 *        will be deleted.
	 * @pre The node must be a valid pointer (non-null).
	 * @post All nodes in the subtree are removed, and dynamically allocated memory is freed.
	 */
	void deleteSubtree(Node* node);

	/**
	 * @brief Adds an account to the tree.
	 * @param accountNumber The unique identifier for the account.
	 * @param description A brief description of the account.
	 * @pre The accountNumber must not already exist in the tree.
	 * @post A new account is added as a root or child node based on its hierarchy.
	 */
	void addAccount(int accountNumber, const std::string& description);

	/**
	 * @brief Removes an account from the tree.
	 * @param accountNumber The unique identifier of the account to remove.
	 * @post The specified account is removed, along with any associated child accounts.
	 */
	void removeAccount(int accountNumber);

	/**
	 * @brief Adds a transaction to a specific account.
	 * @param accountNumber The account number to which the transaction is added.
	 * @param t The transaction details.
	 * @pre The account must exist in the tree.
	 * @post The transaction is added, and balance updates are propagated to parent accounts.
	 */
	void addTransaction(int accountNumber, const Transaction& t);

	/**
	 * @brief Removes a transaction from a specific account.
	 * @param accountNumber The account number from which the transaction is removed.
	 * @param transactionIndex The index of the transaction to remove.
	 * @pre The account and transaction index must be valid.
	 * @post The transaction is removed, and reversed balance updates are propagated to parent accounts.
	 */
	void removeTransaction(int accountNumber, int transactionIndex);

	/**
	 * @brief Finds an account in the tree by its number.
	 * @param accountNumber The account number to search for.
	 * @return Shared pointer to the Account if found; otherwise, nullptr.
	 */
	std::shared_ptr<Account> findAccount(int accountNumber) const;

	/**
	 * @brief Prints the entire tree to an output stream.
	 * @param os The output stream to write to.
	 * @post The tree's structure is displayed in the output stream.
	 */
	void printTree(std::ostream& os) const;

	/**
	 * @brief Prints the tree structure to a file.
	 * @param filename The name of the file to save the tree structure.
	 * @post The tree structure is saved to the specified file.
	 */
	void printTreeToFile(const std::string& filename) const;

	/**
	 * @brief Prints detailed information about a specific account.
	 * @param accountNumber The account number to print details for.
	 * @post The account's details and transactions are displayed in the console.
	 */
	void printAccountInformation(int accountNumber) const;

	/**
	 * @brief Prints detailed account information to a file.
	 * @param accountNumber The account number for which the report is generated.
	 * @param filename The name of the file to save the report.
	 * @post The account report is saved to the specified file.
	 */
	void printAccountReport(int accountNumber, const std::string& filename);

	/**
	 * @brief Prints details and transactions for a specific account and its subaccounts.
	 * @param node The starting node for the account.
	 * @param os The output stream to write to.
	 * @param level The depth level for formatting indentation.
	 * @param accountNumber The account number for filtering.
	 */
	void printAccountDetails(Node* node, std::ostream& os, int level, int accountNumber) const;

	/**
	 * @brief Removes an amount from an account's balance and propagates the update.
	 * @param accountNumber The account number whose balance is updated.
	 * @param t The transaction representing the amount to remove.
	 * @pre The account and transaction amount must be valid.
	 * @post The balance is updated, and the change is propagated to parent accounts.
	 */
	void removeFromBalance(int accountNumber, const Transaction& t);
};

#endif // FORESTTREE_H
