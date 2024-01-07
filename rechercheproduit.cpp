#include "rechercheproduit.h"
#include "ui_rechercheproduit.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
RechercheProduit::RechercheProduit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RechercheProduit),
    model(nullptr)
{
    ui->setupUi(this);
}

RechercheProduit::~RechercheProduit()
{
    delete ui;
     delete model;
}

void RechercheProduit::on_btnRechercheProduit_clicked()
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

    // Utilise une requête paramétrée pour éviter l'injection SQL
    query.prepare("SELECT * FROM Produit WHERE Name LIKE :NomP");
    query.bindValue(":NomP", "%" + NomP + "%");

    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError().text();
        return;
    }

    if (model == nullptr) {
        model = new QSqlQueryModel();
    }

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(3, 300);
    qDebug() << "rows are : " << model->rowCount();
    ui->tableView->show();
}

