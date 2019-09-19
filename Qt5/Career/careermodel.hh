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

#ifndef CAREERMODEL_HH
#define CAREERMODEL_HH

#include <QAbstractTableModel>

#include "career.hh"

namespace Cepheus
{
  namespace Character
  {
    class Career;

    class CareerModel : public QAbstractTableModel
    {
        Q_OBJECT

      public:
        explicit CareerModel(const Character&, QObject* = nullptr);

        // Header:
        QVariant headerData(int, Qt::Orientation, int = Qt::DisplayRole) const override;

        // Basic functionality:
        int rowCount(const QModelIndex& = QModelIndex()) const override;
        int columnCount(const QModelIndex& = QModelIndex()) const override;

        QVariant data(const QModelIndex&, int = Qt::DisplayRole) const override;

      private:
        const Character& mStats;
    };
  };
};

#endif // CAREERMODEL_HH
