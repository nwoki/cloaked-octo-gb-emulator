#include "cartridge.h"
#include "core.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>

Core::Core(QObject *parent)
    : QObject(parent)
    , m_cartridge(new Cartridge(this))
{
}


Core::~Core()
{

}


QString Core::currentRom() const
{
    return m_cartridge->romFile();
}


void Core::setRom(const QString &romFile)
{
    qDebug() << " set rom to : " << romFile;
    m_cartridge->loadRom(romFile);
}
