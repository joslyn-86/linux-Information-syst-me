#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class FenetrePrincipale; }
QT_END_NAMESPACE

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = nullptr);
    ~FenetrePrincipale();

private slots:
    void actualiser();                      
    void surBoutonActualiser();            
    void animerCartes();                   

private:
    // ── commandes système ───────────────────
    QString lancerCommande(const QString &commande);

    // ── getinfo ─────────────────────────────
    QString getinfoNomMachine();
    QString getinfoSysteme();
    QString getinfoTempsActivite();
    QString getinfoCpuNoyaux();
    QString getinfoArchitecture();
    QString getinfoProcessus();
    QString getinfoRamTotal();
    QString getinfoRamDisponible();
    QString getinfoRamPourcentage();        // 0-100
    QString getinfoDiqueTaille();
    QString getinfoDiqueUtilise();
    QString getinfoDiqueLibre();
    QString getinfoDiquePourcentage();      // 0-100
    QString getinfoPaquets();
    QString getinfoAdresseIP();

    // ── mise à jour UI ──────────────────────
    void majCarteRam();
    void majCarteDique();

    Ui::FenetrePrincipale *ui;
    QTimer *minuterie;                     

#endif // FENETREPRINCIPALE_H
