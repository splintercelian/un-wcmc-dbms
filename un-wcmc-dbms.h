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
        //declaration des menus
        //menu Fichier | Ouvrir
        void OnFichierOuvrir(wxCommandEvent &event);
        //menu Fichier | Sauvegarder
        void OnFichierSauvegarder(wxCommandEvent &event);
        //menu Fichier | Quitter
        void OnFichierQuitter(wxCommandEvent &event);
        //menu Info | Apropos
        void OnInfoApropos(wxCommandEvent &event);
    private:
        wxGrid *grid;
        wxFile *file;
        wxMenuBar *menuBar;
        wxMenu *fichierMenu;
        wxMenu *infoMenu;
        wxRibbonBar *ribbonBar;
        wxRibbonPage *dataRibbonPage;
        wxRibbonPanel *dataRibbonPanel;
        wxRibbonButtonBar *dataRibbonButtonBar;
        wxSizer *sizer;

        //structure d'enumeration pour les identifiants des menus
        enum {
            ID_QUITTER = 100,
            ID_OUVRIR,
            ID_SAUVEGARDER,
            ID_APROPOS
        };
    protected:
        //declaration de la directive pour gerer les evenements via une table d'evenements
        DECLARE_EVENT_TABLE();
};

#endif