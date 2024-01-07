#include "ajouterfournisseur.h"
#include "ui_ajouterfournisseur.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

AjouterFournisseur::AjouterFournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterFournisseur)
{
    ui->setupUi(this);
}

AjouterFournisseur::~AjouterFournisseur()
{
    delete ui;
}

void AjouterFournisseur::on_btnSave2_clicked()
{
    QString NomF = ui->txtNomFournisseur->text();
    QString PrenomF = ui->txtPrenomFournisseur->text();
    QString TelephoneF = ui->txtTel->text();
    QString PaysF = ui->txtPaysFournisseur->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

    if (!db.open())
    {
        qDebug() << "Database connection error: " << db.lastError().text();
        return;
    }

    QSqlQuery query(db);

    query.prepare("INSERT INTO Fournisseur (Nom, prenom, Telephone, Pays) "
                  "VALUES (:Nom, :prenom, :Telephone, :Pays)");

    query.bindValue(":Nom", NomF);
    query.bindValue(":prenom", PrenomF);
    query.bindValue(":Telephone", TelephoneF);
    query.bindValue(":Pays", PaysF);

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Add Fournisseur");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ui->lblInfo->setText("Fournisseur Added Successfully!");
            resetElements();
        }
        else
            qDebug() <<"Unable to Add new fournisseur";
     }
    db.close();


}
void AjouterFournisseur::on_btnReset2_clicked()
{
    ui->txtNomFournisseur->clear();
    ui->txtPrenomFournisseur->clear();
    ui->txtTel->clear();
    ui->txtPaysFournisseur->clear();
}
void AjouterFournisseur::resetElements()
{
    ui->txtNomFournisseur->clear();
    ui->txtPrenomFournisseur->clear();
    ui->txtTel->clear();
    ui->txtPaysFournisseur->clear();
}


