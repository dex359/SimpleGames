//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#pragma once

#include <QtCore>

namespace Scaling {

    const int    MIN_WIDTH  = 210;
    const int    MIN_HEIGHT = 320;
    const double W2H        = 0.65625;


    class Map {

    private:
        QMap<QString, double> data;

    public:
        explicit Map() {
            update(210);
        }

        void update(double cur_width) {
            double f = cur_width / MIN_WIDTH;
            data["some"] = 120 * f;
        }

        double& operator[] (const QString& name) {
            return data[name];
        }

    };
}

