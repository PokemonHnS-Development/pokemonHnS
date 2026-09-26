ScorchedSlab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ScorchedSlab_OnTransition
	.byte 0

ScorchedSlab_OnTransition:
	setflag FLAG_LANDMARK_SCORCHED_SLAB
	goto_if_set FLAG_UNLOCK_BIRDS, ScorchedSlab_SwitchToModern
	end

ScorchedSlab_SwitchToModern::
	setmaplayoutindex LAYOUT_SCORCHED_SLAB_MODERN
	end
