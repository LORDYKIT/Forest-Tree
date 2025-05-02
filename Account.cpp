/**
 * @file Account.cpp
 * @brief Implementation file for the Account class.
 *
 * @details
 * Course : CSIS217 - Advanced Data Structures
 * Purpose : Implements the methods of the Account class for managing account details,
 *           transactions, and balance updates.
 *
 * Features:
 * - Adding transactions and updating the balance accordingly
 * - Removing transactions by index
 * - Overloading the insertion operator for streamlined output
 *
 * @authors Mia
 *          Carmen
 * @date November 24th, 2024
 */

#include "Account.h"

/**
 * @brief Adds a transaction to the account and updates the balance if applicable.
 *
 * @param t The transaction to add.
 * @post The transaction is appended to the `transactions` vector, and if it is a debit
 *       transaction (`type == 'D'`), the account balance is updated accordingly.
 */
void Account::addTransaction(const Transaction& t) {
	transactions.push_back(t);

	// Update balance only for debit transactions
	if (t.getType() == 'D') {
		double amount = t.getAmount();
		char type = t.getType();
		updateBalance(amount, type);
	}
}

/**
 * @brief Removes a transaction from the account by its index.
 *
 * @param index The index of the transaction to remove (0-based).
 * @pre `index` must be valid: `0 <= index < transactions.size()`.
 * @post The specified transaction is removed from the `transactions` vector if the index is valid.
 */
void Account::removeTransaction(size_t index) {
	if (index < transactions.size()) {
		transactions.erase(transactions.begin() + index);
	}
}

/**
 * @brief Updates the account balance based on the transaction type.
 *
 * @param amount The amount to update the balance by.
 * @param type The type of transaction (`'D'` for debit, `'C'` for credit).
 * @pre The `type` must be either `'D'` or `'C'`.
 * @post The balance is incremented (for debit) or decremented (for credit) by the specified amount.
 */
void Account::updateBalance(double amount, char type) {
	if (type == 'D') {
		balance += amount;
	} else if (type == 'C') {
		balance -= amount;
	}
}

/**
 * @brief Overloads the insertion operator for printing account details.
 *
 * @param os The output stream to write to.
 * @param acc The account to print.
 * @return std::ostream& The updated output stream.
 *
 * @details Prints the account number, the first 10 characters of the account description,
 * and the account balance in a formatted manner.
 */
std::ostream& operator<<(std::ostream& os, const Account& acc) {
	os << acc.number << " "
	   << acc.description.substr(0, 10) << " "
	   << acc.balance;
	return os;
}
