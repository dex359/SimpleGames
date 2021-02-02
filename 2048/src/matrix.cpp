//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#include "matrix.hpp"


void MatrixWidget::paintEvent(QPaintEvent* event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::NoPen));
    p.setBrush(QColor(cfg->value("Appearance/color.grid").toString()));
    p.drawRoundedRect(QRectF(0, 0, width(), height()),
                      map->get("matrix.rounding"),
                      map->get("matrix.rounding"),
                      Qt::AbsoluteSize);
}
