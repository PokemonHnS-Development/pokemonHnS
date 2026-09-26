SaffronCity_Gym_MapScripts::
	.byte 0

SaffronCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_SAFFRON_GYM, SaffronCity_Gym_EventScript_GymGuy2
	msgbox SaffronCity_Gym_Text_GymGuideIntro, MSGBOX_NPC
	end

SaffronCity_Gym_EventScript_GymGuy2::
	msgbox SaffronCity_Gym_Text_GymGuideWin, MSGBOX_NPC
	end

SaffronCity_Gym_EventScript_Rebecca::
	trainerbattle_single TRAINER_REBECCA SaffronCity_Gym_Text_MediumRebeccaSeen, SaffronCity_Gym_Text_MediumRebeccaBeaten
	msgbox SaffronCity_Gym_Text_MediumRebeccaAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Franklin::
	trainerbattle_single TRAINER_FRANKLIN SaffronCity_Gym_Text_PsychicFranklinSeen, SaffronCity_Gym_Text_PsychicFranklinBeaten
	msgbox SaffronCity_Gym_Text_PsychicFranklinAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Doris::
	trainerbattle_single TRAINER_DORIS SaffronCity_Gym_Text_MediumDorisSeen, SaffronCity_Gym_Text_MediumDorisBeaten
	msgbox SaffronCity_Gym_Text_MediumDorisAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED SaffronCity_Gym_Text_PsychicJaredSeen, SaffronCity_Gym_Text_PsychicJaredBeaten
	msgbox SaffronCity_Gym_Text_PsychicJaredAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Sabrina::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SAFFRON_GYM, SaffronCity_Gym_EventScript_Sabrina_Defeated
	msgbox SaffronCity_Gym_Text_SabrinaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SABRINA, SaffronCity_Gym_Text_SabrinaWinLoss
	message SaffronCity_Gym_Text_ReceivedMarshBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SaffronCity_Gym_Text_MarshBadgeInfo, MSGBOX_DEFAULT
	setflag FLAG_BADGE13_GET
	setflag FLAG_DEFEATED_SAFFRON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 13
	call Common_EventScript_SetGymTrainers
	closemessage
	clearflag FLAG_HIDE_OLIVINE_SABRINA
	release
	end

SaffronCity_Gym_EventScript_Sabrina_Defeated::
	msgbox SaffronCity_Gym_Text_SabrinaPostBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_Gym_Text_SabrinaIntro:
	.string "SABRINA: Sabía que vendrías...\p"
	.string "Hace tres años tuve una visión\n"
	.string "de tu llegada.\p"
	.string "Buscas mi MEDALLA.\p"
	.string "No disfruto luchar, pero es mi\n"
	.string "deber como LÍDER dar\l"
	.string "MEDALLAS a quien haya\l"
	.string "demostrado su valía.\p"
	.string "Ya que lo deseas, ¡te mostraré\n"
	.string "mis poderes psíquicos!$"

SaffronCity_Gym_Text_SabrinaWinLoss:
	.string "SABRINA: Tu poder...\p"
	.string "Supera mucho lo que preví...\p"
	.string "Tal vez no es posible predecir\n"
	.string "todo lo que el futuro guarda...\p"
	.string "Bien, ganaste. Te has ganado la\n"
	.string "MEDALLA MARJA.$"

SaffronCity_Gym_Text_ReceivedMarshBadge:
	.string "{PLAYER} recibió MEDALLA MARJA.$"

SaffronCity_Gym_Text_MarshBadgeInfo:
	.string "SABRINA: La MEDALLA MARJA saca\n"
	.string "tus poderes subliminales...\p"
	.string "Aunque no preví tu poder con\n"
	.string "exactitud, esto sí lo\l"
	.string "sé con certeza.\p"
	.string "¡Te volverás un CAMPEÓN famoso\n"
	.string "y muy querido!$"

SaffronCity_Gym_Text_SabrinaPostBattle:
	.string "SABRINA: El amor por tus\n"
	.string "POKéMON superó mi poder\l"
	.string "psíquico...\p"
	.string "El poder del amor, creo, es\n"
	.string "también un poder psíquico...$"

SaffronCity_Gym_Text_SabrinaRematch:
	.string "SABRINA: Ah, el CAMPEÓN de KANTO.\p"
	.string "Sentí tu regreso.\p"
	.string "Tu poder ha crecido inmensamente.\p"
	.string "Aún ahora, siento tu aura.\p"
	.string "¿Quieres una revancha conmigo?$"

SaffronCity_Gym_Text_SabrinaRematchDefeat:
	.string "SABRINA: El amor por tus\n"
	.string "POKéMON superó otra vez mi\l"
	.string "poder psíquico...$"

SaffronCity_Gym_Text_MediumRebeccaSeen:
	.string "¡El poder de todos los que\n"
	.string "derrotaste llega a mí!$"

SaffronCity_Gym_Text_MediumRebeccaBeaten:
	.string "Fuerte... Demasiado fuerte...$"

SaffronCity_Gym_Text_MediumRebeccaAfter:
	.string "¿Cuál es la fuente de tu poder?$"

SaffronCity_Gym_Text_PsychicFranklinSeen:
	.string "El poder psíquico es el poder de\n"
	.string "tu alma.$"

SaffronCity_Gym_Text_PsychicFranklinBeaten:
	.string "¡Tu alma tiene más poder que\n"
	.string "la mía!$"

SaffronCity_Gym_Text_PsychicFranklinAfter:
	.string "Hiciste tu alma más fuerte, no\n"
	.string "solo tus habilidades.$"

SaffronCity_Gym_Text_MediumDorisSeen:
	.string "Fufufufu... Lo veo claramente.\p"
	.string "¡Puedo ver dentro de tu alma!$"

SaffronCity_Gym_Text_MediumDorisBeaten:
	.string "Aunque te leí, aun así perdí...$"

SaffronCity_Gym_Text_MediumDorisAfter:
	.string "¡Rayos! Olvidé que predije que\n"
	.string "perdería contra ti.$"

SaffronCity_Gym_Text_PsychicJaredSeen:
	.string "El DOJO de LUCHA de al lado\n"
	.string "fue el GIMNASIO de esta ciudad.$"

SaffronCity_Gym_Text_PsychicJaredBeaten:
	.string "No pude ganar...$"

SaffronCity_Gym_Text_PsychicJaredAfter:
	.string "KARATE KING, el maestro del\n"
	.string "DOJO de LUCHA, fue derrotado\l"
	.string "por SABRINA.$"

SaffronCity_Gym_Text_GymGuideIntro:
	.string "¡Hola, futuro CAMPEÓN!\p"
	.string "Un ENTRENADOR tan hábil como tú\n"
	.string "no necesita que le digan cómo\l"
	.string "vencer a los POKéMON PSÍQUICOS,\l"
	.string "¿verdad?\p"
	.string "¡Espero mucho de ti!\p"
	.string "¡Buena suerte!$"

SaffronCity_Gym_Text_GymGuideWin:
	.string "¡Fue otra batalla fantástica!$"

SaffronCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE13_GET, SaffronCity_Gym_EventScript_GymStatuePostVictory
	msgbox SaffronCity_Gym_Text_GymStatue
	releaseall
	end

SaffronCity_Gym_EventScript_GymStatuePostVictory::
	msgbox SaffronCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end


SaffronCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON DE CIUDAD AZAFRÁN\n"
    .string "LÍDER: SABRINA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

SaffronCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON DE CIUDAD AZAFRÁN\n"
    .string "LÍDER: SABRINA\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"
