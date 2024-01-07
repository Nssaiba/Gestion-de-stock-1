#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QDialog>
#include"Databaseheader.h"

namespace Ui {
class Historique;
}

class Historique : public QDialog
{
    Q_OBJECT

public:
    explicit Historique(QWidget *parent = nullptr);
    ~Historique();

private slots:
    void on_btnHistorique_clicked();

private:
    Ui::Historique *ui;
    QSqlQueryModel *model;
};

#endif // HISTORIQUE_H
