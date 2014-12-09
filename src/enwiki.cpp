//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "enwiki.h"
#include "prodwn.h"
#include <core.hpp>
#include <collectable_smartptr.hpp>
#include <localization.hpp>
#include <query.hpp>
#include <querypool.hpp>
#include <mainwindow.hpp>
#include <generic.hpp>
#include <ui_mainwindow.h>
#include <wikiedit.hpp>
#include <wikisite.hpp>
#include <wikipage.hpp>
#include <syslog.hpp>
#include <configuration.hpp>

using namespace Huggle;

bool enwiki::WikiCk(WikiSite *site)
{
    if (site->Name == "enwiki")
        return true;
    Generic::MessageBox("Error", "You can use this feature only on english wikipedia");
    return false;
}

enwiki::enwiki()
{
}

bool enwiki::Register()
{
    Huggle::Core::HuggleCore = (Huggle::Core*) this->HuggleCore;
    Huggle::QueryPool::HugglePool = Huggle::Core::HuggleCore->HGQP;
    Huggle::Localizations::HuggleLocalizations = (Huggle::Localizations*) this->Localization;
    Huggle::Syslog::HuggleLogs = Huggle::Core::HuggleCore->HuggleSyslog;
    Huggle::GC::gc = Huggle::Core::HuggleCore->gc;
    Huggle::Query::NetworkManager = this->Networking;
    Huggle::Configuration::HuggleConfiguration = (Huggle::Configuration*) this->Configuration;
    return true;
}

bool enwiki::IsWorking()
{
    return true;
}

void enwiki::Hook_MainWindowOnLoad(void *window)
{
    this->Window = (Huggle::MainWindow*)window;
    this->menuProd = new QAction("PROD", this->Window->ui->menuPage);
    this->Window->ui->menuPage->addAction(this->menuProd);
    connect(this->menuProd, SIGNAL(triggered()), this, SLOT(ClickPROD()));
}

void enwiki::ClickPROD()
{
    if (!this->Window->CheckEditableBrowserPage() || !enwiki::WikiCk(this->Window->GetCurrentWikiSite()))
        return;
    if (this->Window->GetCurrentWikiEdit()->Page->IsTalk())
    {
        Generic::pMessageBox(this->Window, "Error", "You can't PROD talk pages");
        return;
    }
    QString pn = this->Window->CurrentEdit.GetPtr()->Page->GetNS()->GetCanonicalName();
    if (pn == "Template")
    {
        Generic::MessageBox("Error", "You can't use PROD for templates or categories");
        return;
    }
    ProdWn *ptr = new ProdWn(this->Window);
    //ptr->setAttribute(Qt::WA_DeleteOnClose, true);
    //ptr->show();
}

#if QT_VERSION < 0x05000
    Q_EXPORT_PLUGIN2("org.huggle.extension.qt", enwiki)
#endif


