/**
 * @file Transaction.h
 * @brief Header file for the Transaction class.
 *
 * @details
 * Course : CSIS217 - Advanced Data Structures
 * Purpose : Declares the Transaction class, which represents a single financial transaction
 *           associated with an account.
 *
 * Features:
 * - Stores account number, transaction amount, and type (debit or credit).
 * - Provides accessors for retrieving transaction details.
 * - Overloads the `<<` operator for easy printing of transaction details.
 *
 * Authors : Mia
 *           Carmen
 * @date November 24th, 2024
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>

/**
 * @class Transaction
 * @brief Represents a financial transaction for an account.
 *
 * @details
 * Each transaction records the account number it is associated with,
 * the transaction amount, and the transaction type (either debit or credit).
 */
class Transaction {
private:
	int accountNumber; /**< The account number associated with the transaction */
	double amount;     /**< The transaction amount */
	char type;         /**< The transaction type ('D' for debit, 'C' for credit) */

public:
	/**
	 * @brief Constructor for Transaction.
	 * @param accNum The account number associated with the transaction.
	 * @param amt The transaction amount.
	 * @param t The type of the transaction ('D' for debit, 'C' for credit).
	 */
	Transaction(int accNum, double amt, char t)
		: accountNumber(accNum), amount(amt), type(t) {}

	/**
	 * @brief Retrieves the account number associated with the transaction.
	 * @return The account number as an integer.
	 */
	int getAccountNumber() const {
		return accountNumber;
	}

	/**
	 * @brief Retrieves the transaction amount.
	 * @return The transaction amount as a double.
	 */
	double getAmount() const {
		return amount;
	}

	/**
	 * @brief Retrieves the type of the transaction.
	 * @return A character representing the transaction type ('D' or 'C').
	 */
	char getType() const {
		return type;
	}

	/**
	 * @brief Overloads the stream insertion operator for Transaction.
	 * @param os The output stream to write to.
	 * @param t The Transaction object to print.
	 * @return The modified output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Transaction& t);
};

/**
 * @brief Overloaded stream insertion operator for Transaction.
 * @param os The output stream to write to.
 * @param t The Transaction object to print.
 * @return The modified output stream.
 */
inline std::ostream& operator<<(std::ostream& os, const Transaction& t) {
	os << "Account: " << t.accountNumber
	   << ", Amount: " << t.amount
	   << ", Type: " << (t.type == 'D' ? "Debit" : "Credit");
	return os;
}

#endif // TRANSACTION_H
