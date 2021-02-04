//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_SCALING_HPP
#define SIMPLEGAMES_SCALING_HPP


#include <cmath>

#include <QtCore>


class ScalingMap: public QObject {

public:
    const static int MIN_WIDTH  = 210; // Minimum width & height for main window
    const static int MIN_HEIGHT = 320; // Also used for calculate aspect ratio
    constexpr static double W2H = static_cast<double>(MIN_WIDTH) / MIN_HEIGHT;

    ScalingMap(const int& matrix_res, QObject* parent) : QObject(parent) {
        double mr = 170;                                       // board resolution
        double cs = 4;                                         // space between cells
        double cr = (mr - (matrix_res + 1) * cs) / matrix_res; // cell resolution
        data = {
            {"header.width",       210},
            {"header.height",       85},
            {"subtitle.font",       30},
            {"subtitle.x",          20},
            {"subtitle.y",          45},
            {"score.font",          10},
            {"score.x",            180}, // anchor point when aligning to right
            {"score.y",             20}, // top margin of score rectangles
            {"score.spacing",       15}, // space between score and best
            {"score.padding.v",      6}, // top + bottom summary
            {"score.padding.h",     10}, // lef + right summary
            {"score.rounding",       3},
            {"desc.font",           11},
            {"desc.x",              20},
            {"desc.y",              60},
            {"desc.w",             170},
            {"desc.h",              20},
            {"button.width",        75},
            {"button.height",       25},
            {"button.border.radius", 4},
            {"button.font",         10},
            {"button.x1",           20},
            {"button.x2",          115},
            {"button.y",            88},
            {"board.x",             20},
            {"board.y",            130},
            {"board.resolution",    mr},
            {"board.rounding",       4},
            {"cell.spacing",        cs},
            {"cell.resolution",     cr},
            {"cell.rounding",        3}
        };
    }

    void update(const int& new_width) {
        if (current_width != new_width) {
            double factor = static_cast<double>(new_width) / current_width;
            current_width = new_width;
            for (auto& value: data) {
                value *= factor;
            }
        }
    }

    const double& get(const QString& key) {
        return data[key];
    }

    int getInt(const QString& key) {
        return static_cast<int>(round(data[key]));
    }

    QString getStr(const QString& key) {
        return QString::number(getInt(key));
    }

private:
    int current_width = MIN_WIDTH;
    QMap<QString, double> data;
};


#endif //SIMPLEGAMES_SCALING_HPP
