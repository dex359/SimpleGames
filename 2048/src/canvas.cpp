//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#include "canvas.hpp"

CanvasWidget::CanvasWidget(QWidget *parent) :QWidget(parent), parent{parent} {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}
