//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_MATRIX_HPP
#define SIMPLEGAMES_MATRIX_HPP


#include <random>

#include <QtWidgets>

#include "scaling.hpp"
#include "tile.hpp"


// Matrix representation flags
enum class MxRepr {
    NORMAL,
    REVERSED,
    ROTATED_LEFT,
    ROTATED_RIGHT
};

// Swap direction flags
enum class SwapDir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Matrix {

private:
    QSettings* cfg;
    Scaling::Map* map;
    QRectF* rects_array;
    Tile* tiles_array;
    int res;

    int convertIndex(const int& x, const int& y, MxRepr repr) {
        switch (repr) {
            case MxRepr::NORMAL:
                return x + y * res;
            case MxRepr::REVERSED:
                return (res - 1 - x) + (res - 1 - y) * res;
            case MxRepr::ROTATED_LEFT:
                return x * res + (res - 1 - y);
            case MxRepr::ROTATED_RIGHT:
                return (res - 1 - x) * res + y;
        }
        return 0;
    }

public:
    explicit Matrix(QSettings* config, Scaling::Map* scaling_map)
        :cfg(config), map(scaling_map) {
        res = cfg->value("Game/grid").toInt();
        rects_array = new QRectF[res * res];
        tiles_array = new Tile[res * res];
    }
    ~Matrix() {
        delete[] rects_array;
        delete[] tiles_array;
    }
    int size() {
        return res * res;
    }
    Tile& tile(const int& x, const int& y, MxRepr repr) {
        return tiles_array[convertIndex(x, y, repr)];
    }
    Tile& tile(const int& index) {
        return tiles_array[index];
    }
    QRectF& rect(const int& x, const int& y, MxRepr repr) {
        return rects_array[convertIndex(x, y , repr)];
    }
    QRectF& rect(const int& index) {
        return rects_array[index];
    }
    void updateGeometry() {
        for (int x = 0; x < res; x++) {
            for (int y = 0; y < res; y++) {
                QRectF r(map->get("cell.spacing") * (x + 1) + map->get("cell.resolution") * x,
                         map->get("cell.spacing") * (y + 1) + map->get("cell.resolution") * y,
                         map->get("cell.resolution"),
                         map->get("cell.resolution"));
                rect(x, y, MxRepr::NORMAL) = r;
                tile(x, y, MxRepr::NORMAL).setGeometry(r);
            }
        }
    }

    bool spawn() {
        // find empty cells (zero value)
        int* pool = new int[res * res];
        int head = -1;
        for (int index = 0; index < res * res; index++) {
            if (!tile(index).value()) {
                pool[++head] = index;
            }
        }
        // check is matrix full
        if (head == -1) {
            delete[] pool;
            return false;
        }
        // random select for empty cell and cell value
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dist(0, head);
        int index = dist(mt);
        std::uniform_int_distribution<> dist2(0, 9);
        int value = 2;
        if (dist2(mt) == 9) {
            value = 4;
        }
        // insert tile
        tile(index) = Tile(rect(index),
                           QColor(cfg->value("Appearance/color." + QString::number(value)).toString()),
                           value);
        delete[] pool;
        return true;


    }

    static void merge(MxRepr repr) {
        switch (repr) {
            case MxRepr::NORMAL:
                qDebug() << "left";
                break;
            case MxRepr::REVERSED:
                qDebug() << "right";
                break;
            case MxRepr::ROTATED_RIGHT:
                qDebug() << "down";
                break;
            case MxRepr::ROTATED_LEFT:
                qDebug() << "up";
                break;
        }
    }
};


class MatrixWidget: public QWidget {

private:
    QSettings* cfg;
    Scaling::Map* map;
    Matrix matrix;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override {
        matrix.updateGeometry();
    }
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
            case Qt::Key_Left:
                matrix.merge(MxRepr::NORMAL);
                break;
            case Qt::Key_Right:
                matrix.merge(MxRepr::REVERSED);
                break;
            case Qt::Key_Up:
                matrix.merge(MxRepr::ROTATED_LEFT);
                break;
            case Qt::Key_Down:
                matrix.merge(MxRepr::ROTATED_RIGHT);
                break;
        }
    }

public:
    MatrixWidget(QSettings* config, Scaling::Map* s_map, QWidget* parent)
        :QWidget(parent), cfg(config), map(s_map), matrix(config, s_map) {}
};


#endif //SIMPLEGAMES_MATRIX_HPP
