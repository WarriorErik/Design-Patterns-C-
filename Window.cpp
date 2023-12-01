#include "Window.h"
#include <vector>
#include <memory>
#include <string>
#include <sstream>


template<typename T>
wxString toString(T val) 
{
	std::stringstream ss;
	ss << val;
	return ss.str();
}


enum {
	BUTTON_0 = 1000,
	BUTTON_1 = 1001,
	BUTTON_2 = 1002,
	BUTTON_3 = 1003,
	BUTTON_4 = 1004,
	BUTTON_5 = 1005,
	BUTTON_6 = 1006,
	BUTTON_7 = 1007,
	BUTTON_8 = 1008,
	BUTTON_9 = 1009,
	BUTTON_ADD = 1010,
	BUTTON_SUB = 1011,
	BUTTON_MUL = 1012,
	BUTTON_DIV = 1013,
	BUTTON_00 = 1014,
	BUTTON_CLR = 1015,
	BUTTON_RES = 1016,
	BUTTON_DECM = 1017,
	BUTTON_MOD = 1018
};



wxBEGIN_EVENT_TABLE(Window, wxFrame)

EVT_BUTTON(BUTTON_0, Window::OnButton0)
EVT_BUTTON(BUTTON_00, Window::OnButton00)
EVT_BUTTON(BUTTON_1, Window::OnButton1)
EVT_BUTTON(BUTTON_2, Window::OnButton2)
EVT_BUTTON(BUTTON_3, Window::OnButton3)
EVT_BUTTON(BUTTON_4, Window::OnButton4)
EVT_BUTTON(BUTTON_5, Window::OnButton5)
EVT_BUTTON(BUTTON_6, Window::OnButton6)
EVT_BUTTON(BUTTON_7, Window::OnButton7)
EVT_BUTTON(BUTTON_8, Window::OnButton8)
EVT_BUTTON(BUTTON_9, Window::OnButton9)
EVT_BUTTON(BUTTON_DECM, Window::OnDecm)
EVT_BUTTON(BUTTON_ADD, Window::OnAdd)
EVT_BUTTON(BUTTON_SUB, Window::OnSub)
EVT_BUTTON(BUTTON_MUL, Window::OnMul)
EVT_BUTTON(BUTTON_DIV, Window::OnDiv)
EVT_BUTTON(BUTTON_CLR, Window::OnClr)
EVT_BUTTON(BUTTON_RES, Window::OnRes)
EVT_BUTTON(BUTTON_MOD, Window::OnMod)






END_EVENT_TABLE()


