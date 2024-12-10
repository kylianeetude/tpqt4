#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <widget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;

    // Crée un QTableWidget pour afficher les résultats
    QTableWidget *tableWidget = new QTableWidget(&w);
    tableWidget->setGeometry(20, 20, 500, 300);  // Position et taille du tableau
    tableWidget->setColumnCount(3);  // Nombre de colonnes (3 : prénom , club et note )
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Prénom" << "Club"<< "Note");  // En-têtes de colonnes

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
            QString note = query.value(3).toString();
            // qDebug() << prenom << club << note;

            // Ajouter une nouvelle ligne dans le tableau
            tableWidget->insertRow(row);

            // Ajouter les données dans la ligne et les colonnes
            tableWidget->setItem(row, 0, new QTableWidgetItem(prenom));
            tableWidget->setItem(row, 1, new QTableWidgetItem(club));
            tableWidget->setItem(row, 2, new QTableWidgetItem(note));


            row++;  // Passer à la ligne suivante
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
