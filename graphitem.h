//
// Created by Danil Sasnouski on 21.09.2022
//

#pragma once

#include <QPoint>
#include <QPainter>

enum GraphType {
    Ellipse,
    Triangle,
    Rectangle,
    Undefined
};

class GraphItem
{
public:
    GraphItem();

    QPoint getCentre() const;

    void setPos(QPoint point);

    void setSize(int width, int height);

    void setOldPos(int x, int y);

    GraphType getType() const;

    QPoint getOldPos() const;

    QPoint getPos() const;

    int getH() const;

    int getW() const;

    virtual void draw(QPainter& painter) = 0;

    virtual std::vector<QPoint> getCoordinatest() const = 0;

    virtual bool isPointInFigure(QPoint) const = 0;

    virtual ~GraphItem() = default;

protected:
    GraphType type = Undefined;

    QPoint pos;

    int w = 0;

    int h = 0;

    int oldX = 0;

    int oldY = 0;
};
