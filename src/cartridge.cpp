#include "cartridge.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>

class Cartridge::Private
{
public :
    Private() {
        // start with clean data
        clear();
    };

    void clear() {
        name.clear();
        type = NONE;
    }

    QString name;
    GameBoyType type;
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

    // start loading cartridge data
    if (rom.open(QIODevice::ReadOnly)) {
        QByteArray romData = rom.readAll();
        rom.close();

        // get cartridge name. Max length is 16 as from spec
        for (int i = 0; i < 16; ++i) {
            if (romData.at(0x0134 + i) == 0) {
                break;
            }

            d->name.append(romData.at(0x0134 + i));
        }

        // cartridge type
        if ((quint8)romData.at(0x0143) == 80) {
            d->type = COLOUR;
        } else {
            d->type = NO_COLOUR;
        }

        // DEBUG
        qDebug() << "ROM name: " << d->name;
        qDebug() << "ROM type: " << (quint8)romData.at(0x0143);
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


Cartridge::GameBoyType Cartridge::type() const
{
    return d->type;
}