//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_HEADER_HPP
#define SIMPLEGAMES_HEADER_HPP


#include <QtWidgets>

#include "scaling.hpp"


class Header: public QWidget {

private:
    int score = 0;
    int best = 0;
    QSettings* cfg;
    Scaling::Map* map;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    Header(Scaling::Map* scaling_map, QSettings* config, QWidget* parent)
        :map(scaling_map), cfg(config), QWidget(parent) {}
};


#endif //SIMPLEGAMES_HEADER_HPP
