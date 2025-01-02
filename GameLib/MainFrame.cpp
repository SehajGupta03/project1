/**
 * @file MainFrame.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"
#include <wx/icon.h>

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
	Create(nullptr, wxID_ANY, L"Sparty's Boots", wxDefaultPosition, wxSize(1200, 900));

	// Create a sizer that will lay out child windows vertically
	// one above each other
	auto sizer = new wxBoxSizer(wxVERTICAL);

	// Create the view class object as a child of MainFrame
	auto gameView = new GameView();
	gameView->Initialize(this);


	// Add it to the sizer
	sizer->Add(gameView, 1, wxEXPAND | wxALL);

	// Set the sizer for this frame
	SetSizer(sizer);

	// Layout (place) the child windows.
	Layout();

	auto menuBar = new wxMenuBar();

	/// Adding and binding the menu and its buttons
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);


	/// Different dropdown menus in the menu bar
	auto fileMenu = new wxMenu();
	auto helpMenu = new wxMenu();
	auto gateMenu = new wxMenu();
	auto levelMenu = new wxMenu();
	auto viewMenu = new wxMenu();

	// File menu options
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

	// Help menu options
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnHelp, this, wxID_ABOUT);
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	// View menu options
	viewMenu->Append(IDM_CONTROL_POINTS, "&Control Points", "Show control points", wxITEM_CHECK);

	// Level menu options
	levelMenu->Append(IDM_LEVEL_0, "&Level 0", "Load level 0");
	levelMenu->Append(IDM_LEVEL_1, "&Level 1", "Load level 1");
	levelMenu->Append(IDM_LEVEL_2, "&Level 2", "Load level 2");
	levelMenu->Append(IDM_LEVEL_3, "&Level 3", "Load level 3");
	levelMenu->Append(IDM_LEVEL_4, "&Level 4", "Load level 4");
	levelMenu->Append(IDM_LEVEL_5, "&Level 5", "Load level 5");
	levelMenu->Append(IDM_LEVEL_6, "&Level 6", "Load level 6");
	levelMenu->Append(IDM_LEVEL_7, "&Level 7", "Load level 7");
	levelMenu->Append(IDM_LEVEL_8, "&Level 8", "Load level 8");


	/// Adding the gate options in the menu bar
	gateMenu->Append(IDM_ADDANDGATE, L"&AND", L"Add an AND gate");
	gateMenu->Append(IDM_ADDORGATE, L"&OR", L"Add an OR gate");
	gateMenu->Append(IDM_ADDNOTGATE, L"&NOT", L"Add a Not gate");
	gateMenu->Append(IDM_ADDNANDGATE, L"&NAND", L"Add a Nand gate");

	/// flip flop menu options
	gateMenu->Append(IDM_ADDSRFLIPFLOP, L"&SR Flip flop", L"Add a SR Flip flop");
	gateMenu->Append(IDM_ADDDFLIPFLOP, L"&D Flip flop", L"Add a D Flip flop");

	/// Menu bar options
	menuBar->Append(fileMenu, L"&File");
	menuBar->Append(viewMenu, L"&View");
	menuBar->Append(levelMenu, L"&Level");
	menuBar->Append(gateMenu, L"&Gate");
	menuBar->Append(helpMenu, L"&Help");

	/// Displaying the menu bar on the window
	SetMenuBar(menuBar);

	/// Making a status bar
	CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

	SetIcon(wxIcon("SpartysBoots.ico", wxBITMAP_TYPE_ICO));
}

/**
 * Exit menuoption handler
 * @param event exit event handler
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

/**
 * Help menu option handler
 * @param event event handler for the help button
 */
void MainFrame::OnHelp(wxCommandEvent& event)
{
	wxMessageBox(L"Sparty's Boots",
				L"Sparty's Boots",
				wxOK,
				this);
}

