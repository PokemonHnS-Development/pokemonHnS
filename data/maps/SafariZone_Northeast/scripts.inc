SafariZone_Northeast_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SetTimeEncounters
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

SafariZone_Northeast_AmbipomEvo::
	msgbox SafariZone_Northeast_AmbipomEvo_Text, MSGBOX_NPC
	end

SafariZone_Northeast_AmbipomEvo_Text:
	.string "¡Amo al POKéMON AIPOM!\n"
	.string "¡Son tan lindos!\l"
	.string "¿Sabías que pueden evolucionar?\p"
	.string "Si usas un movimiento que haga\n"
	.string "reír a todos, ¡evolucionará!\p"
	.string "¡Y seguirá siendo adorable!$"

@ Event scripts for SafariZone_Northeast are in SafariZone_South/scripts.inc
