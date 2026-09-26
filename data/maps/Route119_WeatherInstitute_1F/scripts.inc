.set LOCALID_LITTLE_BOY, 5

Route119_WeatherInstitute_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_1F_OnTransition
	.byte 0

Route119_WeatherInstitute_1F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos
	end

Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos::
	setobjectxyperm LOCALID_LITTLE_BOY, 0, 5
	setobjectmovementtype LOCALID_LITTLE_BOY, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_1F_EventScript_LittleBoy::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere
	msgbox Route119_WeatherInstitute_1F_Text_WowYoureStrong, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere::
	msgbox Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker1::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_1F_EventScript_StudyingRain
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_1F_EventScript_StudyingRain  @ Both defeated
	msgbox Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_1F_EventScript_StudyingRain::
	msgbox Route119_WeatherInstitute_1F_Text_ProfStudyingRain, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker2::
	msgbox Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo, MSGBOX_NPC
	end

Route119_WeatherInstitute_1F_EventScript_Bed::
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, Route119_WeatherInstitute_1F_EventScript_Bed_PokecenterChallenge
	lockall
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

Route119_WeatherInstitute_1F_EventScript_Bed_PokecenterChallenge::
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed_PokecenterChallenge, MSGBOX_DEFAULT
	closemessage
	end

Route119_WeatherInstitute_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_ZEKE, Route119_WeatherInstitute_1F_Text_Grunt1Intro, Route119_WeatherInstitute_1F_Text_Grunt1Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_FALKNER_2, Route119_WeatherInstitute_1F_Text_Grunt4Intro, Route119_WeatherInstitute_1F_Text_Grunt4Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_Text_Grunt1Intro:
	.string "Al JEFE le interesó la\n"
	.string "investigación de aquí,\l"
	.string "así que nos envió.\p"
	.string "¡Deja de entrometerte!$"

Route119_WeatherInstitute_1F_Text_Grunt1Defeat:
	.string "Maldición...\n"
	.string "Perdí contra un niño...$"

Route119_WeatherInstitute_1F_Text_Grunt1PostBattle:
	.string "Nuestro JEFE lo sabe todo.\p"
	.string "Pero soy un RECLUTA. ¿Qué sabré\n"
	.string "yo de lo que piensa?$"

Route119_WeatherInstitute_1F_Text_Grunt4Intro:
	.string "¿Eh?\n"
	.string "¿Qué hace un niño aquí?$"

Route119_WeatherInstitute_1F_Text_Grunt4Defeat:
	.string "¿Eh?\n"
	.string "¡¿Perdí?!$"

Route119_WeatherInstitute_1F_Text_Grunt4PostBattle:
	.string "Oh, no...\n"
	.string "Me regañarán por perder con un niño...\p"
	.string "Mejor me tomo una siesta...$"

Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs:
	.string "¡Mientras dormía, todos\n"
	.string "subieron arriba!$"

Route119_WeatherInstitute_1F_Text_WowYoureStrong:
	.string "¡Vaya, eres muy fuerte!\p"
	.string "¡Quisiera ser un ENTRENADOR POKéMON\n"
	.string "como tú!$"

Route119_WeatherInstitute_1F_Text_ProfStudyingRain:
	.string "Al PROFESOR le encanta la lluvia.\n"
	.string "Es un hecho.\p"
	.string "Pero si sigue lloviendo, la gente\n"
	.string "estará en problemas. Otro hecho.\p"
	.string "Por eso, el PROFESOR estudia si la\n"
	.string "lluvia puede ser útil.$"

Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather:
	.string "En el 2do piso del INSTITUTO,\n"
	.string "estudiamos el clima de la\l"
	.string "región de HOENN.\p"
	.string "Hemos notado casos aislados de\n"
	.string "sequías y lluvias fuertes\l"
	.string "últimamente…$"

Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo:
	.string "¡Hola!\n"
	.string "¡Tus acciones nos salvaron!\p"
	.string "Lo que no entiendo es qué rayos\n"
	.string "tramaban los AQUA.$"

Route119_WeatherInstitute_1F_Text_TakeRestInBed:
	.string "Hay una cama…\n"
	.string "Descansaré un poco.$"

Route119_WeatherInstitute_1F_Text_TakeRestInBed_PokecenterChallenge:
	.string "Lo siento, estás jugando el\n"
	.string "desafío del POKéCENTER!$"
