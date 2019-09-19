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

#include "backgrounddialog.hh"
#include "career.hh"
#include "careerdialog.hh"
#include "draftordriftdialog.hh"

#include <cstdlib>

using namespace Cepheus::Character;

Workspace::Workspace(QWidget* parent)
  : QMainWindow(parent),
    mUi(new Ui::Workspace),
    mSortedSkills(this)
{
  mUi->setupUi(this);
  mSortedSkills.setSourceModel(&mCharacter.Skills());
  mSortedSkills.sort(0);
  mUi->skillListView->setModel(&mSortedSkills);

  Character::SetLogger(mUi->logTextEdit);

  srand(time(NULL));

  setUnifiedTitleAndToolBarOnMac(true);
}

Workspace::~Workspace()
{
  delete mUi;
}

Character&
Workspace::GetCharacter()
{
  return mCharacter;
}

const Character&
Workspace::GetCharacter() const
{
  return mCharacter;
}

#define MOD(x) ((((x) > 0) ? "+" : "") + QString::number(x))

void
Workspace::Roll()
{
  mCharacter = Character::Roll();

  mUi->ageLineEdit->setText(QString::number(mCharacter.Age()));
  mUi->termLineEdit->setText(QString::number(mCharacter.Term()));
  mUi->titleLineEdit->setText(NobleTitle());
  mUi->uppLineEdit->setText(mCharacter.AsUPP());
  mUi->careerLineEdit->clear();
  mUi->logTextEdit->clear();
  mUi->createPushButton->setText(tr("Reroll"));

  Log(tr("Age=%1")                .arg(mCharacter.Age(), -2));
  Log(tr("Strength=%1\t\t%2")     .arg(mCharacter.Str(), -2).arg(MOD(mCharacter.GetMod(Characteristic::Str)), 2));
  Log(tr("Dexterity=%1\t\t%2")    .arg(mCharacter.Dex(), -2).arg(MOD(mCharacter.GetMod(Characteristic::Dex)), 2));
  Log(tr("Endurance=%1\t%2")      .arg(mCharacter.End(), -2).arg(MOD(mCharacter.GetMod(Characteristic::End)), 2));
  Log(tr("Intelligence=%1\t%2")   .arg(mCharacter.Int(), -2).arg(MOD(mCharacter.GetMod(Characteristic::Int)), 2));
  Log(tr("Education=%1\t%2")      .arg(mCharacter.Edu(), -2).arg(MOD(mCharacter.GetMod(Characteristic::Edu)), 2));
  Log(tr("Social Standing=%1\t%2").arg(mCharacter.Soc(), -2).arg(MOD(mCharacter.GetMod(Characteristic::Soc)), 2));

  if(mCharacter.Soc() > 9)
    Log(tr("Noble Title=%1").arg(NobleTitle()));

  LogBold(tr("Term %1").arg(mCharacter.Term()));

  if(!BackgroundSkills())
    return;

  const Career* career = SelectCareer();

  if(!career)
    return;

  mUi->careerLineEdit->setText(career->Name());

  career->BasicTraining(mCharacter);
}

QString
Workspace::NobleTitle() const
{
  switch (mCharacter.Soc()) {
    case 10:
      return tr("Lord/Lady");

    case 11:
      return tr("Knight/Dame");

    case 12:
      return tr("Baron/Baroness");

    case 13:
      return tr("Marquis/Marchioness");

    case 14:
      return tr("Count/Countess");

    case 15:
      return tr("Duke/Duchess");

    case 16:
      return tr("Archduke/Archduchess");

    case 17:
      return tr("Crown Prince/Princess");

    case 18:
      return tr("Emperor/Empress");

    default:
      return "";
  }
}

bool
Workspace::BackgroundSkills()
{
  BackgroundDialog dialog(mCharacter.GetMod(Edu),
                          mUi->homeUWPLineEdit->text(), this);

  if(dialog.exec() != CareerDialog::Accepted) {
    return false;
  }

  return dialog.GetSelection(mCharacter);
}

const Career*
Workspace::DraftOrDrift()
{
  DraftOrDriftDialog dialog(this);

  if(dialog.exec() != CareerDialog::Accepted || !dialog.HasSelection()) {
    return nullptr;
  }

  return dialog.GetCareer(mCharacter.Drafted());
}

const Career*
Workspace::SelectCareer()
{
  CareerDialog dialog(mCharacter, this);

  if(dialog.exec() != CareerDialog::Accepted) {
    return nullptr;
  }

  const Career* career = dialog.Selected();

  if(!career)
    return nullptr;

  if(career->Qualify(mCharacter)) {
    Log(tr("Successfully qualified for a %1 career.").arg(career->Name()));
    return career;
  }

  Log(tr("Failed qualification for a %1 career.").arg(career->Name()));

  career = DraftOrDrift();

  if(!career)
    return nullptr;

  if(career == Career::Get(DRIFTER))
    Log(tr("Going on the Drift."));
  else
    Log(tr("Drafted into a %1 career.").arg(career->Name()));

  return career;
}

void
Workspace::Log(const QString& message) const
{
  mCharacter.Log(message);
}

void
Workspace::LogBold(const QString& message) const
{
  mCharacter.Log(tr("<b>%1</b>").arg(message));
}
