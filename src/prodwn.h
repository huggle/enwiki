//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef PRODWN_H
#define PRODWN_H

#include <QDialog>

namespace Ui {
    class ProdWn;
}

#define HUGGLE_PROD "{{subst:proposed deletion|concern="

class ProdWn : public QDialog
{
        Q_OBJECT
    public:
        explicit ProdWn(QWidget *parent = 0);
        ~ProdWn();

    private slots:
        void on_buttonBox_rejected();

        void on_buttonBox_accepted();

    private:
        Ui::ProdWn *ui;
};

#endif // PRODWN_H