Window::Window() : wxFrame(nullptr, wxID_ANY, "Calculator", wxPoint(200, 200), wxSize(500, 500)) {

	pTopBoxSizer = new wxBoxSizer(wxVERTICAL);
	pTopPanel = new wxPanel(this, wxID_ANY);
	//add TopPanel to TopBoxSizer with proportion = 1 and make it expand on frame resize
	//also add 0px border to all sides
	pTopBoxSizer->Add(pTopPanel, 1, wxEXPAND | wxALL, 1);

	//add the TopBoxSizer to this
	this->SetSizer(pTopBoxSizer);

	//sub sizer in which we will add child objects
	
	pSubBoxSizer = new wxBoxSizer(wxVERTICAL); //we will add new widgets vertically
	pTopPanel->SetSizer(pSubBoxSizer); 
	

	//text control for entering operations
	pTextCtrl = new wxTextCtrl(pTopPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_RIGHT);
	pTextCtrl->Bind(wxEVT_KEY_DOWN, &Window::OnKeypad, this); //this wont work in event table
	pTextCtrl->SetFocus();


	//horizontal sizer for TextControl
	pTextCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
	pTextCtrlSizer->Add(pTextCtrl, 1, wxRIGHT | wxLEFT | wxTOP, 10);
	//add this sizer to SubBoxSizer
	pSubBoxSizer->Add(pTextCtrlSizer, 0, wxEXPAND);



	//create buttons
	wxSize buttonSize = wxDefaultSize;
	pButtonClr = new wxButton(pTopPanel, BUTTON_CLR, "Clr", wxDefaultPosition, buttonSize);
	pButtonDiv = new wxButton(pTopPanel, BUTTON_DIV, "/", wxDefaultPosition, buttonSize);
	pButtonMul = new wxButton(pTopPanel, BUTTON_MUL, "x", wxDefaultPosition, buttonSize);
	pButtonMod = new wxButton(pTopPanel, BUTTON_MOD, "%", wxDefaultPosition, buttonSize);
	pButton00 = new wxButton(pTopPanel, BUTTON_00, "00", wxDefaultPosition, buttonSize);
	pButtonDecm = new wxButton(pTopPanel, BUTTON_DECM, ".", wxDefaultPosition, buttonSize);
	pButtonSub = new wxButton(pTopPanel, BUTTON_SUB, "-"); //these 3 buttons will be on the right side
	pButtonAdd = new wxButton(pTopPanel, BUTTON_ADD, "+");
	pButtonRes = new wxButton(pTopPanel, BUTTON_RES, "=");
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_0, "0", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_1, "1", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_2, "2", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_3, "3", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_4, "4", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_5, "5", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_6, "6", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_7, "7", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_8, "8", wxDefaultPosition, buttonSize)));
	Buttons.push_back(std::shared_ptr<wxButton>(new wxButton(pTopPanel, BUTTON_9, "9", wxDefaultPosition, buttonSize)));


	//add grid sizer for buttons
	pLeftKeypadSizer = new wxGridSizer(5, 4, 10, 10);
	pLeftKeypadSizer->Add(pButtonClr);
	pLeftKeypadSizer->Add(pButtonDiv);
	pLeftKeypadSizer->Add(pButtonMul);
	pLeftKeypadSizer->Add(pButtonMod);
	pLeftKeypadSizer->Add(Buttons[7].get());
	pLeftKeypadSizer->Add(Buttons[8].get());
	pLeftKeypadSizer->Add(Buttons[9].get());
	pLeftKeypadSizer->Add(Buttons[4].get());
	pLeftKeypadSizer->Add(Buttons[5].get());
	pLeftKeypadSizer->Add(Buttons[6].get());
	pLeftKeypadSizer->Add(Buttons[1].get());
	pLeftKeypadSizer->Add(Buttons[2].get());
	pLeftKeypadSizer->Add(Buttons[3].get());
	pLeftKeypadSizer->Add(pButton00);
	pLeftKeypadSizer->Add(Buttons[0].get());
	pLeftKeypadSizer->Add(pButtonDecm);


	//right keypad sizer for -/+/= buttons
	pRightKeypadSizer = new wxBoxSizer(wxVERTICAL);
	pRightKeypadSizer->Add(pButtonSub, 1, wxEXPAND | wxALL, 10);
	pRightKeypadSizer->Add(pButtonAdd, 2, wxEXPAND | wxALL, 10);
	pRightKeypadSizer->Add(pButtonRes, 2, wxEXPAND | wxALL, 10);

	//sizer for keypad
	pKeypadSizer = new wxBoxSizer(wxHORIZONTAL);
	pKeypadSizer->Add(pLeftKeypadSizer, 3, wxEXPAND | wxTOP, 10);
	pKeypadSizer->Add(pRightKeypadSizer, 1, wxEXPAND);

	//add KeypadSizer to SubBoxSizer
	pSubBoxSizer->Add(pKeypadSizer, 1, wxEXPAND);
	this->SetMinSize(pSubBoxSizer->GetMinSize());
	this->SetSize(pSubBoxSizer->GetSize());

	Centre();




}

Window::~Window() {


	



}


void Window::OnAdd(wxCommandEvent& event) {
	currentOperand = RIGHT_OPERAND;
	currentOperation = ADD;
	pTextCtrl->SetFocus();
}

void Window::OnSub(wxCommandEvent& event) {
	currentOperand = RIGHT_OPERAND;
	currentOperation = SUB;
	pTextCtrl->SetFocus();
}

void Window::OnMul(wxCommandEvent& event) {
	currentOperand = RIGHT_OPERAND;
	currentOperation = MUL;
	pTextCtrl->SetFocus();
}


void Window::OnMod(wxCommandEvent& event) {
	currentOperand = RIGHT_OPERAND;
	currentOperation = MOD;
	pTextCtrl->SetFocus();
}

void Window::OnDiv(wxCommandEvent& event) {
	currentOperand = RIGHT_OPERAND;
	currentOperation = DIV;
	pTextCtrl->SetFocus();
}

void Window::OnButton0(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('0');
	}
	else {
		rightOp.push_back('0');
	}
	UpdateRes();
}

void Window::OnButton1(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('1');
	}
	else {
		rightOp.push_back('1');
	}
	UpdateRes();
}

void Window::OnButton2(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('2');
	}
	else {
		rightOp.push_back('2');
	}
	UpdateRes();
}


