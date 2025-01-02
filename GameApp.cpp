/**
 * @file GameApp.cpp
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 */

#include "pch.h"
#include "GameApp.h"
#include <MainFrame.h>


/**
 * Initialize the application.
 * @return
 */
bool GameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();


    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);


    return true;
}
