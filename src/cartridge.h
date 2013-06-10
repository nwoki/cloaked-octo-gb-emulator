#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <QtCore/QObject>


class Cartridge : public QObject
{
    Q_OBJECT

public:
    enum CartridgeType {
        ROM_ONLY,
        ROM_MBC1,
        ROM_MBC2,
        ROM_MBC3,
        ROM_MBC5,
        ROM_UNSOPPORTED
    };

    enum GameBoyFunctions {
        GAMEBOY,
        SUPER_GAMEBOY
    };

    enum GameBoyType {
        COLOUR,
        NO_COLOUR,
        NONE
    };

    enum RamSize {
        RAM_NONE,
        RAM_2KB,        // 1 bank
        RAM_8KB,        // 1 bank
        RAM_32KB,       // 4 banks
        RAM_128KB       // 16 banks
    };

    enum RomSize {
        ROM_NONE,       // should never be used actually
        ROM_32KB,       // 2 banks
        ROM_64KB,       // 4 banks
        ROM_128KB,      // 8 banks
        ROM_256KB,      // 16 banks
        ROM_512KB,      // 32 banks
        ROM_1MB,        // 64 banks
        ROM_2MB,        // 128 banks
        ROM_1_1MB,      // 72 banks
        ROM_1_2MB,      // 80 banks
        ROM_1_5MB       // 96 banks
    };


    Cartridge(QObject *parent = 0);
    ~Cartridge();

    GameBoyType gameBoyType() const;
    void loadRom(const QString &romFile);
    QString name() const;
    QByteArray nintendoGraphic() const;
    RamSize ram() const;
    RomSize rom() const;
    QString romFile() const;
    quint8 romVersion() const;
    CartridgeType type() const;

private:
    void determineCartridgeType(quint8 byte);
    void determineRamSize(quint8 byte);
    void determineRomSize(quint8 byte);

    QString m_romFile;  // ROM file path

    // This private class holds all the Cartridge metadata
    class Private;
    Private * const d;
};

#endif  // CARTRIDGE_H