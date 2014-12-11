//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "prodwn.h"
#include "ui_prodwn.h"
#include <generic.hpp>
#include <apiquery.hpp>
#include <exception.hpp>
#include <wikiedit.hpp>
#include <wikisite.hpp>
#include <wikiutil.hpp>

using namespace Huggle;

ProdWn::ProdWn(WikiEdit *edit, QWidget *parent) : QDialog(parent), ui(new Ui::ProdWn)
{
    this->ui->setupUi(this);
    this->edit = edit;
}

ProdWn::~ProdWn()
{
    delete this->ui;
}

bool ProdWn::WatchlistEdit()
{
    return this->ui->checkBox_2->isChecked();
}

bool ProdWn::Message()
{
    return this->ui->checkBox->isChecked();
}

void ProdWn::EnableUI()
{
    this->ui->lineEdit->setEnabled(true);
    this->ui->checkBox->setEnabled(true);
    this->ui->checkBox_2->setEnabled(true);
    this->ui->pushButton->setEnabled(true);
}

static void Failed(Query *qr)
{
    if (!qr->CallbackOwner)
        throw new Huggle::NullPointerException("local qr->CallbackOwner", BOOST_CURRENT_FUNCTION);
    ((ProdWn*)qr->CallbackOwner)->EnableUI();
    Generic::MessageBox("Failed", "Unable to edit page: " + qr->GetFailureReason());
    qr->UnregisterConsumer(HUGGLECONSUMER_CALLBACK);
}

static void Finished(Query *qr)
{
    if (!qr->CallbackOwner)
        throw new Huggle::NullPointerException("local qr->CallbackOwner", BOOST_CURRENT_FUNCTION);
    // if we don't want to send a message we can quit this
    if (((ProdWn*)qr->CallbackOwner)->Message())
    {
        WikiEdit *edit = ((ProdWn*)qr->CallbackOwner)->edit;
        QString message = "Proposed deletion of " + edit->Page->PageName;
        WikiUtil::MessageUser(edit->User, "{{subst:Proposed deletion notify|" + edit->Page->PageName + "}} ~~~~",
                              message, message);
    }
    if (((ProdWn*)qr->CallbackOwner)->WatchlistEdit())
    {
        WikiUtil::Watchlist(((ProdWn*)qr->CallbackOwner)->edit->Page);
    }
    ((ProdWn*)qr->CallbackOwner)->close();
    qr->UnregisterConsumer(HUGGLECONSUMER_CALLBACK);
}

void ProdWn::on_pushButton_clicked()
{
    if (this->ui->lineEdit->text().isEmpty())
    {
        Generic::MessageBox("No reason", "You didn't provide any reason", MessageBoxStyleNormal, false);
        return;
    }
    this->ui->checkBox->setEnabled(false);
    this->ui->checkBox_2->setEnabled(false);
    this->ui->pushButton->setEnabled(false);
    this->ui->lineEdit->setEnabled(false);
    this->qEdit = WikiUtil::PrependTextToPage(edit->Page, QString(HUGGLE_PROD) + this->ui->lineEdit->text() + "}}\n", "Nominating page for deletion");
    this->qEdit->CallbackOwner = this;
    this->qEdit->FailureCallback = (Callback)Failed;
    this->qEdit->callback = (Callback)Finished;
}
