MeteorFalls_B1F_2R_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MeteorFalls_B1F_2R_OnTransition
	.byte 0

MeteorFalls_B1F_2R_OnTransition::
	goto_if_set FLAG_UNLOCK_BIRDS, MeteorFalls_B1F_2R_SwitchToModern
	end

MeteorFalls_B1F_2R_SwitchToModern::
	setmaplayoutindex LAYOUT_METEOR_FALLS_B1F_2R_MODERN
	end
