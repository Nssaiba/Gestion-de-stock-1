#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("c:/Users/Dell/Gestion-des-stocks-MACS");
    int w=ui->label_Img->width();
    int h=ui->label_Img->height();
    ui->label_Img->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    ptrAjouterProduit=new AjouterProduit();
    ptrAjouterFournisseur= new AjouterFournisseur();
    ptrEntreeStock=new EntreeStock();
    ptrSortieStock=new SortieStock();
    ptrRechercheProduit=new RechercheProduit();
    ptrRechercheFournisseur=new RechercheFournisseur();
    ptrStockDisponible=new StockDisponible();
    ptrHistorique=new Historique();
}

MainWindow::~MainWindow()
{
    delete ptrAjouterProduit;
    delete ptrAjouterFournisseur;
    delete ptrEntreeStock;
    delete ptrSortieStock;
    delete ptrRechercheProduit;
    delete ptrRechercheFournisseur;
    delete ptrStockDisponible;
    delete ptrHistorique;
    delete ui;
}


void MainWindow::on_pushButton_9_clicked()
{
    ptrAjouterProduit->show();
}

void MainWindow::on_pushButton_clicked()
{
   ptrAjouterFournisseur->show();
}

void MainWindow::on_pushButton_8_clicked()
{
    ptrRechercheProduit->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    ptrRechercheFournisseur->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    ptrEntreeStock->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ptrSortieStock->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    ptrStockDisponible->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ptrHistorique->show();
}
