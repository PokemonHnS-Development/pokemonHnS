.set LOCALID_MATT, 1
.set LOCALID_SUBMARINE, 4

AquaHideout_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape::
	setvar VAR_0x8008, LOCALID_MATT
	setvar VAR_0x8009, LOCALID_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_GARBAGEFLAG
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_SETH, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_STANLY, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_STEVE, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
	.string "Jejeje...\p"
	.string "¿Ya llegaste aquí?\n"
	.string "¡Te subestimamos!\p"
	.string "¡Pero aquí termina todo!\p"
	.string "Soy superior a los RECLUTAS que\n"
	.string "has visto hasta ahora.\p"
	.string "No voy a perder el tiempo.\n"
	.string "¡Voy a pulverizarte!$"

AquaHideout_B2F_Text_MattDefeat:
	.string "Jejeje...\n"
	.string "Así que yo también perdí...$"

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
	.string "¡Jejeje!\p"
	.string "¡Mientras jugaba contigo, nuestro JEFE\n"
	.string "terminó sus preparativos!$"

AquaHideout_B2F_Text_MattPostBattle:
	.string "¡Jejeje!\p"
	.string "¡Nuestro JEFE ya va camino a\n"
	.string "una cueva bajo el mar!\p"
	.string "Si quieres perseguirlo, mejor\n"
	.string "busca en el gran mar más allá de\l"
	.string "LILYCOVE.\p"
	.string "¿Pero podrás encontrarlo?\n"
	.string "¡Jejeje!$"

AquaHideout_B2F_Text_Grunt4Intro:
	.string "¡Jajaja, me cansé de esperar!\n"
	.string "¡Tú también me debes una batalla!$"

AquaHideout_B2F_Text_Grunt4Defeat:
	.string "Cansado de esperar...\n"
	.string "Perdido y aturdido...$"

AquaHideout_B2F_Text_Grunt4PostBattle:
	.string "JEFE...\n"
	.string "¿Es esto suficiente?$"

AquaHideout_B2F_Text_Grunt6Intro:
	.string "¡Paneles warp, el orgullo de la\n"
	.string "BASE SECRETA!\p"
	.string "No tienes idea de dónde estás,\n"
	.string "¿verdad?\p"
	.string "¡Aturde al enemigo y luego\n"
	.string "golpea fuerte! ¡Ese es el plan!$"

AquaHideout_B2F_Text_Grunt6Defeat:
	.string "¿Qué te pasa?\n"
	.string "¡No estás cansado para nada!$"

AquaHideout_B2F_Text_Grunt6PostBattle:
	.string "Eso me recuerda... No recuerdo\n"
	.string "dónde puse la MASTER BALL.\p"
	.string "Si no la cuido, nuestro JEFE me\n"
	.string "regañará...$"

AquaHideout_B2F_Text_Grunt8Intro:
	.string "Al entrar al TEAM AQUA, lo primero\n"
	.string "que aprendí fue cómo se conectan\l"
	.string "estos paneles de salto.$"

AquaHideout_B2F_Text_Grunt8Defeat:
	.string "Estaba muy distraído pensando en\n"
	.string "los paneles de salto...$"

AquaHideout_B2F_Text_Grunt8PostBattle:
	.string "Tendré que aprender a luchar de\n"
	.string "forma más efectiva...$"
