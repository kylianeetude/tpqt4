#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "widgetgate.h"
#include "widgetstareditor.h"
#include "widgetstarrating.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;

    w.resize(800, 400);  // Ajuster la taille de la fenêtre

    // Crée un QTableWidget pour afficher les résultats
    QTableWidget *tableWidget = new QTableWidget(&w);
    tableWidget->setGeometry(20, 20, 760, 360);  // Position et taille du tableau
    tableWidget->setColumnCount(3);  // Nombre de colonnes : prénom, club et note
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Prénom" << "Club" << "Note");

    // Délégation pour afficher les étoiles dans la colonne "Note"
    tableWidget->setItemDelegateForColumn(2, new StarDelegate);

    // Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("test");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("etudiant");
    db.setPassword("Passciel2");

    if (db.open())
    {
        qDebug() << "Vous êtes maintenant connecté à " << db.hostName();
        QSqlQuery query;
        query.exec("SELECT * FROM `jeu`");

        int row = 0;
        while (query.next())
        {
            QString prenom = query.value(1).toString();
            QString club = query.value(2).toString();
            int note = query.value(3).toInt(); // Note récupérée comme entier

            // Ajouter une nouvelle ligne dans le tableau
            tableWidget->insertRow(row);

            // Ajouter les données dans les colonnes
            tableWidget->setItem(row, 0, new QTableWidgetItem(prenom));
            tableWidget->setItem(row, 1, new QTableWidgetItem(club));

            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::EditRole, QVariant::fromValue(StarRating(note)));
            tableWidget->setItem(row, 2, item);

            row++;
        }

        qDebug() << "Requête ok ! :)";
    }
    else
    {
        qDebug() << "La connexion a échoué, désolé";
    }

    w.show();
    return a.exec();
}
