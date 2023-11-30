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
        TabFrame(const wxString titre, int xpos, int ypos, int width, int height);

        ~TabFrame();
    private:
        wxGrid *grid;
        wxFile *file;
};

#endif