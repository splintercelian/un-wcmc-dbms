//fichier "un-wcmc-dbms.cpp"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/artprov.h>
#include <wx/utils.h>
#include "un-wcmc-dbms.h"

//macro qui remplace la fonction "main" en quelque sorte
IMPLEMENT_APP(UnWcmcDbms)

//initialisation de l'application
bool UnWcmcDbms::OnInit() {
    //creation de l'instance de la fenetre principale
    const wxString Titre("UN World Conservation Monitoring Centre DBMS"); 
    
    TabFrame *frame = new TabFrame(Titre, 50, 50, 1200, 700);
    
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
    fichierMenu->Append(ID_OUVRIR, wxT("&Ouvrir fichier\tCtrl+O"));
    fichierMenu->Append(ID_SAUVEGARDER, wxT("&Sauvergarder fichier\tCtrl+S"));
    fichierMenu->AppendSeparator();
    fichierMenu->Append(ID_QUITTER, wxT("&Quitter\tCtrl+Q"));
    infoMenu->Append(ID_APROPOS, wxT("&A propos\tCtrl+A"));
    //creation de la barre de menu et affectation des menus
    menuBar = new wxMenuBar;
    menuBar->Append(fichierMenu, "&Fichier");
    menuBar->Append(infoMenu, "&Info");
    //ajout de la barre de menu au cadre
    SetMenuBar(menuBar);

    //creation du ruban d'actions
    ribbonBar = new wxRibbonBar(this, -1, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE);
    //creation des pages du ruban
    modRibbonPage = new wxRibbonPage(ribbonBar, wxID_ANY, wxT("Modifications"), wxNullBitmap);
    rechRibbonPage = new wxRibbonPage(ribbonBar, wxID_ANY, wxT("Recherches"), wxNullBitmap);
    //creation des sections a l'interieur des pages du ruban
    modInsertRibbonPanel = new wxRibbonPanel(modRibbonPage, wxID_ANY, wxT("Insertion"), wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    modDeleteRibbonPanel = new wxRibbonPanel(modRibbonPage, wxID_ANY, wxT("Suppression"), wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    modSelectRibbonPanel = new wxRibbonPanel(modRibbonPage, wxID_ANY, wxT("Selection"), wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    rechFilterRibbonPanel = new wxRibbonPanel(rechRibbonPage, wxID_ANY, wxT("Filtre"), wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    //creation des barres de bouton a l'interieur des sections
    modInsertRibbonButtonBar = new wxRibbonButtonBar(modInsertRibbonPanel);
    modDeleteRibbonButtonBar = new wxRibbonButtonBar(modDeleteRibbonPanel);
    modSelectRibbonButtonBar = new wxRibbonButtonBar(modSelectRibbonPanel);
    rechFilterRibbonButtonBar = new wxRibbonButtonBar(rechFilterRibbonPanel);
    //ajout des boutons a l'interieur des barres
    modInsertRibbonButtonBar->AddButton(ID_INSERT_END, wxT("fin"), wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR, wxDefaultSize));
    modInsertRibbonButtonBar->AddButton(ID_INSERT_BEG, wxT("début"), wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR, wxDefaultSize));
    modInsertRibbonButtonBar->AddButton(ID_INSERT_MID, wxT("curseur"), wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR, wxDefaultSize));
    modInsertRibbonButtonBar->AddButton(ID_INSERT_FILE, wxT("fichier"), wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR, wxDefaultSize));
    modDeleteRibbonButtonBar->AddButton(ID_DELETE_LINE, wxT("ligne"), wxArtProvider::GetBitmap(wxART_DEL_BOOKMARK, wxART_TOOLBAR, wxDefaultSize));
    modDeleteRibbonButtonBar->AddButton(ID_DELETE_BLOCK, wxT("bloc"), wxArtProvider::GetBitmap(wxART_DEL_BOOKMARK, wxART_TOOLBAR, wxDefaultSize));
    modSelectRibbonButtonBar->AddButton(ID_SELECT_ALL, wxT("sél. tout"), wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR, wxDefaultSize));
    modSelectRibbonButtonBar->AddButton(ID_DESELECT_ALL, wxT("désél. tout"), wxArtProvider::GetBitmap(wxART_MINUS, wxART_TOOLBAR, wxDefaultSize));
    rechFilterRibbonButtonBar->AddButton(ID_FILTER_NAME, wxT("par nom"), wxArtProvider::GetBitmap(wxART_FIND, wxART_TOOLBAR, wxDefaultSize));
    rechFilterRibbonButtonBar->AddButton(ID_FILTER_YEAR, wxT("par année"), wxArtProvider::GetBitmap(wxART_FIND, wxART_TOOLBAR, wxDefaultSize));
    rechFilterRibbonButtonBar->AddButton(ID_FILTER_COUNTRY, wxT("par pays"), wxArtProvider::GetBitmap(wxART_FIND, wxART_TOOLBAR, wxDefaultSize));
    rechFilterRibbonButtonBar->AddButton(ID_FILTER_UNFILTER, wxT("défiltrer"), wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR, wxDefaultSize));
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

    //si il existe deja des donnees dans la table -> ajout des nouvelles donnees a la suite
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
            if(row == 0) {
                grid->AppendCols();
                switch(col) {
                    case 0 : 
                        grid->SetColLabelValue(col, wxT("Nom"));
                        grid->SetColSize(col, 400);
                        break;
                    case 1 :
                        grid->SetColLabelValue(col, wxT("Pays"));
                        break;
                    case 2 :
                        grid->SetColLabelValue(col, wxT("Latitude"));
                        break;
                    case 3 :
                        grid->SetColLabelValue(col, wxT("Longitude"));
                        break;
                    case 4 :
                        grid->SetColLabelValue(col, wxT("Superficie"));
                        break;
                    case 5 :
                        grid->SetColLabelValue(col, wxT("Année"));
                        break;
                }
            }

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
    EVT_RIBBONBUTTONBAR_CLICKED(ID_INSERT_END, TabFrame::InsertDataEnd)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_INSERT_BEG, TabFrame::InsertDataBeg)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_INSERT_MID, TabFrame::InsertDataMid)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_INSERT_FILE, TabFrame::InsertDataFile)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_DELETE_LINE, TabFrame::DeleteDataLine)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_DELETE_BLOCK, TabFrame::DeleteDataBlock)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_SELECT_ALL, TabFrame::SelectAll)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_DESELECT_ALL, TabFrame::DeselectAll)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_FILTER_NAME, TabFrame::FilterByName)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_FILTER_YEAR, TabFrame::FilterByYear)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_FILTER_COUNTRY, TabFrame::FilterByCountry)
    EVT_RIBBONBUTTONBAR_CLICKED(ID_FILTER_UNFILTER, TabFrame::Unfilter)
    EVT_RIBBONBAR_HELP_CLICK(wxID_ANY, TabFrame::GetHelp)
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

