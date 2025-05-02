#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include "forestTree.h"
#include "Account.h"
#include "Transaction.h"
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TreeView.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Dialogs.hpp>
#include "Unit4.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TLabel *welcomeLbl;
	TButton *addAccountBtn;
	TButton *SearchBtn;
	TButton *addTransactionBtn;
	TButton *deleteTransactionBtn;
	TSaveDialog *SaveDialog1;
	void __fastcall addAccountBtnClick(TObject *Sender);
	void __fastcall backBtnClick(TObject *Sender);
	void __fastcall addTransactionBtnClick(TObject *Sender);
	void __fastcall deleteTransactionBtnClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif

