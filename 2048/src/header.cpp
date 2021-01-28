//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#include <QtGui>

#include "header.hpp"


Header::Header(Scaling::Map* scaling_map, QSettings* config, QWidget* parent)
                  :map(scaling_map), cfg(config), QWidget(parent) {

}

void Header::paintEvent(QPaintEvent* event) {
    // configure painter
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    // draw subtitle
    p.setPen(QColor(cfg->value("Appearance/color.text.dark").toString()));
    QFont font;
    font.setPixelSize(map->getInt("subtitle.font"));
    p.setFont(font);
    p.drawText(map->getInt("subtitle.x"),
               map->getInt("subtitle.y"),
               cfg->value("Locale/subtitle").toString());
    // draw description line
    font.setPixelSize(map->getInt("description.font"));
    p.setFont(font);

}
