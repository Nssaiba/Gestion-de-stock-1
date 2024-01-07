#ifndef RECHERCHEPRODUIT_H
#define RECHERCHEPRODUIT_H

#include <QDialog>
#include <QSqlQueryModel>
#include"Databaseheader.h"

namespace Ui {
class RechercheProduit;
}

class RechercheProduit : public QDialog
{
    Q_OBJECT

public:
    explicit RechercheProduit(QWidget *parent = nullptr);
    ~RechercheProduit();

private slots:
    void on_btnRechercheProduit_clicked();

private:
    Ui::RechercheProduit *ui;
    QSqlQueryModel *model;
};

#endif // RECHERCHEPRODUIT_H
