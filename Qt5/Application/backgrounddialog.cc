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

#include "backgrounddialog.hh"
#include "ui_backgrounddialog.h"

#include "character.hh"

#include <QPushButton>
#include <QDebug>

using namespace Cepheus::Character;

BackgroundDialog::BackgroundDialog(int mod, const QString& uwp, QWidget* parent)
  : QDialog(parent),
    mUi(new Ui::BackgroundDialog),
    mCount(3 + mod), mSkill(this), mSortedSkill(this)
{
  mUi->setupUi(this);
  mSortedSkill.setSourceModel(&mSkill);
  mSortedSkill.sort(0);
  mUi->skillListView->setModel(&mSortedSkill);
  mUi->countLineEdit->setText(QString::number(mCount));
  mUi->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

  AddHomeWorldSkills(uwp);
  AddPrimaryEducationSkills();
}

BackgroundDialog::~BackgroundDialog()
{
  delete mUi;
}

void
BackgroundDialog::AddHomeWorldSkills(const QString& uwp)
{
  enum UWP {
    STARP, WSIZE, ATMOS, HYDRO, POPUL, GOVRN, LAWLV, HYPHEN, TECLV
  };

  if(uwp.isEmpty() || uwp.length() != 9 || uwp.indexOf('-') != 7)
    return;

  bool ok, parsed = true;
  int wsize = uwp.mid(WSIZE, 1).toInt(&ok, 33); parsed = parsed && ok;
  int atmos = uwp.mid(ATMOS, 1).toInt(&ok, 33); parsed = parsed && ok;
  int hydro = uwp.mid(HYDRO, 1).toInt(&ok, 33); parsed = parsed && ok;
  int popul = uwp.mid(POPUL, 1).toInt(&ok, 33); parsed = parsed && ok;
  int govrn = uwp.mid(GOVRN, 1).toInt(&ok, 33); parsed = parsed && ok;
  int lawlv = uwp.mid(LAWLV, 1).toInt(&ok, 33); parsed = parsed && ok;
  int teclv = uwp.mid(TECLV, 1).toInt(&ok, 33); parsed = parsed && ok;

  if(!parsed)
    return;

  bool agric = atmos >= 4  && hydro >= 4 && popul >= 5 &&
               atmos <= 9  && hydro <= 8 && popul <= 7;
  bool astrd = wsize == 0  && atmos == 0 && hydro == 0;
  bool barrn = popul == 0  && govrn == 0 && lawlv == 0;
  bool desrt = atmos >= 2  && hydro == 0;
  bool fluid = atmos >= 10 && hydro >= 1;
  bool gardn =(atmos == 5  || atmos == 6 || atmos == 8) &&
               hydro >= 4  && hydro <= 9 &&
               popul >= 4  && popul <= 8;
  bool hipop = popul >= 9;
  bool hitec = teclv >= 12;
  bool icecp = atmos == 0  && atmos == 1 && hydro >= 1;
  bool indst =((atmos >= 0  && atmos <= 2) || atmos == 4 || atmos == 7 || atmos == 9) &&
               hydro >= 9;
  bool lopop = popul >= 1  && popul <= 3;
  bool lotec = teclv <= 5;
  bool noagr = atmos >= 0  && hydro >= 0 && popul >= 6 &&
               atmos <= 3  && hydro <= 3;
  bool noind = popul >= 4  && popul <= 6;
  bool poor  = atmos >= 2  && hydro <= 0 &&
               atmos <= 5  && hydro <= 3;
  bool rich  =(atmos == 6  || atmos == 8) &&
               popul >= 6  && popul <= 8;
  bool water = hydro == 10;
  bool vacum = atmos == 0;

  if(lawlv <= 6) {
    mSkill.Level(Skill::GunCombat, 0);
  } else if(lawlv <= 9) {
    mSkill.Level(Skill::MeleeCombat, 0);
  }

  if(agric) mSkill.Level(Skill::Animals,    0);
  if(astrd) mSkill.Level(Skill::Zero_G,     0);
  if(desrt) mSkill.Level(Skill::Survival,   0);
  if(fluid) mSkill.Level(Skill::Watercraft, 0);
  if(gardn) mSkill.Level(Skill::Animals,    0);
  if(hitec) mSkill.Level(Skill::Computer,   0);
  if(hipop) mSkill.Level(Skill::Streetwise, 0);
  if(icecp) mSkill.Level(Skill::Zero_G,     0);
  if(indst) mSkill.Level(Skill::Broker,     0);
  if(lotec) mSkill.Level(Skill::Survival,   0);
  if(poor ) mSkill.Level(Skill::Animals,    0);
  if(rich ) mSkill.Level(Skill::Carousing,  0);
  if(water) mSkill.Level(Skill::Watercraft, 0);
  if(vacum) mSkill.Level(Skill::Zero_G,     0);
}

void
BackgroundDialog::AddPrimaryEducationSkills()
{
  mSkill.Level(Skill::Admin,            0);
  mSkill.Level(Skill::Advocate,         0);
  //mSkill.Level(Skill::Animals,          0); // Probably should not be a background skill
  mSkill.Level(Skill::Carousing,        0);
  mSkill.Level(Skill::Comms,            0);
  mSkill.Level(Skill::Computer,         0);
  mSkill.Level(Skill::Electronics,      0);
  mSkill.Level(Skill::Engineering,      0);
  mSkill.Level(Skill::LifeSciences,     0);
  mSkill.Level(Skill::Linguistics,      0);
  mSkill.Level(Skill::Mechanics,        0);
  mSkill.Level(Skill::Medicine,         0);
  mSkill.Level(Skill::PhysicalSciences, 0);
  mSkill.Level(Skill::SocialSciences,   0);
  mSkill.Level(Skill::SpaceSciences,    0);
  mSkill.Level(Skill::Vehicle,          0); // Replacement for Animals (above)
}

void
BackgroundDialog::Clicked(const QModelIndex& index)
{
  QItemSelectionModel* selection = mUi->skillListView->selectionModel();
  QModelIndexList indexList = selection->selectedRows();
  int selected = indexList.size();

  mUi->countLineEdit->setText(QString::number(mCount - selected));
  mUi->dialogButtonBox
      ->button(QDialogButtonBox::Ok)
      ->setEnabled(mCount == selected);
}

bool
BackgroundDialog::GetSelection(Character& character)
{
  QModelIndexList indexList
      = mUi->skillListView->selectionModel()->selectedRows();

  for(QModelIndex proxy: indexList) {
    QModelIndex index = mSortedSkill.mapToSource(proxy);
    Skill skill = mSkill.At(index.row());
    int level = mSkill.Level(skill);
    character.Skills().Level(skill, level);
    character.Log(tr("%1 %2").arg(SkillModel::Name(skill)).arg(level));
  }

  return indexList.size() > 0;
}
