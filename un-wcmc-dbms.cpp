//fichier "un-wcmc-dbms.cpp"

#include <wx/wx.h>
#include "un-wcmc-dbms.h"

IMPLEMENT_APP(UnWcmcDbms)

bool UnWcmcDbms::OnInit() {
    wxFrame *frame = new wxFrame((wxFrame*) NULL, -1, "UN World Conservation Monitoring Centre DBMS");
    frame->Show(TRUE);
    SetTopWindow(frame);
    return true;
}