#include "cartridge.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>

class Cartridge::Private
{
public :
    Private() {};

    void clear() {
        name.clear();
    }

    QString name;
//     GameBoyType type;
};



Cartridge::Cartridge(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
}


Cartridge::~Cartridge()
{
}


void Cartridge::loadRom(const QString &romFile)
{
    if (romFile.isEmpty()) {
        qFatal("No rom file has been set");
    }

    // clear old rom data
    d->clear();

    m_romFile = romFile;
    QFile rom(m_romFile);

    // let's see what data we have
    if (rom.open(QIODevice::ReadOnly)) {
        QByteArray romData = rom.readAll();

        // DEBUG
//         for (int i = 0; i < romData.size(); ++i) {
//             qDebug() << "@ " << i << " -> " << " : " << (quint8)romData.at(i) << " : " << QString(romData.at(i)).toAscii().toHex();
//         }

        // get cartridge name. Max length is 16 as from spec
        for (int i = 0; i < 16; ++i) {
            if (romData.at(0x0134 + i) == 0) {
                break;
            }

            d->name.append(romData.at(0x0134 + i));
        }

        // DEBUG
        qDebug() << d->name;
    }
}


QString Cartridge::name() const
{
    return d->name;
}


QString Cartridge::romFile() const
{
    return m_romFile;
}