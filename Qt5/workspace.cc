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

#include "workspace.hh"
#include "ui_workspace.h"

#include "career.hh"
#include "careerdialog.hh"
#include "stats.hh"

#include <cstdlib>

using namespace Cepheus::Character;

Workspace::Workspace(QWidget *parent)
  : QMainWindow(parent)
  , mUi(new Ui::Workspace)
{
  mUi->setupUi(this);

  srand(time(NULL));

  setUnifiedTitleAndToolBarOnMac(true);
}

Workspace::~Workspace()
{
  delete mUi;

  if(mStats)
    delete mStats;
}

Stats&
Workspace::GetStats()
{
  return *mStats;
}

const Stats&
Workspace::GetStats() const
{
  return *mStats;
}

#define MOD(x) ((((x) > 0) ? "+" : "") + QString::number(x))

void
Workspace::Roll()
{
  if (mStats) {
    delete mStats;
  }

  mAge = 18;
  mStats = Stats::Roll();

  mUi->ageLineEdit->setText(QString::number(mAge));
  mUi->uppLineEdit->setText(mStats->AsUPP());
  mUi->titleLineEdit->setText(NobleTitle());
  mUi->logTextEdit->clear();

  Log("Age="             + QString::number(mAge));
  Log("Strength="        + QString::number(mStats->Str()) + " (" + MOD(mStats->GetMod(Stat::Str)) + ")");
  Log("Dexterity="       + QString::number(mStats->Dex()) + " (" + MOD(mStats->GetMod(Stat::Dex)) + ")");
  Log("Endurance="       + QString::number(mStats->End()) + " (" + MOD(mStats->GetMod(Stat::End)) + ")");
  Log("Intelligence="    + QString::number(mStats->Int()) + " (" + MOD(mStats->GetMod(Stat::Int)) + ")");
  Log("Education="       + QString::number(mStats->Edu()) + " (" + MOD(mStats->GetMod(Stat::Edu)) + ")");
  Log("Social Standing=" + QString::number(mStats->Soc()) + " (" + MOD(mStats->GetMod(Stat::Soc)) + ")");

  if(mStats->Soc() > 9)
    Log("Noble Title=" + NobleTitle());
  LogBold("Term 0");

  Career* career = SelectCareer();
}

QString
Workspace::NobleTitle() const
{
  switch (mStats->Soc()) {
    case 10:
      return "Lord/Lady";

    case 11:
      return "Knight/Dame";

    case 12:
      return "Baron/Baroness";

    case 13:
      return "Marquis/Marchioness";

    case 14:
      return "Count/Countess";

    case 15:
      return "Duke/Duchess";

    case 16:
      return "Archduke/Archduchess";

    case 17:
      return "Crown Prince/Princess";

    case 18:
      return "Emperor/Empress";

    default:
      return "";
  }
}

Career*
Workspace::SelectCareer()
{
  CareerDialog dialog(this);

  if(dialog.exec() != CareerDialog::Accepted) {
    return nullptr;
  }

  return dialog.Selected();
}

void
Workspace::Log(const QString& message) const
{
  mUi->logTextEdit->append(message);
}

void
Workspace::LogBold(const QString& message) const
{
  mUi->logTextEdit->append("<b>" + message + "</b>");
}