//implementation des methodes de TabFrame liees au ruban d'actions
void TabFrame::InsertDataEnd(wxRibbonButtonBarEvent &event) {
    grid->AppendRows();
}
void TabFrame::InsertDataBeg(wxRibbonButtonBarEvent &event) {
    grid->InsertRows();
}
void TabFrame::InsertDataMid(wxRibbonButtonBarEvent &event) {
    grid->InsertRows(grid->GetGridCursorRow());
}
void TabFrame::InsertDataFile(wxRibbonButtonBarEvent &event) {
    wxFileDialog *dlg = new wxFileDialog(this, "Ouvrir un fichier texte", "", "", 
    "Tous les fichiers(*.*)|*.*|Fichiers Textes(*.txt)|*.txt", wxFD_OPEN, wxDefaultPosition);
    if(dlg->ShowModal() == wxID_OK)
        LoadData(dlg->GetFilename());
    dlg->Destroy();
}
void TabFrame::DeleteDataLine(wxRibbonButtonBarEvent &event) {
    grid->DeleteRows(grid->GetGridCursorRow());
}
void TabFrame::DeleteDataBlock(wxRibbonButtonBarEvent &event) {
    wxArrayInt numRows = grid->GetSelectedRows();
    grid->DeleteRows(grid->GetGridCursorRow(), numRows.Count());
}
void TabFrame::SelectAll(wxRibbonButtonBarEvent &event) {
    grid->SelectAll();
}
void TabFrame::DeselectAll(wxRibbonButtonBarEvent &event) {
    grid->ClearSelection();
}
void TabFrame::FilterByName(wxRibbonButtonBarEvent &event) {
    wxString message;
    int col = 0;
    wxTextEntryDialog *dlg = new wxTextEntryDialog(this, wxT("Nom recherché : "), wxT("Entrez une valeur"));
    if(dlg->ShowModal() == wxID_OK) {
        message = dlg->GetValue();
        for(int row = 0; row < grid->GetNumberRows(); row++) {
            if(grid->GetCellValue(row, col) != message)
                grid->HideRow(row);
        }
    }
}
void TabFrame::FilterByYear(wxRibbonButtonBarEvent &event) {
    wxString message;
    int col = 5;
    wxTextEntryDialog *dlg = new wxTextEntryDialog(this, wxT("Année recherchée : "), wxT("Entrez une valeur"));
    if(dlg->ShowModal() == wxID_OK) {
        message = dlg->GetValue();
        for(int row = 0; row < grid->GetNumberRows(); row++) {
            if(grid->GetCellValue(row, col) != message)
                grid->HideRow(row);
        }
    }
}
void TabFrame::FilterByCountry(wxRibbonButtonBarEvent &event) {
    wxString message;
    int col = 1;
    wxTextEntryDialog *dlg = new wxTextEntryDialog(this, wxT("Pays recherché : "), wxT("Entrez une valeur"));
    if(dlg->ShowModal() == wxID_OK) {
        message = dlg->GetValue();
        for(int row = 0; row < grid->GetNumberRows(); row++) {
            if(grid->GetCellValue(row, col) != message)
                grid->HideRow(row);
        }
    }
}
void TabFrame::Unfilter(wxRibbonButtonBarEvent &event) {
    for(int row = 0; row < grid->GetNumberRows(); row++)
            grid->ShowRow(row);
}
void TabFrame::GetHelp(wxRibbonBarEvent &event) {
    wxLaunchDefaultBrowser(wxT("https://github.com/splintercelian/un-wcmc-dbms"));
}