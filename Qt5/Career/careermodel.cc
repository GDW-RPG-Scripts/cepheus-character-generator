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

#include "careermodel.hh"

#include "career.hh"

using namespace Cepheus::Character;

CareerModel::CareerModel(const Character& stats, QObject* parent)
  : QAbstractTableModel(parent), mStats(stats)
{}

QVariant
CareerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(orientation == Qt::Vertical || role != Qt::DisplayRole)
    return QVariant();

  static const QVariant HEADER[] =
  {
    tr("Career"),
    tr("Qualification"),
    tr("Survival"),
    tr("Commission"),
    tr("Advancement"),
    tr("Match")
  };
  return HEADER[section];
}

int
CareerModel::rowCount(const QModelIndex& index) const
{
  return N_CAREERS;
}

int
CareerModel::columnCount(const QModelIndex& index) const
{
  return 6;
}

QVariant
CareerModel::data(const QModelIndex& index, int role) const
{
  if(role != Qt::DisplayRole)
    return QVariant();

  return Career::Get(CareerCode(index.row()))->GetItem(mStats, index.column());
}
