#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include "core.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Cloaked octo gameboy emulator");

    Core core;

    if (argc >= 2) {
        core.setRom(argv[1]);
    }

    return a.exec();
}
