#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <QtCore/QObject>


class Cartridge : public QObject
{
    Q_OBJECT

public:
    enum GameBoyType {
        COLOUR,
        NO_COLOUR,
        NONE
    };

    Cartridge(QObject *parent = 0);
    ~Cartridge();

    void loadRom(const QString &romFile);
    QString name() const;
    QString romFile() const;
    GameBoyType type() const;

private:
    QString m_romFile;  // ROM file path

    // This private class holds all the Cartridge metadata
    class Private;
    Private * const d;
};

#endif  // CARTRIDGE_H