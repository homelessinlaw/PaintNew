//
// Created by Danil Sasnouski on 21.09.2022
//

#pragma once

#include <QMainWindow>

#include "graphitem.h"
#include "paintwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rectButton_clicked();

    void on_ellipseButton_clicked();

    void on_triangleButton_clicked();

    void on_lineButton_clicked();

    void on_deleteButton_clicked();

    void on_moveButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    PaintWidget *widget = nullptr;

};
