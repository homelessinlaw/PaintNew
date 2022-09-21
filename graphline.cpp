//
// Created by Danil Sasnouski on 21.09.2022
//

#include "graphline.h"

#include "graphitem.h"

void GraphLine::draw(QPainter &painter)
{
    painter.drawLine(firstItem->getCentre(), secondItem->getCentre());
}

void GraphLine::setFirstItem(GraphItem *item)
{
    firstItem = item;
}

void GraphLine::setSecondItem(GraphItem *item)
{
    secondItem = item;
}

GraphItem* GraphLine::getFirstItem() const
{
    return firstItem;
}

GraphItem* GraphLine::getSecondItem() const
{
    return secondItem;
}

void GraphLine::setDeleteFlag()
{
    deleteLine = true;
}

bool GraphLine::getDeleteFlag() const
{
    return deleteLine;
}
