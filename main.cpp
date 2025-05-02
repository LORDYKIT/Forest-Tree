/**
 * @file main.cpp
 * @brief Main file for the ForestTree application.
 *
 * @details
 * Course : CSIS217 - Advanced Data Structures
 * Current File : main.cpp (Main)
 * Purpose : To implement a class ForestTree for managing accounts using advanced data structures,
 *           including binary trees, along with associated classes for transactions and account handling.
 * Methods : This file provides a menu-driven interface to utilize methods implemented in ForestTree
 *           and related classes.
 *
 * Features include:
 *  - Loading account data from a file
 *  - Adding accounts and transactions
 *  - Deleting transactions
 *  - Searching accounts
 *  - Generating reports for specific accounts
 *  - Printing account information and saving the tree to a file
 *
 * @authors Mia
 *          Carmen
 * @date November 24th, 2024
 */

#include "ForestTree.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <string>

/**
 * @brief Prompts the user for a positive integer input and validates the input.
 *
 * @details
 * This function repeatedly prompts the user for an integer input until a valid, positive integer
 * is provided. If the input is invalid, an error message is displayed, and the user is prompted again.
 * The input is validated to ensure that it is a positive integer (greater than 0).
 *
 * @param prompt The message displayed to the user, asking for input.
 * @return A valid positive integer entered by the user.
 * @pre The input must be a positive integer.
 * @post The function ensures the input is a valid positive integer and returns it.
 */
int getValidatedInteger(const std::string& prompt) {
	int value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value && value > 0) {
			return value;  // Valid input
		} else {
			std::cout << "Invalid input. Please enter a positive integer.\n";
			std::cin.clear();  // Clear error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
		}
	}
}


/**
 * @brief Prompts the user for a positive floating-point number (amount) and validates the input.
 *
 * @details
 * This function repeatedly prompts the user for a floating-point input (double) until a valid, positive
 * number is provided. If the input is invalid, an error message is displayed, and the user is prompted again.
 * The input is validated to ensure that it is a positive number (greater than 0.0).
 *
 * @param prompt The message displayed to the user, asking for input.
 * @return A valid positive double entered by the user.
 * @pre The input must be a positive number.
 * @post The function ensures the input is a valid positive number and returns it.
 */
