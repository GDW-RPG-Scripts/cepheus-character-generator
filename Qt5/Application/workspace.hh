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

#ifndef WORKSPACE_HH
#define WORKSPACE_HH

#include "character.hh"

#include <QMainWindow>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Workspace; }
QT_END_NAMESPACE

class QTextEdit;

namespace Cepheus
{
  namespace Character
  {
    class Career;

    class Workspace : public QMainWindow
    {
        Q_OBJECT

      public:
        Workspace(QWidget* parent = nullptr);
        ~Workspace();

        Character& GetCharacter();
        const Character& GetCharacter() const;

        QString NobleTitle() const;

      private slots:
        void Roll();

      private:
        bool BackgroundSkills();

        const Career* DraftOrDrift();
        const Career* SelectCareer();

        void Log(const QString&) const;
        void LogBold(const QString&) const;

        Ui::Workspace* mUi;

        Character mCharacter;
        QSortFilterProxyModel mSortedSkills;
    };
  };
};
#endif // WORKSPACE_HH
