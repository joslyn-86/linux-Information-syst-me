#include <QApplication>
#include "fenetreprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("InfoSystème");
    app.setApplicationDisplayName("Informations Système");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("InfoSys");

    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
