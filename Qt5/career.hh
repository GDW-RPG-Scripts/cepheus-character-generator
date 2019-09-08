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

#include "stats.hh"

#include <QString>

class QStandardItem;

namespace Cepheus
{
  namespace Character
  {
    class Workspace;

    struct Check {
        Stat stat;
        int level;

        operator QString() const;
    };

    class Career
    {
      public:
        Career(const QString, const Check&, const Check&, int);
        Career(const QString, const Check&, const Check&, int,
               const Check&, const Check&);

        int QualifyOn(const Stats&) const;
        int SurviveOn(const Stats&) const;

        const QList<QStandardItem*> GetItems(Workspace*) const;

      private:
        double Section(int, int) const;

        QString mName;
        Check mQualify;
        Check mSurvive;

        bool mHasCommission;
        Check mCommission;
        Check mAdvancement;

        int mReEnlistment;
    };
  };
};

#endif // CAREER_HH
