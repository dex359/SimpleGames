//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#include "board.hpp"


void GameBoard::paintEvent(QPaintEvent* event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::NoPen));
    p.setBrush(QColor(cfg->value("Appearance/color.grid").toString()));
    p.drawRoundedRect(QRectF(0, 0, width(), height()),
                      map->get("board.rounding"),
                      map->get("board.rounding"),
                      Qt::AbsoluteSize);
    p.setBrush(QColor(cfg->value("Appearance/color.cell").toString()));
    for (const Node& node: matrix) {
        p.drawRoundedRect(node.geometry(),
                          map->get("cell.rounding"),
                          map->get("cell.rounding"),
                          Qt::AbsoluteSize);
    }
}
