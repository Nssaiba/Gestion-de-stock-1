#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ajouterfournisseur.h"
#include "ajouterproduit.h"
#include "entreestock.h"
#include "sortiestock.h"
#include "historique.h"
#include "rechercheproduit.h"
#include "recherchefournisseur.h"
#include "stockdisponible.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    AjouterProduit *ptrAjouterProduit;
    AjouterFournisseur *ptrAjouterFournisseur;
    EntreeStock *ptrEntreeStock;
    SortieStock *ptrSortieStock;
    Historique *ptrHistorique;
    RechercheProduit *ptrRechercheProduit;
    RechercheFournisseur  * ptrRechercheFournisseur;
    StockDisponible *ptrStockDisponible;
};
#endif // MAINWINDOW_H
