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

#include "characteristics.hh"

#include "die.hh"

#include <QDebug>

using namespace Cepheus::Character;

Characteristics
Characteristics::Roll()
{
  return Characteristics(Die::Roll(), Die::Roll(), Die::Roll(),
               Die::Roll(), Die::Roll(), Die::Roll());
}

Characteristics::Characteristics()
  : mStat{std::numeric_limits<int>::max(),
          std::numeric_limits<int>::max(),
          std::numeric_limits<int>::max(),
          std::numeric_limits<int>::max(),
          std::numeric_limits<int>::max(),
          std::numeric_limits<int>::max(),
          std::numeric_limits<int>::max()}
{}

Characteristics::Characteristics(const Characteristics& stats)
  : mStat{stats.mStat[Characteristic::Str], stats.mStat[Characteristic::Dex], stats.mStat[Characteristic::End],
    stats.mStat[Characteristic::Int], stats.mStat[Characteristic::Edu], stats.mStat[Characteristic::Soc],
    stats.mStat[Characteristic::Psi]}
{}

Characteristics&
Characteristics::operator=(const Characteristics& stats)
{
  mStat[Characteristic::Str] = stats.mStat[Characteristic::Str];
  mStat[Characteristic::Dex] = stats.mStat[Characteristic::Dex];
  mStat[Characteristic::End] = stats.mStat[Characteristic::End];
  mStat[Characteristic::Int] = stats.mStat[Characteristic::Int];
  mStat[Characteristic::Edu] = stats.mStat[Characteristic::Edu];
  mStat[Characteristic::Soc] = stats.mStat[Characteristic::Soc];
  mStat[Characteristic::Psi] = stats.mStat[Characteristic::Psi];

  return *this;
}

Characteristics::Characteristics(int str, int dex, int end, int intl, int edu, int soc, int psi)
  : mStat{str, dex, end, intl, edu, soc, psi}
{}

QString
Characteristics::AsUPP() const
{
  QString result;

  for(int i = 0; i < N_CHARACTERISTICS-1; i++) {
    result += GetUPP(Characteristic(i));
  }

  if(HasPsi())
    result += "-" + GetUPP(Characteristic::Psi);

  return result;
}

QString
Characteristics::GetUPP(Characteristic stat) const
{
  return QString::number(Get(stat), 33).toUpper();
}

int
Characteristics::GetMod(Characteristic stat) const
{
  return Get(stat) / 3 - 2;
}

bool
Characteristics::HasPsi() const
{
  return mStat[Characteristic::Psi] != std::numeric_limits<int>::max();
}

QString
Characteristics::Name(Characteristic stat)
{
  static const QHash<Characteristic, QString> STAT_NAMES =
  {
    {Characteristic::Str, "Str"},
    {Characteristic::Dex, "Dex"},
    {Characteristic::End, "End"},
    {Characteristic::Int, "Int"},
    {Characteristic::Edu, "Edu"},
    {Characteristic::Soc, "Soc"},
    {Characteristic::Psi, "Psi"}
  };

  return STAT_NAMES[stat];
}
