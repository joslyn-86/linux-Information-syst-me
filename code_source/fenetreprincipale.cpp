#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

#include <QProcess>
#include <QDateTime>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>

// ═══════════════════════════════════════════════════════════
//  Constructeur / Destructeur
// ═══════════════════════════════════════════════════════════
FenetrePrincipale::FenetrePrincipale(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    // Connexion bouton actualiser
    connect(ui->boutonActualiser, &QPushButton::clicked,
            this, &FenetrePrincipale::surBoutonActualiser);

    // Minuterie auto-refresh (5 secondes)
    minuterie = new QTimer(this);
    connect(minuterie, &QTimer::timeout, this, &FenetrePrincipale::actualiser);
    minuterie->start(5000);

    // Chargement initial
    actualiser();

    // Animation d'entrée
    QTimer::singleShot(60, this, &FenetrePrincipale::animerCartes);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

// ═══════════════════════════════════════════════════════════
//  Slots
// ═══════════════════════════════════════════════════════════
void FenetrePrincipale::surBoutonActualiser()
{
    actualiser();
}

void FenetrePrincipale::actualiser()
{
    // Système
    ui->valeurNomMachine->setText(getinfoNomMachine());
    ui->valeurSysteme->setText(getinfoSysteme());
    ui->valeurTempsActivite->setText(getinfoTempsActivite());

    // CPU / Processus
    ui->valeurCpuNoyaux->setText(getinfoCpuNoyaux() + tr(" cœurs"));
    ui->valeurArchitecture->setText(getinfoArchitecture() + "-bit");
    ui->valeurProcessus->setText(getinfoProcessus() + tr(" actifs"));

    // RAM
    majCarteRam();

    // Disque
    majCarteDique();

    // Réseau / Paquets
    ui->valeurPaquets->setText(getinfoPaquets() + tr(" installés"));
    ui->valeurAdresseIP->setText(getinfoAdresseIP());

    // Horodatage
    ui->labelDerniereMaj->setText(
        tr("Dernière mise à jour : ") +
        QDateTime::currentDateTime().toString("hh:mm:ss")
    );
}

void FenetrePrincipale::majCarteRam()
{
    ui->valeurRamTotal->setText(getinfoRamTotal() + " Go");
    ui->valeurRamDisponible->setText(getinfoRamDisponible() + " Mo disponibles");

    QString pct = getinfoRamPourcentage();
    if (!pct.isEmpty()) {
        int val = pct.toInt();
        ui->barreRam->setValue(val);
        // Couleur dynamique via stylesheet
        QString couleur;
        if (val < 60)       couleur = "#56d364";   // vert
        else if (val < 85)  couleur = "#e3b341";   // jaune
        else                couleur = "#f85149";   // rouge
        ui->barreRam->setStyleSheet(
            QString("QProgressBar::chunk { background: %1; border-radius: 3px; }").arg(couleur)
        );
    }
}

void FenetrePrincipale::majCarteDique()
{
    ui->valeurDiqueTaille->setText(getinfoDiqueTaille());
    ui->valeurDiqueUtilise->setText(getinfoDiqueUtilise() + tr(" utilisés"));
    ui->valeurDiqueLibre->setText(getinfoDiqueLibre() + tr(" libres"));

    QString pct = getinfoDiquePourcentage();
    if (!pct.isEmpty()) {
        int val = pct.toInt();
        ui->barreDique->setValue(val);
        QString couleur;
        if (val < 70)       couleur = "#56d364";
        else if (val < 90)  couleur = "#e3b341";
        else                couleur = "#f85149";
        ui->barreDique->setStyleSheet(
            QString("QProgressBar::chunk { background: %1; border-radius: 3px; }").arg(couleur)
        );
    }
}

void FenetrePrincipale::animerCartes()
{
    // Liste des widgets à animer (cadres des cartes)
    QList<QWidget*> cartes = {
        ui->carteSysteme,
        ui->carteCpu,
        ui->carteRam,
        ui->carteDique,
        ui->carteReseau
    };

    for (int i = 0; i < cartes.size(); ++i) {
        auto *effet = new QGraphicsOpacityEffect(cartes[i]);
        cartes[i]->setGraphicsEffect(effet);
        effet->setOpacity(0.0);

        auto *anim = new QPropertyAnimation(effet, "opacity", this);
        anim->setDuration(400);
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
        anim->setEasingCurve(QEasingCurve::OutCubic);

        QTimer::singleShot(i * 80, anim, [anim]() { anim->start(); });
    }
}

// ═══════════════════════════════════════════════════════════
//  Commande système générique
// ═══════════════════════════════════════════════════════════
QString FenetrePrincipale::lancerCommande(const QString &commande)
{
    QProcess proc;
    proc.start("bash", {"-c", commande});
    proc.waitForFinished(3000);
    return proc.readAllStandardOutput().trimmed();
}

// ═══════════════════════════════════════════════════════════
//  getinfo — fonctions de collecte
// ═══════════════════════════════════════════════════════════
QString FenetrePrincipale::getinfoNomMachine()
{
    return lancerCommande("hostname");
}

QString FenetrePrincipale::getinfoSysteme()
{
    QString os = lancerCommande("lsb_release -d 2>/dev/null | cut -f2");
    if (os.isEmpty())
        os = lancerCommande("uname -o");
    return os;
}

QString FenetrePrincipale::getinfoTempsActivite()
{
    return lancerCommande("uptime -p");
}

QString FenetrePrincipale::getinfoCpuNoyaux()
{
    return lancerCommande("nproc");
}

QString FenetrePrincipale::getinfoArchitecture()
{
    return lancerCommande("getconf LONG_BIT");
}

QString FenetrePrincipale::getinfoProcessus()
{
    return lancerCommande("ps -e --no-headers | wc -l");
}

QString FenetrePrincipale::getinfoRamTotal()
{
    return lancerCommande("free -g | awk '/^Mem:/ {print $2}'");
}

QString FenetrePrincipale::getinfoRamDisponible()
{
    return lancerCommande("free -m | awk '/^Mem:/ {print $7}'");
}

QString FenetrePrincipale::getinfoRamPourcentage()
{
    // pourcentage utilisé
    QString total = lancerCommande("free -m | awk '/^Mem:/ {print $2}'");
    QString dispo  = lancerCommande("free -m | awk '/^Mem:/ {print $7}'");
    if (total.isEmpty() || total == "0") return {};
    int t = total.toInt(), d = dispo.toInt();
    return QString::number(qRound(100.0 * (t - d) / t));
}

QString FenetrePrincipale::getinfoDiqueTaille()
{
    return lancerCommande("df -h / | awk 'NR==2 {print $2}'");
}

QString FenetrePrincipale::getinfoDiqueUtilise()
{
    return lancerCommande("df -h / | awk 'NR==2 {print $3}'");
}

QString FenetrePrincipale::getinfoDiqueLibre()
{
    return lancerCommande("df -h / | awk 'NR==2 {print $4}'");
}

QString FenetrePrincipale::getinfoDiquePourcentage()
{
    return lancerCommande("df / | awk 'NR==2 {gsub(/%/,\"\",$5); print $5}'");
}

QString FenetrePrincipale::getinfoPaquets()
{
    QString n = lancerCommande("dpkg-query -l 2>/dev/null | grep '^ii' | wc -l");
    if (n.isEmpty() || n == "0")
        n = lancerCommande("rpm -qa 2>/dev/null | wc -l");
    if (n.isEmpty() || n == "0")
        return tr("N/D");
    return n;
}

QString FenetrePrincipale::getinfoAdresseIP()
{
    return lancerCommande("hostname -I 2>/dev/null | cut -d' ' -f1");
}
