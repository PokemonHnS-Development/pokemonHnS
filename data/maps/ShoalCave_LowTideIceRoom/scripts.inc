
ShoalCave_LowTideIceRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_LowTideIceRoom_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

ShoalCave_LowTideIceRoom_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_set FLAG_UNLOCK_DOGS, ShoalCave_LowTideIceRoom_SwitchToModern
	end

ShoalCave_LowTideIceRoom_SwitchToModern::
	setmaplayoutindex LAYOUT_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_MODERN
	goto_if_set FLAG_DEFEATED_SUICUNE, MagmaHideout_End
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	release
	end
