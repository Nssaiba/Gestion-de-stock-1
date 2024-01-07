#ifndef AJOUTERPRODUIT_H
#define AJOUTERPRODUIT_H

#include <QDialog>
#include"Databaseheader.h"
namespace Ui {
class AjouterProduit;
}

class AjouterProduit : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterProduit(QWidget *parent = nullptr);
    ~AjouterProduit();

private slots:
    void on_btnSave1_clicked();

    void on_btnReset1_clicked();

private:
    Ui::AjouterProduit *ui;
    void resetElements();
};

#endif // AJOUTERPRODUIT_H
