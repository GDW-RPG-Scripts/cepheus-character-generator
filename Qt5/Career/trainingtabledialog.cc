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

#include "trainingtabledialog.hh"
#include "ui_trainingtabledialog.h"

#include "trainingtable.hh"

#include <QPushButton>

#include <QDebug>

using namespace Cepheus::Character;

SkillTableDialog::SkillTableDialog(Character& character,
                                   const TrainingTable& personal,
                                   const TrainingTable& service,
                                   const TrainingTable& specialist,
                                   const TrainingTable& advanced,
                                   int skills, QWidget* parent) :
  QDialog(parent),
  mUi(new Ui::SkillTableDialog),
  mIndex(0), mSkills(skills),
  mCharacter(character),
  mPersonal(personal), mService(service),
  mSpecialist(specialist), mAdvanced(advanced)
{
  mUi->setupUi(this);
  mUi->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
  // mUi->rollLineEdit->setText(QString::number(skills));
  mUi->skills1Label->setText(personal);
  mUi->skills2Label->setText(service);
  mUi->skills3Label->setText(specialist);
  mUi->skills4Label->setText(advanced);
  mUi->skillsButtonGroup->setId(mUi->skills1RadioButton, 0);
  mUi->skillsButtonGroup->setId(mUi->skills2RadioButton, 1);
  mUi->skillsButtonGroup->setId(mUi->skills3RadioButton, 2);
  mUi->skillsButtonGroup->setId(mUi->skills4RadioButton, 3);
  if(character.Edu() < 8) {
    mUi->skills4RadioButton->setEnabled(false);
    mUi->skills4Label->setEnabled(false);
  }
}

void
SkillTableDialog::Select(int index)
{
  mIndex = index;
  mUi->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void
SkillTableDialog::AddBenefits() const
{
  const TrainingTable* table[4]
  {
    &mPersonal, &mService, &mSpecialist, &mAdvanced
  };

  table[mIndex]->Roll(mCharacter);
}
