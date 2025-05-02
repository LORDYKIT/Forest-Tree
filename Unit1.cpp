//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>  // For using TText and other standard controls
#include <fstream>          // For file handling
#include <sstream>
#include "Unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

TForm1 *Form1;
ForestTree forest;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TForm1::MenuButtonClick(TObject *Sender)
{
forest.loadAccounts(forest, "C:\\Users\\Sky9x\\AppData\\Local\\Temp\\Rar$DRa1192.19364\\accountswithspace.txt");
// Check if Form2 is already created; if not, create it
	if (!Form3) {
		Application->CreateForm(__classid(TForm3), &Form3);
    }

    // Show Form2
	Form3->Show();

    // Optionally hide the current form
	this->Hide();  // Hides Form1 (optional)
}
//---------------------------------------------------------------------------





