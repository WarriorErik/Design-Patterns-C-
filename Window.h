#pragma once
#include "wx/wx.h"
#include <vector>
#include <memory>

class Window : public wxFrame
{

	wxDECLARE_EVENT_TABLE();

protected:
	
	wxPanel* pTopPanel; //top panel
	wxBoxSizer* pTopBoxSizer, 
		* pSubBoxSizer, 
		* pTextCtrlSizer, 
		* pKeypadSizer, 
		* pRightKeypadSizer; //will contain buttons : -, + and result
	wxGridSizer* pLeftKeypadSizer; //sizer for our buttons 
	wxTextCtrl* pTextCtrl; 

	//buttons
	std::vector<std::shared_ptr<wxButton>> Buttons; //buttons for 0-9
	wxButton* pButtonAdd, * pButtonSub, * pButtonDiv, * pButtonMul, * pButtonMod, 
		* pButton00, * pButtonClr, * pButtonRes, * pButtonDecm;

	wxCommandEvent e; //empty event; in case

	double result = 0;
	std::string leftOp = "", rightOp = "";

	//current active operand
	enum Operand { LEFT_OPERAND, RIGHT_OPERAND };
	enum Operation { ADD, SUB, MUL, DIV, MOD };
	Operand currentOperand = LEFT_OPERAND;
	Operation currentOperation;

	void OnAdd(wxCommandEvent& event);
	void OnSub(wxCommandEvent& event);
	void OnDiv(wxCommandEvent& event);
	void OnMul(wxCommandEvent& event);
	void OnMod(wxCommandEvent& event);
	void OnClr(wxCommandEvent& event);
	void OnDecm(wxCommandEvent& event);
	void OnRes(wxCommandEvent& event);
	void OnButton0(wxCommandEvent& event);
	void OnButton1(wxCommandEvent& event);
	void OnButton2(wxCommandEvent& event);
	void OnButton3(wxCommandEvent& event);
	void OnButton4(wxCommandEvent& event);
	void OnButton5(wxCommandEvent& event);
	void OnButton6(wxCommandEvent& event);
	void OnButton7(wxCommandEvent& event);
	void OnButton8(wxCommandEvent& event);
	void OnButton9(wxCommandEvent& event);
	void OnButton00(wxCommandEvent& event);
	void UpdateRes();
	void OnKeypad(wxKeyEvent& event);

public:

	Window();
	~Window();
	


};

