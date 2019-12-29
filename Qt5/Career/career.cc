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

#include "rank.hh"
#include "die.hh"
#include "character.hh"

#include <QCoreApplication>
#include <QStandardItem>

using namespace Cepheus::Character;

Check::operator QString() const
{
  return QCoreApplication::translate("Check", "%1 %2+")
      .arg(Character::Name(mCharacteristic))
      .arg(QString::number(mLevel));
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
  : mName(career.mName), mCode(career.mCode), mQualify(career.mQualify),
    mSurvive(career.mSurvive), mHasCommission(career.mHasCommission),
    mCommission(career.mCommission), mAdvancement(career.mAdvancement),
    mReEnlistment(career.mReEnlistment),
    mBenefits(career.mBenefits),
    mPersonal(career.mPersonal), mService(career.mService),
    mSpecialist(career.mSpecialist), mAdvanced(career.mAdvanced)
{}

Career&
Career::operator=(const Career& career)
{
  mName = career.mName;
  mCode = career.mCode;
  mQualify = career.mQualify;
  mSurvive = career.mSurvive;
  mHasCommission = career.mHasCommission;
  mCommission = career.mCommission;
  mAdvancement = career.mAdvancement;
  mReEnlistment = career.mReEnlistment;
  mBenefits = career.mBenefits;
  mPersonal = career.mPersonal;
  mService = career.mService;
  mSpecialist = career.mSpecialist;
  mAdvanced = career.mAdvanced;
  return *this;
}

Career::Career(const QString name, CareerCode code,
               const Check& qualify, const Check& survival, int reenlistment,
               const TrainingTable& personal, const TrainingTable& service,
               const TrainingTable& specialist, const TrainingTable& advanced,
               const RankTable& benefits)
  : mName(name), mCode(code), mQualify(qualify), mSurvive(survival),
    mHasCommission(false), mReEnlistment(reenlistment),
    mBenefits(benefits),
    mPersonal(personal), mService(service),
    mSpecialist(specialist), mAdvanced(advanced)
{}

Career::Career(const QString name, CareerCode code,
               const Check& qualify, const Check& survival, int reenlistment,
               const TrainingTable& personal, const TrainingTable& service,
               const TrainingTable& specialist, const TrainingTable& advanced,
               const Check& position, const Check& promotion,
               const RankTable& benefits)
  : mName(name), mCode(code), mQualify(qualify), mSurvive(survival),
    mHasCommission(true), mCommission(position),
    mAdvancement(promotion), mReEnlistment(reenlistment),
    mBenefits(benefits),
    mPersonal(personal), mService(service),
    mSpecialist(specialist), mAdvanced(advanced)
{}

bool
Career::Roll(const Character& character, const Check& check)
{
  int roll = Die::Roll();
  int mod = character.GetMod(check.mCharacteristic);
  int level = check.mLevel;

  return (roll + mod) >= level;
}

bool
Career::Qualified(const Character& character) const
{
  return Roll(character, mQualify);
}

bool
Career::Survived(const Character& character) const
{
  return Roll(character, mSurvive);
}

void
Career::BasicTraining(Character& character) const
{
  mService.IncrementAll(character, 0);
}

void
Career::AddBenefits(Character& character) const
{
  mBenefits.AddBenefit(character);
}

int
Career::QualifyOn(const Character& character) const
{
  return mQualify.mLevel - character.GetMod(mQualify.mCharacteristic);
}

int
Career::SurviveOn(const Character& character) const
{
  return mSurvive.mLevel - character.GetMod(mSurvive.mCharacteristic);
}

int
Career::ReEnlistment() const
{
  return mReEnlistment;
}

bool
Career::Commission(Character& character) const
{
  if(!mHasCommission || character.Drafted() == 1)
    return false;

  if(!Roll(character, mCommission))
    return false;

  character.Rank() = 1;
  character.Log(tr("Character commissioned as %1")
                .arg(mBenefits.Name(character.Rank())));
  AddBenefits(character);

  return true;
}

bool
Career::Advance(Character& character) const
{
  if(!mHasCommission || character.Rank() == 6)
    return false;

  if(!Roll(character, mAdvancement))
    return false;

  character.Rank() += 1;
  character.Log(tr("Character promoted to %1")
                .arg(mBenefits.Name(character.Rank())));
  AddBenefits(character);

  return true;
}

QVariant
Career::GetItem(const Character& character, int index) const
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
          QString("%1%").arg(100 * Section(QualifyOn(character),
                                           SurviveOn(character)), 3, 'f', 2);
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

QString
Career::Rank(int rank) const
{
  return mBenefits.Name(rank);
}

CareerCode
Career::Code() const
{
  return mCode;
}

const TrainingTable&
Career::Personal() const
{
  return mPersonal;
}

const TrainingTable&
Career::Service() const
{
  return mService;
}

const TrainingTable&
Career::Specialist() const
{
  return mSpecialist;
}

const TrainingTable&
Career::Advanced() const
{
  return mAdvanced;
}

std::vector<Career>
Career::CAREER =
{
  {
    tr("Aerospace Defense"), AEROSPACE_DEFENCE,
    {Characteristic::End, 5}, {Characteristic::Dex, 5}, 5,
    {Str, Dex, End, Athletics, MeleeCombat, Vehicle},
    {Mechanics, GunCombat, Gunnery, MeleeCombat, Survival, Aircraft},
    {Comms, Computer, Electronics, Gunnery, Recon, Piloting},
    {Advocate, Gravitics, Jack_of_All_Trades, Medicine, Leadership, Tactics},
    {Characteristic::Edu, 6}, {Characteristic::Edu, 7},
    {{"Airman", Aircraft},
     {"Flight Officer"}, {"Flight Lieutenant"}, {"Squadron Leader", Leadership},
     {"Wing Commander"}, {"Group Captain"}, {"Air Commodore"}}
  },{
    tr("Agent"), AGENT,
    {Characteristic::Soc, 6}, {Characteristic::Int, 6}, 6,
    {Dex, End, Int, Edu, Athletics, Carousing},
    {Admin, Computer, Streetwise, Bribery, Leadership, Vehicle},
    {GunCombat, MeleeCombat, Bribery, Leadership, Recon, Survival},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Leadership},
    {Characteristic::Edu, 7}, {Characteristic::Edu, 6},
    {{"Agent", Streetwise},
     {"Special Agent"}, {"Special Agent in Charge"}, {"Unit Chief"},
     {"Section Chief", Admin}, {"Assistant Director"}, {"Director"}}
  },{
    tr("Athlete"), ATHLETE,
    {Characteristic::End, 8}, {Characteristic::Dex, 5}, 6,
    {Dex, Int, Edu, Soc, Carousing, MeleeCombat},
    {Athletics, Admin, Carousing, Computer, Gambling, Vehicle},
    {Zero_G, Athletics, Athletics, Computer, Leadership, Gambling},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Sciences},
    {Athletics}
  },{
    tr("Barbarian"), BARBARIAN,
    {Characteristic::End, 5}, {Characteristic::Str, 6}, 5,
    {Str, Dex, End, Int, Athletics, GunCombat},
    {Mechanics, GunCombat, MeleeCombat, Recon, Survival, Animals},
    {GunCombat, Jack_of_All_Trades, MeleeCombat, Recon, Animals, Tactics},
    {Advocate, Linguistics, Medicine, Leadership, Tactics, Broker},
    {MeleeCombat}
  },{
    tr("Belter"), BELTER,
    {Characteristic::Int, 4}, {Characteristic::Dex, 7}, 5,
    {Str, Dex, End, Zero_G, MeleeCombat, Gambling},
    {Comms, Demolitions, GunCombat, Gunnery, PhysicalSciences, Piloting},
    {Zero_G, Computer, Electronics, Prospecting, Sciences, Vehicle},
    {Advocate, Engineering, Medicine, Navigation, Comms, Tactics},
    {Zero_G}
  },{
    tr("Bureaucrat"), BUREAUCRAT,
    {Characteristic::Soc, 6}, {Characteristic::Edu, 4}, 5,
    {Dex, End, Int, Edu, Athletics, Carousing},
    {Admin, Computer, Carousing, Bribery, Leadership, Vehicle},
    {Admin, Computer, Advocate, Leadership, Steward, Vehicle},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Admin},
    {Characteristic::Soc, 5}, {Characteristic::Int, 8},
    {{"Assistant", Admin},
     {"Clerk"}, {"Supervisor"}, {"Manager"},
     {"Chief", Advocate}, {"Director"}, {"Minister"}}
  },{
    tr("Colonist"), COLONIST,
    {Characteristic::End, 5}, {Characteristic::End, 6}, 5,
    {Str, Dex, End, Int, Athletics, GunCombat},
    {Mechanics, GunCombat, Animals, MeleeCombat, Survival, Vehicle},
    {Survival, Electronics, Jack_of_All_Trades, Medicine, Animals, Vehicle},
    {Advocate, Linguistics, Medicine, Liaison, Admin, VeterinaryMedicine},
    {Characteristic::Int, 7}, {Characteristic::Edu, 6},
    {{"Citizen", Survival},
     {"District Leader"}, {"District Delegate"}, {"Council Advisor", Liaison},
     {"Councilor"}, {"Lieutenant Governor"}, {"Governor"}}
  },{
    tr("Diplomat"), DIPLOMAT,
    {Characteristic::Soc, 6}, {Characteristic::Edu, 5}, 5,
    {Dex, End, Int, Edu, Athletics, Carousing},
    {Admin, Computer, Carousing, Bribery, Liaison, Vehicle},
    {Carousing, Linguistics, Bribery, Liaison, Steward, Vehicle},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Leadership},
    {Characteristic::Int, 7}, {Characteristic::Soc, 7},
    {{"Attaché", Liaison},
     {"Third Secretary"}, {"Second Secretary"}, {"First Secretary", Admin},
     {"Counselor"}, {"Minister"}, {"Ambassador"}}
  },{
    tr("Drifter"), DRIFTER,
    {Characteristic::Dex, 5}, {Characteristic::End, 5}, 5,
    {Str, Dex, End, MeleeCombat, Bribery, Gambling},
    {Streetwise, Mechanics, GunCombat, MeleeCombat, Recon, Vehicle},
    {Electronics, MeleeCombat, Bribery, Streetwise, Gambling, Recon},
    {Computer, Engineering, Jack_of_All_Trades, Medicine, Liaison, Tactics},
    {}
  },{
    tr("Entertainer"), ENTERTAINER,
    {Characteristic::Soc, 8}, {Characteristic::Int, 4}, 6,
    {Dex, Int, Edu, Soc, Carousing, MeleeCombat},
    {Athletics, Admin, Carousing, Bribery, Gambling, Vehicle},
    {Computer, Carousing, Bribery, Liaison, Gambling, Recon},
    {Advocate, Computer, Carousing, Linguistics, Medicine, Sciences},
    {Carousing}
  },{
    tr("Hunter"), HUNTER,
    {Characteristic::End, 5}, {Characteristic::Str, 8}, 6,
    {Str, Dex, End, Int, Athletics, GunCombat},
    {Mechanics, GunCombat, MeleeCombat, Recon, Survival, Vehicle},
    {Admin, Comms, Electronics, Recon, Animals, Vehicle},
    {Advocate, Linguistics, Medicine, Liaison, Tactics, Animals},
    {Survival}
  },{
    tr("Marine"), MARINE,
    {Characteristic::Int, 6}, {Characteristic::End, 6}, 6,
    {Str, Dex, End, Int, Edu, MeleeCombat},
    {Comms, Demolitions, GunCombat, Gunnery, MeleeCombat, BattleDress},
    {Electronics, GunCombat, MeleeCombat, Survival, Recon, Vehicle},
    {Advocate, Computer, Gravitics, Medicine, Navigation, Tactics},
    {Characteristic::Edu, 6}, {Characteristic::Soc, 7},
    {{"Trooper", Zero_G},
     {"Lieutenant"}, {"Captain"}, {"Major", Tactics},
     {"Lt Colonel"}, {"Colonel"}, {"Brigadier"}}
  },{
    tr("Maritime Defense"), MARITIME_DEFENCE,
    {Characteristic::End, 5}, {Characteristic::End, 5}, 5,
    {Str, Dex, End, Athletics, MeleeCombat, Vehicle},
    {Mechanics, GunCombat, Gunnery, MeleeCombat, Survival, Watercraft},
    {Comms, Electronics, GunCombat, Demolitions, Recon, Watercraft},
    {Advocate, Computer, Jack_of_All_Trades, Medicine, Leadership, Tactics},
    {Characteristic::Int, 6}, {Characteristic::Edu, 7},
    {{"Seaman", Watercraft},
     {"Ensign"}, {"Lieutenant"}, {"Lt. Commander", Leadership},
     {"Commander"}, {"Captain"}, {"Admiral"}}
  },{
    tr("Mercenary"), MERCENARY,
    {Characteristic::Int, 4}, {Characteristic::End, 6}, 5,
    {Str, Dex, End, Zero_G, MeleeCombat, Gambling},
    {Comms, Mechanics, GunCombat, MeleeCombat, Gambling, BattleDress},
    {Gravitics, GunCombat, Gunnery, MeleeCombat, Recon, Vehicle},
    {Advocate, Engineering, Medicine, Navigation, Sciences, Tactics},
    {Characteristic::Int, 7}, {Characteristic::Int, 6},
    {{"Private", GunCombat},
     {"Lieutenant"}, {"Captain"}, {"Major", Tactics},
     {"Lt. Colonel"}, {"Colonel"}, {"Brigadier"}}
  },{
    tr("Merchant"), MERCHANT,
    {Characteristic::Int, 4}, {Characteristic::Int, 5}, 4,
    {Str, Dex, End, Zero_G, MeleeCombat, Steward},
    {Comms, Engineering, GunCombat, MeleeCombat, Broker, Vehicle},
    {Carousing, Gunnery, Jack_of_All_Trades, Medicine, Navigation, Piloting},
    {Advocate, Engineering, Medicine, Navigation, Sciences, Tactics},
    {Characteristic::Int, 5}, {Characteristic::Edu, 8},
    {{"Crewman", Steward},
     {"Deck Cadet"}, {"Fourth Officer"}, {"Third Officer", Piloting},
     {"Second Officer"}, {"First Officer"}, {"Captain"}}
  },{
    tr("Navy"), NAVY,
    {Characteristic::Int, 6}, {Characteristic::Int, 5}, 5,
    {Str, Dex, End, Int, Edu, MeleeCombat},
    {Comms, Engineering, GunCombat, Gunnery, MeleeCombat, Vehicle},
    {Gravitics, Jack_of_All_Trades, MeleeCombat, Navigation, Leadership, Piloting},
    {Advocate, Computer, Engineering, Medicine, Navigation, Tactics},
    {Characteristic::Soc, 7}, {Characteristic::Edu, 6},
    {{"Starman", Zero_G},
     {"Midshipman"}, {"Lieutenant"}, {"Lt. Commander", Tactics},
     {"Commander"}, {"Captain"}, {"Commodore"}}
  },{
    tr("Noble"), NOBLE,
    {Characteristic::Soc, 8}, {Characteristic::Soc, 4}, 6,
    {Dex, Int, Edu, Soc, Carousing, MeleeCombat},
    {Athletics, Admin, Carousing, Leadership, Gambling, Vehicle},
    {Computer, Carousing, GunCombat, MeleeCombat, Liaison, Animals},
    {Advocate, Computer, Liaison, Linguistics, Medicine, Sciences},
    {Characteristic::Edu, 5}, {Characteristic::Int, 8},
    {{"Courtier", Carousing},
     {"Knight"}, {"Baron"}, {"Marquis"},
     {"Count", Advocate}, {"Duke"}, {"Archduke"}}
  },{
    tr("Physician"), PHYSICIAN,
    {Characteristic::Edu, 6}, {Characteristic::Int, 4}, 5,
    {Str, Dex, End, Int, Edu, GunCombat},
    {Admin, Computer, Mechanics, Medicine, Leadership, Sciences},
    {Computer, Carousing, Electronics, Medicine, Medicine, Sciences},
    {Advocate, Computer, Jack_of_All_Trades, Linguistics, Medicine, Sciences},
    {Characteristic::Int, 5}, {Characteristic::Edu, 8},
    {{"Intern", Medicine},
     {"Resident"}, {"Senior Resident"}, {"Chief Resident"},
     {"Attending Physician", Admin}, {"Service Chief"}, {"Hospital Admin"}}
  },{
    tr("Pirate"), PIRATE,
    {Characteristic::Dex, 5}, {Characteristic::Dex, 6}, 5,
    {Str, Dex, End, MeleeCombat, Bribery, Gambling},
    {Streetwise, Electronics, GunCombat, MeleeCombat, Recon, Vehicle},
    {Zero_G, Comms, Engineering, Gunnery, Navigation, Piloting},
    {Computer, Gravitics, Jack_of_All_Trades, Medicine, Advocate, Tactics},
    {Characteristic::Str, 7}, {Characteristic::Int, 6},
    {{"Crewman", Gunnery},
     {"Corporal"}, {"Lieutenant", Piloting}, {"Lt. Commander"},
     {"Commander"}, {"Captain"}, {"Commodore"}}
  },{
    tr("Rogue"), ROGUE,
    {Characteristic::Dex, 5}, {Characteristic::Dex, 4}, 4,
    {Str, Dex, End, MeleeCombat, Bribery, Gambling},
    {Streetwise, Mechanics, GunCombat, MeleeCombat, Recon, Vehicle},
    {Computer, Electronics, Bribery, Broker, Recon, Vehicle},
    {Computer, Gravitics, Jack_of_All_Trades, Medicine, Advocate, Tactics},
    {Characteristic::Str, 6}, {Characteristic::Int, 7},
    {{"Independent", Streetwise},
     {"Associate"}, {"Soldier", GunCombat}, {"Lieutenant"},
     {"Underboss"}, {"Consigliere"}, {"Boss"}}
  },{
    tr("Scientist"), SCIENTIST,
    {Characteristic::Edu, 6}, {Characteristic::Edu, 5}, 5,
    {Str, Dex, End, Int, Edu, GunCombat},
    {Admin, Computer, Electronics, Medicine, Bribery, Sciences},
    {Navigation, Admin, Sciences, Sciences, Animals, Vehicle},
    {Advocate, Computer, Jack_of_All_Trades, Linguistics, Medicine, Sciences},
    {Characteristic::Int, 7}, {Characteristic::Int, 6},
    {{"Instructor", Sciences},
     {"Adjunct Professor"}, {"Research Professor"}, {"Assistant Professor", Computer},
     {"Associate Professor"}, {"Professor"}, {"Distinguished Professor"}}
  },{
    tr("Scout"), SCOUT,
    {Characteristic::Int, 6}, {Characteristic::End, 7}, 6,
    {Str, Dex, End, Edu, Jack_of_All_Trades, MeleeCombat},
    {Comms, Electronics, GunCombat, Gunnery, Recon, Piloting},
    {Engineering, Gunnery, Demolitions, Navigation, Medicine, Vehicle},
    {Advocate, Computer, Linguistics, Medicine, Navigation, Tactics},
    {Piloting}
  },{
    tr("Surface Defense"), SURFACE_DEFENCE,
    {Characteristic::End, 5}, {Characteristic::Edu, 5}, 5,
    {Str, Dex, End, Athletics, MeleeCombat, Vehicle},
    {Mechanics, GunCombat, Gunnery, MeleeCombat, Recon, BattleDress},
    {Comms, Demolitions, GunCombat, MeleeCombat, Survival, Vehicle},
    {Advocate, Computer, Jack_of_All_Trades, Medicine, Leadership, Tactics},
    {Characteristic::End, 6}, {Characteristic::Edu, 7},
    {{"Private", GunCombat},
     {"Lieutenant"}, {"Captain"}, {"Major", Leadership},
     {"Lt. Colonel"}, {"Colonel"}, {"General"}}
  },{
    tr("Technician"), TECHNICIAN,
    {Characteristic::Edu, 6}, {Characteristic::Dex, 4}, 5,
    {Str, Dex, End, Int, Edu, GunCombat},
    {Admin, Computer, Mechanics, Medicine, Electronics, Sciences},
    {Computer, Electronics, Gravitics, Linguistics, Engineering, Animals},
    {Advocate, Computer, Jack_of_All_Trades, Linguistics, Medicine, Sciences},
    {Characteristic::Edu, 5}, {Characteristic::Int, 8},
    {{"Technician", Computer},
     {"Team Lead"}, {"Supervisor"}, {"Manager"},
     {"Director", Admin}, {"Vice-President"}, {"Executive Officer"}}
  }
};
