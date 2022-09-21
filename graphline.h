//
// Created by Danil Sasnouski on 21.09.2022
//

#pragma once

#include <QPainter>

class GraphItem;

class GraphLine
{
public:
    void draw(QPainter& painter);

    void setFirstItem(GraphItem* item);

    void setSecondItem(GraphItem* item);

    void setDeleteFlag();

    bool getDeleteFlag() const;

    GraphItem* getFirstItem() const;

    GraphItem* getSecondItem() const;

private:
    GraphItem *firstItem = nullptr;

    GraphItem *secondItem = nullptr;

    bool deleteLine = false;
};
