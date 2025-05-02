//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "forestTree.h"
#include "Account.h"
#include "Transaction.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::SubmitBtnClick(TObject *Sender)
{

	String accountNumStr = accountNumEdit->Text;
    String amountStr = amountEdit->Text;

    // Step 2: Validate the inputs
    if (accountNumStr.IsEmpty() || amountStr.IsEmpty()) {
        ShowMessage("Please fill in both account number and amount.");
        return;
    }

    // Convert account number and amount to integers
    int accountNumber = accountNumStr.ToInt();
    double amount = amountStr.ToDouble();

    if (accountNumber <= 0 || amount <= 0) {
        ShowMessage("Please enter a valid account number and amount.");
        return;
    }

    // Step 3: Check if a radio button is selected
    if (!Cbtn->IsChecked && !Dbtn->IsChecked) {
        ShowMessage("Please select either Credit or Debit.");
        return;
    }

    // Step 4: Create a Transaction object
    char transactionType = (Dbtn->IsChecked) ? 'D' : 'C';
    Transaction t(accountNumber, amount, transactionType); // Create the transaction

    // Step 5: Call the appropriate function based on the selected radio button
    try {
        if (Dbtn->IsChecked) {
            forest.addTransaction(accountNumber, t);
            ShowMessage("Transaction successfully added as Debit.");
        } else if (Cbtn->IsChecked) {
            forest.removeFromBalance(accountNumber, t);
            ShowMessage("Transaction successfully processed as Credit.");
        }
    } catch (const std::exception &ex) {
        // Handle any errors or exceptions thrown by addTransaction or removeFromBalance
        ShowMessage("Error: " + String(ex.what()));
	}

    try{
		std::ostringstream accountInfoStream;
		forest.printAccountInformation(accountNumber, accountInfoStream);

        // Set Memo1 text with the captured account information
        Memo1->Lines->Clear();
        Memo1->Lines->Add(accountInfoStream.str().c_str());

	} catch (const std::exception &ex) {
		// Handle any errors or exceptions thrown by addTransaction or removeFromBalance
		ShowMessage("Error: " + String(ex.what()));
	}
}
//---------------------------------------------------------------------------
