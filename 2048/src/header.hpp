//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_HEADER_HPP
#define SIMPLEGAMES_HEADER_HPP


#include <QtWidgets>

#include "scaling.hpp"


class GameHeader: public QWidget {

private:
    int score = 0;
    int best = 0;
    QSettings* cfg;
    ScalingMap* map;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    GameHeader(QSettings* config, ScalingMap* scaling_map, QWidget* parent)
        :cfg(config), map(scaling_map), QWidget(parent) {}
};


#endif //SIMPLEGAMES_HEADER_HPP
