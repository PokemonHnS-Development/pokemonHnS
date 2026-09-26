.set LOCALID_OLIVINE_SILVER, 4

OlivineCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_OnFrame
	.byte 0

OlivineCity_MapScript_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

OlivineCity_MapScript_ClearWeather::
	setweather WEATHER_NONE
	end

OlivineCity_OnFrame::
	map_script_2 VAR_SAFARI_ZONE_GATE_STATE, 1, OlivineCity_EventScript_BaobaCall
	.2byte 0

OlivineCity_EventScript_BaobaCall::
	lock
	pokenavcall OlivineCity_Text_Baoba
	waitmessage
	delay 30
	setvar VAR_SAFARI_ZONE_GATE_STATE, 2
	release
	end

OlivineCity_Text_Baoba:
	.string "{PLAYER}!\p"
	.string "Soy el GUARDIA BAOBA.\p"
	.string "Siento haberte hecho esperar.\n"
	.string "¡Al fin abrimos la\l"
	.string "ZONA SAFARI!\p"
	.string "¿Sabes dónde está?\p"
	.string "¿Conoces la PUERTA de la cueva\n"
	.string "en CIUDAD ORQUIDEA?\p"
	.string "Si pasas por ahí y caminas\n"
	.string "un poco, pronto verás\l"
	.string "la ZONA SAFARI!\p"
	.string "Estamos algo apartados, pero\n"
	.string "¡ven a visitarnos!$"

OlivineCity_EventScript_CityTrigger:: @FLAGHEAP
	setflag FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
	setflag FLAG_HIDE_OLIVINE_SILVER
	setflag FLAG_VISITED_OLIVINE_CITY
	clearflag FLAG_SAFARI_ZONE_WEST_EXPANSION
	clearflag FLAG_SAFARI_ZONE_EAST_EXPANSION
	clearflag FLAG_HIDE_BATTLEFRONTIER_ENGINEER
	clearflag FLAG_HIDE_LIGHTHOUSE_JASMINE
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	setvar VAR_GETFLY, 0
	
	setvar VAR_OLIVINE_CITY_STATE, 1

	@cianwood flags
	setvar VAR_SUICUNE_ENCOUNTERS, 1
	clearflag FLAG_HIDE_CIANWOOD_SUICUNE
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setvar VAR_CIANWOOD_CITY_STATE, 1
	end

OlivineCity_EventScript_SilverTrigger::
	lock
	clearflag FLAG_HIDE_OLIVINE_SILVER
	opendoor 11, 27
	addobject LOCALID_OLIVINE_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	delay 20 
	closedoor 11, 27
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverWalkToPlayer1
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverWalkToPlayer2
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverWalkToPlayer3
	msgbox OlivineCity_Text_SilverEncounter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverLeaveAdjust1
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverLeaveAdjust2
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverLeaveAdjust2
	applymovement LOCALID_OLIVINE_SILVER, OlivineCity_Movement_SilverLeave
	waitmovement 0
	setvar VAR_OLIVINE_CITY_STATE, 2
	setflag FLAG_HIDE_OLIVINE_SILVER
	removeobject LOCALID_OLIVINE_SILVER
	fadedefaultbgm
	release
	end

OlivineCity_EventScript_SilverWalkToPlayer1::
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer1
	waitmovement 0
	return

OlivineCity_EventScript_SilverWalkToPlayer2::
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer2
	waitmovement 0
	return

OlivineCity_EventScript_SilverWalkToPlayer3::
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer3
	waitmovement 0
	return

OlivineCity_EventScript_SilverLeaveAdjust1::
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkDown1
	waitmovement 0
	return

OlivineCity_EventScript_SilverLeaveAdjust2::
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkUp1
	waitmovement 0
	return

OlivineCity_Movement_SilverWalkToPlayer1:
	walk_down
	walk_right
	walk_right
	walk_right
	step_end
OlivineCity_Movement_SilverWalkToPlayer2:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end
OlivineCity_Movement_SilverWalkToPlayer3:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end


OlivineCity_Movement_SilverLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OlivineCity_Text_SilverEncounter:
	.string "¿Tú otra vez?\n"
	.string "No hace falta que estés alerta.\p"
	.string "No me molesto con debiluchos\n"
	.string "como tú.\p"
	.string "Hablando de débiles, el\n"
	.string "LÍDER del GIMNASIO no está,\l"
	.string "dicen que cuida a un POKéMON\l"
	.string "enfermo en el\l"
	.string "FARO.\p"
	.string "¡Bah! ¡Qué llanto!\n"
	.string "¡Deja ir a los POKéMON enfermos!\p"
	.string "¡Un POKéMON que no lucha\n"
	.string "no vale nada!\p"
	.string "¿Por qué no entrenas en el\n"
	.string "FARO?\p"
	.string "¡Quién sabe! ¡Quizás seas un\n"
	.string "mejor Entrenador!$"

