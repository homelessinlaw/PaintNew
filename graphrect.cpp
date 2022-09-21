//
// Created by Danil Sasnouski on 21.09.2022
//

#include "graphrect.h"

GraphRect::GraphRect()
{
    type = Rectangle;
}

void GraphRect::draw(QPainter& painter)
{
    painter.drawRect(pos.x(), pos.y(), w, h);
}

std::vector<QPoint> GraphRect::getCoordinatest() const
{
    return {
        { pos.x(), pos.y() },
        { pos.x() + w, pos.y() },
        { pos.x(), pos.y() + h },
        { pos.x() + w, pos.y() + h }
    };

}

bool GraphRect::isPointInFigure(QPoint point) const
{
    int i1, i2, n, N, S, S1, S2, S3, x = point.x(), y = point.y();
    bool isIn;
    std::vector<QPoint> p = getCoordinatest();
      N = 4;
      for (n=0; n<N; n++)
      {
        isIn = false;
        i1 = n < N-1 ? n + 1 : 0;
        while (isIn == false)
        {
            i2 = i1 + 1;
            if (i2 >= N)
                i2 = 0;
            if (i2 == (n < N-1 ? n + 1 : 0))
                break;
            S = abs (p[i1].x() * (p[i2].y() - p[n ].y()) +
                 p[i2].x() * (p[n ].y() - p[i1].y()) +
                 p[n].x()  * (p[i1].y() - p[i2].y()));
            S1 = abs (p[i1].x() * (p[i2].y() - y) +
                  p[i2].x() * (y - p[i1].y()) +
                  x * (p[i1].y() - p[i2].y()));
            S2 = abs (p[n ].x() * (p[i2].y() - y) +
                  p[i2].x() * (y - p[n ].y()) +
                  x * (p[n ].y() - p[i2].y()));
            S3 = abs (p[i1].x() * (p[n ].y() - y) +
                  p[n ].x() * (y - p[i1].y()) +
                  x * (p[i1].y() - p[n ].y()));
            if (S == S1 + S2 + S3)
            {
                isIn = true;
                break;
            }
            i1 = i1 + 1;
            if (i1 >= N)
            {
                i1 = 0;
                break;
            }
       }
       if (isIn == true)
         break;
      }
      return isIn;
}
