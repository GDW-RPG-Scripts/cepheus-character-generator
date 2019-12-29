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

#include "trainingtable.hh"

#include "character.hh"
#include "die.hh"
#include "skillmodel.hh"

#include <QCoreApplication>

#

using namespace Cepheus::Character;

TrainingTable::TrainingTable()
  : mAttribute{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
{}

TrainingTable::TrainingTable(const TrainingTable& table)
  : mAttribute{
      table.mAttribute[0]->Copy(),
    table.mAttribute[1]->Copy(),
    table.mAttribute[2]->Copy(),
    table.mAttribute[3]->Copy(),
    table.mAttribute[4]->Copy(),
    table.mAttribute[5]->Copy()
  }
{}

TrainingTable&
TrainingTable::operator=(const TrainingTable& table)
{
  for(int i = 0; i < 6; i++)
    mAttribute[i] = table.mAttribute[i]->Copy();

  return *this;
}

TrainingTable::TrainingTable(Characteristic a, Characteristic b, Characteristic c, SkillCode d, SkillCode e, SkillCode f)
  : mAttribute {
      new CharacteristicIncrementor(a),
      new CharacteristicIncrementor(b),
      new CharacteristicIncrementor(c),
      new SkillIncrementor(d),
      new SkillIncrementor(e),
      new SkillIncrementor(f)
      }
{}

TrainingTable::TrainingTable(Characteristic a, Characteristic b, Characteristic c, Characteristic d, SkillCode e, SkillCode f)
  : mAttribute {
      new CharacteristicIncrementor(a),
      new CharacteristicIncrementor(b),
      new CharacteristicIncrementor(c),
      new CharacteristicIncrementor(d),
      new SkillIncrementor(e),
      new SkillIncrementor(f)
      }
{}

TrainingTable::TrainingTable(Characteristic a, Characteristic b, Characteristic c,
                             Characteristic d, Characteristic e, SkillCode f)
  : mAttribute {
      new CharacteristicIncrementor(a),
      new CharacteristicIncrementor(b),
      new CharacteristicIncrementor(c),
      new CharacteristicIncrementor(d),
      new CharacteristicIncrementor(e),
      new SkillIncrementor(f)
      }
{}

TrainingTable::TrainingTable(SkillCode a, SkillCode b, SkillCode c, SkillCode d, SkillCode e, SkillCode f)
  : mAttribute {
      new SkillIncrementor(a),
      new SkillIncrementor(b),
      new SkillIncrementor(c),
      new SkillIncrementor(d),
      new SkillIncrementor(e),
      new SkillIncrementor(f)
      }
{}

TrainingTable::~TrainingTable()
{
  for(int i = 0; i < 6; i++)
    delete mAttribute[i];
}

void
TrainingTable::IncrementAll(Character& character, int increment) const
{
  for(int i = 0; i < 6; i++) {
    mAttribute[i]->Increment(character, increment);
  }
}

void
TrainingTable::Roll(Character& character) const
{
  mAttribute[Die::Roll(1, 0)]->Increment(character);
}

TrainingTable::operator QString() const
{
  QString result;
  for(int i = 0; i < 6; i++) {
    result += "\n";
    result += mAttribute[i]->AsString();
  }
  return result;
}

//
// -- Incrementor Functions
//

TrainingTable::AttributeIncrementor::~AttributeIncrementor()
{}

TrainingTable::CharacteristicIncrementor::CharacteristicIncrementor(Characteristic characteristic)
  : mCharacteristic(characteristic)
{}

TrainingTable::CharacteristicIncrementor*
TrainingTable::CharacteristicIncrementor::Copy() const
{
  return new CharacteristicIncrementor(mCharacteristic);
}

const QString
TrainingTable::CharacteristicIncrementor::NAME[]
{
  tr("Str"), tr("Dex"), tr("End"), tr("Int"), tr("Edu"), tr("Soc"),
  tr("Psi")
};

void
TrainingTable::CharacteristicIncrementor::Increment(Character& character,
                                                    int increment)
{
  int level = character.Get(mCharacteristic);
  character.Set(mCharacteristic, level + increment);
  character.Log(tr(increment > 0 ? "%1 +%2" : "%1 %2").arg(NAME[mCharacteristic]).arg(increment));
}

QString
TrainingTable::CharacteristicIncrementor::AsString() const
{
  return QString("+1 %1").arg(NAME[mCharacteristic]);
}


TrainingTable::SkillIncrementor::SkillIncrementor(SkillCode skill)
  : mSkill(skill)
{}

TrainingTable::SkillIncrementor*
TrainingTable::SkillIncrementor::Copy() const
{
  return new SkillIncrementor(mSkill);
}

void
TrainingTable::SkillIncrementor::Increment(Character& character,
                                           int increment)
{
  SkillCode skill = Skill::Cascade(mSkill);

  int level = 0;
  SkillModel& skillModel = character.Skills();
  if(skillModel.Contains(skill))
    level = skillModel.Level(skill);
  skillModel.Level(skill, level + increment);
  character.Log(tr(increment > 0 ? "%1 +%2" : "%1 %2").arg(Skill::Name(skill)).arg(increment));
}

QString
TrainingTable::SkillIncrementor::AsString() const
{
  return Skill::Name(mSkill);
}
