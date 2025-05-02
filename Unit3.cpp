#include <fmx.h>
#pragma hdrstop

#include "Unit3.h"
#include <FMX.DialogService.hpp>
#include "Unit4.h"
#include "Unit1.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}



void __fastcall TForm3::addAccountBtnClick(TObject *Sender)
{
  // Check if Form2 is already created; if not, create it
	if (!Form4) {
		Application->CreateForm(__classid(TForm4), &Form4);
    }

	// Show Form2
	Form4->Show();

}
//---------------------------------------------------------------------------

void __fastcall TForm3::backBtnClick(TObject *Sender)
{
		  // Check if Form2 is already created; if not, create it
	if (!Form1) {
		Application->CreateForm(__classid(TForm1), &Form1);
	}

	// Show Form2
	Form1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::addTransactionBtnClick(TObject *Sender)
{

	if (!Form5) {
		Application->CreateForm(__classid(TForm5), &Form5);
	}

	// Show Form5
	Form5->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::deleteTransactionBtnClick(TObject *Sender)
{

	if (!Form6) {
		Application->CreateForm(__classid(TForm6), &Form6);
	}

	// Show Form5
	Form6->Show();
}
//---------------------------------------------------------------------------



