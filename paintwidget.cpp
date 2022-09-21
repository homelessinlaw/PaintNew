//
// Created by Danil Sasnouski on 21.09.2022
//

#include "paintwidget.h"

#include <qdebug.h>
#include <QMouseEvent>
#include <QJsonDocument>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy( Qt::StrongFocus );
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));

    for (auto& item: objList)
    {
        item->draw(painter);
    }

    for (auto it = lineList.begin(); it != lineList.end(); it++)
    {

        if((*it)->getDeleteFlag())
        {
           it = lineList.erase(it);
           it--;
           continue;
        }
        if((*it) != nullptr)
        {
            (*it)->draw(painter);
        }
    }

    if (tempObj != nullptr)
    {
        tempObj->draw(painter);
    }

    if (tempLine != nullptr && tempLine->getFirstItem() != nullptr)
    {
        tempLine->draw(painter);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::RightButton)
    {
        tempLine.reset();
        tempObj = nullptr;
        update();
    }

    if(deleteFlag)
    {
        for (auto it = objList.begin(); it != objList.end(); it++)
        {
            if ((*it)->isPointInFigure(ev->pos()))
            {
                deleteLine(it->get());
                it = objList.erase(it);
                deleteFlag = false;
                update();
                return;
            }
        }
    }
    if(moveFlag)
    {
        for (auto it = objList.begin(); it != objList.end(); it++)
        {
            if ((*it)->isPointInFigure(ev->pos()))
            {
                setCursor(Qt::OpenHandCursor);
                (*it)->setOldPos(ev->pos().x() - (*it)->getPos().x(), ev->pos().y() - (*it)->getPos().y());
                tempObj = it->get();
                return;
            }
        }
    }

    if(tempObj != nullptr)
    {
        tempObj->setPos(ev->pos());
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(tempLine != nullptr && tempLine->getFirstItem() != nullptr)
    {
        point->setPos(ev->pos());
        tempLine->setSecondItem(point.get());
        update();
    }

    if(moveFlag == true && tempObj != nullptr)
    {
        tempObj->setPos(QPoint(ev->pos().x() - tempObj->getOldPos().x(), ev->pos().y() - tempObj->getOldPos().y()));
        update();
        return;
    }

    if(tempObj == nullptr)
    {
        return;
    }

    tempObj->setSize(ev->pos().x() - tempObj->getPos().x(),ev->pos().y() - tempObj->getPos().y());
    update();

}

void PaintWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if(tempLine != nullptr)
    {
        for (auto it = objList.begin(); it != objList.end(); it++)
        {
            if ((*it)->isPointInFigure(ev->pos()))
            {
                if(tempLine->getFirstItem() == nullptr)
                {
                    tempLine->setFirstItem(it->get());
                    point = std::make_unique<GraphPoint>();
                    point->setPos(ev->pos());
                    tempLine->setSecondItem(point.get());
                    return;
                }

                tempLine->setSecondItem(it->get());

                if(tempLine->getFirstItem() == tempLine->getSecondItem())
                {
                    tempLine.reset();
                    return;
                }
                lineList.emplace_back(std::move(tempLine));
                update();
                return;
            }
        }

        if(tempLine->getSecondItem() == nullptr)
        {
            tempLine.reset();
            return;
        }

    }

    if(moveFlag == true && tempObj != nullptr)
    {
        moveFlag = false;
        tempObj->setOldPos(0,0);
        tempObj = nullptr;
        this->setCursor(Qt::ArrowCursor);
        return;
    }

    if(tempObj == nullptr)
    {
        return;
    }

    tempObj->setSize(ev->pos().x() - tempObj->getPos().x(),ev->pos().y() - tempObj->getPos().y());
    objList.emplace_back(tempObj);
    tempObj = nullptr;
}

void PaintWidget::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Escape)
    {
        tempLine.reset();
        tempObj = nullptr;
        moveFlag = false;
        deleteFlag = false;
        this->setCursor(Qt::ArrowCursor);
        update();
    }
}

void PaintWidget::setLine()
{
    tempLine = std::make_unique<GraphLine>();
}

