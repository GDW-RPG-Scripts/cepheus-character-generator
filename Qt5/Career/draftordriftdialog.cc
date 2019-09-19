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

#include "draftordriftdialog.hh"
#include "ui_draftordriftdialog.h"

#include "career.hh"
#include "die.hh"

using namespace Cepheus::Character;

DraftOrDriftDialog::DraftOrDriftDialog(QWidget* parent)
  : QDialog(parent)
  , mUi(new Ui::DraftOrDriftDialog)
  , mSelected(std::numeric_limits<int>::max())
{
  mUi->setupUi(this);
  mUi->selectionButtonGroup->setId(mUi->draftRadioButton, CareerCode::N_CAREERS);
  mUi->selectionButtonGroup->setId(mUi->driftRadioButton, CareerCode::DRIFTER);
}

DraftOrDriftDialog::~DraftOrDriftDialog()
{
  delete mUi;
}

bool
DraftOrDriftDialog::HasSelection() const
{
  return mSelected != std::numeric_limits<int>::max();
}

const Career*
DraftOrDriftDialog::GetCareer(bool& drafted) const
{
  if(mSelected > N_CAREERS)
    return nullptr;

  CareerCode selected = CareerCode(mSelected);

  drafted = selected == N_CAREERS;

  if(drafted) {
    static CareerCode DRAFT_CAREER[] = {
      AEROSPACE_DEFENCE, MARINE, MARITIME_DEFENCE, NAVY, SCOUT, SURFACE_DEFENCE
    };

    selected = DRAFT_CAREER[Die::Roll(1, 0)];
  }

  return Career::Get(selected);
}

void
DraftOrDriftDialog::Select(int id)
{
  mSelected = id;
}
