//fichier "un-wcmc-dbms.cpp"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textfile.h>
#include "un-wcmc-dbms.h"

//macro qui remplace la fonction "main" en quelque sorte
IMPLEMENT_APP(UnWcmcDbms)

//initialisation de l'application
bool UnWcmcDbms::OnInit() {
    //creation de l'instance de la fenetre principale
    const wxString Titre("UN World Conservation Monitoring Centre DBMS"); 
    
    TabFrame *frame = new TabFrame(Titre, 50, 50, 450, 300);
    
    //affichage du frame (la fenetre)
    frame->Show(TRUE);

    //mise en avant du frame comme fenetre principal
    SetTopWindow(frame);

    //retourne "true" si tout s'est bien deroule
    return true;
}

TabFrame::TabFrame(const wxString titre, int xpos, int ypos, int width, int height):wxFrame((wxFrame *) NULL, -1, titre, wxPoint(xpos, ypos), wxSize(width, height)) {
    //initialisation du pointeur pour la grille
    grid = (wxGrid *) NULL;
    file = (wxFile *) NULL;

    const wxString NomFichier("data_wcmc.txt");
    grid = new wxGrid(this, -1, wxDefaultPosition, wxDefaultSize);
    file = new wxFile(NomFichier, wxFile::read_write);
}

TabFrame::~TabFrame() {}