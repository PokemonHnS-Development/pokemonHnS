.set LOCALID_DRAGONSDEN2_CLAIR, 5
.set LOCALID_DEN_CLAIR, 35

DragonsDen_Cavern_MapScripts::
	@map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonsDen_Cavern_OnFrame
	.byte 0

DragonsDen_Cavern_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 3, DragonsDen_Cavern_EventScript_Clair
	.2byte 0

DragonsDen_EventScript_ClairRematch::
    lock
    faceplayer
    msgbox DragonsDen_Text_Clair, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_DEN_CLAIR
    removeobject LOCALID_DEN_CLAIR
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_CLAIR
    release
    end

DragonsDen_Text_Clair:
    .string "{PLAYER}… Así que estás aquí.\p"
	.string "Si crees que puedes seguirme\n"
	.string "el ritmo, ve al DOJO DE LUCHA\l"
	.string "en CIUDAD AZAFRÁN.$"

DragonsDen_Cavern_Trigger_ClairLeft::
	lock
	setflag FLAG_TEMP_HIDE_FOLLOWER 
	playse SE_PIN
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 60
	call DragonsDen_Cavern_EventScript_Clair
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER
	waitmovement 0
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveLeft
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	setrespawn HEAL_LOCATION_BLACKTHORN_CITY
	releaseall
	end

DragonsDen_Cavern_Trigger_ClairMid::
	lock 
	playse SE_PIN
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveMid
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	release
	end

DragonsDen_Cavern_Trigger_ClairRight::
	lock 
	playse SE_PIN
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveRight
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	release
	end


DragonsDen_Cavern_EventScript_Clair::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox DragonsDen_Cavern_Text_ClairGiveDragonclaw, MSGBOX_DEFAULT
	giveitem ITEM_TM_DRAGON_CLAW
	msgbox DragonsDen_Cavern_Text_ClairDescribeDragonclaw, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox DragonsDen_Cavern_Text_ClairWhatsTheMatter, MSGBOX_DEFAULT
	closemessage
	delay 10
	clearflag FLAG_GOT_DRATINI
	return

DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER:
	walk_fast_down
	face_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveLeft:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveMid:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveRight:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Text_ClairGiveDragonclaw:
    .string "CLAIR: ¡ESPERA!\p"
	.string "Siento mucho lo ocurrido.\n"
    .string "Toma esto como mi disculpa.$"

DragonsDen_Cavern_Text_ClairDescribeDragonclaw:
    .string "Contiene GARRA DRAGÓN.\p"
    .string "No, no tiene nada que ver\n"
    .string "con mis uñas.\p"
    .string "Si no lo quieres, no tienes\n"
    .string "que aceptarlo.$"

DragonsDen_Cavern_Text_ClairWhatsTheMatter:
    .string "¿Qué pasa? ¿No vas a ir a la\n"
    .string "LIGA POKéMON?\l"
    .string "\p"
    .string "Si eres CAMPEÓN, podrás retar a\n"
    .string "cualquier LÍDER de GIMNASIO que\l"
    .string "quieras.\p"
    .string "Ve a la LIGA POKéMON.\p"
    .string "¿Sabes cómo llegar?\p"
    .string "Ve desde aquí a PUEBLO PRIMAVERA.\p"
    .string "Luego usa SURF al este a la LIGA.\p"
    .string "La ruta es muy difícil.\p"
    .string "¡No te atrevas a perder en la\n"
    .string "LIGA POKéMON!\p"
    .string "¡Si lo haces, me sentiré peor por\n"
    .string "haber perdido contra ti!\p"
    .string "¡Da todo lo que tengas!$"

DragonsDen_Cavern_EventScript_Darin::
	trainerbattle_single TRAINER_DARIN DragonsDen_Cavern_Text_CooltrainermDarinSeen, DragonsDen_Cavern_Text_CooltrainermDarinBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainermDarinAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_Cara::
	trainerbattle_single TRAINER_CARA DragonsDen_Cavern_Text_CooltrainerfCaraSeen, DragonsDen_Cavern_Text_CooltrainerfCaraBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainerfCaraAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_TwinLea::
	trainerbattle_double TRAINER_LEA_AND_PIA, DragonsDen_Cavern_Text_TwinsLeaandPia1Seen, DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia1After, MSGBOX_DEFAULT
	release
	end
	
DragonsDen_Cavern_EventScript_TwinPia::
	trainerbattle_double TRAINER_LEA_AND_PIA, DragonsDen_Cavern_Text_TwinsLeaandPia2Seen, DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia2After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_EventScript_Item_Dragon_Fang::
	finditem ITEM_DRAGON_FANG
	end
DragonsDen_Cavern_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end
DragonsDen_Cavern_EventScript_Item_PP_Max::
	finditem ITEM_PP_MAX
	end



DragonsDen_Cavern_Text_DragonShrineSign:
    .string "SANTUARIO DRAGÓN\p"
    .string "Un santuario en honor a los\n"
    .string "POKéMON dragón\p"
    .string "que vivieron en la GUARIDA\n"
    .string "DEL DRAGÓN.$"

DragonsDen_Cavern_Text_SilverTraining1:
    .string "…\n"
    .string "¿Qué? ¿{PLAYER}?\p"
    .string "…No, no lucharé contigo ahora…\p"
    .string "Mis POKéMON no están listos\n"
    .string "para vencerte.\p"
    .string "No puedo forzarlos demasiado.\p"
    .string "Debo ser disciplinada para ser\n"
    .string "la mejor ENTRENADORA POKéMON…$"

DragonsDen_Cavern_Text_SilverTraining2:
    .string "…\p"
    .string "Uff…\p"
    .string "Aprende a no estorbarme…$"

DragonsDen_Cavern_Text_CooltrainermDarinSeen:
    .string "¡Tú! ¡Cómo te atreves a entrar\n"
    .string "sin invitación!$"

DragonsDen_Cavern_Text_CooltrainermDarinBeaten:
    .string "¡F-fuerte!$"

DragonsDen_Cavern_Text_CooltrainermDarinAfter:
    .string "El SANTUARIO es el hogar del\n"
    .string "MAESTRO de nuestro clan dragón.\p"
    .string "¡No puedes entrar así nada más!$"

DragonsDen_Cavern_Text_CooltrainerfCaraSeen:
    .string "¡No deberías estar aquí!$"

DragonsDen_Cavern_Text_CooltrainerfCaraBeaten:
    .string "¡Ay no, perdí!$"

DragonsDen_Cavern_Text_CooltrainerfCaraAfter:
    .string "Pronto tendré el permiso del\n"
    .string "MAESTRO para usar dragones.\p"
    .string "Cuando pase, seré un gran\n"
    .string "ENTRENADOR dragón y tendré la\l"
    .string "aprobación del MAESTRO.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Seen:
    .string "Es un extraño que no conocemos.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten:
    .string "Ay, ay.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1After:
    .string "Fue como tener que luchar\n"
    .string "contra LANCE.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Seen:
    .string "¿Quién eres?$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten:
    .string "¡Qué malo eres!$"

DragonsDen_Cavern_Text_TwinsLeaandPia2After:
    .string "Te delataremos.\p"
    .string "MASTER se enojará contigo.$"
