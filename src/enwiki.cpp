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
#include <huggle_core/core.hpp>
#include <huggle_core/collectable_smartptr.hpp>
#include <huggle_core/localization.hpp>
#include <huggle_core/query.hpp>
#include <huggle_core/querypool.hpp>
#include <huggle_ui/mainwindow.hpp>
#include <huggle_core/generic.hpp>
#include <huggle_core/wikiedit.hpp>
#include <huggle_core/wikisite.hpp>
#include <huggle_core/wikipage.hpp>
#include <huggle_core/wikiuser.hpp>
#include <huggle_ui/speedyform.hpp>
#include <huggle_core/syslog.hpp>
#include <huggle_core/configuration.hpp>
#include <huggle_ui/uigeneric.hpp>
#include <QMenu>
#include <QMessageBox>

using namespace Huggle;

bool enwiki::WikiCk(WikiSite *site)
{
    if (site->Name == "enwiki")
        return true;
    UiGeneric::MessageBox("Error", "You can use this feature only on english wikipedia");
    return false;
}

enwiki::enwiki()
{
}

enwiki::~enwiki()
{
    delete this->menuAfd;
    delete this->menuProd;
}

bool enwiki::Register()
{
    this->Init();
    return true;
}

bool enwiki::IsWorking()
{
    return true;
}

void enwiki::Hook_MainWindowOnLoad(void *window)
{
    this->Window = (Huggle::MainWindow*)window;
    this->menuProd = new QAction("PROD", (QObject*)this->Window->GetMenu(HUGGLE_MW_MENU_PAGE));
    this->Window->GetMenu(HUGGLE_MW_MENU_PAGE)->addAction(this->menuProd);
    connect(this->menuProd, SIGNAL(triggered()), this, SLOT(ClickPROD()));
}

bool enwiki::Hook_RevertPreflight(void *edit)
{
    if (edit == nullptr)
        return true;
    WikiEdit *E = (WikiEdit*)edit;
    if (E->GetSite()->Name != "enwiki")
        return true;
    if (E->Page->FounderKnown() && E->Page->GetFounder() == E->User->Username)
    {
        int result = UiGeneric::MessageBox("Revert", "This edit was made by a person who created this page, do you want to request a speedy deletion instead?", Huggle::MessageBoxStyleQuestionAbort);
        if (result == QMessageBox::Yes)
        {
            this->Window->RequestPD(E);
            return false;
        } else if (result == QMessageBox::No)
        {
            return true;
        } else
        {
            // Cancel the request
            return false;
        }
    }
    return true;
}

bool enwiki::Hook_SpeedyBeforeOK(void *edit, void *form)
{
    SpeedyForm *sw = (SpeedyForm*)form;
    if (((WikiEdit*)edit)->GetSite()->Name != "enwiki")
        return true;
    // blank a target page if warning is g3 or g10
    if (sw->GetSelectedTagID() == "db-g3")
    {
        sw->ReplacingText = "{{subst:Courtesy blanked}}";
        sw->ReplacePage = true;
    }
    else if (sw->GetSelectedTagID() == "db-g10")
    {
        sw->ReplacePage = true;
    }
    // don't send a message to user on G7
    if (sw->GetSelectedTagID() == "db-g7")
        sw->SetMessageUserCheck(false);
    return true;
}

void enwiki::ClickPROD()
{
    if (!this->Window->CheckEditableBrowserPage() || !enwiki::WikiCk(this->Window->GetCurrentWikiSite()))
        return;
    if (this->Window->GetCurrentWikiEdit()->Page->IsTalk())
    {
        UiGeneric::pMessageBox(this->Window, "Error", "You can't PROD talk pages");
        return;
    }
    QString pn = this->Window->CurrentEdit->Page->GetNS()->GetCanonicalName();
    if (pn == "Template")
    {
        UiGeneric::MessageBox("Error", "You can't use PROD for templates or categories");
        return;
    }
    ProdWn *ptr = new ProdWn(this->Window->CurrentEdit, this->Window);
    ptr->setAttribute(Qt::WA_DeleteOnClose, true);
    ptr->show();
}

#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2("org.huggle.extension.qt", enwiki)
#endif


