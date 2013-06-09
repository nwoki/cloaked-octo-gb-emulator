#ifndef CORE_H
#define CORE_H

#include <QtCore/QObject>

class Cartridge;

class Core : public QObject
{
    Q_OBJECT

public:
    Core(QObject *parent = 0);
    ~Core();

    QString currentRom() const;
    void setRom(const QString &romFile);

private:
    Cartridge *m_cartridge;
};

#endif  // CORE_H