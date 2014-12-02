//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef ENWIKI_H
#define ENWIKI_H

#define HUGGLE_EXTENSION
#include <iextension.hpp>
#include <QDeclarativeItem>

class enwiki : public QDeclarativeItem, public Huggle::iExtension
{
    Q_OBJECT
#if QT_VERSION >= 0x05000
        Q_PLUGIN_METADATA(IID "org.huggle.extension.qt" FILE "enwiki.json")
#endif
    Q_INTERFACES(Huggle::iExtension)
    public:
        enwiki();
        bool Register();
        bool IsWorking();
        //void Hook_MainWindowOnLoad(void *window);
        QString GetExtensionName() { return "English wikipedia tools"; }
        QString GetExtensionAuthor() { return "Petr Bena"; }
        QString GetExtensionDescription() { return "Various tools for english wikipedia"; }
        QAction *menu;
        bool RequestCore() { return true; }
        bool RequestNetwork() { return true; }
        bool RequestConfiguration() { return true; }
    private slots:
    private:
};

QML_DECLARE_TYPE(enwiki)

#endif // ENWIKI_H
