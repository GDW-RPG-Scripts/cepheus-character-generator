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

#include "careerdialog.hh"
#include "ui_careerdialog.h"

#include <QStandardItemModel>
#include <QStringList>

using namespace GDW::RPG;

CareerDialog::CareerDialog(QWidget *parent) :
  QDialog(parent),
  mUi(new Ui::CareerDialog)
{
  mUi->setupUi(this);

  QStandardItemModel* model = new QStandardItemModel(this);

  static const QStringList HEADERS = {
    tr("Career"),
    tr("Qualification"),
    tr("Survival"),
    tr("Position"),
    tr("Promotion")
  };

  model->setHorizontalHeaderLabels(HEADERS);

  std::vector<QList<QStandardItem*> > CAREERS =
  {{
     new QStandardItem(tr("Aerospace Defense")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("Dex 5+")),
     new QStandardItem(tr("Edu 6+")),
     new QStandardItem(tr("Edu 7+"))
   }, {
     new QStandardItem(tr("Agent")),
     new QStandardItem(tr("Soc 6+")),
     new QStandardItem(tr("Int 6+")),
     new QStandardItem(tr("Edu 7+")),
     new QStandardItem(tr("Edu 6+"))
   }, {
     new QStandardItem(tr("Athlete")),
     new QStandardItem(tr("End 8+")),
     new QStandardItem(tr("Dex 5+")),
     new QStandardItem(tr("--")),
     new QStandardItem(tr("--"))
   }, {
     new QStandardItem(tr("Barbarian")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("Str 6+")),
     new QStandardItem(tr("--")),
     new QStandardItem(tr("--"))
   }, {
     new QStandardItem(tr("Belter")),
     new QStandardItem(tr("Int 4+")),
     new QStandardItem(tr("Dex 7+")),
     new QStandardItem(tr("--")),
     new QStandardItem(tr("--"))
   }, {
     new QStandardItem(tr("Bureaucrat")),
     new QStandardItem(tr("Soc 6+")),
     new QStandardItem(tr("Edu 4+")),
     new QStandardItem(tr("Soc 5+")),
     new QStandardItem(tr("Int 8+"))
   }, {
     new QStandardItem(tr("Colonist")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("End 6+")),
     new QStandardItem(tr("Int 7+")),
     new QStandardItem(tr("Edu 6+"))
   }, {
     new QStandardItem(tr("Diplomat")),
     new QStandardItem(tr("Soc 6+")),
     new QStandardItem(tr("Edu 5+")),
     new QStandardItem(tr("Int 7+")),
     new QStandardItem(tr("Soc 7+"))
   }, {
     new QStandardItem(tr("Drifter")),
     new QStandardItem(tr("Dex 5+")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("--")),
     new QStandardItem(tr("--"))
   }, {
     new QStandardItem(tr("Entertainer")),
     new QStandardItem(tr("Soc 8+")),
     new QStandardItem(tr("Int 4+")),
     new QStandardItem(tr("--")),
     new QStandardItem(tr("--"))
   }, {
     new QStandardItem(tr("Hunter")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("Str 8+")),
     new QStandardItem(tr("--")),
     new QStandardItem(tr("--"))
   }, {
     new QStandardItem(tr("Marine")),
     new QStandardItem(tr("Int 6+")),
     new QStandardItem(tr("End 6+")),
     new QStandardItem(tr("Edu 6+")),
     new QStandardItem(tr("Soc 7+"))
   }, {
     new QStandardItem(tr("Maritime Defense")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("Int 6+")),
     new QStandardItem(tr("Edu 7+"))
   }, {
     new QStandardItem(tr("Mercenary")),
     new QStandardItem(tr("Int 4+")),
     new QStandardItem(tr("End 6+")),
     new QStandardItem(tr("Int 7+")),
     new QStandardItem(tr("Int 6+"))
   }, {
     new QStandardItem(tr("Merchant")),
     new QStandardItem(tr("Int 4+")),
     new QStandardItem(tr("Int 5+")),
     new QStandardItem(tr("Int 5+")),
     new QStandardItem(tr("Edu 8+"))
   }, {
     new QStandardItem(tr("Navy")),
     new QStandardItem(tr("Int 6+")),
     new QStandardItem(tr("Int 5+")),
     new QStandardItem(tr("Soc 7+")),
     new QStandardItem(tr("Edu 6+"))
   }, {
     new QStandardItem(tr("Noble")),
     new QStandardItem(tr("Soc 8+")),
     new QStandardItem(tr("Soc 4+")),
     new QStandardItem(tr("Edu 5+")),
     new QStandardItem(tr("Int 8+"))
   }, {
     new QStandardItem(tr("Physician")),
     new QStandardItem(tr("Edu 6+")),
     new QStandardItem(tr("Int 4+")),
     new QStandardItem(tr("Int 5+")),
     new QStandardItem(tr("Edu 8+"))
   }, {
     new QStandardItem(tr("Pirate")),
     new QStandardItem(tr("Dex 5+")),
     new QStandardItem(tr("Dex 6+")),
     new QStandardItem(tr("Str 7+")),
     new QStandardItem(tr("Int 6+"))
   }, {
     new QStandardItem(tr("Rogue")),
     new QStandardItem(tr("Dex 5+")),
     new QStandardItem(tr("Dex 4+")),
     new QStandardItem(tr("Str 6+")),
     new QStandardItem(tr("Int 7+"))
   }, {
     new QStandardItem(tr("Scientist")),
     new QStandardItem(tr("Edu 6+")),
     new QStandardItem(tr("Edu 5+")),
     new QStandardItem(tr("Int 7+")),
     new QStandardItem(tr("Int 6+"))
   }, {
     new QStandardItem(tr("Scout")),
     new QStandardItem(tr("Int 6+")),
     new QStandardItem(tr("End 7+")),
     new QStandardItem(tr("--")),
     new QStandardItem(tr("--"))
   }, {
     new QStandardItem(tr("Surface Defense")),
     new QStandardItem(tr("End 5+")),
     new QStandardItem(tr("Edu 5+")),
     new QStandardItem(tr("End 6+")),
     new QStandardItem(tr("Edu 7+"))
   }, {
     new QStandardItem(tr("Technician")),
     new QStandardItem(tr("Edu 6+")),
     new QStandardItem(tr("Dex 4+")),
     new QStandardItem(tr("Edu 5+")),
     new QStandardItem(tr("Int 8+"))
   }};

  for(QList<QStandardItem*> list: CAREERS) {
    model->appendRow(list);
  }

  mUi->careerTableView->setModel(model);
  mUi->careerTableView->resizeColumnsToContents();
  mUi->careerTableView->resizeRowsToContents();
}

CareerDialog::~CareerDialog()
{
  delete mUi;
}

void
CareerDialog::Select(const QModelIndex&)
{

}

void
CareerDialog::SelectAndAccept(const QModelIndex&)
{

}
