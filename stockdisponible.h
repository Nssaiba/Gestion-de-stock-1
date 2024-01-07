#ifndef STOCKDISPONIBLE_H
#define STOCKDISPONIBLE_H

#include <QDialog>
#include <QSqlQueryModel>
#include"Databaseheader.h"

namespace Ui {
class StockDisponible;
}

class StockDisponible : public QDialog
{
    Q_OBJECT

public:
    explicit StockDisponible(QWidget *parent = nullptr);
    ~StockDisponible();

private slots:
    void on_btnStockDispo_clicked();

private:
    Ui::StockDisponible *ui;
    QSqlQueryModel *model;
};

#endif // STOCKDISPONIBLE_H
