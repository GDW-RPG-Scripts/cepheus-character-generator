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

#ifndef CAREER_HH
#define CAREER_HH

#include "career_global.hh"

#include "character.hh"
#include "skill.hh"
#include "trainingtable.hh"

#include <QMetaType>
#include <QObject>
#include <QString>

class QStandardItem;

namespace Cepheus
{
  namespace Character
  {
    class SkillModel;
    class TrainingTable;
    class Character;

    struct CAREER_EXPORT Check {
        Characteristic stat;
        int level;

        operator QString() const;
        operator QVariant() const;
    };

    enum CareerCode {
      AEROSPACE_DEFENCE, AGENT, ATHLETE, BARBARIAN, BELTER, BUREAUCRAT,
      COLONIST, DIPLOMAT, DRIFTER, ENTERTAINER, HUNTER, MARINE,
      MARITIME_DEFENCE, MERCENARY, MERCHANT, NAVY, NOBLE, PHYSICIAN, PIRATE,
      ROGUE, SCIENTIST, SCOUT, SURFACE_DEFENCE, TECHNICIAN,
      N_CAREERS
    };

    class CAREER_EXPORT Career : public QObject
    {
        Q_OBJECT

      public:
        static const Career* Get(CareerCode);

        Career();
        Career(const Career&);
        Career& operator=(const Career&);

        Career(const QString, const Check&, const Check&, int,
               const TrainingTable&, const TrainingTable&,
               const TrainingTable&, const TrainingTable&);
        Career(const QString, const Check&, const Check&, int,
               const TrainingTable&, const TrainingTable&,
               const TrainingTable&, const TrainingTable&,
               const Check&, const Check&);

        bool Qualify(const Character&) const;

        void BasicTraining(Character&) const;

        int QualifyOn(const Character&) const;
        int SurviveOn(const Character&) const;

        QVariant GetItem(const Character&, int) const;
        const QList<QStandardItem*> GetItems(const Character&) const;

        QString Name() const;

      private:
        double Section(int, int) const;

        QString mName;

        Check mQualify;
        Check mSurvive;

        bool mHasCommission;
        Check mCommission;
        Check mAdvancement;

        int mReEnlistment;

        TrainingTable mPersonal, mService, mSpecialist, mAdvanced;

        static std::vector<Career> CAREER;
    };
  };
};

Q_DECLARE_METATYPE(Cepheus::Character::Career)

#endif // CAREER_HH
