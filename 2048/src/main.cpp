//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#include <QtWidgets>
#include <QtCore>

#include "scaling.hpp"
#include "header.hpp"
#include "matrix.hpp"


class GameWidget: public QWidget {
    Q_OBJECT

private:
    QSettings*       cfg;
    QPushButton*  undo_b;
    QPushButton*  newg_b;
    HeaderWidget* header;
    MatrixWidget* matrix;
    Scaling::Map*    map;

public:
    explicit GameWidget(QWidget* parent) :QWidget(parent) {
        // construct
        cfg       = new QSettings("2048.conf", QSettings::IniFormat, this);
        map       = new Scaling::Map(cfg->value("Game/grid").toInt(), this);
        header    = new HeaderWidget(cfg, map, this);
        matrix    = new MatrixWidget(cfg, map, this);
        undo_b    = new QPushButton(cfg->value("Locale/undo").toString(), this);
        newg_b    = new QPushButton(cfg->value("Locale/new").toString(), this);
        // configure this
        setObjectName("GameWidget");
        connect(undo_b, SIGNAL(clicked(bool)), this, SLOT(undo()));
        connect(newg_b, SIGNAL(clicked(bool)), this, SLOT(new_game()));

        // configure host window
        parent->resize(cfg->value("Window/size").toSize());
        parent->setWindowTitle(cfg->value("Locale/title").toString());
        parent->setWindowIcon(QIcon("icon.png"));
        parent->setStyleSheet(QString("background-color: %1;").arg(
                              cfg->value("Appearance/color.background").toString()));




    }

    void updateButtonsGeometry() {
        // gen dynamic stylesheet
        auto qss = QString(
            "QPushButton {"
            "border: 1px solid %1;"
            "border-radius: %2;"
            "background-color: %3;"
            "font: %4px;"
            "color: %5;"
            "}").arg(
            cfg->value("Appearance/color.grid").toString(),
            map->getStr("button.border.radius"),
            cfg->value("Appearance/color.grid").toString(),
            map->getStr("button.font"),
            cfg->value("Appearance/color.background").toString());
        // apply
        undo_b->setStyleSheet(qss);
        newg_b->setStyleSheet(qss);
        // update geometry according to game widget width
        undo_b->setGeometry(map->getInt("button.x1"),
                            map->getInt("button.y"),
                            map->getInt("button.width"),
                            map->getInt("button.height"));
        newg_b->setGeometry(map->getInt("button.x2"),
                            map->getInt("button.y"),
                            map->getInt("button.width"),
                            map->getInt("button.height"));

    }

    void updateHeaderGeometry() {
        header->setGeometry(0, 0,
            map->getInt("header.width"),
            map->getInt("header.height"));
    }

    void updateMatrixGeometry() {
        matrix->setGeometry(map->getInt("matrix.x"),
                            map->getInt("matrix.y"),
                            map->getInt("matrix.width"),
                            map->getInt("matrix.height"));
    }

    void resizeEvent(QResizeEvent *event) override {
        map->update(event->size().width());
        updateHeaderGeometry();
        updateButtonsGeometry();
        updateMatrixGeometry();
    }

    ~GameWidget() override {
        cfg->setValue("Window/size", size());
        cfg->sync();
    }

public slots:
    void new_game() {
        qDebug() << "New game";
    };

    void undo() {
        qDebug() << "Undo";
    }


};

class HostWindow: public QWidget {

private:
    QWidget* child = nullptr;

public:
    HostWindow() {setMinimumSize(Scaling::MIN_WIDTH, Scaling::MIN_HEIGHT);}
    void resizeEvent(QResizeEvent *event) override;
};


void HostWindow::resizeEvent(QResizeEvent *event) {
    int new_width, new_height;
    if (!child) child = findChild<QWidget*>("GameWidget");
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
    child->setGeometry((width() - new_width) / 2,
                       (height() - new_height) / 2,
                       new_width,
                       new_height);
}

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    HostWindow host;
    GameWidget game(&host);
    host.show();
    return QApplication::exec();
}
