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

#ifndef CHARACTERISTICS_HH
#define CHARACTERISTICS_HH

#include "Characteristics_global.hh"

#include <QString>

namespace Cepheus
{
  namespace Character
  {
    class CHARACTERISTICS_EXPORT Characteristics
    {
      public:
        static Characteristics Roll();

        static QString Name(Characteristic);

        Characteristics();
        Characteristics(const Characteristics&);
        Characteristics& operator=(const Characteristics&);

        QString AsUPP() const;
        QString GetUPP(Characteristic) const;

        int GetMod(Characteristic) const;

        inline int Get(const Characteristic& s) const { return mStat[s]; }
        inline void Set(const Characteristic& s, int v) { mStat[s] = v; }

        inline int Str() const { return Get(Characteristic::Str); }
        inline void Str(int v) { Set(Characteristic::Str, v); }

        inline int Dex() const { return Get(Characteristic::Dex); }
        inline void Dex(int v) { Set(Characteristic::Dex, v); }

        inline int End() const { return Get(Characteristic::End); }
        inline void End(int v) { Set(Characteristic::End, v); }

        inline int Int() const { return Get(Characteristic::Int); }
        inline void Int(int v) { Set(Characteristic::Int, v); }

        inline int Edu() const { return Get(Characteristic::Edu); }
        inline void Edu(int v) { Set(Characteristic::Edu, v); }

        inline int Soc() const { return Get(Characteristic::Soc); }
        inline void Soc(int v) { Set(Characteristic::Soc, v); }

        inline int Psi() const { return Get(Characteristic::Psi); }
        inline void Psi(int v) { Set(Characteristic::Psi, v); }

        bool HasPsi() const;

      private:
        Characteristics(int, int, int, int, int, int,
              int = std::numeric_limits<int>::max());

        int mStat[N_CHARACTERISTICS];
    };
  };
};

#endif // CHARACTERISTICS_HH
