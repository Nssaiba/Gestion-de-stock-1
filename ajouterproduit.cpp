#include "ajouterproduit.h"
#include "ui_ajouterproduit.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

AjouterProduit::AjouterProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterProduit)
{
    ui->setupUi(this);
}

AjouterProduit::~AjouterProduit()
{
    delete ui;
}

void AjouterProduit::on_btnSave1_clicked()
{
    QString NomP = ui->txtNomProduit->text();
    QString prix = ui->txtPrixProduit->text();
    QString Quantite1 = ui->txtQuantiteProduit->text();
    QString description = ui->txtDescriptionProduit->toPlainText();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

    if (!db.open())
    {
        qDebug() << "Database connection error: " << db.lastError().text();
        return;
    }

    QSqlQuery query(db);

    // Use a parameterized query to prevent SQL injection
    query.prepare("INSERT INTO Produit (Name, Quantity, Description, SellingPrice) "
                  "VALUES (:Name, :Quantity, :Description, :SellingPrice)");

    query.bindValue(":Name", NomP);
    query.bindValue(":Quantity", Quantite1.toInt());  // Assuming Quantity is an integer
    query.bindValue(":Description", description);
    query.bindValue(":SellingPrice", prix);

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Add Item");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ui->lblInfo->setText("Item Added Successfully!");
            resetElements();
        }
        else
            qDebug() <<"Unable to Add new Item";
     }
    db.close();
}
void AjouterProduit::resetElements()
{
    ui->txtNomProduit->clear();
    ui->txtPrixProduit->clear();
    ui->txtQuantiteProduit->clear();
    ui->txtDescriptionProduit->clear();
}

void AjouterProduit::on_btnReset1_clicked()
{
    ui->txtNomProduit->clear();
    ui->txtPrixProduit->clear();
    ui->txtQuantiteProduit->clear();
    ui->txtDescriptionProduit->clear();

}