OlivineCity_EventScript_Sailor1::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Sailor2::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox OlivineCity_Text_YoungsterPokegear, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Machoke::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
	msgbox OlivineCity_Text_Machoke, MSGBOX_DEFAULT
	waitmoncry
	release
	end

OlivineCity_EventScript_Sign::
	lock
	msgbox OlivineCity_Text_Sign, MSGBOX_SIGN
	end

OlivineCity_EventScript_PortSign::
	lock
	msgbox OlivineCity_Text_PortSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_CafeSign::
	msgbox OlivineCity_Text_CafeSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_GymSign::
	lock
	msgbox OlivineCity_Text_GymSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_LighthouseSign::
	lock
	msgbox OlivineCity_Text_LighthouseSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_Item_Shockwave::
	finditem ITEM_TM_SHOCK_WAVE
	end

OlivineCity_EventScript_EonTicketWoman::
	lock
	faceplayer
	checkitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_EventScript_EonTicketWomanAfter
	goto_if_set FLAG_IS_KANTO_CHAMPION, OlivineCity_EventScript_EonTicketWomanChamp
	msgbox OlivineCity_Text_EonTicketWoman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_EonTicketWomanChamp::
	msgbox OlivineCity_Text_EonTicketWoman2, MSGBOX_DEFAULT
	giveitem ITEM_AURORA_TICKET
	closemessage
	release
	end

OlivineCity_EventScript_EonTicketWomanAfter::
	msgbox OlivineCity_Text_EonTicketWoman3, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSign:
	.string "CAFÉ DE OLIVO\n"
	.string "DONDE MARINEROS FUERTES\l"
	.string "COMEN PLATOS DE PODER$"

OlivineCity_Text_EonTicketWoman1:
	.string "¡Mi nombre es MARY!\p"
	.string "Es broma, ¡pero amo el programa\n"
	.string "de radio de MARY!$"

OlivineCity_Text_EonTicketWoman2:
	.string "¡¡¡Tú debes ser {PLAYER}!!!\p"
	.string "¡Cielos! ¡El campeón!\p"
	.string "¡Oí hablar de ti en el programa\n"
	.string "de radio de MARY!\p"
	.string "¡Toma esto!$"

OlivineCity_Text_EonTicketWoman3:
	.string "¡No creo que haya conocido\n"
	.string "al campeón!!!$"

OlivineCity_Text_Sailor1:
	.string "Los caminos oscuros son peligrosos\n"
	.string "de noche.\p"
	.string "Pero en la oscuridad total\n"
	.string "de la noche, el mar es aún más\l"
	.string "traicionero!\p"
	.string "Sin la luz del FARO para\n"
	.string "guiarlo,\l"
	.string "ningún barco puede navegar.$"

OlivineCity_Text_YoungsterPokegear:
	.string "Eso que tienes...\n"
	.string "es un POKéGEAR, ¿verdad?\l"
	.string "Vaya, ¡está genial!$"

OlivineCity_Text_YoungsterPokedex:
	.string "¡Vaya, tienes una POKéDEX!\p"
	.string "¡Eso es genial!$"

OlivineCity_Text_Sailor2:
	.string "La liga dice que JASMINE\n"
	.string "es la sexta\l"
	.string "LÍDER de GIMNASIO más fuerte!\p"
	.string "¡Ja! ¡Eso es mentira!\p"
	.string "¡PRYCE no podría hacerle nada\n"
	.string "a los POKéMON de ACERO\l"
	.string "de JASMINE!\p"
	.string "Es pura burocracia.\p"
	.string "¡Ella es temible,\n"
	.string "de eso estoy seguro!$"

OlivineCity_Text_Sign:
	.string "CIUDAD OLIVO\p"
	.string "El puerto más cercano al exterior$"

OlivineCity_Text_PortSign:
	.string "PUERTO OLIVO\n"
	.string "MUELLE DE BARCOS RÁPIDOS$"

OlivineCity_Text_GymSign:
	.string "GIMNASIO POKéMON CIUDAD OLIVO\n"
	.string "LÍDER: JASMINE\p"
	.string "La chica de la defensa de acero$"

OlivineCity_Text_LighthouseSign:
	.string "FARO DE OLIVO\n"
	.string "También llamado FARO\l"
	.string "CENTELLEANTE$"

OlivineCity_Text_BattleTowerSign:
	.string "COLINA ENTRENADOR y\n"
	.string "TIENDAS DE BATALLA ADELANTE.\p"
	.string "¡Ya abrieron!$"

OlivineCity_Text_Machoke:
	.string "MACHOKE: ¡CHO!$"
