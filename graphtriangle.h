//
// Created by Danil Sasnouski on 21.09.2022
//

#pragma once

#include "graphitem.h"

class GraphTriangle final: public GraphItem
{
public:
    GraphTriangle();
    void draw(QPainter& paint) override;
    std::vector<QPoint> getCoordinatest() const override;
    bool isPointInFigure(QPoint point) const override;
};

