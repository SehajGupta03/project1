/**
 * @file MainFrame.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 * The top-level (main) frame of the application
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H


/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
};


#endif //MAINFRAME_H
