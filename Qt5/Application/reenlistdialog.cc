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

#include "reenlistdialog.hh"
#include "ui_reenlistdialog.h"

#include <QPushButton>

using namespace Cepheus::Character;

ReenlistDialog::ReenlistDialog(QWidget *parent)
  : QDialog(parent)
  , mUi(new Ui::ReenlistDialog)
  , mSelected(std::numeric_limits<int>::max())
{
  mUi->setupUi(this);
  mUi->reenlistButtonGroup->setId(mUi->musterOutBadioButton, 0);
  mUi->reenlistButtonGroup->setId(mUi->reenlistRadioButton, 1);
  mUi->reenlistButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

ReenlistDialog::~ReenlistDialog()
{
  delete mUi;
}

bool
ReenlistDialog::HasSelection() const
{
  return mSelected != std::numeric_limits<int>::max();
}

bool
ReenlistDialog::MusterOut() const
{
  return mSelected == 0;
}

bool
ReenlistDialog::ReEnlist() const
{
  return mSelected == 1;
}

void
ReenlistDialog::Select(int id)
{
  mSelected = id;
  mUi->reenlistButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
