#include "entreestock.h"
#include "ui_entreestock.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
EntreeStock::EntreeStock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntreeStock)
{
    ui->setupUi(this);
}

EntreeStock::~EntreeStock()
{
    delete ui;
}

void EntreeStock::on_btnSave3_clicked()
{
        QString Produit = ui->txtEntreePrN->text();
        QString Fournisseur = ui->txtEntreeFour->text();
        int Quantite = ui->txtEntreeQte->text().toInt();
        QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
        QString Prix = ui->txtPrixAchat->text();

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

        if (!db.open())
        {
            qDebug() << "Database connection error: " << db.lastError().text();
            return;
        }

        QSqlQuery query(db);

        // Utiliser une requête paramétrée pour éviter l'injection SQL
        query.prepare("INSERT INTO EntreeStock (ProduitID, FournisseurID, Quantite, DateEntree, PrixUnitaire) "
                      "VALUES (:ProduitID, :FournisseurID, :Quantite, :DateEntree, :PrixUnitaire)");

        query.bindValue(":ProduitID", Produit);
        query.bindValue(":FournisseurID", Fournisseur);
        query.bindValue(":Quantite", Quantite);
        query.bindValue(":DateEntree", date);
        query.bindValue(":PrixUnitaire", Prix);

        if (!query.exec())
        {
            qDebug() << "Insert query error: " << query.lastError().text() << query.lastQuery();
            ui->lblInfo->setText("Unable to Add Item");
            db.close();
            return;
        }

        // Utiliser une requête pour mettre à jour la quantité dans la table Produit
        query.prepare("UPDATE Produit SET Quantity = Quantity + :Quantite WHERE Id = :ProduitID");
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



void EntreeStock::on_btnReset3_clicked()
{
    ui->txtEntreePrN->clear();
    ui->txtEntreeFour->clear();
    ui->txtEntreeQte->clear();
    ui->dateEdit->clear();
    ui->txtPrixAchat->clear();
}

void EntreeStock::resetElements()
{
    ui->txtEntreePrN->clear();
    ui->txtEntreeFour->clear();
    ui->txtEntreeQte->clear();
    ui->dateEdit->clear();
    ui->txtPrixAchat->clear();
}
