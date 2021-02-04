//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_BOARD_HPP
#define SIMPLEGAMES_BOARD_HPP


#include <random>

#include <QtWidgets>

#include "scaling.hpp"
#include "tile.hpp"
#include "matrix.hpp"


class GameBoard: public QWidget {

private:
    QSettings* cfg;
    ScalingMap* map;
    Matrix matrix;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override {
        matrix.updateGeometry(map->getInt("cell.spacing"),
                              map->getInt("cell.resolution"));
    }
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
            case Qt::Key_Left:
                break;
            case Qt::Key_Right:
                break;
            case Qt::Key_Up:
                break;
            case Qt::Key_Down:
                break;
        }
    }

public:
    GameBoard(QSettings* cfg, ScalingMap* map, QWidget* parent)
        :QWidget(parent), cfg(cfg), map(map), matrix(cfg->value("Game/grid").toInt()) {
        setFocus();
    }
};


#endif //SIMPLEGAMES_BOARD_HPP
