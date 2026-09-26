.set LOCALID_MANTYKEMAN, 7

SafariZone_Southeast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_TRANSITION, SetTimeEncounters
	.byte 0

SafariZone_Southeast_GliscorEvo::
	msgbox SafariZone_Southeast_GliscorEvo_Text, MSGBOX_NPC
	end

SafariZone_Southeast_GliscorEvo_Text:
	.string "¡Amo los POKéMON de SINNOH!\p"
	.string "¡Debo atrapar un GLIGAR para\n"
	.string "conseguir un GLISCOR!\p"
	.string "Evolucionan solo de noche,\n"
	.string "como SNEASEL y MURKROW.$"

SafariZone_Southeast_MantykeEvo::
	msgbox SafariZone_Southeast_MantykeEvo_Text, MSGBOX_SIGN
	waitmessage
	msgbox SafariZone_Southeast_MantykeEvo_Text2, MSGBOX_NPC
	applymovement LOCALID_MANTYKEMAN, SafariZone_Southeast_MantykeEvoMoves
	waitmovement 0
	end

SafariZone_Southeast_MantykeEvoMoves:
	face_right
	step_end

SafariZone_Southeast_MantykeEvo_Text:
	.string "¡OH!$"

SafariZone_Southeast_MantykeEvo_Text2:
	.string "¿VISTE ESO?\p"
	.string "¡Ese MANTYKE intentaba evolucionar\n"
	.string "usando PULSO AGUA!\l"
	.string "¡La naturaleza es bella!$"

@ Event scripts for SafariZone_Southeast are in SafariZone_South/scripts.inc
