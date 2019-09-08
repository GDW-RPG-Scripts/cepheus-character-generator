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
#include "workspace.hh"

#include <QStringList>

#include <QDebug>

using namespace Cepheus::Character;

CareerDialog::CareerDialog(Workspace* workspace) :
  QDialog(workspace),
  mUi(new Ui::CareerDialog), mModel(this)
{
  mUi->setupUi(this);

  static const QStringList HEADERS = {
    tr("Career"),
    tr("Qualification"),
    tr("Survival"),
    tr("Commission"),
    tr("Advancement"),
    tr("Match")
  };

  mModel.setHorizontalHeaderLabels(HEADERS);

  static std::vector<Career> CAREER =
  {
    Career(tr("Aerospace Defense"), {Stat::End, 5}, {Stat::Dex, 5}, 5, {Stat::Edu, 6}, {Stat::Edu, 7}),
    Career(tr("Agent"),             {Stat::Soc, 6}, {Stat::Int, 6}, 6, {Stat::Edu, 7}, {Stat::Edu, 6}),
    Career(tr("Athlete"),           {Stat::End, 8}, {Stat::Dex, 5}, 6),
    Career(tr("Barbarian"),         {Stat::End, 5}, {Stat::Str, 6}, 5),
    Career(tr("Belter"),            {Stat::Int, 4}, {Stat::Dex, 7}, 5),
    Career(tr("Bureaucrat"),        {Stat::Soc, 6}, {Stat::Edu, 4}, 5, {Stat::Soc, 5}, {Stat::Int, 8}),
    Career(tr("Colonist"),          {Stat::End, 5}, {Stat::End, 6}, 5, {Stat::Int, 7}, {Stat::Edu, 6}),
    Career(tr("Diplomat"),          {Stat::Soc, 6}, {Stat::Edu, 5}, 5, {Stat::Int, 7}, {Stat::Soc, 7}),
    Career(tr("Drifter"),           {Stat::Dex, 5}, {Stat::End, 5}, 5),
    Career(tr("Entertainer"),       {Stat::Soc, 8}, {Stat::Int, 4}, 6),
    Career(tr("Hunter"),            {Stat::End, 5}, {Stat::Str, 8}, 6),
    Career(tr("Marine"),            {Stat::Int, 6}, {Stat::End, 6}, 6, {Stat::Edu, 6}, {Stat::Soc, 7}),
    Career(tr("Maritime Defense"),  {Stat::End, 5}, {Stat::End, 5}, 5, {Stat::Int, 6}, {Stat::Edu, 7}),
    Career(tr("Mercenary"),         {Stat::Int, 4}, {Stat::End, 6}, 5, {Stat::Int, 7}, {Stat::Int, 6}),
    Career(tr("Merchant"),          {Stat::Int, 4}, {Stat::Int, 5}, 4, {Stat::Int, 5}, {Stat::Edu, 8}),
    Career(tr("Navy"),              {Stat::Int, 6}, {Stat::Int, 5}, 5, {Stat::Soc, 7}, {Stat::Edu, 6}),
    Career(tr("Noble"),             {Stat::Soc, 8}, {Stat::Soc, 4}, 6, {Stat::Edu, 5}, {Stat::Int, 8}),
    Career(tr("Physician"),         {Stat::Edu, 6}, {Stat::Int, 4}, 5, {Stat::Int, 5}, {Stat::Edu, 8}),
    Career(tr("Pirate"),            {Stat::Dex, 5}, {Stat::Dex, 6}, 5, {Stat::Str, 7}, {Stat::Int, 6}),
    Career(tr("Rogue"),             {Stat::Dex, 5}, {Stat::Dex, 4}, 4, {Stat::Str, 6}, {Stat::Int, 7}),
    Career(tr("Scientist"),         {Stat::Edu, 6}, {Stat::Edu, 5}, 5, {Stat::Int, 7}, {Stat::Int, 6}),
    Career(tr("Scout"),             {Stat::Int, 6}, {Stat::End, 7}, 6),
    Career(tr("Surface Defense"),   {Stat::End, 5}, {Stat::Edu, 5}, 5, {Stat::End, 6}, {Stat::Edu, 7}),
    Career(tr("Technician"),        {Stat::Edu, 6}, {Stat::Dex, 4}, 5, {Stat::Edu, 5}, {Stat::Int, 8})
  };

  for(Career& career: CAREER)
    mModel.appendRow(career.GetItems(workspace));

  mModel.sort(5, Qt::DescendingOrder);
  mUi->careerTableView->setModel(&mModel);
  //mUi->careerTableView->hideColumn(5);
  mUi->careerTableView->resizeColumnsToContents();
  mUi->careerTableView->resizeRowsToContents();
}

CareerDialog::~CareerDialog()
{
  delete mUi;
}

Career*
CareerDialog::Selected() const
{
  return nullptr;
}

void
CareerDialog::Select(const QModelIndex& index)
{
  qDebug() << "Select: " << index;
  void* ptr = index.internalPointer();
}

void
CareerDialog::SelectAndAccept(const QModelIndex& index)
{

}
