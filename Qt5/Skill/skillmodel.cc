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

QString
SkillModel::Name(Skill skill)
{
  return SKILL[skill];
}

const QHash<Skill, QString> SkillModel::SKILL =
{
  {Skill::Admin,              QCoreApplication::translate("Skill", "Admin")},
  {Skill::Advocate,           QCoreApplication::translate("Skill", "Advocate")},
  {Skill::Aircraft,           QCoreApplication::translate("Skill", "Aircraft")},
  {Skill::Airship,            QCoreApplication::translate("Skill", "Airship")},
  {Skill::Animals,            QCoreApplication::translate("Skill", "Animals")},
  {Skill::Archery,            QCoreApplication::translate("Skill", "Archery")},
  {Skill::Athletics,          QCoreApplication::translate("Skill", "Athletics")},
  {Skill::BattleDress,        QCoreApplication::translate("Skill", "Battle Dress")},
  {Skill::BayWeapons,         QCoreApplication::translate("Skill", "Bay Weapons")},
  {Skill::BludgeoningWeapons, QCoreApplication::translate("Skill", "Bludgeoning Weapons")},
  {Skill::Bribery,            QCoreApplication::translate("Skill", "Bribery")},
  {Skill::Broker,             QCoreApplication::translate("Skill", "Broker")},
  {Skill::Carousing,          QCoreApplication::translate("Skill", "Carousing")},
  {Skill::Comms,              QCoreApplication::translate("Skill", "Comms")},
  {Skill::Computer,           QCoreApplication::translate("Skill", "Computer")},
  {Skill::Demolitions,        QCoreApplication::translate("Skill", "Demolitions")},
  {Skill::Electronics,        QCoreApplication::translate("Skill", "Electronics")},
  {Skill::EnergyPistol,       QCoreApplication::translate("Skill", "Energy Pistol")},
  {Skill::EnergyRifle,        QCoreApplication::translate("Skill", "Energy Rifle")},
  {Skill::Engineering,        QCoreApplication::translate("Skill", "Engineering")},
  {Skill::Farming,            QCoreApplication::translate("Skill", "Farming")},
  {Skill::Gambling,           QCoreApplication::translate("Skill", "Gambling")},
  {Skill::GravVehicle,        QCoreApplication::translate("Skill", "Grav Vehicle")},
  {Skill::Gravitics,          QCoreApplication::translate("Skill", "Gravitics")},
  {Skill::GunCombat,          QCoreApplication::translate("Skill", "Gun Combat")},
  {Skill::Gunnery,            QCoreApplication::translate("Skill", "Gunnery")},
  {Skill::HeavyWeapons,       QCoreApplication::translate("Skill", "Heavy Weapons")},
  {Skill::Jack_of_All_Trades, QCoreApplication::translate("Skill", "Jack-of-All-Trades")},
  {Skill::Leadership,         QCoreApplication::translate("Skill", "Leadership")},
  {Skill::Linguistics,        QCoreApplication::translate("Skill", "Linguistics")},
  {Skill::Liaison,            QCoreApplication::translate("Skill", "Liaison")},
  {Skill::LifeSciences,       QCoreApplication::translate("Skill", "Life Sciences")},
  {Skill::Mechanics,          QCoreApplication::translate("Skill", "Mechanics")},
  {Skill::Medicine,           QCoreApplication::translate("Skill", "Medicine")},
  {Skill::MeleeCombat,        QCoreApplication::translate("Skill", "Melee Combat")},
  {Skill::Mole,               QCoreApplication::translate("Skill", "Mole")},
  {Skill::Motorboats,         QCoreApplication::translate("Skill", "Motorboats")},
  {Skill::NaturalWeapons,     QCoreApplication::translate("Skill", "Natural Weapons")},
  {Skill::Navigation,         QCoreApplication::translate("Skill", "Navigation")},
  {Skill::OceanShips,         QCoreApplication::translate("Skill", "Ocean Ships")},
  {Skill::PhysicalSciences,   QCoreApplication::translate("Skill", "Physical Sciences")},
  {Skill::PiercingWeapons,    QCoreApplication::translate("Skill", "Piercing Weapons")},
  {Skill::Piloting,           QCoreApplication::translate("Skill", "Piloting")},
  {Skill::Prospecting,        QCoreApplication::translate("Skill", "Prospecting")},
  {Skill::Recon,              QCoreApplication::translate("Skill", "Recon")},
  {Skill::Riding,             QCoreApplication::translate("Skill", "Riding")},
  {Skill::RotorAircraft,      QCoreApplication::translate("Skill", "Rotor Aircraft")},
  {Skill::Sciences,           QCoreApplication::translate("Skill", "Sciences")},
  {Skill::SailingShips,       QCoreApplication::translate("Skill", "Sailing Ships")},
  {Skill::Screens,            QCoreApplication::translate("Skill", "Screens")},
  {Skill::Shotgun,            QCoreApplication::translate("Skill", "")},
  {Skill::SlashingWeapons,    QCoreApplication::translate("Skill", "Slashing Weapons")},
  {Skill::SlugPistol,         QCoreApplication::translate("Skill", "Slug Pistol")},
  {Skill::SlugRifle,          QCoreApplication::translate("Skill", "Slug Rifle")},
  {Skill::SocialSciences,     QCoreApplication::translate("Skill", "Social Sciences")},
  {Skill::SpaceSciences,      QCoreApplication::translate("Skill", "Space Sciences")},
  {Skill::SpinalMounts,       QCoreApplication::translate("Skill", "Spinal Mounts")},
  {Skill::Steward,            QCoreApplication::translate("Skill", "Steward")},
  {Skill::Streetwise,         QCoreApplication::translate("Skill", "Streetwise")},
  {Skill::Submarine,          QCoreApplication::translate("Skill", "Submarine")},
  {Skill::Survival,           QCoreApplication::translate("Skill", "Survival")},
  {Skill::Tactics,            QCoreApplication::translate("Skill", "Tactics")},
  {Skill::TrackedVehicle,     QCoreApplication::translate("Skill", "Tracked Vehicle")},
  {Skill::TurretWeapons,      QCoreApplication::translate("Skill", "Turret Weapons")},
  {Skill::Vehicle,            QCoreApplication::translate("Skill", "Vehicle")},
  {Skill::VeterinaryMedicine, QCoreApplication::translate("Skill", "Veterinary Medicine")},
  {Skill::Watercraft,         QCoreApplication::translate("Skill", "Watercraft")},
  {Skill::WheeledVehicle,     QCoreApplication::translate("Skill", "Wheeled Vehicle")},
  {Skill::WingedAircraft,     QCoreApplication::translate("Skill", "Winged Aircraft")},
  {Skill::Zero_G,             QCoreApplication::translate("Skill", "Zero_G")}
};

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

  Skill skill = mSkill[index.row()];

  return QVariant(SKILL[skill] + "-" + QString::number(mLevel[skill]));
}

const Skill&
SkillModel::At(int i) const
{
  return mSkill.at(i);
}

bool
SkillModel::Contains(Skill skill) const
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
SkillModel::Level(Skill skill) const
{
  if(!mSkill.contains(skill))
    return -3;

  return mLevel[skill];
}

void
SkillModel::Level(Skill skill, int level)
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
