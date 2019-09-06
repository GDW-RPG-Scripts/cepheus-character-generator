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

#ifndef WORKSPACE_HH
#define WORKSPACE_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Workspace; }
QT_END_NAMESPACE

namespace GDW
{
  namespace RPG
  {
    class Stats;

    class Workspace : public QMainWindow
    {
        Q_OBJECT

      public:
        Workspace(QWidget *parent = nullptr);
        ~Workspace();

        QString NobleTitle() const;

      private slots:
        void Roll();

      private:
        void SelectCareer();

        void Log(const QString&) const;
        void LogBold(const QString&) const;

        Ui::Workspace* mUi;

        int mAge;
        Stats* mStats;
    };
  };
};
#endif // WORKSPACE_HH
