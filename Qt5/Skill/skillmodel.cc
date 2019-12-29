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

#include "skillmodel.hh"

#include <QCoreApplication>

using namespace Cepheus::Character;


SkillModel::SkillModel(QObject *parent)
  : QAbstractListModel(parent)
{}

SkillModel::SkillModel(const SkillModel& skills, QObject* parent)
  : QAbstractListModel(parent), mSkill(skills.mSkill), mLevel(skills.mLevel)
{}

SkillModel&
SkillModel::operator=(const SkillModel& skills)
{
  beginResetModel();

  mSkill = skills.mSkill;
  mLevel = skills.mLevel;

  endResetModel();

  return *this;
}

QVariant
SkillModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(orientation == Qt::Vertical || role != Qt::DisplayRole)
    return QVariant();

  static const QVariant HEADER[] =
  {
    tr("Skill"),
    tr("Level")
  };
  return HEADER[section];
}

int
SkillModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
    return 0;

  return mSkill.size();
}

QVariant
SkillModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || role != Qt::DisplayRole)
    return QVariant();

  SkillCode skill = mSkill[index.row()];

  return QVariant(Skill::Name(skill) + "-" + QString::number(mLevel[skill]));
}

const SkillCode&
SkillModel::At(int i) const
{
  return mSkill.at(i);
}

bool
SkillModel::Contains(SkillCode skill) const
{
  return mSkill.contains(skill);
}

void
SkillModel::Clear()
{
  beginResetModel();
  mSkill.clear();
  mLevel.clear();
  endResetModel();
}

int
SkillModel::Level(SkillCode skill) const
{
  if(!mSkill.contains(skill))
    return -3;

  return mLevel[skill];
}

void
SkillModel::Level(SkillCode skill, int level)
{
  if(!mSkill.contains(skill)) {
    beginInsertRows(QModelIndex(), mSkill.size(), mSkill.size());
    mSkill.append(skill);
    mLevel[skill] = level;
    endInsertRows();
  } else if(mLevel[skill] != level) {
    QModelIndex idx = index(mSkill.indexOf(skill));
    mLevel[skill] = level;
    emit dataChanged(idx, idx);
  }
}
