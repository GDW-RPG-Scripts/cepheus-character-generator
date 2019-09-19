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

#ifndef SKILLTABLE_HH
#define SKILLTABLE_HH

#include "career_global.hh"

#include "character.hh"
#include "skill.hh"

namespace Cepheus
{
  namespace Character
  {
    class Character;
    class SkillModel;

    class CAREER_EXPORT TrainingTable
    {
      public:
        TrainingTable();
        TrainingTable(const TrainingTable&);
        TrainingTable& operator=(const TrainingTable&);
        ~TrainingTable();

        TrainingTable(Characteristic, Characteristic, Characteristic,
                      Skill, Skill, Skill);
        TrainingTable(Characteristic, Characteristic, Characteristic,
                      Characteristic, Skill, Skill);
        TrainingTable(Characteristic, Characteristic, Characteristic,
                      Characteristic, Characteristic, Skill);
        TrainingTable(Skill, Skill, Skill, Skill, Skill, Skill);

        void IncrementAll(Character&, int = 1) const;

      private:
        class AttributeIncrementor
        {
          public:
            virtual ~AttributeIncrementor();
            virtual AttributeIncrementor* Copy() const = 0;
            virtual void Increment(Character&, int = 1) = 0;
        };

        class CharacteristicIncrementor : public AttributeIncrementor
        {
          public:
            CharacteristicIncrementor(Characteristic);
            CharacteristicIncrementor* Copy() const override;
            void Increment(Character&, int = 1) override;

          private:
            Characteristic mCharacteristic;
        };

        class SkillIncrementor : public AttributeIncrementor
        {
          public:
            SkillIncrementor(Skill);
            SkillIncrementor* Copy() const override;
            virtual void Increment(Character&, int = 1) override;

          private:
            Skill mSkill;
        };

        AttributeIncrementor* mAttribute[6];
    };
  };
};

#endif // SKILLTABLE_HH
