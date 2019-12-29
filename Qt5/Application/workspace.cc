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

#include "agingdialog.hh"
#include "backgrounddialog.hh"
#include "career.hh"
#include "careerdialog.hh"
#include "die.hh"
#include "draftordriftdialog.hh"
#include "reenlistdialog.hh"
#include "trainingtabledialog.hh"

#include <array>
#include <cstdlib>

using namespace Cepheus::Character;

Workspace::Workspace(QWidget* parent)
  : QMainWindow(parent)
  , mUi(new Ui::Workspace)
  , mTerminate(false)
  , mSortedSkills(this)
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

void
Workspace::Roll()
{
  mCareers.clear();
  mCareerLength.clear();
  mCharacter = Character::Roll();

  mUi->ageLineEdit->setText(QString::number(mCharacter.Age()));
  mUi->careerLineEdit->clear();
  mUi->createPushButton->setText(tr("Reroll"));
  mUi->logTextEdit->clear();
  mUi->rankLineEdit->clear();
  mUi->termLineEdit->setText(QString::number(mCharacter.Term()));
  mUi->titleLineEdit->setText(NobleTitle());
  mUi->uppLineEdit->setText(mCharacter.AsUPP());

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

  const Career* career;

  while((career = SelectCareer())) {
    mCareers.append(career->Name());

    mUi->careerLineEdit->setText(career->Name());
    mUi->rankLineEdit->setText(career->Rank(mCharacter.Rank()));
    mUi->termLineEdit->setText(QString::number(mCharacter.Term()));

    // On the first term of a new career, you gain Basic Training
    // as you learn the basics for your chosen career.
    if(mCareers.length() == 1) {
      // For your first career only, you get all the skills listed in
      // the Service Skills table at Level 0 as your basic training.
      career->BasicTraining(mCharacter);
    } else {
      // For any subsequent careers, you may pick any one skill listed
      // in the Service Skills table at Level 0 as your basic training.
      // SkillSelectDialog dialog(career->Service());
    }

    career->AddBenefits(mCharacter);

    do {
      LogBold(tr("Term %1").arg(++mCharacter.Term()));

      mCareerLength[career->Name()] += 1;

      mUi->careerLineEdit->setText(career->Name());
      mUi->termLineEdit->setText(QString::number(mCharacter.Term()));

      if(!career->Survived(mCharacter)) {
        QString name = mUi->characterNameLineEdit->text();
        Log(tr("%1 suffered death.")
            .arg(name.length() > 0 ? name : tr("Character")));
        Log(tr("Press Reroll to create a new character."));
        return;
      }

      if(mCharacter.Rank() == 0 && career->Commission(mCharacter))
        TermSkillsAndTraining(career);

      if(mCharacter.Rank() > 0 && career->Advance(mCharacter))
        TermSkillsAndTraining(career);

      mUi->rankLineEdit->setText(career->Rank(mCharacter.Rank()));

      TermSkillsAndTraining(career);
      AgingCheck();
    } while(ReEnlist(career));

    MusterOut(career);
  }
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

void
Workspace::AgingCheck()
{
  mUi->ageLineEdit->setText(QString::number(mCharacter.Age() += 4));

  if(mCharacter.Age() < 34)
    return;

  int roll = Die::Roll() - mCharacter.Term();
  Log(tr("Aging roll: %1").arg(roll));
  if(roll <= 0) {
    std::vector<int> mental;
    std::vector<int> physical;

    switch(roll) {
      case -2:
        physical.push_back(1);
      case -1:
        physical.push_back(1);
      case 0:
        physical.push_back(1);
        break;

      case -3:
        physical.push_back(2);
        physical.push_back(1);
        physical.push_back(1);
        break;

      case -4:
        physical.push_back(2);
        physical.push_back(2);
        physical.push_back(1);
        break;

      case -5:
        physical.push_back(2);
        physical.push_back(2);
        physical.push_back(2);
        break;

      default:
        physical.push_back(2);
        physical.push_back(2);
        physical.push_back(2);
        mental.push_back(1);
        break;
    }

    AgingDialog dialog(mCharacter, mental, physical);

    if(dialog.exec() != SkillTableDialog::Accepted) {
      return;
    }

    int selection = dialog.Selected();
    for(int n : physical) {
      Characteristic c = Characteristic((selection & 0x03) - 1);
      int characteristic = mCharacter.Get(c) - n;
      Log(tr("%1 reduced by %2: %3")
          .arg(Character::Name(c))
          .arg(n)
          .arg(characteristic));
      mCharacter.Set(c, characteristic);
      selection >>= 2;
    }

    for(int n : mental) {
      Characteristic c = Characteristic((selection & 0x03) + 2);
      int characteristic = mCharacter.Get(c) - n;
      Log(tr("%1 reduced by %2: %3")
          .arg(Character::Name(c))
          .arg(n)
          .arg(characteristic));
      mCharacter.Set(c, characteristic);
      selection >>= 2;
    }

    mUi->uppLineEdit->setText(mCharacter.AsUPP());
  }
}

void
Workspace::MusterOut(const Career* career)
{

}

bool
Workspace::ReEnlist(const Career* career)
{
  ReenlistDialog dialog;

  if(dialog.exec() != SkillTableDialog::Accepted) {
    return false;
  }

  int roll = Die::Roll();

  if(dialog.ReEnlist()) {
    // A character may not serve 7 or more terms unless rolling a natural 12
    if(mCharacter.Term() >= 7 && roll != 12) {
      Log(tr("Forced into retirement after serving 7 or more terms."));
      return false;
    }

    // A character may re-enlist by making a re-enlist check
    if(roll >= career->ReEnlistment()) {
      if(mCharacter.Term() < 7)
        Log(tr("Re-enlisted for another term."));
      else
        Log(tr("Re-enlistment approved despite serving 7 or more terms."));

      return true;
    }

    Log(tr("Failed re-enlistment."));
    return false;
  } else
    // Rolling a natural 12 forces re-enlistment
    if(roll == 12) {
      Log(tr("Forced to re-enlist for one more term."));
      return true;
    }

  Log(tr("Mustered out of %1.").arg(career->Name()));
  return false;
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

void
Workspace::TermSkillsAndTraining(const Career* career)
{
  int skillRolls;

  switch (career->Code()) {
    case ATHLETE:
    case BARBARIAN:
    case BELTER:
    case DRIFTER:
    case ENTERTAINER:
    case HUNTER:
    case SCOUT:
      skillRolls = 2;
      break;

    default:
      skillRolls = 1;
  }

  for (int i = 0; i < skillRolls; i++) {
    SkillTableDialog dialog(mCharacter,
                            career->Personal(), career->Service(),
                            career->Specialist(), career->Advanced());

    if(dialog.exec() != SkillTableDialog::Accepted) {
      return;
    }

    dialog.AddBenefits();
  }

  mUi->uppLineEdit->setText(mCharacter.AsUPP());
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
  CareerDialog dialog(mCharacter, mCareers, this);

  if(dialog.exec() != CareerDialog::Accepted) {
    return nullptr;
  }

  const Career* career = dialog.Selected();

  if(!career)
    return nullptr;

  if(career->Qualified(mCharacter)) {
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
