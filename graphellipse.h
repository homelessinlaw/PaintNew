//
// Created by Danil Sasnouski on 21.09.2022
//

#pragma once

#include "graphitem.h"

class GraphEllipse final: public GraphItem
{
public:
    GraphEllipse();
    void draw(QPainter& painter) override;
    std::vector<QPoint> getCoordinatest() const override;
    bool isPointInFigure(QPoint point) const override;
};
