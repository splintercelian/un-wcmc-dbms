//fichier "un-wcmc-dbms.h"

#ifndef UN_WCMC_DBMS_H
#define UN_WCMC_DBMS_H

//declare l'application "un-wcmc-dbms"
class UnWcmcDbms : public wxApp {
    public:
        //methode "OnInit()" qui doit etre redefinie
        virtual bool OnInit();
};

//classe pour la fenetre principale
class TabFrame : public wxFrame {
    public:
        //declaration des methodes publiques de la classe TabFrame
        TabFrame(const wxString titre, int xpos, int ypos, int width, int height); //constructeur
        void LoadData(const wxString& nomFichier); //pour charger les donnees d'un fichier dans le tableur
        void SaveData(const wxString& nomFichier); //pour sauvegarder les donnees du tableur dans un fichier
        ~TabFrame(); //destructeur
        
        //MENUS
        //menu Fichier | Ouvrir
        void OnFichierOuvrir(wxCommandEvent &event);
        //menu Fichier | Sauvegarder
        void OnFichierSauvegarder(wxCommandEvent &event);
        //menu Fichier | Quitter
        void OnFichierQuitter(wxCommandEvent &event);
        //menu Info | Apropos
        void OnInfoApropos(wxCommandEvent &event);

        //RUBAN D'ACTION
        //ruban Modifications | Insertion | InsererALaFin
        void InsertDataEnd(wxRibbonButtonBarEvent &event);
        //ruban Modifications | Insertion | InsererALaFin
        void InsertDataBeg(wxRibbonButtonBarEvent &event);
        //ruban Modifications | Insertion | InsererAuMilieu
        void InsertDataMid(wxRibbonButtonBarEvent &event);
        //ruban Modifications | Insertion | InsererAuMilieu
        void InsertDataFile(wxRibbonButtonBarEvent &event);
        //ruban Modifications | Suppression | SupprimerLigne
        void DeleteDataLine(wxRibbonButtonBarEvent &event);
        //ruban Modifications | Suppression | SupprimerBlocDeLignes
        void DeleteDataBlock(wxRibbonButtonBarEvent &event);
        //ruban Modifications | Selection | SelectionnerTout
        void SelectAll(wxRibbonButtonBarEvent &event);
        //ruban Modifications | Selection | SelectionnerTout
        void DeselectAll(wxRibbonButtonBarEvent &event);
        //ruban Recherches | Filtre | ParNom
        void FilterByName(wxRibbonButtonBarEvent &event);
        //ruban Recherches | Filtre | ParAnnee
        void FilterByYear(wxRibbonButtonBarEvent &event);
        //ruban Recherches | Filtre | ParPays
        void FilterByCountry(wxRibbonButtonBarEvent &event);
        //ruban Recherches | Filtre | Defiltrer
        void Unfilter(wxRibbonButtonBarEvent &event);
        //ruban Defaut | Aide | AfficherAide
        void GetHelp(wxRibbonBarEvent &event);
    private:
        //general
        wxGrid *grid;
        wxFile *file;
        
        //menus
        wxMenuBar *menuBar;
        wxMenu *fichierMenu;
        wxMenu *infoMenu;
        
        //ruban d'actions
        wxRibbonBar *ribbonBar;
        wxRibbonPage *modRibbonPage;
        wxRibbonPage *rechRibbonPage;
        wxRibbonPanel *modInsertRibbonPanel;
        wxRibbonPanel *modDeleteRibbonPanel;
        wxRibbonPanel *modSelectRibbonPanel;
        wxRibbonPanel *rechFilterRibbonPanel;
        wxRibbonButtonBar *modInsertRibbonButtonBar;
        wxRibbonButtonBar *modDeleteRibbonButtonBar;
        wxRibbonButtonBar *modSelectRibbonButtonBar;
        wxRibbonButtonBar *rechFilterRibbonButtonBar;
        
        //layout
        wxSizer *sizer;

        //structure d'enumeration pour les identifiants des menus
        enum {
            ID_QUITTER = 100,
            ID_OUVRIR,
            ID_SAUVEGARDER,
            ID_APROPOS,
            ID_INSERT_END,
            ID_INSERT_BEG,
            ID_INSERT_MID,
            ID_INSERT_FILE,
            ID_DELETE_LINE,
            ID_DELETE_BLOCK,
            ID_SELECT_ALL,
            ID_DESELECT_ALL,
            ID_FILTER_NAME,
            ID_FILTER_YEAR,
            ID_FILTER_COUNTRY,
            ID_FILTER_UNFILTER
        };
    protected:
        //declaration de la directive pour gerer les evenements via une table d'evenements
        DECLARE_EVENT_TABLE();
};

#endif