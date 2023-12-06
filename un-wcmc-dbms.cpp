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
    const wxString nomFichier = "C:/Temp/un-wcmc-dbms/data_wcmc.txt";

    //creation de l'instance de wxGrid
    grid = new wxGrid(this, -1, wxDefaultPosition, wxDefaultSize);

    //creation de la grille (la taille sera ajustee dynamiquement)
    grid->CreateGrid(0, 0);

    //chargement des donnees
    LoadData(nomFichier);

    //fait dodo
    Sleep(1000);

    //sauvegarde des donnees
    SaveData(wxT("saveTest.txt"));
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

        //ajout d'une ligne dans la grille pour contenir les donnees de la ligne lue dans le fichier
        grid->AppendRows();

        //initialisation d'une variable colonne pour lister les champs recuperes
        int col = 0;

        while(tokenizer.HasMoreTokens()) {
            //recuperation de la valeur du champ
            wxString token = tokenizer.GetNextToken();

            //remplacement des guillemets par rien du tout
            token.Replace(wxT("\""), wxT(""));

            //ajout d'une colonne dans la grille pour contenir le champ si il s'agit de la premiere ligne
            if(row == 0)
                grid->AppendCols();

            //mise en place du champ dans la grille et passage au champ suivant
            grid->SetCellValue(row, col, token);

            //passage a la colonne suivante
            col++;
        }

        //passage a la ligne suivante
        row++;
    }

    //fermeture du fichier
    fichier.Close();
}

void TabFrame::SaveData(const wxString& nomFichier) {
    int ligne = 0, colonne = 0;
    wxString data = "";
    wxTextFile fichier;
    fichier.Create(nomFichier);
    for(ligne = 0; ligne < grid->GetNumberRows(); ligne++) {
        for(colonne = 0; colonne < grid->GetNumberCols(); colonne++) {
            data += "\"" + grid->GetCellValue(ligne, colonne) + "\"";
            if(colonne != grid->GetNumberCols() - 1)
                data += "\t";
        }
        fichier.AddLine(data);
        data = "";
    }
    fichier.Write();
}

TabFrame::~TabFrame() {}