void Window::OnButton3(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('3');
	}
	else {
		rightOp.push_back('3');
	}
	UpdateRes();
}

void Window::OnButton4(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('4');
	}
	else {
		rightOp.push_back('4');
	}
	UpdateRes();
}


void Window::OnButton5(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('5');
	}
	else {
		rightOp.push_back('5');
	}
	UpdateRes();
}

void Window::OnButton6(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('6');
	}
	else {
		rightOp.push_back('6');
	}
	UpdateRes();
}

void Window::OnButton7(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('7');
	}
	else {
		rightOp.push_back('7');
	}
	UpdateRes();
}

void Window::OnButton8(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('8');
	}
	else {
		rightOp.push_back('8');
	}
	UpdateRes();
}

void Window::OnButton9(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('9');
	}
	else {
		rightOp.push_back('9');
	}
	UpdateRes();
}

void Window::OnButton00(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp.push_back('0');
		leftOp.push_back('0');
	}
	else {
		rightOp.push_back('0');
		rightOp.push_back('0');
	}
	UpdateRes();
}

void Window::OnDecm(wxCommandEvent& event) {
	if (currentOperand == LEFT_OPERAND) {
		leftOp += ".";
	}
	else {
		rightOp += ".";
	}
	UpdateRes();
}

void Window::OnRes(wxCommandEvent& event) {
	if (currentOperand == RIGHT_OPERAND) {
		if (currentOperation == ADD) {
			result = stod(leftOp) + stod(rightOp);
		}
		else if (currentOperation == SUB) {
			result = stod(leftOp) - stod(rightOp);
		}
		else if (currentOperation == MUL) {
			result = stod(leftOp) * stod(rightOp);
		}		
		else {
			result = stod(leftOp) / stod(rightOp);
		}
		pTextCtrl->Clear();
		pTextCtrl->AppendText(toString(result));

		//reset operand and update the result as leftOp
		currentOperand = LEFT_OPERAND;
		leftOp = toString(result);
		rightOp.clear();
	}
	pTextCtrl->SetFocus();
}


void Window::OnClr(wxCommandEvent& event) {
	leftOp.clear();
	rightOp.clear();
	result = 0;
	pTextCtrl->Clear();
	pTextCtrl->SetFocus();
}


void Window::UpdateRes() {
	if (currentOperand == LEFT_OPERAND) {
		pTextCtrl->Clear();
		pTextCtrl->AppendText(toString(leftOp));
	}
	else {
		pTextCtrl->Clear();
		pTextCtrl->AppendText(toString(rightOp));
	}
	pTextCtrl->SetFocus();
}


void Window::OnKeypad(wxKeyEvent& event) {
	event.Skip(); //skip if we werent able to process the evt

	if (event.GetKeyCode() == WXK_NUMPAD0) OnButton0(e);
	else if (event.GetKeyCode() == WXK_NUMPAD1) OnButton1(e);
	else if (event.GetKeyCode() == WXK_NUMPAD2) OnButton2(e);
	else if (event.GetKeyCode() == WXK_NUMPAD3) OnButton3(e);
	else if (event.GetKeyCode() == WXK_NUMPAD4) OnButton4(e);
	else if (event.GetKeyCode() == WXK_NUMPAD5) OnButton5(e);
	else if (event.GetKeyCode() == WXK_NUMPAD6) OnButton6(e);
	else if (event.GetKeyCode() == WXK_NUMPAD7) OnButton7(e);
	else if (event.GetKeyCode() == WXK_NUMPAD8) OnButton8(e);
	else if (event.GetKeyCode() == WXK_NUMPAD9) OnButton9(e);
	else if (event.GetKeyCode() == WXK_NUMPAD_ADD) OnAdd(e);
	else if (event.GetKeyCode() == WXK_NUMPAD_SUBTRACT) OnSub(e);
	else if (event.GetKeyCode() == WXK_NUMPAD_MULTIPLY) OnMul(e);
	else if (event.GetKeyCode() == WXK_NUMPAD_DIVIDE) OnDiv(e);
	else if (event.GetKeyCode() == WXK_NUMPAD_DECIMAL) OnDecm(e);
	else if (event.GetKeyCode() == WXK_NUMPAD_ENTER || event.GetKeyCode() == WXK_RETURN) OnRes(e);
	else if (event.GetKeyCode() == WXK_BACK) {
		if (currentOperand == LEFT_OPERAND && leftOp.size()) leftOp.pop_back();
		else if (rightOp.size()) rightOp.pop_back();
		UpdateRes();
	}
}