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

#include "die.hh"
#include "character.hh"

#include <QStandardItem>

using namespace Cepheus::Character;

Check::operator QString() const
{
  return Character::Name(stat) + " " + QString::number(level) + "+";
}

Check::operator QVariant() const
{
  return operator QString();
}

const Career*
Career::Get(CareerCode index)
{
  return &CAREER[index];
}

Career::Career()
{}

Career::Career(const Career& career)
  : mName(career.mName), mQualify(career.mQualify),
    mSurvive(career.mSurvive), mHasCommission(career.mHasCommission),
    mCommission(career.mCommission), mAdvancement(career.mAdvancement),
    mReEnlistment(career.mReEnlistment),
    mPersonal(career.mPersonal), mService(career.mService),
    mSpecialist(career.mSpecialist), mAdvanced(career.mAdvanced)
{}

Career&
Career::operator=(const Career& career)
{
  mName = career.mName;
  mQualify = career.mQualify;
  mSurvive = career.mSurvive;
  mHasCommission = career.mHasCommission;
  mCommission = career.mCommission;
  mAdvancement = career.mAdvancement;
  mReEnlistment = career.mReEnlistment;
  mPersonal = career.mPersonal;
  mService = career.mService;
  mSpecialist = career.mSpecialist;
  mAdvanced = career.mAdvanced;
  return *this;
}

Career::Career(const QString name,
               const Check& qualify, const Check& survival, int reenlistment,
               const TrainingTable& personal, const TrainingTable& service,
               const TrainingTable& specialist, const TrainingTable& advanced)
  : mName(name), mQualify(qualify), mSurvive(survival),
    mHasCommission(false), mReEnlistment(reenlistment),
    mPersonal(personal), mService(service),
    mSpecialist(specialist), mAdvanced(advanced)
{}

Career::Career(const QString name,
               const Check& qualify, const Check& survival, int reenlistment,
               const TrainingTable& personal, const TrainingTable& service,
               const TrainingTable& specialist, const TrainingTable& advanced,
               const Check& position, const Check& promotion)
  : mName(name), mQualify(qualify), mSurvive(survival),
    mHasCommission(true), mCommission(position), mAdvancement(promotion),
    mReEnlistment(reenlistment),
    mPersonal(personal), mService(service),
    mSpecialist(specialist), mAdvanced(advanced)
{}

bool
Career::Qualify(const Character& stats) const
{
  int roll = Die::Roll();
  int mod = stats.GetMod(mQualify.stat);
  int level = mQualify.level;

  return (roll + mod) >= level;
}

void
Career::BasicTraining(Character& character) const
{
  mService.IncrementAll(character, 0);
}

int
Career::QualifyOn(const Character& stats) const
{
  return mQualify.level - stats.GetMod(mQualify.stat);
}

int
Career::SurviveOn(const Character& stats) const
{
  return mSurvive.level - stats.GetMod(mSurvive.stat);
}

