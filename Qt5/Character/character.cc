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

#include "character.hh"

#include "die.hh"

#include <QTextEdit>

using namespace Cepheus::Character;

QTextEdit*
Character::LOG = nullptr;

void
Character::SetLogger(QTextEdit* logger)
{
  LOG = logger;
}

void
Character::Log(const QString& message) const
{
  if(LOG)
    LOG->append(message);
}

Character
Character::Roll()
{
  return Character(Die::Roll(), Die::Roll(), Die::Roll(),
                   Die::Roll(), Die::Roll(), Die::Roll());
}

Character::Character()
  : mAge(18), mTerm(0), mDrafted(false),
    mChars {
      std::numeric_limits<int>::max(),
      std::numeric_limits<int>::max(),
      std::numeric_limits<int>::max(),
      std::numeric_limits<int>::max(),
      std::numeric_limits<int>::max(),
      std::numeric_limits<int>::max(),
      std::numeric_limits<int>::max()
      }
{}

Character::Character(const Character& c)
  : mAge(18), mTerm(0), mDrafted(false),
    mChars {
      c.mChars[Characteristic::Str],
    c.mChars[Characteristic::Dex],
    c.mChars[Characteristic::End],
    c.mChars[Characteristic::Int],
    c.mChars[Characteristic::Edu],
    c.mChars[Characteristic::Soc],
    c.mChars[Characteristic::Psi]
    },
    mSkills(c.mSkills)
{}

Character&
Character::operator=(const Character& stats)
{
  mChars[Characteristic::Str] = stats.mChars[Characteristic::Str];
  mChars[Characteristic::Dex] = stats.mChars[Characteristic::Dex];
  mChars[Characteristic::End] = stats.mChars[Characteristic::End];
  mChars[Characteristic::Int] = stats.mChars[Characteristic::Int];
  mChars[Characteristic::Edu] = stats.mChars[Characteristic::Edu];
  mChars[Characteristic::Soc] = stats.mChars[Characteristic::Soc];
  mChars[Characteristic::Psi] = stats.mChars[Characteristic::Psi];

  mSkills = stats.mSkills;

  return *this;
}

Character::Character(int str, int dex, int end, int intl, int edu, int soc, int psi)
  : mAge(18), mTerm(0), mDrafted(false),
    mChars{str, dex, end, intl, edu, soc, psi}
{}

QString
Character::AsUPP() const
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
Character::GetUPP(Characteristic stat) const
{
  return QString::number(Get(stat), 33).toUpper();
}

int
Character::GetMod(Characteristic stat) const
{
  return Get(stat) / 3 - 2;
}

bool
Character::HasPsi() const
{
  return mChars[Characteristic::Psi] != std::numeric_limits<int>::max();
}

QString
Character::Name(Characteristic stat)
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

SkillModel&
Character::Skills()
{
  return mSkills;
}

const SkillModel&
Character::Skills() const
{
  return mSkills;
}
