.set LOCALID_CIANWOOD_CHUCK, 1
.set LOCALID_CIANWOOD_CHUCK_ROCK_LEFT, 10
.set LOCALID_CIANWOOD_CHUCK_ROCK_RIGHT, 9

CianwoodGym_MapScripts::
	.byte 0


CianwoodGym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, CianwoodGym_EventScript_Statue2
	msgbox CianwoodGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_EventScript_Statue2::
	msgbox CianwoodGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_GymStatue:
	.string "GIMNASIO POKéMON CIUDAD ROCA$"

CianwoodGym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD AZUR\p"
	.string "ENTRENADORES DE CHUCK:\n"
	.string "{PLAYER}$"

CianwoodGym_EventScript_Chuck::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_DOJO_CHUCK, CianwoodGym_EventScript_ChuckAtDojo
	goto_if_set FLAG_VISITED_VERMILION_CITY, CianwoodGym_EventScript_ChuckGotoDojo
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, CianwoodGym_EventScript_Chuck_Defeated
	msgbox CianwoodGym_Text_ChuckIntro1, MSGBOX_DEFAULT
	applymovement LOCALID_CIANWOOD_CHUCK, CianwoodGym_Movement_ChuckLeft
	waitmovement 0
	message CianwoodGym_Text_ChuckIntro2
	applymovement LOCALID_CIANWOOD_CHUCK_ROCK_LEFT, Movement_SmashRock
	playse SE_M_ROCK_THROW
	waitmovement 0

	delay 20

	applymovement LOCALID_CIANWOOD_CHUCK, CianwoodGym_Movement_ChuckRight
	waitmovement 0
	applymovement LOCALID_CIANWOOD_CHUCK_ROCK_RIGHT, Movement_SmashRock
	playse SE_M_ROCK_THROW
	waitmovement 0
	waitmessage
	turnobject LOCALID_CIANWOOD_CHUCK, DIR_SOUTH
	msgbox CianwoodGym_Text_ChuckIntro3, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, CianwoodGym_EventScript_OlivineCheckMahog
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, CianwoodGym_EventScript_MahogCheckOlivine
	goto CianwoodGym_EventScript_Chuck_Battle1

CianwoodGym_EventScript_ChuckVictory::
	message CianwoodGym_Text_GetStormBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox CianwoodGym_Text_ChuckBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE05_GET
	setflag FLAG_DEFEATED_CIANWOOD_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers
	giveitem ITEM_TM_FOCUS_PUNCH
	msgbox CianwoodGym_Text_ChuckTMSpeech, MSGBOX_DEFAULT
	setvar VAR_GETFLY, 1
	setrespawn HEAL_LOCATION_CIANWOOD_CITY
	closemessage
	release
	end

CianwoodGym_EventScript_ChuckGotoDojo::
	msgbox CianwoodGym_Text_ChuckGotoDojo, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_DOJO_CHUCK
	release
	end

CianwoodGym_Text_ChuckGotoDojo:
	.string "¡JAJAJAJA {PLAYER}!\n"
	.string "¡Estoy entrenando ahora mismo!\p"
	.string "Si quieres otra batalla, ve al\n"
	.string "DOJO DE LUCHA en SAFFRON!$"	

CianwoodGym_EventScript_ChuckAtDojo::
	msgbox CianwoodGym_Text_ChuckAtDojo, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_ChuckAtDojo:
	.string "¡Te veré en el DOJO!\n"
	.string "WAHAHAHAHAHA$"

CianwoodGym_EventScript_OlivineCheckMahog::
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, CianwoodGym_EventScript_Chuck_Battle3
	goto CianwoodGym_EventScript_Chuck_Battle2

CianwoodGym_EventScript_MahogCheckOlivine::
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, CianwoodGym_EventScript_Chuck_Battle3
	goto CianwoodGym_EventScript_Chuck_Battle2
	
CianwoodGym_EventScript_Chuck_Battle1::
	trainerbattle_no_intro TRAINER_CHUCK_1, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Battle2::
	trainerbattle_no_intro TRAINER_CHUCK_1_2, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Battle3::
	trainerbattle_no_intro TRAINER_CHUCK_1_3, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Defeated::
	msgbox CianwoodGym_Text_ChuckAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Movement_ChuckLeft:
	jump_in_place_left
	step_end

CianwoodGym_Movement_ChuckRight:
	jump_in_place_right
	step_end

CianwoodGym_Text_ChuckIntro1:
	.string "¡JAJAJAJA!\p"
	.string "¡Así que llegaste hasta aquí!\p"
	.string "¡Déjame decirte que soy fuerte!\p"
	.string "¡Mis POKéMON aplastarán piedras y\n"
	.string "romperán huesos!\p"
	.string "¡Mira esto!$"

