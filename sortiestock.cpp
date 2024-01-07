#include "sortiestock.h"
#include "ui_sortiestock.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

SortieStock::SortieStock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortieStock)
{
    ui->setupUi(this);
}

SortieStock::~SortieStock()
{
    delete ui;
}

void SortieStock::on_btnSave_clicked()
{
    QString Produit = ui->txtSortieProd->text();
        int Quantite = ui->txtSortieQTE->text().toInt();
        QString date = ui->dateEdit->date().toString("yyyy-MM-dd");

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

        if (!db.open())
        {
            qDebug() << "Database connection error: " << db.lastError().text();
            return;
        }

        QSqlQuery query(db);

        // Vérifier si la quantité demandée en sortie est inférieure ou égale à la quantité en stock
        query.prepare("SELECT Quantity FROM Produit WHERE Id = :ProduitID");
        query.bindValue(":ProduitID", Produit);

        if (!query.exec())
        {
            qDebug() << "Select query error: " << query.lastError().text() << query.lastQuery();
            ui->lblInfo->setText("Unable to check stock quantity");
            db.close();
            return;
        }

        if (query.next())
        {
            int stockQuantity = query.value("Quantity").toInt();

            if (Quantite > stockQuantity)
            {
                qDebug() << "Insufficient stock quantity";
                ui->lblInfo->setText("Insufficient stock quantity");
                db.close();
                return;
            }
        }
        else
        {
            qDebug() << "Product not found in the database";
            ui->lblInfo->setText("Product not found in the database");
            db.close();
            return;
        }

        // Si la vérification de la quantité en stock réussit, procéder à la sortie de stock
        query.prepare("INSERT INTO Sortie_Stock (ProduitID, Quantite, DateSortie) "
                      "VALUES (:ProduitID, :Quantite, :DateSortie)");

        query.bindValue(":ProduitID", Produit);
        query.bindValue(":Quantite", Quantite);
        query.bindValue(":DateSortie", date);

        if (!query.exec())
        {
            qDebug() << "Insert query error: " << query.lastError().text() << query.lastQuery();
            ui->lblInfo->setText("Unable to Add Item");
            db.close();
            return;
        }

        // Mettre à jour la quantité en stock
        query.prepare("UPDATE Produit SET Quantity = Quantity - :Quantite WHERE Id = :ProduitID");
        query.bindValue(":ProduitID", Produit);
        query.bindValue(":Quantite", Quantite);

        if (!query.exec())
        {
            qDebug() << "Update query error: " << query.lastError().text() << query.lastQuery();
            ui->lblInfo->setText("Unable to Update Quantity");
            db.close();
            return;
        }

        qDebug() << "Item added successfully!";
        ui->lblInfo->setText("Item Added Successfully!");
        resetElements();

        db.close();
}

void SortieStock::resetElements()
{
    ui->txtSortieProd->clear();
    ui->txtSortieQTE->clear();
    ui->dateEdit->clear();

}
void SortieStock::on_btnReset4_clicked()
{
    ui->txtSortieProd->clear();
    ui->txtSortieQTE->clear();
    ui->dateEdit->clear();
}
