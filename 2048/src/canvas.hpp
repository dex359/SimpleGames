//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#pragma once

#include <QtWidgets>

class CanvasWidget: public QWidget {

private:
    QWidget* parent;

public:
    explicit CanvasWidget(QWidget* parent);
};