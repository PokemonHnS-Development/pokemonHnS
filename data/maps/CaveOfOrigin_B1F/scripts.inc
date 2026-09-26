.set LOCALID_WALLACE, 1

CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_GARBAGEVAR, 3
	removeobject LOCALID_WALLACE
	clearflag FLAG_GARBAGEFLAG
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "Ah, ¿así que eres {PLAYER}{KUN}?\n"
	.string "He oído hablar de tus hazañas.\p"
	.string "Mi nombre es WALLACE.\p"
	.string "Fui el LÍDER del GIMNASIO de\n"
	.string "CIUDAD SURTIDO, pero surgió algo.\p"
	.string "Así que ahora, le confié a mi mentor\n"
	.string "JUAN la gestión del GIMNASIO.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "GROUDON y KYOGRE, los dos POKéMON\n"
	.string "que causan caos, son considerados\l"
	.string "POKéMON superantiguos.\p"
	.string "Pero no hay solo dos POKéMON\n"
	.string "superantiguos.\p"
	.string "Hay uno más en algún lugar.\p"
	.string "En algún lugar hay un POKéMON\n"
	.string "superantiguo llamado RAYQUAZA.\p"
	.string "Dicen que fue RAYQUAZA quien\n"
	.string "calmó a los combatientes en\l"
	.string "el pasado remoto.\p"
	.string "Pero ni yo sé dónde se encuentra\n"
	.string "RAYQUAZA ahora mismo…$"

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
	.string "WALLACE: {PLAYER}{KUN}, ¿sabes tal vez\n"
	.string "dónde está RAYQUAZA ahora?\p"
	.string "Si lo sabes, por favor dímelo.$"

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
	.string "WALLACE: ¿La CUEVA ORIGEN?\p"
	.string "¡Pero si está justo aquí!\n"
	.string "¡Tienes que esforzarte más!\p"
	.string "Por favor, piensa bien en\n"
	.string "dónde podría estar RAYQUAZA.$"

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
	.string "WALLACE: ¿MT. PYRE?\p"
	.string "Cuando vi a la anciana allí\n"
	.string "antes, no mencionó nada.\p"
	.string "Dudo que la anciana intente\n"
	.string "ocultarme algo…\p"
	.string "{PLAYER}{KUN}, ¿podrías pensarlo\n"
	.string "con más cuidado por mí?$"

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
	.string "WALLACE: ¿Eh? ¿No recuerdas?\n"
	.string "Hmm… Eso es un problema…\p"
	.string "¿No puedes recordarlo de algún modo?$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "WALLACE: ¿El PILAR CIELO?\p"
	.string "¡Eso es!\n"
	.string "¡Debe ser el PILAR CIELO!\p"
	.string "{PLAYER}{KUN}, ¡no hay tiempo que perder!\n"
	.string "¡Iremos al PILAR CIELO ahora mismo!$"

