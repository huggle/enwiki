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
#include <huggle_core/iextension.hpp>
#include <QAction>

namespace Huggle
{
    class MainWindow;
    class WikiSite;
}

class enwiki : public QObject, public Huggle::iExtension
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
        Q_PLUGIN_METADATA(IID "org.huggle.extension.qt" FILE "enwiki.json")
#endif
    Q_INTERFACES(Huggle::iExtension)
    public:
        static bool WikiCk(Huggle::WikiSite *site);

        enwiki();
        ~enwiki();
        bool Register();
        bool IsWorking();
        void Hook_MainWindowOnLoad(void *window);
        QString GetExtensionName() { return "English wikipedia tools"; }
        QString GetExtensionAuthor() { return "Petr Bena"; }
        QString GetExtensionDescription() { return "Various tools for english wikipedia"; }
        QString GetExtensionVersion() { return "1.0.2"; }
        QAction *menu;
        bool Hook_RevertPreflight(void *edit);
        bool Hook_SpeedyBeforeOK(void *edit, void *form);
        bool RequestCore() { return true; }
        bool RequestNetwork() { return true; }
        bool RequestConfiguration() { return true; }
    private slots:
        void ClickPROD(bool checked = false);
    private:
        QAction *menuProd = nullptr;
        QAction *menuAfd = nullptr;
        Huggle::MainWindow *Window;
};

#endif // ENWIKI_H
