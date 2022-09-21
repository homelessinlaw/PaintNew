//
// Created by Danil Sasnouski on 21.09.2022
//

#include "graphellipse.h"

#include <math.h>

GraphEllipse::GraphEllipse()
{
    type = Ellipse;
}

void GraphEllipse::draw(QPainter& painter)
{
    painter.drawEllipse(pos.x(), pos.y(), w, h);
}

std::vector<QPoint> GraphEllipse::getCoordinatest() const
{
    return {};
}

bool GraphEllipse::isPointInFigure(QPoint point) const
{
    int localX = point.x() - getCentre().x();
    int localY = point.y() - getCentre().y();
    return (pow(localX,2) / pow((w/2),2) + pow(localY,2) / pow((h/2),2) <= 1);
}
