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

#include "rank.hh"

#include "character.hh"
#include "skillmodel.hh"

using namespace Cepheus::Character;

Rank::Rank(const QString& name, SkillCode skill)
  : mName(name), mSkill(skill)
{}

//
// Benefits
//

RankTable::RankTable(const RankTable& benefits)
  : mRanks(benefits.mRanks)
{}

RankTable&
RankTable::operator=(const RankTable& benefits)
{
  mRanks = benefits.mRanks;
  return *this;
}

RankTable::~RankTable()
{}

RankTable::RankTable(SkillCode skill)
  : mRanks{{"", skill}, {}, {}, {}, {}, {}}
{}

RankTable::RankTable(const Rank& a,
                   const Rank& b, const Rank& c, const Rank& d,
                   const Rank& e, const Rank& f, const Rank& g)
  : mRanks{a, b, c, d, e, f, g}
{}

void
RankTable::AddBenefit(Character& character) const
{
  SkillCode skill = Skill::Cascade(mRanks[character.Rank()].GetSkill());

  if(skill == NO_SKILL)
    return;

  int level = character.Skills().Contains(skill) ?
                character.Skills().Level(skill) : 0;

  character.Skills().Level(skill, level+1);
  character.Log(QString("%1 +1").arg(Skill::Name(skill)));
}

QString
RankTable::Name(int rank) const
{
  return mRanks[rank].GetName();
}
