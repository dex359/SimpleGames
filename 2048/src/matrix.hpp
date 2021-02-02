//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_MATRIX_HPP
#define SIMPLEGAMES_MATRIX_HPP


#include <QtWidgets>

#include "scaling.hpp"


class Matrix {
private:

};


class MatrixWidget: public QWidget {

private:
    QSettings* cfg;
    Scaling::Map* map;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MatrixWidget(QSettings* config, Scaling::Map* s_map, QWidget* parent)
        :cfg(config), map(s_map), QWidget(parent) {}
};


#endif //SIMPLEGAMES_MATRIX_HPP
