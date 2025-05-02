//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::addBtnClick(TObject *Sender)
{
  

      try {
        // Retrieve input from the edit boxes
        String accountNumStr = accountNumEdit->Text;
        std::string description = AnsiString(descriptionEdit->Text).c_str(); // Convert UnicodeString to std::string

        // Convert account number to integer
        int accountNumber = accountNumStr.ToInt();

        // Validate description
        if (description.empty()) { // Correctly check for empty std::string
            ShowMessage("Description cannot be empty!");
            return;
        }

        // Attempt to add the account
		forest.addAccount(accountNumber, description);


        // Provide success feedback to the user
        ShowMessage("Account added successfully!");

    } catch (const Exception &e) {
        // Handle invalid input or other issues
        ShowMessage("Error: " + e.Message);
    } catch (const std::exception &ex) {
        // Handle standard exceptions
        ShowMessage("Error: " + String(ex.what()));
	}
}
//---------------------------------------------------------------------------
