//
// Created by Danil Sasnouski on 21.09.2022
//

#pragma once

#include <QWidget>
#include <memory>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QPair>
#include <QString>

#include "graphitem.h"
#include "graphrect.h"
#include "graphellipse.h"
#include "graphtriangle.h"
#include "graphline.h"
#include "graphpoint.h"

class PaintWidget final : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent);

    bool isPointInsideEllispse(int a, int b, int x, int y);

    void setLine();

    void setDeleteFlag();

    void resetFlags();

    void setMoveFlag();

    void deleteLine(GraphItem* item);

    void saveData();

    void loadData();

    QPair<int,int> getLink(GraphLine*) const;

    void setLinks(int first, int second, GraphLine*);

    template <typename T>
    void setFigure()
    {
        tempObj = new T();
    }

private:
    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *ev) override;

    void mouseReleaseEvent(QMouseEvent *ev) override;

    void mouseMoveEvent(QMouseEvent *ev) override;

    void keyPressEvent(QKeyEvent *ev) override;

    std::vector<std::unique_ptr<GraphItem>> objList;

    GraphItem* tempObj = nullptr;

    std::vector<std::unique_ptr<GraphLine>> lineList;

    std::unique_ptr<GraphLine> tempLine;

    bool deleteFlag = false;

    bool moveFlag = false;

    std::unique_ptr<GraphPoint> point;

    QJsonObject objData;

    QJsonObject lineData;

    QJsonObject finalData;

    QJsonDocument document;

    QString path = "test.json";
};

