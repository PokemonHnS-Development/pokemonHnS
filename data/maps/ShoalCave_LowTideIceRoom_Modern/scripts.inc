ShoalCave_LowTideIceRoom_Modern_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_LowTideIceRoom_Modern_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

ShoalCave_LowTideIceRoom_Modern_OnTransition::
	callnative SetTimeBasedEncounters
	end
