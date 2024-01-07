#ifndef SORTIESTOCK_H
#define SORTIESTOCK_H

#include <QDialog>
#include"Databaseheader.h"
namespace Ui {
class SortieStock;
}

class SortieStock : public QDialog
{
    Q_OBJECT

public:
    explicit SortieStock(QWidget *parent = nullptr);
    ~SortieStock();

private slots:
    void on_btnSave_clicked();

    void on_btnReset4_clicked();

private:
    Ui::SortieStock *ui;
    void resetElements();
};

#endif // SORTIESTOCK_H