void PaintWidget::setDeleteFlag()
{
    deleteFlag = true;
}

void PaintWidget::setMoveFlag()
{
    moveFlag = true;
}

void PaintWidget::deleteLine(GraphItem *item)
{
    for (auto& line : lineList)
    {
        if (line->getFirstItem() == item || line->getSecondItem() == item)
        {
            line->setDeleteFlag();
        }
    }
}

void PaintWidget::saveData()
{
    QJsonArray arrayObj, arrayLines;
    for(auto it = objList.begin(); it != objList.end(); it++)
    {
        objData.insert("PosX", (*it)->getPos().x());
        objData.insert("PosY", (*it)->getPos().y());
        objData.insert("Height", (*it)->getH());
        objData.insert("Width", (*it)->getW());
        objData.insert("ObjType", (*it)->getType());
        arrayObj.append(objData);
    }
    finalData["object"] = arrayObj;

    for(auto it = lineList.begin(); it != lineList.end(); it++)
    {
        QPair<int,int> links;
        links = getLink(it->get());
        lineData.insert("first", links.first);
        lineData.insert("second", links.second);
        arrayLines.append(lineData);
    }
    finalData["lines"] = arrayLines;
    document.setObject(finalData);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);
    QFile file(path);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream iStream (&file);
        iStream.setCodec("utf-8");
        iStream << bytes;
        file.close();
    }
    else
    {
       qDebug() << "file open fail";
    }
}

void PaintWidget::loadData()
{
    objList.clear();
    lineList.clear();
    QFile file("test.json");
    QJsonArray arrayObj, arrayLines;
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray bytes = file.readAll();
        file.close();
        QJsonParseError jsonError;
        document = QJsonDocument::fromJson(bytes, &jsonError);
        if(jsonError.error != QJsonParseError::NoError)
        {
            qDebug() << "error load";
        }

        if(document.isObject())
        {
            finalData = document.object();
        }

        for(auto it = finalData.begin(); it != finalData.end(); it++)
        {
            if(it.key() == "lines")
                arrayLines = (*it).toArray();
            if(it.key() == "object")
                arrayObj = (*it).toArray();
        }

        for(auto it = arrayObj.begin(); it != arrayObj.end(); it++)
        {
           QJsonObject tempJsonObj = it->toObject();
           if(tempJsonObj.value("ObjType") == Rectangle)
               tempObj = new GraphRect();
           if(tempJsonObj.value("ObjType") == Triangle)
               tempObj = new GraphTriangle();
           if(tempJsonObj.value("ObjType") == Ellipse)
               tempObj = new GraphEllipse();
           tempObj->setPos(QPoint(tempJsonObj.value("PosX").toInt(), tempJsonObj.value("PosY").toInt()));
           tempObj->setSize(tempJsonObj.value("Width").toInt(), tempJsonObj.value("Height").toInt());
           objList.emplace_back(tempObj);
        }
        for(auto it = arrayLines.begin(); it != arrayLines.end(); it++)
        {
            QJsonObject tempJsonObj = it->toObject();
            tempLine = std::make_unique<GraphLine>();
            setLinks(tempJsonObj.value("first").toInt(), tempJsonObj.value("second").toInt(), tempLine.get());
            lineList.emplace_back(std::move(tempLine));
        }
        file.close();
        tempLine.reset();
        tempObj = nullptr;

    }
    update();

}

QPair<int,int> PaintWidget::getLink(GraphLine *line) const
{
    QPair<int,int> links;
    for(int i = 0; i < objList.size(); i++)
    {
        if(objList[i].get() == line->getFirstItem())
        {
            links.first = i;
        }
        if(objList[i].get() == line->getSecondItem())
        {
            links.second = i;
        }

    }
    return links;
}

void PaintWidget::setLinks(int first, int second, GraphLine* line)
{
    for(int i = 0; i < objList.size(); i++)
    {
        if(i == first)
        {
            line->setFirstItem(objList.at(i).get());
        }
        if(i == second)
        {
            line->setSecondItem(objList.at(i).get());
        }
    }

}

void PaintWidget::resetFlags()
{
    deleteFlag = false;
    moveFlag = false;
}
