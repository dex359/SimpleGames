//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#include "scaling.hpp"


void Scaling::fill(const int &matrix_res) {
    data = {
        {"button.width", 75},
        {"button.height", 25},
        {"button.border.radius", 4},
        {"button.font", 10},
        {"button.x1", 20},
        {"button.x2", 115},
        {"button.y", 88}
    };
}

void Scaling::update(const int& new_width) {
    if (current_width != new_width) {
        double factor = static_cast<double>(new_width) / current_width;
        current_width = new_width;
        for (auto& value: data) {
            value *= factor;
        }
    }
}

const double& Scaling::get(const QString &key) {
    return data[key];
}

int Scaling::getInt(const QString &key) {
    return static_cast<int>(round(data[key]));
}

QString Scaling::getStr(const QString &key) {
    return QString::number(getInt(key));
}
