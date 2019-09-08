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

#include "stats.hh"

#include "die.hh"

#include <QDebug>

using namespace Cepheus::Character;

Stats*
Stats::Roll()
{
  Stats* result =
      new Stats(Die::Roll(), Die::Roll(), Die::Roll(),
                Die::Roll(), Die::Roll(), Die::Roll());

  return result;
}

Stats::Stats(int str, int dex, int end, int intl, int edu, int soc, int psi)
  : mHasPsi(false), mStat{str, dex, end, intl, edu, soc, psi}
{}

QString
Stats::AsUPP() const
{
  QString result;

  for(int i = 0; i < N_STATS-1; i++) {
    result += GetUPP(Stat(i));
  }

  if(HasPsi())
    result += "-" + GetUPP(Stat::Psi);

  return result;
}

QString
Stats::GetUPP(Stat stat) const
{
  return QString::number(Get(stat), 33).toUpper();
}

int
Stats::GetMod(Stat stat) const
{
  return Get(stat) / 3 - 2;
}

bool
Stats::HasPsi() const
{
  return mHasPsi;
}

QString
Stats::Name(Stat stat)
{
  static const QHash<Stat, QString> STAT_NAMES =
  {
    {Stat::Str, "Str"},
    {Stat::Dex, "Dex"},
    {Stat::End, "End"},
    {Stat::Int, "Int"},
    {Stat::Edu, "Edu"},
    {Stat::Soc, "Soc"},
    {Stat::Psi, "Psi"}
  };

  return STAT_NAMES[stat];
}
