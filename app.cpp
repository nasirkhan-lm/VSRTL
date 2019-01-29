#include <QApplication>
#include "vsrtl_adderandreg.h"
#include "vsrtl_mainwindow.h"
#include "vsrtl_manynestedcomponents.h"
#include "vsrtl_nestedexponenter.h"

#include <chrono>

#include <QDebug>
#include <QFile>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Q_INIT_RESOURCE(icons);

    vsrtl::ManyNestedComponents design;
    vsrtl::MainWindow w(design);

    w.show();

    app.exec();
}