#ifndef RECHERCHEFOURNISSEUR_H
#define RECHERCHEFOURNISSEUR_H

#include <QDialog>
#include <QSqlQueryModel>
#include"Databaseheader.h"
namespace Ui {
class RechercheFournisseur;
}

class RechercheFournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit RechercheFournisseur(QWidget *parent = nullptr);
    ~RechercheFournisseur();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RechercheFournisseur *ui;
    QSqlQueryModel *model;
};

#endif // RECHERCHEFOURNISSEUR_H
