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
  : mAge(18), mDrafted(false), mRank(0), mTerm(0),
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

Character::Character(const Character& character)
  : mAge(character.mAge), mDrafted(character.mDrafted),
    mRank(character.mRank), mTerm(character.mTerm),
    mChars {
      character.mChars[Characteristic::Str],
    character.mChars[Characteristic::Dex],
    character.mChars[Characteristic::End],
    character.mChars[Characteristic::Int],
    character.mChars[Characteristic::Edu],
    character.mChars[Characteristic::Soc],
    character.mChars[Characteristic::Psi]
    },
    mSkills(character.mSkills)
{}

Character&
Character::operator=(const Character& character)
{
  mAge = character.mAge;
  mRank = character.mRank;
  mTerm = character.mTerm;
  mDrafted = character.mDrafted;

  mChars[Characteristic::Str] = character.mChars[Characteristic::Str];
  mChars[Characteristic::Dex] = character.mChars[Characteristic::Dex];
  mChars[Characteristic::End] = character.mChars[Characteristic::End];
  mChars[Characteristic::Int] = character.mChars[Characteristic::Int];
  mChars[Characteristic::Edu] = character.mChars[Characteristic::Edu];
  mChars[Characteristic::Soc] = character.mChars[Characteristic::Soc];
  mChars[Characteristic::Psi] = character.mChars[Characteristic::Psi];

  mSkills = character.mSkills;

  return *this;
}

Character::Character(int str, int dex, int end, int intl, int edu, int soc, int psi)
  : mAge(18), mDrafted(false), mRank(0), mTerm(0),
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
