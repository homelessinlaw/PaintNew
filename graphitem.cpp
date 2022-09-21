//
// Created by Danil Sasnouski on 21.09.2022
//

#include "graphitem.h"

GraphItem::GraphItem()
{

}
QPoint GraphItem::getCentre() const
{
    return { pos.x() + w/2, pos.y() + h/2 };
}

void GraphItem::setPos(QPoint point)
{
    pos = point;
}

void GraphItem::setSize(int width, int height)
{
    w = width;
    h = height;
}

QPoint GraphItem::getPos() const
{
    return pos;
}

int GraphItem::getH() const
{
    return h;
}

int GraphItem::getW() const
{
    return w;
}

void GraphItem::setOldPos(int x, int y)
{
    oldX = x;
    oldY = y;
}

QPoint GraphItem::getOldPos() const
{
    return { oldX, oldY };
}

GraphType GraphItem::getType() const
{
    return type;
}
