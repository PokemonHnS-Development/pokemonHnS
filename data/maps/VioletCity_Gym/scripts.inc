VioletCity_Gym_MapScripts::
	.byte 0

VioletCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_GymGuy2
	msgbox VioletGym_Text_GymGuide_Intro, MSGBOX_DEFAULT
	closemessage
	release
	end
	
VioletCity_Gym_EventScript_GymGuy2::
	msgbox VioletGym_Text_GymGuide_Win, MSGBOX_DEFAULT
	release
	end	

VioletCity_Gym_EventScript_Rod::
	trainerbattle_single TRAINER_ROD VioletGym_Text_BirdKeeperRod_Seen, VioletGym_Text_BirdKeeperRod_Beaten
	msgbox VioletGym_Text_BirdKeeperRod_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Abe::
	trainerbattle_single TRAINER_ABE VioletGym_Text_BirdKeeperAbe_Seen, VioletGym_Text_BirdKeeperAbe_Beaten
	msgbox VioletGym_Text_BirdKeeperAbe_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Falkner::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Falkner_Defeated
	msgbox VioletGym_Text_Falkner_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_FALKNER_1, VioletGym_Text_Falkner_WinLoss
	message VioletGym_Text_ReceivedZephyrBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox VioletGym_Text_Falkner_BadgeExplain, MSGBOX_DEFAULT
	setflag FLAG_BADGE01_GET
	setflag FLAG_DEFEATED_VIOLET_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	giveitem ITEM_TM_DOUBLE_TEAM
	msgbox VioletGym_Text_Falkner_TMExplain, MSGBOX_DEFAULT
	setvar VAR_VIOLET_CITY_STATE, 3
	setrespawn HEAL_LOCATION_VIOLET_CITY
	closemessage
	release
	end

VioletCity_Gym_EventScript_Falkner_Defeated::
	msgbox VioletGym_Text_Falkner_AfterFight, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletGym_Text_Falkner_Intro:
	.string "¡Soy FALKNER, el líder del\n"
	.string "GIMNASIO de CIUDAD MALVA!\p"
	.string "Dicen que puedes cortar las alas\n"
	.string "de los POKéMON VOLADORES\p"
	.string "con una descarga eléctrica...\n"
	.string "¡No permitiré tales insultos a los\l"
	.string "POKéMON ave!\p"
	.string "¡Te mostraré el poder real de los\n"
	.string "magníficos POKéMON ave!$"

VioletGym_Text_Falkner_WinLoss:
	.string "...¡Rayos! El POKéMON ave\n"
	.string "querido de mi padre...\p"
	.string "Está bien. Toma esto.\p"
	.string "Es la MEDALLA CEFIRO oficial\n"
	.string "de la LIGA POKéMON.$"

VioletGym_Text_ReceivedZephyrBadge:
	.string "{PLAYER} recibió MEDALLA CEFIRO.$"

VioletGym_Text_Falkner_BadgeExplain:
	.string "La MEDALLA CEFIRO sube el ATAQUE\n"
	.string "de los POKéMON.\p"
	.string "También permite usar FLASH\n"
	.string "en cualquier momento,\l"
	.string "si pueden aprenderlo.\p"
	.string "Toma, llévate esto también.$"

VioletGym_Text_Falkner_TMExplain:
	.string "Con una MT, un POKéMON\n"
	.string "aprenderá un movimiento al instante.\p"
	.string "La MT32 contiene DOBLE EQUIPO.\p"
	.string "Sube la evasión del POKéMON.\p"
	.string "En otras palabras, será más\n"
	.string "difícil de golpear.$"

VioletGym_Text_Falkner_AfterFight:
	.string "Hay GIMNASIOS POKéMON en las\n"
	.string "ciudades que vienen.\p"
	.string "Deberías probar tus habilidades\n"
	.string "en esos GIMNASIOS.\p"
	.string "¡Entrenaré más para ser el mejor\n"
	.string "maestro de aves!$"

VioletGym_Text_Falkner_Rematch:
	.string "¡Felicidades por derrotar\n"
	.string "al ALTO MANDO!\p"
	.string "He entrenado a mis POKéMON\n"
	.string "VOLADORES aún más duro.\p"
	.string "¿Crees que puedes enfrentar el\n"
	.string "poder del cielo otra vez?$"

VioletGym_Text_Falkner_RematchLoss:
	.string "Vaya... Me venciste otra vez.\p"
	.string "¡Entrenaré más para ser el mejor\n"
	.string "maestro de aves!$"

VioletGym_Text_BirdKeeperRod_Seen:
	.string "¡La clave es agallas!\p"
	.string "Aquí entrenan día y noche para\n"
	.string "ser maestros POKéMON voladores.\p"
	.string "¡Vamos!$"

VioletGym_Text_BirdKeeperRod_Beaten:
	.string "¡Gaaah!$"

VioletGym_Text_BirdKeeperRod_After:
	.string "¡El nivel de FALKNER es real!\p"
	.string "¡No te confíes solo porque\n"
	.string "me venciste!$"

VioletGym_Text_BirdKeeperAbe_Seen:
	.string "¡Veré si eres lo bastante bueno\n"
	.string "para enfrentar a FALKNER!$"

VioletGym_Text_BirdKeeperAbe_Beaten:
	.string "¡Esto no puede ser cierto!$"

VioletGym_Text_BirdKeeperAbe_After:
	.string "Es patético perder contra un\n"
	.string "entrenador novato…$"

VioletGym_Text_GymGuide_Intro:
	.string "¡Hola! No soy entrenador,\n"
	.string "¡pero puedo darte un consejo!\p"
	.string "Créeme, si tienes fe, el sueño\n"
	.string "de ser campeón se hará realidad.\p"
	.string "¿Crees? Entonces escucha.\p"
	.string "El as de FALKNER es un búho\n"
	.string "que ama comer BAYAS.\p"
	.string "No es el más fuerte, pero\n"
	.string "aguanta muchos golpes.\p"
	.string "Usa ataques ELÉCTRICOS o de\n"
	.string "ROCA, ¡pero cuidado con\l"
	.string "Bofetón Lodo!\p"
	.string "Si quieres más ayuda, ve a la\n"
	.string "ACADEMIA POKéMON.\p"
	.string "¡Los alumnos de ahí saben\n"
	.string "mucho!$"

VioletGym_Text_GymGuide_Win:
	.string "¡Buena batalla! ¡Sigue así\n"
	.string "y serás el CAMPEÓN en muy\l"
	.string "poco tiempo!$"

VioletCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Statue2
	msgbox VioletCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_EventScript_Statue2::
	msgbox VioletCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON CIUDAD MALVA$"

VioletCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD MALVA\p"
	.string "ENTRENADORES DE FALKNER:\n"
	.string "{PLAYER}$"