double getValidatedAmount(const std::string& prompt) {
	double value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value && value > 0.0) {
			return value;
		} else {
			std::cout << "Invalid input. Please enter a positive number.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}


/**
 * @brief Checks if the transaction type is valid ('C' for credit, 'D' for debit).
 *
 * @param type The transaction type to validate.
 * @return True if the type is 'C', 'c', 'D', or 'd', otherwise false.
 */
bool isValidTransactionType(char type) {
	return type == 'C' || type == 'c' || type == 'D' || type == 'd';
}

/**
 * @brief Loads account data from a file and populates the ForestTree.
 *
 * @param forest Reference to the ForestTree object.
 * @param filename Name of the file containing account data. Each line should contain
 *        an account number followed by its description.
 * @pre File must be formatted correctly with each line containing an integer followed by text.
 * @post ForestTree is populated with accounts from the file.
 */
void loadAccounts(ForestTree& forest, const std::string& filename) {
	std::ifstream file(filename);
	int number;
	std::string description;

	while (file >> number) {
		file.ignore(); // Skip the space after the number
		std::getline(file, description); // Read the rest of the line as the description
		forest.addAccount(number, description); // Add account to the tree
	}
}

/**
 * @brief Main function to run the program.
 * @details Displays a menu for managing accounts and transactions, allowing the user
 *          to perform various operations on the ForestTree.
 *
 * @return int Program exit status.
 */
int main() {
	ForestTree forest; // Binary tree structure for managing accounts

	// Step 1: Load accounts from a file
	loadAccounts(forest, "accountswithspace.txt");
	std::cout << "Accounts loaded successfully.\n";

	int choice = 0; // Variable for user menu choice

	while (true) {
		// Step 2: Display the menu
		std::cout << "\nMenu:\n";
		std::cout << "1) Print all accounts\n";
		std::cout << "2) Add an account\n";
		std::cout << "3) Add a transaction\n";
		std::cout << "4) Delete a transaction\n";
		std::cout << "5) Print a specific account to a file\n";
		std::cout << "6) Search for an account by account number\n";
		std::cout << "7) Print account information to console\n";
		std::cout << "8) Save the entire tree to a file\n";
		std::cout << "9) Exit program\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			/**
			 * @case 1: Print all accounts
			 * @details Calls the ForestTree::printTree() method to display all accounts
			 *          in the tree structure.
			 * @post All accounts are printed to the console in an in-order traversal format.
			 */
			forest.printTree(std::cout);
			break;

		case 2: {
			/**
			 * @case 2: Add an account
			 * @details Prompts the user to enter an account number and description, then
			 *          adds the account to the tree with a default balance of 0.
			 * @post The account is added to the tree, after validation for the account number.
			 */
			int accountNumber;
			std::string description;

			accountNumber = getValidatedInteger("Enter account number: ");

			std::cout << "Enter account description: ";
			std::cin >> description;

			if (forest.findAccount(accountNumber)) {
				std::cout << "Account already exists.\n";
				break;
			}


			forest.addAccount(accountNumber, description);

			// Check if the account was added successfully
			if (forest.findAccount(accountNumber)) {
				std::cout << "Account added successfully.\n";
			} else {
				std::cout << "Failed to add account. Please try again.\n";
			}

			break;
		}

		case 3: {
			/**
			 * @case 3: Add transactions
			 * @details Allows the user to add debit or credit transactions to an account.
			 * @pre The account must exist in the tree.
			 * @post The transaction is added, and the account balance is updated, after validating the amount and type.
			 */

			char type;

			int accountNumber = getValidatedInteger("Enter account number: ");

			std::cout << "Enter transaction type (D for debit, C for credit): ";
			std::cin >> type;

			type = toupper(type);

			// Validate transaction type
			if (!isValidTransactionType(type)) {
				std::cout << "Invalid transaction type entered. Please enter 'C' for credit or 'D' for debit.\n";
				break;
			}

			double amount = getValidatedAmount("Enter transaction amount: ");

			if (type == 'D' || type == 'd') {
				forest.addTransaction(accountNumber, Transaction(accountNumber, amount, type));
			} else if (type == 'C' || type == 'c') {
				forest.removeFromBalance(accountNumber, Transaction(accountNumber, amount, type));
			}
			break;
		}

		case 4: {
			/**
			 * @case 4: Delete a transaction
			 * @details Displays all transactions for a specified account and allows the user
			 *          to delete one by its index.
			 * @pre The account must exist, and the transaction index must be valid.
			 * @post The specified transaction is removed from the account.
			 */
			int accountNumber, transactionIndex;

			accountNumber = getValidatedInteger("Enter account number: ");


			auto account = forest.findAccount(accountNumber);
			if (account) {
				const auto& transactions = account->getTransactions();

				// Check if there are any transactions
				if (transactions.empty()) {
					std::cout << "No transactions found for this account.\n";
					break;
				}

				// Display transactions with valid indexes
				for (size_t i = 0; i < transactions.size(); ++i) {
					std::cout << i + 1 << ") Amount: " << transactions[i].getAmount()
					          << ", Type: " << transactions[i].getType() << "\n";
				}

				// Ask the user to choose a transaction index to delete
				while (true) {
					std::cout << "Enter transaction number to delete: ";
					std::cin >> transactionIndex;

					// Validate if the entered index is valid
					if (transactionIndex >= 1 && transactionIndex <= transactions.size()) {
						// Valid index, proceed with deletion
						forest.removeTransaction(accountNumber, transactionIndex - 1);
						std::cout << "Transaction deleted successfully.\n";
						break;
					} else {
						// Invalid index, show a message and ask again
						std::cout << "You can only pick from the existing indexes (1 to " << transactions.size() << "). Please try again.\n";
					}
				}
			} else {
				std::cout << "Account not found.\n";
			}
			break;
		}


		case 5: {
			/**
			 * @case 5: Print a specific account to a file
			 * @details Prompts the user for an account number and generates a report
			 *          saved to a file.
			 * @pre The account must exist in the tree.
			 * @post A report is saved to a file.
			 */
			int accountNumber;
			accountNumber = getValidatedInteger("Enter account number to generate a report: ");


			std::string filename = "account_" + std::to_string(accountNumber) + "_report.txt";
			forest.printAccountReport(accountNumber, filename);

			break;
		}

		case 6: {
			/**
			 * @case 6: Search for an account by account number
			 * @details Searches for an account in the tree and displays it if found.
			 * @post Displays the account information if found, or a not found message.
			 */

			int accountNumber = getValidatedInteger("Enter account number to search: ");

			auto account = forest.findAccount(accountNumber);
			if (account) {
				std::cout << "Account found: " << *account << "\n";
			} else {
				std::cout << "Account not found.\n";
			}
			break;
		}

		case 7: {
			/**
			 * @case 7: Print account information to the console
			 * @details Prompts the user for an account number and prints detailed
			 *          account information to the console.
			 * @pre The account must exist.
			 * @post Account information is displayed.
			 */

			int accountNumber = getValidatedInteger("Enter account number to print account information: ");
			forest.printAccountInformation(accountNumber);
			break;
		}

		case 8: {
			/**
			 * @case 8: Save the entire tree to a file
			 * @details Prompts the user for a filename and saves the entire ForestTree structure
			 *          to that file.
			 * @post The tree structure is saved to the file.
			 */
			std::string filename;
			std::cout << "Enter filename to save the entire tree: ";
			std::cin >> filename;
			forest.printTreeToFile(filename);
			break;
		}

		case 9: {
			/**
			 * @case 9: Exit program
			 * @details Exits the program and displays a thank you message to the user.
			 * @post Program exits.
			 */
			std::cout << "Exiting program.\n";
			std::cout << "Thank you for using our account management system.\n";
			return 0;
		}

		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}
