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

ProdWn::ProdWn(QWidget *parent) : QDialog(parent), ui(new Ui::ProdWn)
{
    this->ui->setupUi(this);
}

ProdWn::~ProdWn()
{
    delete this->ui;
}

void ProdWn::on_buttonBox_rejected()
{
    this->close();
}

void ProdWn::on_buttonBox_accepted()
{

}
