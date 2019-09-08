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

#include "career.hh"

#include "workspace.hh"

#include <QStandardItem>

using namespace Cepheus::Character;

Check::operator QString() const
{
  return Stats::Name(stat) + " " + QString::number(level) + "+";
}

Career::Career(const QString name, const Check& qualify, const Check& survival,
               int reenlistment)
  : mName(name), mQualify(qualify), mSurvive(survival),
    mHasCommission(false), mReEnlistment(reenlistment)
{}

Career::Career(const QString name, const Check& qualify, const Check& survival,
               int reenlistment, const Check& position, const Check& promotion)
  : mName(name), mQualify(qualify), mSurvive(survival),
    mHasCommission(true), mCommission(position), mAdvancement(promotion),
    mReEnlistment(reenlistment)
{}

int
Career::QualifyOn(const Stats& stats) const
{
  return mQualify.level - stats.GetMod(mQualify.stat);
}

int
Career::SurviveOn(const Stats& stats) const
{
  return mSurvive.level - stats.GetMod(mSurvive.stat);
}

const QList<QStandardItem*>
Career::GetItems(Workspace* workspace) const
{
  int qualifyOn = QualifyOn(workspace->GetStats());
  int surviveOn = SurviveOn(workspace->GetStats());
  QString formatted =
      QString("%1%").arg(100 * Section(qualifyOn, surviveOn), 3, 'f', 2);

  QList<QStandardItem*> list =
  {
    new QStandardItem(mName),
    new QStandardItem(mQualify),
    new QStandardItem(mSurvive),
    new QStandardItem("--"),
    new QStandardItem("--"),
    new QStandardItem(formatted)
  };

  if(mHasCommission) {
    QStandardItem* pos = list[3];
    QStandardItem* pro = list[4];

    list[3] = new QStandardItem(mCommission);
    list[4] = new QStandardItem(mAdvancement);

    delete pos;
    delete pro;
  }

  return list;
}


double
Career::Section(int a, int b = 0) const
{
  if(a > 12 || b > 12)
    return 0.0;

  static double PROBABILITY[] =
  {
    36.0 / 36.0, //  0+
    36.0 / 36.0, //  1+
    36.0 / 36.0, //  2+ is 36 in 36, = 2 is 1 in 36
    35.0 / 36.0, //  3+ is 35 in 36, = 3 is 2 in 36
    33.0 / 36.0, //  4+ is 33 in 36, = 4 is 3 in 36
    30.0 / 36.0, //  5+ is 30 in 36, = 5 is 4 in 36
    26.0 / 36.0, //  6+ is 26 in 36, = 6 is 5 in 36
    21.0 / 36.0, //  7+ is 21 in 36, = 7 is 6 in 36
    15.0 / 36.0, //  8+ is 15 in 36, = 8 is 5 in 36
    10.0 / 36.0, //  9+ is 10 in 36, = 9 is 4 in 36
     6.0 / 36.0, // 10+ is  6 in 36, =10 is 3 in 36
     3.0 / 36.0, // 11+ is  3 in 36, =11 is 2 in 36
     1.0 / 36.0  // 12+ is  1 in 36, =12 is 1 in 36
  };

  double pa = 1.0;
  double pb = 1.0;

  if(a > 2) {
    pa = PROBABILITY[a];
  }
  if(b > 2) {
    pb = PROBABILITY[b];
  }

  return pa * pb;
}
