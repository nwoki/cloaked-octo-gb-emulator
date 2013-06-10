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
        ramSize = RAM_NONE;
        romSize = ROM_NONE;
    }

    QString name;
    GameBoyType gameBoyType;
    CartridgeType type;
    QByteArray nintendoGraphic;
    RamSize ramSize;
    RomSize romSize;
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


void Cartridge::determineRamSize(quint8 byte)
{
    switch (byte) {
        case 0:
            d->ramSize = RAM_NONE;
            qDebug("NONE");
            break;
        case 1:
            d->ramSize = RAM_2KB;
            break;
        case 2:
            d->ramSize = RAM_8KB;
            break;
        case 3:
            d->ramSize = RAM_32KB;
            break;
        case 4:
            d->ramSize = RAM_128KB;
            break;
        default:
            d->ramSize = RAM_NONE;
            break;
    };
}


void Cartridge::determineRomSize(quint8 byte)
{
    switch (byte) {
        case 0:
            d->romSize = ROM_32KB;
            break;
        case 1:
            d->romSize = ROM_64KB;
            break;
        case 2:
            d->romSize = ROM_128KB;
            break;
        case 3:
            d->romSize = ROM_256KB;
            break;
        case 4:
            d->romSize = ROM_512KB;
            break;
        case 5:
            d->romSize = ROM_1MB;
            break;
        case 6:
            d->romSize = ROM_2MB;
            break;
        default:
            d->romSize = ROM_NONE;
            break;
    };
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

        // ram
        determineRamSize((quint8)romData.at(0x0149));

        // rom
        determineRomSize((quint8)romData.at(0x0148));

        // DEBUG
        qDebug() << "ROM name: " << d->name;
        qDebug() << "ROM gameBoyType: " << (quint8)romData.at(0x0143);
        qDebug() << "Cartridge type: " << (quint8)romData.at(0x0147);
        qDebug() << "ROM size: " << (quint8)romData.at(0x0148);
        qDebug() << "RAM size: " << (quint8)romData.at(0x0149);
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


Cartridge::RamSize Cartridge::ram() const
{
    return d->ramSize;
}


Cartridge::RomSize Cartridge::rom() const
{
    return d->romSize;
}


QString Cartridge::romFile() const
{
    return m_romFile;
}


Cartridge::CartridgeType Cartridge::type() const
{
    return d->type;
}