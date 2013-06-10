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
        gameBoyType = NONE;
        type = ROM_UNSOPPORTED;
        nintendoGraphic.clear();
    }

    QString name;
    GameBoyType gameBoyType;
    CartridgeType type;
    QByteArray nintendoGraphic;
};



Cartridge::Cartridge(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
}


Cartridge::~Cartridge()
{
}


void Cartridge::determineCartridgeType(quint8 byte)
{
    switch (byte) {
        case 0:         // rom only
        case 8:         // rom + ram
        case 9:         // rom + ram + batt
            qDebug("ROM");
            d->type = ROM_ONLY;
            break;
        case 1:         // rom + mbc1
        case 2:         // rom + mbc1 + ram
        case 3:         // rom + mbc1 + ram + batt
            qDebug("ROM_MBC1");
            d->type = ROM_MBC1;
            break;
        case 5:         // rom + mbc2
        case 6:
            qDebug("ROM_MBC2");
            d->type = ROM_MBC2;
            break;
        case 15:        // rom + mbc3 + timer + batt
        case 16:        // rom + mbc3 + timer + batt + ram
        case 17:        // rom + mbc3
        case 18:        // rom + mbc3 + ram
        case 19:        // rom + mbc3 + ram + batt
            qDebug("ROM_MBC3");
            d->type = ROM_MBC3;
            break;
        case 25:        // rom + mbc5
        case 26:        // rom + mbc5 + ram
        case 27:        // rom + mbc5 + ram + batt
        case 28:        // rom + mbc5 + rumble
        case 29:        // rom + mbc5 + rumble + sram
        case 30:        // rom + mbc5 + rumble + sram + batt
            qDebug("ROM_MBC5");
            d->type = ROM_MBC5;
            break;
        default:
            qDebug("ROM_UNSOPPORTED");
            d->type = ROM_UNSOPPORTED;
            break;
    };
}


Cartridge::CartridgeType Cartridge::type() const
{
    return d->type;
}


Cartridge::GameBoyType Cartridge::gameBoyType() const
{
    return d->gameBoyType;
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

        // get nintendo graphic data
        for (int i = 0; i < 48; ++i) {
            d->nintendoGraphic.append(romData.at(0x0104+i));
        }

        // get cartridge name. Max length is 16 as from spec
        for (int i = 0; i < 16; ++i) {
            if (romData.at(0x0134 + i) == 0) {
                break;
            }

            d->name.append(romData.at(0x0134 + i));
        }

        // gameBoy type
        if ((quint8)romData.at(0x0143) == 80) {
            d->gameBoyType = COLOUR;
        } else {
            d->gameBoyType = NO_COLOUR;
        }

        // cartridge type
        determineCartridgeType((quint8)romData.at(0x0147));

        // DEBUG
        qDebug() << "ROM name: " << d->name;
        qDebug() << "ROM gameBoyType: " << (quint8)romData.at(0x0143);
        qDebug() << "Cartridge type: " << (quint8)romData.at(0x0147);
        qDebug() << "ROM size: " << (quint32)romData.at(0x0148);
    }
}


QString Cartridge::name() const
{
    return d->name;
}


QByteArray Cartridge::nintendoGraphic() const
{
    return d->nintendoGraphic;
}


QString Cartridge::romFile() const
{
    return m_romFile;
}