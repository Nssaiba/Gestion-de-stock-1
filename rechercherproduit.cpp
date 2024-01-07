#include "rechercherproduit.h"
#include "ui_rechercherproduit.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
RechercherProduit::RechercherProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RechercherProduit)
{
    ui->setupUi(this);
}

RechercherProduit::~RechercherProduit()
{
    delete ui;
    delete model;
}

void RechercherProduit::on_btnRechercheProduit_clicked()
{
    QString NomP = ui->txtRechercheProduit->text();


        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

        if (!db.open())
        {
            qDebug() << "Database connection error: " << db.lastError().text();
            return;
        }

        QSqlQuery query(db);

        // Use a parameterized query to prevent SQL injection
        query.prepare("select * from Produit where Name like '%"+NomP+"%'");
        query.exec();
        qDebug() << query.lastError().text() << query.lastQuery();
        if(model == NULL){

            model=new QSqlQueryModel();
        }


        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(1,200);
        ui->tableView->setColumnWidth(3,300);
        qDebug() << "rows are : " << model->rowCount();
        ui->tableView->show();
}
