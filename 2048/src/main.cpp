//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#include <QtWidgets>
#include <QtCore>

#include "canvas.hpp"
#include "scaling.hpp"

class GameWidget: public QWidget {

private:
    QSettings* cfg = nullptr;
    CanvasWidget* canvas = nullptr;
    Scaling::Map map;

public:
    GameWidget() {
        cfg = new QSettings("2048.conf", QSettings::IniFormat, this);
        canvas = new CanvasWidget(this);

        setMinimumSize(QSize(Scaling::MIN_WIDTH, Scaling::MIN_HEIGHT));
        setGeometry(cfg->value("Window/geometry").toRect());
        setWindowTitle(cfg->value("Locale/window.title").toString());
        setWindowIcon(QIcon("icon.png"));
    }

    void resizeEvent(QResizeEvent *event) override {
        int new_width, new_height;
        if (event->oldSize().width() != event->size().width()) {
            new_height = static_cast<int>(event->size().width() / Scaling::W2H);
            new_width = event->size().width();
            if (new_height > event->size().height()) {
                new_height = event->size().height();
                new_width = static_cast<int>(new_height * Scaling::W2H);
            }
        } else {
            new_width = static_cast<int>(event->size().height() * Scaling::W2H);
            new_height = event->size().height();
            if (new_width > event->size().width()) {
                new_width = event->size().width();
                new_height = static_cast<int>(new_width / Scaling::W2H);
            }
        }
        canvas->resize(new_width, new_height);
        canvas->move((width() - new_width) / 2, (height() - new_height) / 2);
        event->accept();
    }

    void closeEvent(QCloseEvent *event) override {
        cfg->setValue("Window/geometry", geometry());
        cfg->sync();
        event->accept();
    }
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameWidget game;
    game.show();
    return QApplication::exec();
}
