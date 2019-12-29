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

#include "skill.hh"
#include "skillcascadedialog.hh"

using namespace Cepheus::Character;

SkillCode
Skill::Cascade(SkillCode skillCode)
{
  switch (skillCode) {
    case SkillCode::Animals:
    case SkillCode::GunCombat:
    case SkillCode::Gunnery:
    case SkillCode::MeleeCombat:
    case SkillCode::Sciences:
    case SkillCode::Vehicle:
    case SkillCode::Aircraft:
    case SkillCode::GroundVehicle:
    case SkillCode::Watercraft: {
      SkillCascadeDialog dialog(skillCode);

      if(dialog.exec() != SkillCascadeDialog::Accepted) {
        return NO_SKILL;
      }

      return dialog.Selection();
    }
    default:
      return skillCode;
  }
}

SkillCode
Skill::Code(QString skill)
{
  return MAP.Code[skill];
}

QString
Skill::Name(SkillCode skill)
{
  return MAP.Name[skill];
}

QHash<QString, SkillCode>
Skill::Map::Remap(std::initializer_list<std::pair<SkillCode, QString> > list)
{
  QHash<QString, SkillCode> map;
  for(auto item: list)
  {
    map.insert(item.second, item.first);
  }
  return map;
}

Skill::Map::Map(std::initializer_list<std::pair<SkillCode, QString> > list)
  : Code(Remap(list)), Name(list)
{}

const Skill::Map Skill::MAP =
{
  {SkillCode::Admin,              tr("Admin")},
  {SkillCode::Advocate,           tr("Advocate")},
  {SkillCode::Aircraft,           tr("Aircraft")},
  {SkillCode::Airship,            tr("Airship")},
  {SkillCode::Animals,            tr("Animals")},
  {SkillCode::Archery,            tr("Archery")},
  {SkillCode::Athletics,          tr("Athletics")},
  {SkillCode::BattleDress,        tr("Battle Dress")},
  {SkillCode::BayWeapons,         tr("Bay Weapons")},
  {SkillCode::BludgeoningWeapons, tr("Bludgeoning Weapons")},
  {SkillCode::Bribery,            tr("Bribery")},
  {SkillCode::Broker,             tr("Broker")},
  {SkillCode::Carousing,          tr("Carousing")},
  {SkillCode::Comms,              tr("Comms")},
  {SkillCode::Computer,           tr("Computer")},
  {SkillCode::Demolitions,        tr("Demolitions")},
  {SkillCode::Electronics,        tr("Electronics")},
  {SkillCode::EnergyPistol,       tr("Energy Pistol")},
  {SkillCode::EnergyRifle,        tr("Energy Rifle")},
  {SkillCode::Engineering,        tr("Engineering")},
  {SkillCode::Farming,            tr("Farming")},
  {SkillCode::Gambling,           tr("Gambling")},
  {SkillCode::GravVehicle,        tr("Grav Vehicle")},
  {SkillCode::Gravitics,          tr("Gravitics")},
  {SkillCode::GunCombat,          tr("Gun Combat")},
  {SkillCode::Gunnery,            tr("Gunnery")},
  {SkillCode::HeavyWeapons,       tr("Heavy Weapons")},
  {SkillCode::Jack_of_All_Trades, tr("Jack-of-All-Trades")},
  {SkillCode::Leadership,         tr("Leadership")},
  {SkillCode::Linguistics,        tr("Linguistics")},
  {SkillCode::Liaison,            tr("Liaison")},
  {SkillCode::LifeSciences,       tr("Life Sciences")},
  {SkillCode::Mechanics,          tr("Mechanics")},
  {SkillCode::Medicine,           tr("Medicine")},
  {SkillCode::MeleeCombat,        tr("Melee Combat")},
  {SkillCode::Mole,               tr("Mole")},
  {SkillCode::Motorboats,         tr("Motorboats")},
  {SkillCode::NaturalWeapons,     tr("Natural Weapons")},
  {SkillCode::Navigation,         tr("Navigation")},
  {SkillCode::OceanShips,         tr("Ocean Ships")},
  {SkillCode::PhysicalSciences,   tr("Physical Sciences")},
  {SkillCode::PiercingWeapons,    tr("Piercing Weapons")},
  {SkillCode::Piloting,           tr("Piloting")},
  {SkillCode::Prospecting,        tr("Prospecting")},
  {SkillCode::Recon,              tr("Recon")},
  {SkillCode::Riding,             tr("Riding")},
  {SkillCode::RotorAircraft,      tr("Rotor Aircraft")},
  {SkillCode::Sciences,           tr("Sciences")},
  {SkillCode::SailingShips,       tr("Sailing Ships")},
  {SkillCode::Screens,            tr("Screens")},
  {SkillCode::Shotgun,            tr("Shotgun")},
  {SkillCode::SlashingWeapons,    tr("Slashing Weapons")},
  {SkillCode::SlugPistol,         tr("Slug Pistol")},
  {SkillCode::SlugRifle,          tr("Slug Rifle")},
  {SkillCode::SocialSciences,     tr("Social Sciences")},
  {SkillCode::SpaceSciences,      tr("Space Sciences")},
  {SkillCode::SpinalMounts,       tr("Spinal Mounts")},
  {SkillCode::Steward,            tr("Steward")},
  {SkillCode::Streetwise,         tr("Streetwise")},
  {SkillCode::Submarine,          tr("Submarine")},
  {SkillCode::Survival,           tr("Survival")},
  {SkillCode::Tactics,            tr("Tactics")},
  {SkillCode::TrackedVehicle,     tr("Tracked Vehicle")},
  {SkillCode::TurretWeapons,      tr("Turret Weapons")},
  {SkillCode::Vehicle,            tr("Vehicle")},
  {SkillCode::VeterinaryMedicine, tr("Veterinary Medicine")},
  {SkillCode::Watercraft,         tr("Watercraft")},
  {SkillCode::WheeledVehicle,     tr("Wheeled Vehicle")},
  {SkillCode::WingedAircraft,     tr("Winged Aircraft")},
  {SkillCode::Zero_G,             tr("Zero-G")}
};
