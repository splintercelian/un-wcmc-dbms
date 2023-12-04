//fichier "un-wcmc-dbms.cpp"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
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
    //initialisation des pointeurs et variables
    grid = (wxGrid *) NULL;
    const wxString nomFichier = "C:/Temp/un-wcmc-dbms/test.txt";

    //creation de l'instance de wxGrid
    grid = new wxGrid(this, -1, wxDefaultPosition, wxDefaultSize);

    //creation de la grille (la taille sera ajustee dynamiquement)
    grid->CreateGrid(3, 3);
    /*grid->SetCellValue(0, 0, "c1");
    grid->SetCellValue(0, 1, "c2");
    grid->SetCellValue(0, 2, "c3");
    grid->SetCellValue(1, 0, "v1");
    grid->SetCellValue(1, 1, "v2");
    grid->SetCellValue(1, 2, "v3");*/


    //chargement des donnees
    LoadData(nomFichier);
}

void TabFrame::LoadData(const wxString& nomFichier) {
    //initialisation de variables
    wxTextFile fichier(nomFichier);
    wxString ligne;
    int row = 0;

    if(!fichier.Open()) {
        wxMessageBox("Impossible d'ouvrir le fichier", "Erreur", wxOK | wxICON_ERROR);
        return;
    }
    
    for(ligne = fichier.GetFirstLine(); !fichier.Eof(); ligne = fichier.GetNextLine()) {
        //separation de la ligne lue en morceaux representant les differents champs de la table
        wxStringTokenizer tokenizer(ligne, "\t", wxTOKEN_RET_EMPTY);

        //initialisation d'une variable colonne pour lister les champs recuperes
        int col = 0;

        while(tokenizer.HasMoreTokens()) {
            //recuperation de la valeur du champ
            wxString token = tokenizer.GetNextToken();

            //mise en place du champ dans la grille et passage au champ suivant
            grid->SetCellValue(row, col, token);
            col++;
        }

        //verification de la taille de la grille et ajustement si necessaire (colonnes)
        if(col > grid->GetNumberCols())
            grid->AppendCols(col - grid->GetNumberCols());

        //passage a la ligne suivante
        row++;
    }

    //verification de la taille de la grille et ajustement si necessaire (lignes)
    if(row > grid->GetNumberRows())
        grid->AppendRows(row - grid->GetNumberRows());

    //fermeture du fichier
    fichier.Close();
}

TabFrame::~TabFrame() {}