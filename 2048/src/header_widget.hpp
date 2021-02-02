//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_HEADER_WIDGET_HPP
#define SIMPLEGAMES_HEADER_WIDGET_HPP


#include <QtWidgets>

#include "scaling.hpp"


class HeaderWidget: public QWidget {

private:
    int score = 0;
    int best = 0;
    QSettings* cfg;
    Scaling::Map* map;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    HeaderWidget(QSettings* config, Scaling::Map* scaling_map, QWidget* parent)
        :cfg(config), map(scaling_map), QWidget(parent) {}
};


#endif //SIMPLEGAMES_HEADER_WIDGET_HPP
