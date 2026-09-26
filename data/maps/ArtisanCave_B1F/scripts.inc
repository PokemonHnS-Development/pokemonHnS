ArtisanCave_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArtisanCave_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

ArtisanCave_B1F_OnTransition:
	callnative SetTimeBasedEncounters
	setflag FLAG_LANDMARK_ARTISAN_CAVE
	end

