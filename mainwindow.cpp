#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QItemSelectionModel>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../GameDatabase/world.db");
    db.open();
    qDebug() << db.lastError().driverText();

    locations = new QSqlTableModel(this);
    locations->setTable("location");
    locations->select();
    locations->setHeaderData(1, Qt::Horizontal, "Název");
    locations->setHeaderData(2, Qt::Horizontal, "Potřebný level");
    ui->viewLocation->setModel(locations);
    ui->viewLocation->hideColumn(0);
    ui->viewLocation->setSelectionBehavior(QAbstractItemView::SelectRows);

    sublocations = new QSqlTableModel(this);
    sublocations->setTable("sublocation");
    sublocations->setHeaderData(2, Qt::Horizontal, "Název");
    ui->viewSublocation->setModel(sublocations);
    ui->viewSublocation->hideColumn(0);
    ui->viewSublocation->hideColumn(1);
    ui->viewSublocation->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}

