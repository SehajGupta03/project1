/**
 * @file ids.h
 * @author Ethan Springer, Daksh Mehta, Sehaj Gupta, Lukas Schaefer, Jack McNamara
 *
 *
 */

#ifndef IDS_H
#define IDS_H
#include <wx/defs.h>

/// Member ids of the various data with different priority settings

enum IDs
{
	IDM_ADDANDGATE = wxID_HIGHEST + 1,
	IDM_ADDORGATE = wxID_HIGHEST + 2,
	IDM_ADDNOTGATE = wxID_HIGHEST + 3,
	IDM_ADDDFLIPFLOP = wxID_HIGHEST + 4,
	IDM_ADDSRFLIPFLOP = wxID_HIGHEST + 5,
	IDM_LEVEL_0 = wxID_HIGHEST + 6,
	IDM_LEVEL_1 = wxID_HIGHEST + 7,
	IDM_LEVEL_2 = wxID_HIGHEST + 8,
	IDM_LEVEL_3 = wxID_HIGHEST + 9,
	IDM_LEVEL_4 = wxID_HIGHEST + 10,
	IDM_LEVEL_5 = wxID_HIGHEST + 11,
	IDM_LEVEL_6 = wxID_HIGHEST + 12,
	IDM_CONTROL_POINTS = wxID_HIGHEST + 13,
	IDM_ADDNANDGATE = wxID_HIGHEST + 14,
	IDM_LEVEL_7 = wxID_HIGHEST + 15,
	IDM_LEVEL_8 = wxID_HIGHEST + 16,
};

#endif //IDS_H