QVariant
Career::GetItem(const Character& stats, int index) const
{
  switch (index) {
    case 0:
      return mName;

    case 1:
      return mQualify;

    case 2:
      return mSurvive;

    case 3:
      return mHasCommission ? mCommission : QVariant("--");

    case 4:
      return mHasCommission ? mAdvancement : QVariant("--");

    case 5:
      return
          QString("%1%").arg(100 * Section(QualifyOn(stats),
                                           SurviveOn(stats)), 3, 'f', 2);
    default:
      return QVariant();
  }
}
const QList<QStandardItem*>
Career::GetItems(const Character& stats) const
{
  int qualifyOn = QualifyOn(stats);
  int surviveOn = SurviveOn(stats);
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

QString
Career::Name() const
{
  return mName;
}

std::vector<Career>
Career::CAREER
{
  {
    tr("Aerospace Defense"),
    {Characteristic::End, 5}, {Characteristic::Dex, 5}, 5,
    {Str, Dex, End, Athletics, MeleeCombat, Vehicle},
    {Mechanics, GunCombat, Gunnery, MeleeCombat, Survival, Aircraft},
    {Comms, Computer, Electronics, Gunnery, Recon, Piloting},
    {Advocate, Gravitics, Jack_of_All_Trades, Medicine, Leadership, Tactics},
    {Characteristic::Edu, 6}, {Characteristic::Edu, 7}
  },{
    tr("Agent"),
    {Characteristic::Soc, 6}, {Characteristic::Int, 6}, 6,
    {Dex, End, Int, Edu, Athletics, Carousing},
    {Admin, Computer, Streetwise, Bribery, Leadership, Vehicle},
    {GunCombat, MeleeCombat, Bribery, Leadership, Recon, Survival},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Leadership},
    {Characteristic::Edu, 7}, {Characteristic::Edu, 6}
  },{
    tr("Athlete"),
    {Characteristic::End, 8}, {Characteristic::Dex, 5}, 6,
    {Dex, Int, Edu, Soc, Carousing, MeleeCombat},
    {Athletics, Admin, Carousing, Computer, Gambling, Vehicle},
    {Zero_G, Athletics, Athletics, Computer, Leadership, Gambling},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Sciences},
  },{
    tr("Barbarian"),
    {Characteristic::End, 5}, {Characteristic::Str, 6}, 5,
    {Str, Dex, End, Int, Athletics, GunCombat},
    {Mechanics, GunCombat, MeleeCombat, Recon, Survival, Animals},
    {GunCombat, Jack_of_All_Trades, MeleeCombat, Recon, Animals, Tactics},
    {Advocate, Linguistics, Medicine, Leadership, Tactics, Broker}
  },{
    tr("Belter"),
    {Characteristic::Int, 4}, {Characteristic::Dex, 7}, 5,
    {Str, Dex, End, Zero_G, MeleeCombat, Gambling},
    {Comms, Demolitions, GunCombat, Gunnery, PhysicalSciences, Piloting},
    {Zero_G, Computer, Electronics, Prospecting, Sciences, Vehicle},
    {Advocate, Engineering, Medicine, Navigation, Comms, Tactics}
  },{
    tr("Bureaucrat"),
    {Characteristic::Soc, 6}, {Characteristic::Edu, 4}, 5,
    {Dex, End, Int, Edu, Athletics, Carousing},
    {Admin, Computer, Carousing, Bribery, Leadership, Vehicle},
    {Admin, Computer, Advocate, Leadership, Steward, Vehicle},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Admin},
    {Characteristic::Soc, 5}, {Characteristic::Int, 8}
  },{
    tr("Colonist"),
    {Characteristic::End, 5}, {Characteristic::End, 6}, 5,
    {Str, Dex, End, Int, Athletics, GunCombat},
    {Mechanics, GunCombat, Animals, MeleeCombat, Survival, Vehicle},
    {Survival, Electronics, Jack_of_All_Trades, Medicine, Animals, Vehicle},
    {Advocate, Linguistics, Medicine, Liaison, Admin, VeterinaryMedicine},
    {Characteristic::Int, 7}, {Characteristic::Edu, 6}
  },{
    tr("Diplomat"),
    {Characteristic::Soc, 6}, {Characteristic::Edu, 5}, 5,
    {Dex, End, Int, Edu, Athletics, Carousing},
    {Admin, Computer, Carousing, Bribery, Liaison, Vehicle},
    {Carousing, Linguistics, Bribery, Liaison, Steward, Vehicle},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Leadership},
    {Characteristic::Int, 7}, {Characteristic::Soc, 7}
  },{
    tr("Drifter"),
    {Characteristic::Dex, 5}, {Characteristic::End, 5}, 5,
    {Str, Dex, End, MeleeCombat, Bribery, Gambling},
    {Streetwise, Mechanics, GunCombat, MeleeCombat, Recon, Vehicle},
    {Electronics, MeleeCombat, Bribery, Streetwise, Gambling, Recon},
    {Computer, Engineering, Jack_of_All_Trades, Medicine, Liaison, Tactics}
  },{
    tr("Entertainer"),
    {Characteristic::Soc, 8}, {Characteristic::Int, 4}, 6,
    {Dex, Int, Edu, Soc, Carousing, MeleeCombat},
    {Athletics, Admin, Carousing, Bribery, Gambling, Vehicle},
    {Computer, Carousing, Bribery, Liaison, Gambling, Recon},
    {Advocate, Computer, Carousing, Linguistics, Medicine, Sciences}
  },{
    tr("Hunter"),
    {Characteristic::End, 5}, {Characteristic::Str, 8}, 6,
    {Str, Dex, End, Int, Athletics, GunCombat},
    {Mechanics, GunCombat, MeleeCombat, Recon, Survival, Vehicle},
    {Admin, Comms, Electronics, Recon, Animals, Vehicle},
    {Advocate, Linguistics, Medicine, Liaison, Tactics, Animals}
  },{
    tr("Marine"),
    {Characteristic::Int, 6}, {Characteristic::End, 6}, 6,
    {Str, Dex, End, Int, Edu, MeleeCombat},
    {Comms, Demolitions, GunCombat, Gunnery, MeleeCombat, BattleDress},
    {Electronics, GunCombat, MeleeCombat, Survival, Recon, Vehicle},
    {Advocate, Computer, Gravitics, Medicine, Navigation, Tactics},
    {Characteristic::Edu, 6}, {Characteristic::Soc, 7}
  },{
    tr("Maritime Defense"),
    {Characteristic::End, 5}, {Characteristic::End, 5}, 5,
    {Str, Dex, End, Athletics, MeleeCombat, Vehicle},
    {Mechanics, GunCombat, Gunnery, MeleeCombat, Survival, Watercraft},
    {Comms, Electronics, GunCombat, Demolitions, Recon, Watercraft},
    {Advocate, Computer, Jack_of_All_Trades, Medicine, Leadership, Tactics},
    {Characteristic::Int, 6}, {Characteristic::Edu, 7}
  },{
    tr("Mercenary"),
    {Characteristic::Int, 4}, {Characteristic::End, 6}, 5,
    {Str, Dex, End, Zero_G, MeleeCombat, Gambling},
    {Comms, Mechanics, GunCombat, MeleeCombat, Gambling, BattleDress},
    {Gravitics, GunCombat, Gunnery, MeleeCombat, Recon, Vehicle},
    {Advocate, Engineering, Medicine, Navigation, Sciences, Tactics},
    {Characteristic::Int, 7}, {Characteristic::Int, 6}
  },{
    tr("Merchant"),
    {Characteristic::Int, 4}, {Characteristic::Int, 5}, 4,
    {Str, Dex, End, Zero_G, MeleeCombat, Steward},
    {Comms, Engineering, GunCombat, MeleeCombat, Broker, Vehicle},
    {Carousing, Gunnery, Jack_of_All_Trades, Medicine, Navigation, Piloting},
    {Advocate, Engineering, Medicine, Navigation, Sciences, Tactics},
    {Characteristic::Int, 5}, {Characteristic::Edu, 8}
  },{
    tr("Navy"),
    {Characteristic::Int, 6}, {Characteristic::Int, 5}, 5,
    {Str, Dex, End, Int, Edu, MeleeCombat},
    {Comms, Engineering, GunCombat, Gunnery, MeleeCombat, Vehicle},
    {Gravitics, Jack_of_All_Trades, MeleeCombat, Navigation, Leadership, Piloting},
    {Advocate, Computer, Engineering, Medicine, Navigation, Tactics},
    {Characteristic::Soc, 7}, {Characteristic::Edu, 6}
  },{
    tr("Noble"),
    {Characteristic::Soc, 8}, {Characteristic::Soc, 4}, 6,
    {Dex, Int, Edu, Soc, Carousing, MeleeCombat},
    {Athletics, Admin, Carousing, Leadership, Gambling, Vehicle},
    {Computer, Carousing, GunCombat, MeleeCombat, Liaison, Animals},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Sciences},
    {Characteristic::Edu, 5}, {Characteristic::Int, 8}
  },{
    tr("Physician"),
    {Characteristic::Edu, 6}, {Characteristic::Int, 4}, 5,
    {Str, Dex, End, Int, Edu, GunCombat},
    {Admin, Computer, Mechanics, Medicine, Leadership, Sciences},
    {Computer, Carousing, Electronics, Medicine, Medicine, Sciences},
    {Advocate, Computer, Jack_of_All_Trades, Linguistics, Medicine, Sciences},
    {Characteristic::Int, 5}, {Characteristic::Edu, 8}
  },{
    tr("Pirate"),
    {Characteristic::Dex, 5}, {Characteristic::Dex, 6}, 5,
    {Str, Dex, End, MeleeCombat, Bribery, Gambling},
    {Streetwise, Electronics, GunCombat, MeleeCombat, Recon, Vehicle},
    {Zero_G, Comms, Engineering, Gunnery, Navigation, Piloting},
    {Computer, Gravitics, Jack_of_All_Trades, Medicine, Advocate, Tactics},
    {Characteristic::Str, 7}, {Characteristic::Int, 6}
  },{
    tr("Rogue"),
    {Characteristic::Dex, 5}, {Characteristic::Dex, 4}, 4,
    {Str, Dex, End, MeleeCombat, Bribery, Gambling},
    {Streetwise, Mechanics, GunCombat, MeleeCombat, Recon, Vehicle},
    {Computer, Electronics, Bribery, Broker, Recon, Vehicle},
    {Computer, Gravitics, Jack_of_All_Trades, Medicine, Advocate, Tactics},
    {Characteristic::Str, 6}, {Characteristic::Int, 7}
  },{
    tr("Scientist"),
    {Characteristic::Edu, 6}, {Characteristic::Edu, 5}, 5,
    {Str, Dex, End, Int, Edu, GunCombat},
    {Admin, Computer, Electronics, Medicine, Bribery, Sciences},
    {Navigation, Admin, Sciences, Sciences, Animals, Vehicle},
    {Advocate, Computer, Jack_of_All_Trades, Linguistics, Medicine, Sciences},
    {Characteristic::Int, 7}, {Characteristic::Int, 6}
  },{
    tr("Scout"),
    {Characteristic::Int, 6}, {Characteristic::End, 7}, 6,
    {Str, Dex, End, Edu, Jack_of_All_Trades, MeleeCombat},
    {Comms, Electronics, GunCombat, Gunnery, Recon, Piloting},
    {Engineering, Gunnery, Demolitions, Navigation, Medicine, Vehicle},
    {Advocate, Computer, Linguistics, Medicine, Navigation, Tactics}
  },{
    tr("Surface Defense"),
    {Characteristic::End, 5}, {Characteristic::Edu, 5}, 5,
    {Str, Dex, End, Athletics, MeleeCombat, Vehicle},
    {Mechanics, GunCombat, Gunnery, MeleeCombat, Recon, BattleDress},
    {Comms, Demolitions, GunCombat, MeleeCombat, Survival, Vehicle},
    {Advocate, Computer, Jack_of_All_Trades, Medicine, Leadership, Tactics},
    {Characteristic::End, 6}, {Characteristic::Edu, 7}
  },{
    tr("Technician"),
    {Characteristic::Edu, 6}, {Characteristic::Dex, 4}, 5,
    {Str, Dex, End, Int, Edu, GunCombat},
    {Admin, Computer, Mechanics, Medicine, Electronics, Sciences},
    {Computer, Electronics, Gravitics, Linguistics, Engineering, Animals},
    {Advocate, Computer, Jack_of_All_Trades, Linguistics, Medicine, Sciences},
    {Characteristic::Edu, 5}, {Characteristic::Int, 8}
  }
};
