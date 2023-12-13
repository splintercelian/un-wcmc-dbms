//fichier "un-wcmc-dbms.cpp"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/artprov.h>
#include <wx/aui/aui.h>
#include "un-wcmc-dbms.h"

//macro qui remplace la fonction "main" en quelque sorte
IMPLEMENT_APP(UnWcmcDbms)

//initialisation de l'application
bool UnWcmcDbms::OnInit() {
    //creation de l'instance de la fenetre principale
    const wxString Titre("UN World Conservation Monitoring Centre DBMS"); 
    
    TabFrame *frame = new TabFrame(Titre, 50, 50, 900, 700);
    
    //affichage du frame (la fenetre)
    frame->Show(TRUE);

    //mise en avant du frame comme fenetre principal
    SetTopWindow(frame);

    //retourne "true" si tout s'est bien deroule
    return true;
}

TabFrame::TabFrame(const wxString titre, int xpos, int ypos, int width, int height):wxFrame(
                    (wxFrame *) NULL, -1, titre, wxPoint(xpos, ypos), wxSize(width, height), wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER) {
    //initialisation des pointeurs et variables
    const wxString nomFichier;

    //creation de l'instance de wxGrid
    grid = new wxGrid(this, -1, wxDefaultPosition, wxDefaultSize);

    //creation de la grille (la taille sera ajustee dynamiquement)
    grid->CreateGrid(0, 0);

    //creation des menus
    fichierMenu = new wxMenu;
    infoMenu = new wxMenu;
    //affectation des id et libelles au differents menus
    fichierMenu->Append(ID_OUVRIR, "&Ouvrir fichier");
    fichierMenu->Append(ID_SAUVEGARDER, "&Sauvergarder fichier");
    fichierMenu->AppendSeparator();
    fichierMenu->Append(ID_QUITTER, "&Quitter");
    infoMenu->Append(ID_APROPOS, "&A propos");
    //creation de la barre de menu et affectation des menus
    menuBar = new wxMenuBar;
    menuBar->Append(fichierMenu, "&Fichier");
    menuBar->Append(infoMenu, "&Info");
    //ajout de la barre de menu au cadre
    SetMenuBar(menuBar);

    //creation du ruban d'actions
    ribbonBar = new wxRibbonBar(this, -1, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE);
    //creation des pages du ruban
    dataRibbonPage = new wxRibbonPage(ribbonBar, wxID_ANY, wxT("Données"), wxNullBitmap);
    //creation des sections a l'interieur des pages du ruban
    dataRibbonPanel = new wxRibbonPanel(dataRibbonPage, wxID_ANY, wxT("Insertion"), wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    //creation des barres de bouton a l'interieur des sections
    dataRibbonButtonBar = new wxRibbonButtonBar(dataRibbonPanel);
    //ajout des boutons a l'interieur des barres
    dataRibbonButtonBar->AddButton(wxID_ANY, wxT("Insérer à la fin"), wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR, wxDefaultSize));
    //activer le ruban
    ribbonBar->Realize();

    //creation du layout
    sizer = new wxBoxSizer(wxVERTICAL);
    //ajout du ruban dans le layout
    sizer->Add(ribbonBar, 0, wxEXPAND);
    //ajout du tableau dans le layout
    sizer->Add(grid, 1, wxEXPAND);
    //activation du layout
    SetSizer(sizer);
}

TabFrame::~TabFrame() {}

