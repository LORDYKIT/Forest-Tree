/**
 * @file Account.h
 * @brief Header file for the Account class.
 *
 * @details
 * Course : CSIS217 - Advanced Data Structures
 * Purpose : Defines the Account class for managing individual account data,
 *           including account details, balance, and associated transactions.
 *
 * Features:
 * - Stores account details (number, description, balance)
 * - Manages a collection of transactions
 * - Supports adding and removing transactions
 * - Provides methods to update the balance based on transactions
 * - Overloads the insertion operator for streamlined output
 *
 * @authors Mia
 *          Carmen
 * @date November 24th, 2024
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h"

/**
 * @class Account
 * @brief Represents a single account with its associated details and transactions.
 *
 * @details The Account class is designed to store the details of an individual account,
 * including its unique number, description, balance, and a list of transactions. It provides
 * functionality to manage transactions and keep the account balance updated.
 */
class Account {
private:
	int number;  ///< Unique account number
	std::string description;  ///< Description of the account
	double balance;  ///< Current balance of the account
	std::vector<Transaction> transactions;  ///< List of transactions associated with the account

public:
	/**
	 * @brief Constructor to initialize an account.
	 *
	 * @param num The unique account number.
	 * @param desc The description of the account.
	 * @param bal The initial balance of the account (default is 0).
	 */
	Account(int num, const std::string& desc, double bal = 0)
		: number(num), description(desc), balance(bal) {}

	/**
	 * @brief Retrieves the account number.
	 * @return int The account number.
	 */
	int getNumber() const {
		return number;
	}

	/**
	 * @brief Retrieves the account description.
	 * @return const std::string& The account description.
	 */
	const std::string& getDescription() const {
		return description;
	}

	/**
	 * @brief Retrieves the current account balance.
	 * @return double The account balance.
	 */
	double getBalance() const {
		return balance;
	}

	/**
	 * @brief Retrieves the list of transactions associated with the account.
	 * @return const std::vector<Transaction>& The list of transactions.
	 */
	const std::vector<Transaction>& getTransactions() const {
		return transactions;
	}

	/**
	 * @brief Adds a transaction to the account.
	 *
	 * @param t The transaction to add.
	 * @post The transaction is appended to the transactions vector, and the balance is updated accordingly.
	 */
	void addTransaction(const Transaction& t);

	/**
	 * @brief Removes a transaction from the account.
	 *
	 * @param index The index of the transaction to remove (0-based).
	 * @pre The index must be valid (0 <= index < transactions.size()).
	 * @post The specified transaction is removed from the transactions vector.
	 */
	void removeTransaction(size_t index);

	/**
	 * @brief Updates the account balance based on a transaction type.
	 *
	 * @param amount The amount to update the balance by.
	 * @param type The type of transaction ('D' for debit, 'C' for credit).
	 * @pre The type must be either 'D' or 'C'.
	 * @post The balance is incremented (credit) or decremented (debit) by the specified amount.
	 */
	void updateBalance(double amount, char type);

	/**
	 * @brief Overloads the insertion operator for printing account details.
	 *
	 * @param os The output stream.
	 * @param acc The account to print.
	 * @return std::ostream& The updated output stream.
	 * @details Prints the account number, description, balance, and transaction count.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Account& acc);
};

#endif
