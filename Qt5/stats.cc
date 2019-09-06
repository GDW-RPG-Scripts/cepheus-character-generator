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

#include "stats.hh"

#include "die.hh"

#include <QDebug>

using namespace GDW::RPG;

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
