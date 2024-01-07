#ifndef ENTREESTOCK_H
#define ENTREESTOCK_H

#include <QDialog>
#include"Databaseheader.h"
namespace Ui {
class EntreeStock;
}

class EntreeStock : public QDialog
{
    Q_OBJECT

public:
    explicit EntreeStock(QWidget *parent = nullptr);
    ~EntreeStock();

private slots:
    void on_btnSave3_clicked();

    void on_btnReset3_clicked();

private:
    Ui::EntreeStock *ui;
    void resetElements();
};

#endif // ENTREESTOCK_H
