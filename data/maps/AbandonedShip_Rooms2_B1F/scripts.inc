AbandonedShip_Rooms2_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SetTimeEncounters
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

AbandonedShip_Rooms2_B1F_EventScript_Camper::
	msgbox AbandonedShip_Rooms2_B1F_Text_PerfectPlaceToGoExploring, MSGBOX_NPC
	end

AbandonedShip_Rooms2_B1F_Text_PerfectPlaceToGoExploring:
	.string "¡Es un lugar ideal para explorar!\n"
	.string "¡Qué emocionante!\p"
	.string "Apuesto a que hay tesoros increíbles\n"
	.string "a bordo.$"

