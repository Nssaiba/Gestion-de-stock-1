#ifndef AJOUTERFOURNISSEUR_H
#define AJOUTERFOURNISSEUR_H

#include <QDialog>
#include"Databaseheader.h"
namespace Ui {
class AjouterFournisseur;
}

class AjouterFournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterFournisseur(QWidget *parent = nullptr);
    ~AjouterFournisseur();

private slots:
    void on_btnSave2_clicked();

    void on_btnReset2_clicked();

private:
    Ui::AjouterFournisseur *ui;
    void resetElements();
};

#endif // AJOUTERFOURNISSEUR_H
