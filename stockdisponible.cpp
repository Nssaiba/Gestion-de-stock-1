#include "stockdisponible.h"
#include "ui_stockdisponible.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>

StockDisponible::StockDisponible(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockDisponible)
{
    ui->setupUi(this);
}

StockDisponible::~StockDisponible()
{
    delete ui;
}

void StockDisponible::on_btnStockDispo_clicked()
{
    // Récupère le nom du produit depuis l'interface utilisateur
    QString NomP = ui->txtNomPDispo->text();

    // Crée une connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

    // Vérifie si la connexion à la base de données est réussie
    if (!db.open())
    {
        qDebug() << "Database connection error: " << db.lastError().text();
        return;
    }

    // Utilise une requête paramétrée pour éviter l'injection SQL
    QSqlQuery query(db);
    query.prepare("SELECT Id, Name, Quantity FROM Produit WHERE Name LIKE :NomP");
    query.bindValue(":NomP", "%" + NomP + "%");

    // Exécute la requête
    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError().text();
        return;
    }

    // Crée un modèle de requête si nécessaire
    QSqlQueryModel *model = new QSqlQueryModel();

    // Configure le modèle avec la requête
    model->setQuery(query);

    // Configure la vue pour afficher le modèle
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 150);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 200);

    // Affiche le nombre de lignes dans la console de débogage
    qDebug() << "Rows count: " << model->rowCount();
}
