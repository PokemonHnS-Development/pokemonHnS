PewterCity_Gym_MapScripts::
	.byte 0



PewterCity_Gym_EventScript_Jerry::
	trainerbattle_single TRAINER_JERRY, PewterCity_Gym_Text_CamperJerry_Seen, PewterCity_Gym_Text_CamperJerry_Beaten
	msgbox PewterCity_Gym_Text_CamperJerry_AfterBattle, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_Brock::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_PEWTER_GYM, PewterCity_Gym_EventScript_Brock_Defeated
	msgbox PewterCity_Gym_Text_Brock_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BROCK, PewterCity_Gym_Text_Brock_WinLoss
	message PewterCity_Gym_Text_ReceivedBoulderBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PewterCity_Gym_Text_Brock_FightDone, MSGBOX_DEFAULT
	giveitem ITEM_TM_EARTHQUAKE
	setflag FLAG_BADGE09_GET
	setflag FLAG_DEFEATED_PEWTER_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 9
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_DIGLETT_BROCK
	closemessage
	release
	end

PewterCity_Gym_EventScript_Brock_Defeated::
	msgbox PewterCity_Gym_Text_Brock_FightDone, MSGBOX_DEFAULT
	closemessage
	release
	end


PewterCity_Gym_Text_Brock_Intro:
	.string "BROCK: Vaya, no es común recibir un\n"
	.string "reto de JOHTO.\p"
	.string "Soy BROCK, LÍDER del GIMNASIO PEWTER.\p"
	.string "Experto en POKéMON tipo ROCA.\p"
	.string "Mis POKéMON resisten casi todo\n"
	.string "ataque físico. Te costará mucho\l"
	.string "hacerme daño.\p"
	.string "¡Ven ya!$"

PewterCity_Gym_Text_Brock_WinLoss:
	.string "BROCK: Los fuertes ataques de tus\n"
	.string "POKéMON vencieron mi defensa...\p"
	.string "Eres más fuerte de lo que creía...\p"
	.string "Toma, ten esta MEDALLA.$"

PewterCity_Gym_Text_ReceivedBoulderBadge:
	.string "{PLAYER} recibió la MEDALLA ROCA.$"

PewterCity_Gym_Text_Brock_BoulderBadge:
	.string "BROCK: {PLAYER}, gracias. Disfruté\n"
	.string "luchar contigo, aunque estoy algo\l"
	.string "triste.\p"
	.string "La MEDALLA ROCA hará que tus\n"
	.string "POKéMON sean aún más fuertes.$"

PewterCity_Gym_Text_Brock_FightDone:
	.string "BROCK: El mundo es enorme. Hay\n"
	.string "muchos ENTRENADORES fuertes.\p"
	.string "Ya verás. Yo también me volveré\n"
	.string "mucho más fuerte.$"

PewterCity_Gym_Text_CamperJerry_Seen:
	.string "Los ENTRENADORES de este GIMNASIO\n"
	.string "usan POKéMON tipo ROCA.\p"
	.string "El tipo ROCA tiene mucha DEFENSA.\p"
	.string "Las batallas pueden durar mucho.\n"
	.string "¿Estás listo para esto?$"

PewterCity_Gym_Text_CamperJerry_Beaten:
	.string "Tengo que ganar estas batallas...$"

PewterCity_Gym_Text_CamperJerry_AfterBattle:
	.string "¡Oye, tú! ¡ENTRENADOR de JOHTO!\n"
	.string "BROCK es duro. Te castigará si no\l"
	.string "lo tomas en serio.$"

PewterCity_Gym_Text_Guide:
	.string "¡Hola! ¡Futuro CAMPEÓN! De verdad\n"
	.string "estás brillando.\p"
	.string "¿Luchas contra los LÍDERES de\n"
	.string "KANTO?\p"
	.string "Son fuertes y dedicados,\n"
	.string "como los LÍDERES de JOHTO.$"

PewterCity_Gym_Text_Guide_Win:
	.string "¡Hola, futuro CAMPEÓN! Ese GIMNASIO\n"
	.string "no fue problema para ti.\p"
	.string "Tu forma de mandar fue inspiradora.\n"
	.string "Lo digo muy en serio.$"

PewterCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_PEWTER_GYM, PewterCity_Gym_EventScript_GymGuyAfter
	msgbox PewterCity_Gym_Text_Guide, MSGBOX_NPC
	end

PewterCity_Gym_EventScript_GymGuyAfter::
	msgbox PewterCity_Gym_Text_Guide_Win, MSGBOX_NPC
	end


PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE09_GET, PewterCity_Gym_EventScript_GymStatuePostVictory
	msgbox PewterCity_Gym_Text_GymStatue
	releaseall
	end

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON DE PIEDRA\n"
    .string "LÍDER: BROCK\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

PewterCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON DE PIEDRA\n"
    .string "LÍDER: BROCK\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"


