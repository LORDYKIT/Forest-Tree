//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "forestTree.h"
#include "Account.h"
#include "Transaction.h"
#include "Unit6.h"
#include <FMX.Dialogs.hpp>  // This includes the TMsgDlgButton

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::getTransBtnClick(TObject *Sender)
{
   // Step 1: Get the account number from the input field (assumed to be a TEdit)
    String accountNumStr = accountNumEdit->Text;

    // Step 2: Validate input
    if (accountNumStr.IsEmpty()) {
        ShowMessage("Please enter an account number.");
        return;
    }

    int accountNumber = accountNumStr.ToInt();  // Convert the account number to integer

    // Step 3: Find the account and get transactions
    auto account = forest.findAccount(accountNumber);
    if (!account) {
        ShowMessage("Account not found.");
        return;
    }

    const auto& transactions = account->getTransactions();
    if (transactions.empty()) {
        ShowMessage("No transactions available for this account.");
        return;
    }

    // Step 4: Display transactions in the ListBox
    ListBox1->Clear();  // Clear any previous items
    for (size_t i = 0; i < transactions.size(); ++i) {
        const auto& t = transactions[i];
		ListBox1->Items->Add("Transaction " + IntToStr(static_cast<int>(i + 1)) + ": Amount " +
							 t.getAmount() + ", Type: " +
                              (t.getType() == 'D' ? "Debit" : "Credit"));
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm6::ListBox1Click(TObject *Sender)
{
 // Step 1: Get selected item index
    int selectedIndex = ListBox1->ItemIndex;
    if (selectedIndex == -1) {
        ShowMessage("No transaction selected.");
        return;
    }

    // Step 2: Get account number from input field
    String accountNumStr = accountNumEdit->Text;
    int accountNumber = accountNumStr.ToInt();

    auto account = forest.findAccount(accountNumber);
    if (!account) {
        ShowMessage("Account not found.");
        return;
    }

    const auto& transactions = account->getTransactions();

// // Step 3: Confirm deletion
//        if (MessageDlg("Are you sure you want to delete this transaction?",
//                       TMsgDlgType::mtConfirmation,
//                       TMsgDlgButtons() << TMsgDlgButton::mbYes << TMsgDlgButton::mbNo,
//					   0) == mrYes) {

        // Step 4: Remove the transaction (adjusting for 0-based index)
        forest.removeTransaction(accountNumber, selectedIndex);
        ShowMessage("Transaction deleted successfully.");

        // Step 5: Reload transactions in the list box
        ListBox1->Clear();  // Clear previous items
        for (size_t i = 0; i < transactions.size(); ++i) {
            const auto& t = transactions[i];
			ListBox1->Items->Add("Transaction " + IntToStr(static_cast<int>(i + 1)) + ": Amount " +
								  t.getAmount() + ", Type: " +
                                  (t.getType() == 'D' ? "Debit" : "Credit"));
        }
    }


//--------------------------------------------------------------------------
