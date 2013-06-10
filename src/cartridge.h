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

    enum GameBoyType {
        COLOUR,
        NO_COLOUR,
        NONE
    };

    Cartridge(QObject *parent = 0);
    ~Cartridge();

    CartridgeType type() const;
    void loadRom(const QString &romFile);
    QString name() const;
    QByteArray nintendoGraphic() const;
    QString romFile() const;
    GameBoyType gameBoyType() const;

private:
    void determineCartridgeType(quint8 byte);

    QString m_romFile;  // ROM file path

    // This private class holds all the Cartridge metadata
    class Private;
    Private * const d;
};

#endif  // CARTRIDGE_H