void TabFrame::LoadData(const wxString& nomFichier) {
    //declaration et initialisation de variables
    wxTextFile fichier(nomFichier);
    wxString ligne;
    int row = 0;

    //si il existe deja des donnees dans la table on rajoute les nouvelles donnees a la suite
    if(grid->GetNumberRows() > 0)
        row = grid->GetNumberRows();

    //si le fichier ne s'ouvre pas -> envoi d'un message a l'utilisateur
    if(!fichier.Open()) {
        wxMessageBox("Impossible d'ouvrir le fichier", "Erreur", wxOK | wxICON_ERROR);
        return;
    }
    
    //boucle sur les lignes du fichier (lecture ligne par ligne)
    for(ligne = fichier.GetFirstLine(); !fichier.Eof(); ligne = fichier.GetNextLine()) {
        //separation de la ligne lue en morceaux representant les differents champs de la table
        wxStringTokenizer tokenizer(ligne, "\t", wxTOKEN_RET_EMPTY);

        //ajout d'une ligne dans la grille pour contenir les donnees de la ligne lue dans le fichier
        grid->AppendRows();

        //initialisation d'une variable colonne pour lister les champs recuperes
        int col = 0;

        //tant que des valeurs sont presentes ajout de la valeur suivante dans une nouvelle colonne
        while(tokenizer.HasMoreTokens()) {
            //recuperation de la valeur du champ
            wxString token = tokenizer.GetNextToken();

            //remplacement des guillemets par rien du tout
            token.Replace(wxT("\""), wxT(""));

            //ajout d'une colonne dans la grille pour contenir le champ, si il s'agit de la premiere ligne
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
    //declaration et initialisation des variables
    int ligne = 0, colonne = 0;
    wxString data = "";
    wxTextFile fichier;

    //creation d'un fichier
    fichier.Create(nomFichier);
    
    //boucle sur l'ensemble des cellules pour enregistrer les valeurs dans le fichier selon le format attendu
    for(ligne = 0; ligne < grid->GetNumberRows(); ligne++) { //boucle sur les lignes
        for(colonne = 0; colonne < grid->GetNumberCols(); colonne++) { //boucle sur les colonnes
            data += "\"" + grid->GetCellValue(ligne, colonne) + "\""; //ajout des guillemets a la valeur du champ
            //si il ne s'agit pas de la derniere colonne ajout d'une tabulation
            if(colonne != grid->GetNumberCols() - 1)
                data += "\t";
        }
        fichier.AddLine(data); //ajout ligne par ligne dans le fichier
        data = ""; //re-initialisation de data pour la prochaine ligne
    }
    //ecriture dans le fichier
    fichier.Write();
}

//implementation de la table pour la gestion des evenements
BEGIN_EVENT_TABLE(TabFrame, wxFrame)
    EVT_MENU(ID_OUVRIR, TabFrame::OnFichierOuvrir)
    EVT_MENU(ID_SAUVEGARDER, TabFrame::OnFichierSauvegarder)
    EVT_MENU(ID_QUITTER, TabFrame::OnFichierQuitter)
    EVT_MENU(ID_APROPOS, TabFrame::OnInfoApropos)
END_EVENT_TABLE()

//implementation des methodes de TabFrame liees aux differents menus
void TabFrame::OnFichierOuvrir(wxCommandEvent &event) {
    wxFileDialog *dlg = new wxFileDialog(this, "Ouvrir un fichier texte", "", "", 
    "Tous les fichiers(*.*)|*.*|Fichiers Textes(*.txt)|*.txt", wxFD_OPEN, wxDefaultPosition);
    if(dlg->ShowModal() == wxID_OK)
        LoadData(dlg->GetFilename());
    dlg->Destroy();
}
void TabFrame::OnFichierSauvegarder(wxCommandEvent &event) {
    wxFileDialog *dlg = new wxFileDialog(this, "Sauvegarder un fichier texte", "", "", 
    "Tous les fichiers(*.*)|*.*|Fichiers Textes(*.txt)|*.txt", wxFD_SAVE, wxDefaultPosition);
    if(dlg->ShowModal() == wxID_OK)
        SaveData(dlg->GetFilename());
    dlg->Destroy();
}
void TabFrame::OnFichierQuitter(wxCommandEvent &event) {
    wxMessageDialog *dlg = new wxMessageDialog(this, "Voulez-vous vraiment quitter le programme?", 
    "Boite de dialogue", wxYES_NO | wxNO_DEFAULT | wxCENTRE | wxICON_QUESTION, wxDefaultPosition);
    if(dlg->ShowModal() == wxID_NO)
        return;
    else
        Close(FALSE);
}
void TabFrame::OnInfoApropos(wxCommandEvent &event) {
    wxMessageDialog *dlg = new wxMessageDialog(this, "Gestionnaire de table de donnees basique", 
    "Message", wxOK | wxCENTRE | wxICON_INFORMATION, wxDefaultPosition);
    dlg->ShowModal();
    dlg->Destroy();
}