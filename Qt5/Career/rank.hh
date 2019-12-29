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

#ifndef ADVANCEMENT_HH
#define ADVANCEMENT_HH

#include "career_global.hh"

#include "skill.hh"

#include <QMetaType>
#include <QString>

#include <vector>

namespace Cepheus
{
  namespace Character
  {
    class Character;

    class CAREER_EXPORT Rank {
      public:
        Rank(const QString& = {}, SkillCode = NO_SKILL);

        inline QString GetName() const  { return mName; }
        inline SkillCode   GetSkill() const { return mSkill; }

      private:
        QString mName;
        SkillCode mSkill;
    };

    class CAREER_EXPORT RankTable
    {
      public:
        RankTable(SkillCode = NO_SKILL);
        RankTable(const Rank&,
                 const Rank&, const Rank&, const Rank&,
                 const Rank&, const Rank&, const Rank&);

        RankTable(const RankTable&);
        RankTable& operator=(const RankTable&);
        ~RankTable();

        void AddBenefit(Character&) const;
        QString Name(int) const;

      private:
        std::vector<Rank> mRanks;
    };
  };
};

#endif // ADVANCEMENT_HH
