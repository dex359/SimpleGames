//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//


#include "header.hpp"


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
    font.setPixelSize(map->getInt("desc.font"));
    p.setFont(font);
    auto rect = QRect(map->getInt("desc.x"),
                      map->getInt("desc.y"),
                      map->getInt("desc.w"),
                      map->getInt("desc.h"));
    p.drawText(rect, Qt::AlignCenter, cfg->value("Locale/help").toString());
    // draw current score and best
    font.setPixelSize(map->getInt("score.font"));
    p.setFont(font);
    auto score_line = QString(cfg->value("Locale/score").toString() + "\n" +
                              QString::number(score));
    auto best_line = QString(cfg->value("Locale/best").toString() + "\n" +
                             QString::number(best));
    // define score and best boundary rectangles
    auto sbr = p.boundingRect(geometry(),
                               Qt::AlignCenter | Qt::TextWordWrap,
                               score_line);
    auto bbr = p.boundingRect(geometry(),
                               Qt::AlignCenter | Qt::TextWordWrap,
                               best_line);
    // define score and best background rectangles
    auto score_rect = QRect(map->getInt("score.x") -
                            sbr.width() -
                            bbr.width() -
                            map->getInt("score.spacing"),
                            map->getInt("score.y"),
                            sbr.width() + map->getInt("score.padding.h"),
                            sbr.height() + map->getInt("score.padding.v"));
    auto best_rect = QRect(map->getInt("score.x") - bbr.width(),
                           map->getInt("score.y"),
                           bbr.width() + map->getInt("score.padding.h"),
                           bbr.height() + map->getInt("score.padding.v"));
    // draw background rectangles
    p.setPen(QColor(cfg->value("Appearance/color.grid").toString()));
    p.setBrush(QColor(cfg->value("Appearance/color.grid").toString()));
    p.drawRoundedRect(score_rect,
                      map->getInt("score.rounding"),
                      map->getInt("score.rounding"),
                      Qt::AbsoluteSize);
    p.drawRoundedRect(best_rect,
                      map->getInt("score.rounding"),
                      map->getInt("score.rounding"),
                      Qt::AbsoluteSize);
    p.setPen(QColor(cfg->value("Appearance/color.background").toString()));
    p.drawText(score_rect, Qt::AlignCenter, score_line);
    p.drawText(best_rect, Qt::AlignCenter, best_line);


}