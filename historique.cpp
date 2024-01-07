#include "historique.h"
#include "ui_historique.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
Historique::Historique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Historique)
{
    ui->setupUi(this);
}

Historique::~Historique()
{
    delete ui;
}

void Historique::on_btnHistorique_clicked()
{
    QString sValue = ui->txtHistorique->text();
    QString sCriteriaColum = "";

    if (ui->radioId->isChecked())
        sCriteriaColum = "ProduitID";
    else if (ui->radioName->isChecked())
        sCriteriaColum = "Name";
    else if (ui->radioAll->isChecked())
        sCriteriaColum = "All";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

    if (!db.open())
    {
        qDebug() << "Database connection error: " << db.lastError().text();
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query(db);

    if (sCriteriaColum == "ProduitID")
        query.prepare("select * from EntreeStock where " + sCriteriaColum + " like '%" + sValue + "%'");
    else if (sCriteriaColum == "Name") {
        // Corrigé : Utilisation d'une sous-requête correcte
        query.prepare("select * from EntreeStock where ProduitID in (select Id from Produit where Name like '%" + sValue + "%')");
    }
    else if (sCriteriaColum == "All")
        query.prepare("select * from EntreeStock");

    if (!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
    {
        if (query.numRowsAffected() > 0)
            qDebug() << "== success query fetch() : " << query.lastQuery();
        else {
            qDebug() << " No record found ";
            qDebug() << " Query is : " << query.lastQuery();
        }
    }

    model->setQuery(query);
    ui->tableView->setModel(model);
    qDebug() << "rows are : " << model->rowCount();
    ui->tableView->show();

    // Répétez le processus pour la deuxième table (Sortie_Stock)
    query.clear();
    model = new QSqlQueryModel();

    if (sCriteriaColum == "ProduitID")
        query.prepare("select * from Sortie_Stock where " + sCriteriaColum + " like '%" + sValue + "%'");
    else if (sCriteriaColum == "Name") {
        // Corrigé : Utilisation d'une sous-requête correcte
        query.prepare("select * from Sortie_Stock where ProduitID in (select Id from Produit where Name like '%" + sValue + "%')");
    }
    else if (sCriteriaColum == "All")
        query.prepare("select * from Sortie_Stock");

    if (!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
    {
        if (query.numRowsAffected() > 0)
            qDebug() << "== success query fetch() : " << query.lastQuery();
        else {
            qDebug() << " No record found ";
            qDebug() << " Query is : " << query.lastQuery();
        }
    }

    model->setQuery(query);
    ui->tableView_2->setModel(model);
    qDebug() << "rows are : " << model->rowCount();
    ui->tableView_2->show();

    db.close();
}


