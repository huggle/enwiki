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

#include <editquery.hpp>
#include <collectable_smartptr.hpp>
#include <definitions.hpp>
#include <QDialog>

namespace Ui
{
    class ProdWn;
}

namespace Huggle
{
    class QueryResult;
    class ApiQuery;
    class WikiEdit;
}

#define HUGGLE_PROD "{{subst:proposed deletion|concern="

class ProdWn : public QDialog
{
        Q_OBJECT
    public:
        explicit ProdWn(Huggle::WikiEdit *edit, QWidget *parent = 0);
        ~ProdWn();
        bool WatchlistEdit();
        //! Whether a message is sent to user or not
        bool Message();
        void EnableUI();
        Huggle::Collectable_SmartPtr<Huggle::EditQuery> qEdit;
        Huggle::WikiEdit *edit;

    private slots:
        void on_pushButton_clicked();

    private:
        Ui::ProdWn *ui;
};

#endif // PRODWN_H
