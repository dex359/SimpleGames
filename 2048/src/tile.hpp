//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_TILE_HPP
#define SIMPLEGAMES_TILE_HPP


#include <QtWidgets>
#include <utility>


class Tile {

private:
    QRectF rect;
    QColor color;
    int val;

public:
    Tile() :val(0) {}
    Tile(const QRectF& r, QColor  c, int v) :rect(r), color(std::move(c)), val(v) {}

    const QRectF& geometry() {
        return rect;
    }

    void setGeometry(const QRectF& r) {
        rect = r;
    }
    int value() {
        return val;
    }
    void move(const QRectF& r) {
        rect = r;
    }
    void render(QPainter* p) {
        if (val) {
            p->drawRoundedRect(rect, 3, 3, Qt::AbsoluteSize);
            p->drawText(rect, Qt::AlignCenter, QString::number(val));
        }
    }
};


#endif //SIMPLEGAMES_TILE_HPP
