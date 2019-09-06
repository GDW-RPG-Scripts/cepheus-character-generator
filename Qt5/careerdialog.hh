/**
 * Cepheus Character Generator, a character generator for the Cepheus Engine
 * and derived RPG systems.
 *
 * Copyright (C) 2019 Michael N. Henry
 *
 * This file is part of the Cepheus Character Generator.
 *
 * GDW RPG Vehicles is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * GDW RPG Vehicles is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with GDW RPG Vehicles. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CAREERDIALOG_HH
#define CAREERDIALOG_HH

#include <QDialog>

class QModelIndex;

namespace Ui {
  class CareerDialog;
}

namespace GDW
{
  namespace RPG
  {
    class CareerDialog : public QDialog
    {
        Q_OBJECT

      public:
        explicit CareerDialog(QWidget *parent = nullptr);
        ~CareerDialog();

      private slots:
        void Select(const QModelIndex&);
        void SelectAndAccept(const QModelIndex&);

      private:
        Ui::CareerDialog *mUi;
    };
  };
};

#endif // CAREERDIALOG_HH
