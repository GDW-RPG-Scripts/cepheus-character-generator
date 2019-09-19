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

#include "careerdialog.hh"
#include "ui_careerdialog.h"

#include "career.hh"

#include <QPushButton>
#include <QStringList>

#include <QDebug>

using namespace Cepheus::Character;

CareerDialog::CareerDialog(const Character& stats, QWidget* parent) :
  QDialog(parent),
  mUi(new Ui::CareerDialog), mModel(stats, this), mProxyModel(this)
{
  mUi->setupUi(this);

  mProxyModel.setSourceModel(&mModel);
  mProxyModel.sort(5, Qt::DescendingOrder);
  mUi->careerTableView->setModel(&mProxyModel);
  mUi->careerTableView->resizeColumnsToContents();
  mUi->careerTableView->resizeRowsToContents();
  //mUi->careerTableView->hideColumn(5);
  mUi->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

CareerDialog::~CareerDialog()
{
  delete mUi;
}

const Career*
CareerDialog::Selected() const
{
  return mCareer;
}

void
CareerDialog::Select(const QModelIndex& index)
{
  bool selected =
      mUi->careerTableView->selectionModel()->selectedRows().size() > 0;

  mUi->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(selected);

  if(selected) {
    QModelIndex source = mProxyModel.mapToSource(index);
    mCareer = Career::Get(CareerCode(source.row()));
  }
}

void
CareerDialog::SelectAndAccept(const QModelIndex& index)
{
  Select(index);
  accept();
}
