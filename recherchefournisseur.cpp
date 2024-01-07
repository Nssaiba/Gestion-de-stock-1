#include "recherchefournisseur.h"
#include "ui_recherchefournisseur.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>

RechercheFournisseur::RechercheFournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RechercheFournisseur),
    model(nullptr)
{
    ui->setupUi(this);
}

RechercheFournisseur::~RechercheFournisseur()
{
    delete ui;
    delete model;
}

void RechercheFournisseur::on_pushButton_clicked()
{
    QString NomF = ui->lineEdit->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

    if (!db.open())
    {
        qDebug() << "Database connection error: " << db.lastError().text();
        return;
    }

    QSqlQuery query(db);

    // Use a parameterized query to prevent SQL injection
    query.prepare("SELECT * FROM Fournisseur WHERE Nom LIKE :NomF");
    query.bindValue(":NomF", "%" + NomF + "%");

    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError().text();
        return;
    }

    if (model == nullptr) {
        model = new QSqlQueryModel();
    }

    model->setQuery(query);
    ui->tableView->setModel(model);

    qDebug() << "rows are : " << model->rowCount();
    ui->tableView->show();
}
