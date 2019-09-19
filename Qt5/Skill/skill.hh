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

#ifndef SKILL_HH
#define SKILL_HH

#include "Skill_global.hh"

namespace Cepheus
{
  namespace Character
  {
    enum SKILL_EXPORT Skill
    {
      Admin, Advocate, Athletics,
      BattleDress, Bribery, Broker,
      Carousing, Comms, Computer,
      Demolitions,
      Electronics, Engineering,
      Gambling, Gravitics,
      Jack_of_All_Trades,
      Leadership, Linguistics, Liaison,
      Mechanics, Medicine,
      Navigation,
      Piloting, Prospecting,
      Recon,
      Steward, Streetwise,
      Tactics,
      Zero_G,

      // Cascade Skills
      Animals       = 0x0040,
      Farming, Riding, Survival, VeterinaryMedicine,

      Sciences      = 0x0060,
      LifeSciences, PhysicalSciences, SocialSciences, SpaceSciences,

      // Weapon Skills
      GunCombat     = 0x0100,
      Archery, EnergyPistol, EnergyRifle, Shotgun, SlugPistol, SlugRifle,

      Gunnery       = 0x0140,
      BayWeapons, HeavyWeapons, Screens, SpinalMounts, TurretWeapons,

      MeleeCombat   = 0x0180,
      BludgeoningWeapons, NaturalWeapons, PiercingWeapons, SlashingWeapons,

      // Transport Skills
      Vehicle       = 0x0200,

      Aircraft      = 0x0240,
      Airship, GravVehicle, RotorAircraft, WingedAircraft,

      GroundVehicle = 0x0280,
      Mole, TrackedVehicle, WheeledVehicle,

      Watercraft,
      Motorboats, OceanShips, SailingShips, Submarine
    };
  };
};

#endif // SKILL_HH
