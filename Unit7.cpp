//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit7.h"
#include "forestTree.h"
#include "Account.h"
#include "Transaction.h"
#include <FMX.TreeView.hpp> // For ListView and ListViewItem (FMX)
#include <Vcl.ComCtrls.hpp>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall TForm7::searchBtnClick(TObject *Sender)
{
    String accountNumStr = accountNumEdit->Text;
    if (accountNumStr.IsEmpty()) {
        ShowMessage("Please enter an account number.");
        return;
    }

    int accountNumber = accountNumStr.ToInt();
    auto account = forest.findAccount(accountNumber);

   if (account) {
    // Get the description and balance separately
    std::string description = account->getDescription();
    double balance = account->getBalance();

    // Step 1: Display account information in Text1
    String accountInfo = "Account Number: " + IntToStr(accountNumber) + "\n";

    accountInfo += "Balance: " + FloatToStr(balance) + " $";
    Text1->Text = accountInfo;


        // Step 2: Create a stream to hold the formatted account information and add it to the ListView
        std::ostringstream outputStream;
        forest.printAccountInformation(accountNumber, outputStream);

        // Split the output stream by new lines and add them as items in ListView
        std::istringstream inputStream(outputStream.str());
        std::string line;

        // Clear existing items in ListView
        ListView1->Items->Clear();

        // Add the root item for the account
        auto rootItem = ListView1->Items->Add();
        rootItem->Text = "Account: " + IntToStr(accountNumber);

        // Adding child nodes (sub-items) under the root item
        while (std::getline(inputStream, line)) {
            auto childItem = ListView1->Items->Add();
            childItem->Text = line.c_str(); // Display each line from the output stream as a child item
        }

        // Step 3: Display transactions in ListBox1
        const auto& transactions = account->getTransactions();
        if (transactions.empty()) {
            ShowMessage("No transactions available for this account.");
            return;
        }

        ListBox1->Clear();  // Clear any previous items in ListBox1
        for (size_t i = 0; i < transactions.size(); ++i) {
            const auto& t = transactions[i];
            ListBox1->Items->Add("Transaction " + IntToStr(static_cast<int>(i + 1)) + ": Amount " +
                                  t.getAmount() + ", Type: " +
                                  (t.getType() == 'D' ? "Debit" : "Credit"));
        }
    } else {
        ShowMessage("Account not found.");
        Text1->Text = "Account not found.";
    }
}



void __fastcall TForm7::ListView1ItemClick(TObject * const Sender, TListViewItem * const AItem)

{
  // Ensure the clicked item is valid
    if (!AItem) {
        ShowMessage("No Accounts Selected.");
        return;
    }

    // Get the text of the clicked item
	String itemText = AItem->Text;
    ShowMessage(itemText);

}
//---------------------------------------------------------------------------

void __fastcall TForm7::printBtnClick(TObject *Sender)
{
// Create and configure the SaveDialog
    if (SaveDialog1->Execute()) {
        // Get the selected file path from the SaveDialog
        String fileName = SaveDialog1->FileName;

        // Validate input from the account number edit field
        String accountNumStr = accountNumEdit->Text;
        if (accountNumStr.IsEmpty()) {
            ShowMessage("Please enter an account number.");
            return;
        }

        int accountNumber = accountNumStr.ToIntDef(-1); // Convert input to integer
        if (accountNumber == -1) {
            ShowMessage("Invalid account number format.");
            return;
        }

        // Convert fileName to std::string
        std::string stdFileName = AnsiString(fileName).c_str();

        // Call ForestTree::printAccountReport
        try {
            forest.printAccountReport(accountNumber, stdFileName); // Generate the report
            ShowMessage("Report saved to: " + fileName);
        } catch (const std::exception& e) {
            ShowMessage("Error generating the report: " + UnicodeString(e.what()));
        }
    } else {
        ShowMessage("File save operation canceled.");
    }
}
//---------------------------------------------------------------------------

