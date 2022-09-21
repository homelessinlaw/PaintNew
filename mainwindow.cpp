//
// Created by Danil Sasnouski on 21.09.2022
//

#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QVBoxLayout>

class GraphRect;
class GraphEllipse;
class GraphTriangle;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new PaintWidget(this);
    ui->verticalLayout->addWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rectButton_clicked()
{
    widget->setFigure<GraphRect>();
    widget->setMouseTracking(false);
    widget->resetFlags();
}


void MainWindow::on_ellipseButton_clicked()
{
    widget->setFigure<GraphEllipse>();
    widget->setMouseTracking(false);
    widget->resetFlags();
}

void MainWindow::on_triangleButton_clicked()
{
    widget->setFigure<GraphTriangle>();
    widget->setMouseTracking(false);
    widget->resetFlags();
}

void MainWindow::on_lineButton_clicked()
{
    widget->setLine();
    widget->setMouseTracking(true);
    widget->resetFlags();
}

void MainWindow::on_deleteButton_clicked()
{
    widget->resetFlags();
    widget->setDeleteFlag();
}

void MainWindow::on_moveButton_clicked()
{
    widget->resetFlags();
    widget->setMoveFlag();
}

void MainWindow::on_saveButton_clicked()
{
    widget->saveData();
    widget->resetFlags();
}

void MainWindow::on_loadButton_clicked()
{
    widget->loadData();
    widget->resetFlags();
}
