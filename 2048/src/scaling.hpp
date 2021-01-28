//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#pragma once

#include <cmath>
#include <QtCore>


namespace Scaling {

    const int    MIN_WIDTH  = 210;  // Minimum width & height for main window
    const int    MIN_HEIGHT = 320;  // Also used for calculate aspect ratio for game frame
    const double W2H        = static_cast<double>(MIN_WIDTH) / MIN_HEIGHT;

    class Map: public QObject {

    private:
        int current_width = MIN_WIDTH;
        QMap<QString, double> data;

    public:
        Map(const int &matrix_resolution, QObject* parent);
        void update(const int& new_width);
        const double& get(const QString& key);
        int getInt(const QString& key);
        QString getStr(const QString& key);
    };
}