CianwoodGym_Text_ChuckIntro2:
	.string "CHUCK: ¡Urggh!\n"
	.string "…\p"
	.string "¡Oooarrgh!$"

CianwoodGym_Text_ChuckIntro3:
	.string "¡Toma! ¿Ahora tienes miedo?\p"
	.string "¿Qué? No tiene nada que ver con\n"
	.string "POKéMON?\p"
	.string "¡Es verdad!\p"
	.string "Vamos. ¡A luchar!$"

CianwoodGym_Text_ChuckLoss:
	.string "¿Qué? ¿Eh? ¿Perdí?\p"
	.string "¡No puede ser!\n"
	.string "¡Mereces la STORMBADGE!$"

CianwoodGym_Text_GetStormBadge:
	.string "{PLAYER} recibió la INSIGNIA TORMENTA.$"

CianwoodGym_Text_ChuckBadgeSpeech:
	.string "STORMBADGE hace que POKéMON hasta\n"
	.string "L70 obedezcan, aun los cambiados.\p"
	.string "Permite que tus POKéMON usen FLY\n"
	.string "fuera de combate.\p"
	.string "¡Toma esto también!$"

CianwoodGym_Text_ChuckTMSpeech:
	.string "Es FOCUS PUNCH.\p"
	.string "Es lento pero hace un daño enorme.\n"
	.string "¡No dejes que te golpeen primero!$"

CianwoodGym_Text_ChuckAfter:
	.string "¡JAJAJA! ¡Me gustó luchar contigo!\p"
	.string "¡Pero una derrota es una derrota!\p"
	.string "¡Desde ahora entrenaré las 24\n"
	.string "horas del día!$"

CianwoodGym_Text_ChuckRematch:
	.string "¡JAJAJA! ¡CAMPEÓN DE JOHTO!\p"
	.string "¡Has vuelto por más!\p"
	.string "¡Veo que tus habilidades mejoraron!\p"
	.string "¿Listo para ver quién es más fuerte?$"

CianwoodGym_Text_ChuckRematchDefeat:
	.string "¿Qué? ¿Cómo? ¿Perdí?\n"
	.string "¿Otra vez?$"

CianwoodGym_EventScript_Yoshi::
	trainerbattle_single TRAINER_YOSHI CianwoodGym_Text_BlackbeltYoshiSeen, CianwoodGym_Text_BlackbeltYoshiBeaten
	msgbox CianwoodGym_Text_BlackbeltYoshiAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltYoshiSeen:
	.string "Mi POKéMON y yo estamos unidos por\n"
	.string "la amistad.\p"
	.string "¡Nuestro vínculo jamás se romperá!$"

CianwoodGym_Text_BlackbeltYoshiBeaten:
	.string "¡Esto no puede ser real!$"

CianwoodGym_Text_BlackbeltYoshiAfter:
	.string "¡Tú también tienes un vínculo fuerte\n"
	.string "con tus POKéMON!$"

CianwoodGym_EventScript_Lao::
	trainerbattle_single TRAINER_LAO CianwoodGym_Text_BlackbeltLaoSeen, CianwoodGym_Text_BlackbeltLaoBeaten
	msgbox CianwoodGym_Text_BlackbeltLaoAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLaoSeen:
	.string "¡Los artistas marciales no temen nada!$"

CianwoodGym_Text_BlackbeltLaoBeaten:
	.string "¡Eso es impactante!$"

CianwoodGym_Text_BlackbeltLaoAfter:
	.string "Los POKéMON lucha temen a los\n"
	.string "psíquicos…$"


CianwoodGym_EventScript_Nob::
	trainerbattle_single TRAINER_NOB CianwoodGym_Text_BlackbeltNobSeen, CianwoodGym_Text_BlackbeltNobBeaten
	msgbox CianwoodGym_Text_BlackbeltNobAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltNobSeen:
	.string "Las palabras no sirven.\n"
	.string "¡Que hablen tus puños!$"

CianwoodGym_Text_BlackbeltNobBeaten:
	.string "…$"

CianwoodGym_Text_BlackbeltNobAfter:
	.string "¡Perdí! ¡No tengo palabras!$"

CianwoodGym_EventScript_Lung::
	trainerbattle_single TRAINER_LUNG CianwoodGym_Text_BlackbeltLungSeen, CianwoodGym_Text_BlackbeltLungBeaten
	msgbox CianwoodGym_Text_BlackbeltLungAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLungSeen:
	.string "¡Mis puños furiosos destrozarán a\n"
	.string "tus POKéMON!$"

CianwoodGym_Text_BlackbeltLungBeaten:
	.string "¡Me destrozaron!$"

CianwoodGym_Text_BlackbeltLungAfter:
	.string "Mi POKéMON perdió...\n"
	.string "Mi... mi orgullo está roto...$"

