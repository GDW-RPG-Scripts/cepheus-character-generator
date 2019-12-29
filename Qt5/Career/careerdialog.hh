/**
 * Cepheus Character Generator, an RPG character generator for the Cepheus
 * Engine and derived RPG systems.
 *
 * Copyright (C) 2019 Michael N. Henry <mike.henry@mikehenry.se>
 *
 * This file is part of the Cepheus Character Generator.
 *
 * Cepheus Character Generator is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at your
 * option) any later version.
 *
 * Cepheus Character Generator is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have
 * received a copy of the GNU General Public License along with Cepheus
 * Character Generator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CAREERDIALOG_HH
#define CAREERDIALOG_HH

#include "careermodel.hh"
#include "character.hh"

#include <QDialog>
#include <QSortFilterProxyModel>

class QModelIndex;

namespace Ui {
  class CareerDialog;
}

namespace Cepheus
{
  namespace Character
  {
    class Career;
    class Characteristics;

    class CareerDialog : public QDialog
    {
        Q_OBJECT

      public:
        explicit CareerDialog(const Character&, const QVector<QString>&,
                              QWidget* = nullptr);
        ~CareerDialog();

        const Career* Selected() const;

      private slots:
        void Select(const QModelIndex&);
        void SelectAndAccept(const QModelIndex&);

      private:
        Ui::CareerDialog *mUi;

        const Career* mCareer;

        CareerModel mModel;
        QSortFilterProxyModel mProxyModel;
    };
  };
};

#endif // CAREERDIALOG_HH
