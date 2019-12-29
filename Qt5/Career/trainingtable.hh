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
        Q_DECLARE_TR_FUNCTIONS(Skill)

      public:
        TrainingTable();
        TrainingTable(const TrainingTable&);
        TrainingTable& operator=(const TrainingTable&);
        ~TrainingTable();

        TrainingTable(Characteristic, Characteristic, Characteristic,
                      SkillCode, SkillCode, SkillCode);
        TrainingTable(Characteristic, Characteristic, Characteristic,
                      Characteristic, SkillCode, SkillCode);
        TrainingTable(Characteristic, Characteristic, Characteristic,
                      Characteristic, Characteristic, SkillCode);
        TrainingTable(SkillCode, SkillCode, SkillCode, SkillCode, SkillCode, SkillCode);

        void IncrementAll(Character&, int = 1) const;
        void Roll(Character&) const;

        operator QString() const;

      private:
        class AttributeIncrementor
        {
          public:
            virtual ~AttributeIncrementor();
            virtual AttributeIncrementor* Copy() const = 0;
            virtual void Increment(Character&, int = 1) = 0;
            virtual QString AsString() const = 0;
        };

        class CharacteristicIncrementor : public AttributeIncrementor
        {
          public:
            CharacteristicIncrementor(Characteristic);
            CharacteristicIncrementor* Copy() const override;
            void Increment(Character&, int = 1) override;
            QString AsString() const override;

          private:
            Characteristic mCharacteristic;

            static const QString NAME[N_CHARACTERISTICS];
        };

        class SkillIncrementor : public AttributeIncrementor
        {
          public:
            SkillIncrementor(SkillCode);
            SkillIncrementor* Copy() const override;
            void Increment(Character&, int = 1) override;
            QString AsString() const override;

          private:
            SkillCode mSkill;
        };

        AttributeIncrementor* mAttribute[6];
    };
  };
};

#endif // SKILLTABLE_HH
