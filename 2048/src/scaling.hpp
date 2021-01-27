//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#pragma once

#include <cmath>
#include <QtCore>

#define MIN_W 210  // Minimum width & height for main window
#define MIN_H 320  // Also used for calculate aspect ratio for game frame

class Scaling {

private:
    int current_width = MIN_W;
    QMap<QString, double> data;

public:
    static const int MIN_WIDTH  = MIN_W;
    static const int MIN_HEIGHT = MIN_H;
    static constexpr double W2H = static_cast<double>(MIN_W) / MIN_H;

    void fill(const int& matrix_res);
    void update(const int& new_width);
    const double& get(const QString& key);
    int getInt(const QString& key);
    QString getStr(const QString& key);

};

