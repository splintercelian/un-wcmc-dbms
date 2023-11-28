//fichier "un-wcmc-dbms.h"

#ifndef UN_WCMC_DBMS_H
#define UN_WCMC_DBMS_H

//declare l'application "un-wcmc-dbms"

class UnWcmcDbms : public wxApp {
    public:
        //methode "OnInit()" qui doit etre redefinie
        virtual bool OnInit();
};

#endif