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
#include "skillmodel.hh"

#include <QCoreApplication>

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

TrainingTable::TrainingTable(Characteristic a, Characteristic b, Characteristic c, Skill d, Skill e, Skill f)
  : mAttribute {
      new CharacteristicIncrementor(a),
      new CharacteristicIncrementor(b),
      new CharacteristicIncrementor(c),
      new SkillIncrementor(d),
      new SkillIncrementor(e),
      new SkillIncrementor(f)
      }
{}

TrainingTable::TrainingTable(Characteristic a, Characteristic b, Characteristic c, Characteristic d, Skill e, Skill f)
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
                             Characteristic d, Characteristic e, Skill f)
  : mAttribute {
      new CharacteristicIncrementor(a),
      new CharacteristicIncrementor(b),
      new CharacteristicIncrementor(c),
      new CharacteristicIncrementor(d),
      new CharacteristicIncrementor(e),
      new SkillIncrementor(f)
      }
{}

TrainingTable::TrainingTable(Skill a, Skill b, Skill c, Skill d, Skill e, Skill f)
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

void
TrainingTable::CharacteristicIncrementor::Increment(Character& character,
                                                    int increment)
{
  static const QString NAME[N_CHARACTERISTICS]
  {
    QCoreApplication::translate("TrainingTable", "Str"),
    QCoreApplication::translate("TrainingTable", "Dex"),
    QCoreApplication::translate("TrainingTable", "End"),
    QCoreApplication::translate("TrainingTable", "Int"),
    QCoreApplication::translate("TrainingTable", "Edu"),
    QCoreApplication::translate("TrainingTable", "Soc"),
    QCoreApplication::translate("TrainingTable", "Psi")
  };

  int level = character.Get(mCharacteristic);
  character.Set(mCharacteristic, level + increment);
  character.Log(QCoreApplication::translate("TrainingTable", increment > 0 ? "%1 +%2" : "%1 %2").arg(NAME[mCharacteristic]).arg(increment));
}

TrainingTable::SkillIncrementor::SkillIncrementor(Skill skill)
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
  SkillModel& skillModel = character.Skills();
  int level = 0;
  if(skillModel.Contains(mSkill))
    level = skillModel.Level(mSkill);
  skillModel.Level(mSkill, level + increment);
  character.Log(QCoreApplication::translate("TrainingTable", increment > 0 ? "%1 +%2" : "%1 %2").arg(SkillModel::Name(mSkill)).arg(increment));
}
