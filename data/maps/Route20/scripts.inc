.set LOCALID_ROUTE20_DENNIS, 17
.set LOCALID_ROUTE20_HEADLOCKER, 16

Route20_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route20_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route20_EventScript_ShellBell::
	finditem ITEM_SHELL_BELL
	end

Route20_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route20_EventScript_Nicole::
	trainerbattle_single TRAINER_NICOLE Route20_Text_SwimmerfNicoleSeen, Route20_Text_SwimmerfNicoleBeaten
	msgbox Route20_Text_SwimmerfNicoleAfterBattle, MSGBOX_AUTOCLOSE
	end	

Route20_EventScript_Lori::
	trainerbattle_single TRAINER_LORI Route20_Text_SwimmerfLoriSeen, Route20_Text_SwimmerfLoriBeaten
	msgbox Route20_Text_SwimmerfLoriAfterBattle, MSGBOX_AUTOCLOSE
	end	

Route20_EventScript_Cameron::
	trainerbattle_single TRAINER_CAMERON Route20_Text_SwimmermCameronSeen, Route20_Text_SwimmermCameronBeaten
	msgbox Route20_Text_SwimmermCameronAfterBattle, MSGBOX_AUTOCLOSE
	end	

Route20_EventScript_SeafoamSign::
	msgbox Route20_Text_SeafoamSign, MSGBOX_SIGN
	end

Route20_EventScript_GymSign::
	msgbox Route20_Text_CinnabarIsland_GymUnusedSign, MSGBOX_SIGN
	end

Route20_EventScript_Seel::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SEEL, CRY_MODE_NORMAL
	msgbox Route20_Text_Seel, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route20_EventScript_Dewgong::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DEWGONG, CRY_MODE_NORMAL
	msgbox Route20_Text_Dewgong, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route20_EventScript_Dennis::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAGIKARP, CRY_MODE_NORMAL
	msgbox Route20_Text_Dennis, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route20_EventScript_Headlocker::
	lock
	faceplayer
	msgbox Route20_Text_Headlocker, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE20_HEADLOCKER, DIR_SOUTH
	release
	end

Route20_Text_Dennis:
	.string "DENNIS: ¡SHAAAAAAAA!$"

Route20_Text_Headlocker:
	.string "Hay un POKéMON raro en esta\n"
	.string "ruta.\p"
	.string "Y a veces lleva un objeto de\n"
	.string "evolución raro.\p"
	.string "¡Eso es doblemente raro!\p"
	.string "Quiero completar mi POKéDEX, así\n"
	.string "¡que llevo horas pescando aquí!$"

Route20_Text_Seel:
	.string "SEEL: ¡Seel seel!$"

Route20_Text_Dewgong:
	.string "DEWGONG: ¡Goooong!$"

Route20_Text_SeafoamSign:
	.string "ISLAS ESPUMA$"

Route20_Text_SwimmerfNicoleSeen:
	.string "Me siento más ligero en el agua.$"

Route20_Text_SwimmerfNicoleBeaten:
	.string "¡Oh, no!$"

Route20_Text_SwimmerfNicoleAfterBattle:
	.string "Nadar ejercita todo el cuerpo.\p"
	.string "Es muy bueno para ti.$"

Route20_Text_SwimmerfLoriSeen:
	.string "¡Qué colección de MEDALLAS de\n"
	.string "GIMNASIO! ¡Luchemos!$"

Route20_Text_SwimmerfLoriBeaten:
	.string "¡No!$"

Route20_Text_SwimmerfLoriAfterBattle:
	.string "SURF ya no es la única MO\n"
	.string "que usas en el agua.$"

Route20_Text_SwimmermCameronSeen:
	.string "Supongo que es imposible nadar\n"
	.string "hasta JOHTO.$"

Route20_Text_SwimmermCameronBeaten:
	.string "¡Aiyah!$"

Route20_Text_SwimmermCameronAfterBattle:
	.string "Aparte del mar, también puedo\n"
	.string "nadar en estanques y ríos.$"

Route20_Text_CinnabarIsland_GymUnusedSign:
	.string "¿Qué dice este cartel?\p"
	.string "LÍDER DEL GIMNASIO: BLAINE$"

