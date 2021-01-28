//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#pragma once

#include <QtWidgets>
#include "scaling.hpp"

class Header: public QWidget {

private:
    QSettings* cfg;
    Scaling::Map* map;

public:
    Header(Scaling::Map* scaling_map, QSettings* config, QWidget* parent);

protected:
    void paintEvent(QPaintEvent *event) override;

};