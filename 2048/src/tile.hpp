//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_TILE_HPP
#define SIMPLEGAMES_TILE_HPP


#include <QRectF>


class Tile {

public:
    using RectType  = QRectF;
    using RectCoord = double;

    explicit Tile(int value = 0) : tile_value(value) {}
    explicit Tile(int value, const RectType& rect) : tile_value(value), tile_rect(rect) {}

    const RectType& geometry() {return tile_rect;}
    void setGeometry(const RectType& rect) {tile_rect = rect;}
    void setGeometry(RectCoord x, RectCoord y, RectCoord w, RectCoord h) {tile_rect.setRect(x, y, w, h);}
    int value() const {return tile_value;}

private:
    RectType tile_rect;
    int tile_value;
};


#endif //SIMPLEGAMES_TILE_HPP
