/**
 * Cepheus Character Generator, a character generator for the Cepheus Engine
 * and derived RPG systems.
 *
 * Copyright (C) 2019 Michael N. Henry
 *
 * This file is part of the Cepheus Character Generator.
 *
 * GDW RPG Vehicles is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * GDW RPG Vehicles is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with GDW RPG Vehicles. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHARACTERISTICS_HH
#define CHARACTERISTICS_HH

#include <QString>

namespace GDW
{
  namespace RPG
  {
    enum Stat
    {
      Str,
      Dex,
      End,
      Int,
      Edu,
      Soc,
      Psi,
      N_STATS
    };

    class Stats
    {
      public:
        static Stats* Roll();

        QString AsUPP() const;
        QString GetUPP(Stat) const;

        int GetMod(Stat) const;

        inline int Get(const Stat& s) const { return mStat[s]; }
        inline void Set(const Stat& s, int v) { mStat[s] = v; }

        inline int Str() const { return Get(Stat::Str); }
        inline void Str(int v) { Set(Stat::Str, v); }

        inline int Dex() const { return Get(Stat::Dex); }
        inline void Dex(int v) { Set(Stat::Dex, v); }

        inline int End() const { return Get(Stat::End); }
        inline void End(int v) { Set(Stat::End, v); }

        inline int Int() const { return Get(Stat::Int); }
        inline void Int(int v) { Set(Stat::Int, v); }

        inline int Edu() const { return Get(Stat::Edu); }
        inline void Edu(int v) { Set(Stat::Edu, v); }

        inline int Soc() const { return Get(Stat::Soc); }
        inline void Soc(int v) { Set(Stat::Soc, v); }

        inline int Psi() const { return Get(Stat::Psi); }
        inline void Psi(int v) { Set(Stat::Psi, v); }

        bool HasPsi() const;

      private:
        Stats(int, int, int, int, int, int, int = 0);

        bool mHasPsi;
        int mStat[N_STATS];
    };
  };
};

#endif // CHARACTERISTICS_HH
