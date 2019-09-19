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

#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "Character_global.hh"

#include "skillmodel.hh"

class QTextEdit;

namespace Cepheus
{
  namespace Character
  {
    enum CHARACTER_EXPORT Characteristic
    {
      Str,
      Dex,
      End,
      Int,
      Edu,
      Soc,
      Psi,
      N_CHARACTERISTICS
    };

    class CHARACTER_EXPORT Character
    {
      public:
        static Character Roll();
        static QString Name(Characteristic stat);
        static void SetLogger(QTextEdit*);

        void Log(const QString&) const;

        Character();
        Character(const Character&);
        Character& operator=(const Character&);

        int& Age() { return mAge; }
        int& Term() { return mTerm; }
        bool& Drafted() { return mDrafted; }

        QString AsUPP() const;
        QString GetUPP(Characteristic) const;

        int GetMod(Characteristic) const;

        inline int Get(const Characteristic& s) const { return mChars[s]; }
        inline void Set(const Characteristic& s, int v) { mChars[s] = v; }

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

        SkillModel& Skills();
        const SkillModel& Skills() const;

      private:
        Character(int, int, int, int, int, int,
                  int = std::numeric_limits<int>::max());

        int mAge;
        int mTerm;
        bool mDrafted;

        int mChars[N_CHARACTERISTICS];

        SkillModel mSkills;

        static QTextEdit* LOG;
    };
  };
};

#endif // CHARACTER_HH
