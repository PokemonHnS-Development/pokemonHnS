.set LOCALID_GROUDON, 1
.set LOCALID_GRUNT_1, 2
.set LOCALID_GRUNT_2, 3
.set LOCALID_GRUNT_3, 4
.set LOCALID_TABITHA, 5
.set LOCALID_MAXIE, 6
.set LOCALID_GROUDON_SLEEPING, 7

MagmaHideout_4F_MapScripts::
	.byte 0

MagmaHideout_4F_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_GROUDON_SLEEPING
	addobject LOCALID_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_GROUDON
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	setvar VAR_GARBAGEVAR, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_TABITHA
	setflag FLAG_GARBAGEFLAG
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

MagmaHideout_4F_Movement_GroudonExit:
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro:
	.string "Yo también quiero ver a GROUDON, pero\n"
	.string "no me dejan ver ni su cola...\p"
	.string "Me siento muy frustrado.\p"
	.string "¡Oh, no!\n"
	.string "¡Hablé de más sobre GROUDON!$"

MagmaHideout_4F_Text_Grunt11Defeat:
	.string "Supongo que es imposible ganar si uno\n"
	.string "no tiene la mente calmada...$"

MagmaHideout_4F_Text_Grunt11PostBattle:
	.string "¿Me pregunto si GROUDON tiene cola?$"

MagmaHideout_4F_Text_Grunt12Intro:
	.string "¡Fuhahaha!\n"
	.string "¡Pronto! ¡Muy pronto!\l"
	.string "¡Lograremos nuestro gran objetivo!$"

MagmaHideout_4F_Text_Grunt12Defeat:
	.string "Grrr...\n"
	.string "Llegué tan lejos, ¿y ahora esto?$"

MagmaHideout_4F_Text_Grunt12PostBattle:
	.string "¡Señor MAXIE!\n"
	.string "¡Un intruso se dirige hacia usted!$"

MagmaHideout_4F_Text_Grunt13Intro:
	.string "¡Aún no has terminado!\n"
	.string "¡No pasarás por aquí tan fácil!$"

MagmaHideout_4F_Text_Grunt13Defeat:
	.string "¿Tan fácil fue derrotarme?$"

MagmaHideout_4F_Text_Grunt13PostBattle:
	.string "V-vamos, ¡una batalla más…!$"

MagmaHideout_4F_Text_TabithaIntro:
	.string "¡Jejeje!\n"
	.string "Llegaste hasta aquí, ¡te lo diré!\p"
	.string "¡Así es!\n"
	.string "¡Más adelante, GROUDON duerme!\p"
	.string "¡MAXIE fue con GROUDON hace unos\n"
	.string "segundos!\p"
	.string "¡Despertará muy pronto!\n"
	.string "¡Jeje! ¡Jejeje!$"

MagmaHideout_4F_Text_TabithaDefeat:
	.string "Me vencieron otra vez…\n"
	.string "Jeje…$"

MagmaHideout_4F_Text_TabithaPostBattle:
	.string "…Y mientras perdías tiempo conmigo,\n"
	.string "MAXIE ya debió despertar a GROUDON…$"

MagmaHideout_4F_Text_MaxieAwakenGroudon:
	.string "MAXIE: GROUDON…\p"
	.string "Nada podría despertarte de tu\n"
	.string "sueño bañado en magma…\p"
	.string "Buscabas el ORBE AZUL.\n"
	.string "¿No es así?\p"
	.string "Te he traído el ORBE AZUL.\n"
	.string "¡Que su brillo te despierte!\p"
	.string "Y muéstrame…\n"
	.string "¡Muéstrame todo tu poder!$"

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong:
	.string "MAXIE: ¡GROUDON!\n"
	.string "¿Qué pasa?\p"
	.string "¿No era el ORBE AZUL la clave?\p"
	.string "¡GROUDON!\n"
	.string "¿A dónde te has ido…$"

MagmaHideout_4F_Text_MaxieOhItWasYou:
	.string "MAXIE: Oh, ¿fuiste tú?\p"
	.string "Te vi husmeando sin invitación\n"
	.string "por aquí y por allá…\p"
	.string "¡Ya entiendo!\n"
	.string "¡Hiciste una jugada barata!$"

MagmaHideout_4F_Text_MaxieDefeat:
	.string "¿Qué te hace tan experto manejando\n"
	.string "POKéMON?$"

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon:
	.string "MAXIE: Debe haber alguna razón\n"
	.string "por la que GROUDON huyó…\p"
	.string "Eso es lo que intentas decir,\n"
	.string "¿verdad?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Humph…\n"
	.string "¿Crees que no lo sabía?\p"
	.string "Sin GROUDON, ya no hay necesidad\n"
	.string "de este maldito volcán.\p"
	.string "Iré tras GROUDON, ¡así que aquí\n"
	.string "nos separamos!$"
