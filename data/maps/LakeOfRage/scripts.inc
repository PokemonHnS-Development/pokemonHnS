.set LOCALID_LAKEOFRAGE_GYARADOS, 8
.set LOCALID_LAKEOFRAGE_LANCE, 3
.set LOCALID_LAKEOFRAGE_DRAGONITE, 16
.set LOCALID_LAKEOFRAGE_OLDMAN, 4
.set LOCALID_LAKE_PRYCE, 17

LakeOfRage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LakeOfRage_OnTransition
	.byte 0

LakeOfRage_OnTransition::
	setflag FLAG_VISITED_LAKE_OF_RAGE
	call_if_lt VAR_MAHOGANY_TOWN_STATE, 2, LakeOfRage_EventScript_HideLois
	goto_if_lt VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_SetHighTide
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_LAKE_OF_RAGE_TIDE, LakeOfRage_EventScript_SetHighTide
	goto LakeOfRage_EventScript_SetLowTide

LakeOfRage_EventScript_SetLowTide::
	setweather WEATHER_NONE
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_LOW_TIDE
	end

LakeOfRage_EventScript_SetHighTide::
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE
	goto_if_lt VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_ThunderStorm
	random 2
	goto_if_eq VAR_RESULT, 1, LakeOfRage_EventScript_ThunderStorm
	end

LakeOfRage_EventScript_HideLois::
	setflag FLAG_TEMP_1
	return

LakeOfRage_EventScript_ThunderStorm::
	setweather WEATHER_RAIN_THUNDERSTORM
	end

LakeOfRage_EventScript_Pryce::
    lock
    faceplayer
    msgbox LakeOfRage_Text_Pryce, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_LAKE_PRYCE
    removeobject LOCALID_LAKE_PRYCE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_PRYCE
    release
    end

LakeOfRage_Text_Pryce:
    .string "{PLAYER}.\p"
	.string "Incluso aquí, el frío me mantiene\p"
	.string "alerta. Si quieres luchar de nuevo,\n"
	.string "ve al DOJO DE LUCHA.$"

LakeOfRage_EventScript_Gramps::
	goto_if_ge VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_Gramps2
	msgbox LakeOfRage_Text_Gramps, MSGBOX_NPC
	end

LakeOfRage_EventScript_Gramps2::
	msgbox LakeOfRage_Text_GrampsCleared, MSGBOX_NPC
	end
LakeOfRage_EventScript_Lass::
	msgbox LakeOfRage_Text_CooltrainerF, MSGBOX_NPC
	end

LakeOfRage_EventScript_Nerd::
	msgbox LakeOfRage_Text_SuperNerd, MSGBOX_NPC
	end

LakeOfRage_EventScript_Andre::
	trainerbattle_single TRAINER_ANDRE LakeOfRage_Text_FisherAndreSeen, LakeOfRage_Text_FisherAndreBeaten
	msgbox LakeOfRage_Text_FisherAndreAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Raymond::
	trainerbattle_single TRAINER_RAYMOND LakeOfRage_Text_FisherRaymondSeen, LakeOfRage_Text_FisherRaymondBeaten
	msgbox LakeOfRage_Text_FisherRaymondAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Aaron::
	trainerbattle_single TRAINER_AARON LakeOfRage_Text_CooltrainermAaronSeen, LakeOfRage_Text_CooltrainermAaronBeaten
	msgbox LakeOfRage_Text_CooltrainermAaronAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Lois::
	trainerbattle_single TRAINER_LOIS LakeOfRage_Text_CooltrainerfLoisSeen, LakeOfRage_Text_CooltrainerfLoisBeaten
	msgbox LakeOfRage_Text_CooltrainerfLoisAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Gyarados::
	lock
	faceplayer
	msgbox LakeOfRage_Text_GyaradosCry, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_GYARADOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattleshiny SPECIES_GYARADOS, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LakeOfRage_EventScript_Defeated_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, LakeOfRage_EventScript_Ran_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, LakeOfRage_EventScript_Ran_Gyarados
LakeOfRage_EventScript_Defeated_Gyarados::
	setflag FLAG_HIDE_LAKE_OF_RAGE_GYARADOS
	clearflag FLAG_TEMP_1
	removeobject LOCALID_LAKEOFRAGE_GYARADOS
	clearflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	addobject LOCALID_LAKEOFRAGE_LANCE
	giveitem ITEM_RED_SCALE
	setobjectxyperm LOCALID_LAKEOFRAGE_OLDMAN, 32, 38
	setvar VAR_MAHOGANY_TOWN_STATE, 2
	release
	end

LakeOfRage_EventScript_Ran_Gyarados::
	release
	end

LakeOfRage_EventScript_Item_Full_Restore::
	finditem ITEM_FULL_RESTORE
	end
LakeOfRage_EventScript_Item_Max_Revive::
	finditem ITEM_MAX_REVIVE
	end
LakeOfRage_EventScript_Item_Red_Flute::
	finditem ITEM_RED_FLUTE
	end

LakeOfRage_EventScript_Dragonite::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	msgbox LakeOfRage_Text_Dragonite, MSGBOX_DEFAULT
	waitmoncry
	turnobject LOCALID_LAKEOFRAGE_DRAGONITE, DIR_WEST
	release
	end

LakeOfRage_EventScript_Lance::
	lock
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 3, LakeOfRage_EventScript_Lance_Return
	msgbox LakeOfRage_Text_LanceForcedToEvolve, MSGBOX_DEFAULT
	closemessage
	delay 20
	faceplayer
	turnobject LOCALID_LAKEOFRAGE_OLDMAN, DIR_WEST
	msgbox LakeOfRage_Text_LanceIntro2, MSGBOX_DEFAULT
	setvar VAR_MAHOGANY_TOWN_STATE, 3
	msgbox LakeOfRage_Text_LanceIntro3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined
LakeOfRage_EventScript_LanceAccept::
	lock
	msgbox LakeOfRage_Text_LanceRadioSignal, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, LakeOfRage_EventScript_LanceDragoniteLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeave
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeave
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE
LakeOfRage_EventScript_EndScene::
	setflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_DRAGONITE
	setvar VAR_MAHOGANY_TOWN_STATE, 4
	clearflag FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS
	release
	end

LakeOfRage_EventScript_Lance_Return::
	lock
	faceplayer
	msgbox LakeOfRage_Text_LanceAskHelp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, LakeOfRage_EventScript_LanceAccept
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined

LakeOfRage_EventScript_LancDeclined::
	msgbox LakeOfRage_Text_LanceRefused, MSGBOX_DEFAULT
	closemessage
	release
	end


LakeOfRage_EventScript_LanceDragoniteLeaveNorth::
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeaveNorth
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE
	goto LakeOfRage_EventScript_EndScene

LakeOfRage_Movement_LanceLeaveNorth:
	walk_left
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeaveNorth:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_LanceLeave:
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeave:
	delay_16
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Text_Dragonite:
	.string "DRAGONITE: ¡Gyafooha!$"

LakeOfRage_Text_LanceForcedToEvolve:
    .string "Este lago está lleno de GYARADOS\n"
    .string "pero nada más…\p"
    .string "Los MAGIKARP están siendo\n"
    .string "forzados a evolucionar…$"

LakeOfRage_Text_LanceIntro1:
    .string "¿Viniste aquí por los\n"
    .string "rumores?\p"
    .string "¿Eres {PLAYER}? Soy LANCE, un\n"
    .string "ENTRENADOR como tú.$"

LakeOfRage_Text_LanceIntro2:
    .string "Este hombre me informó sobre\n"
    .string "unos rumores.\p"
    .string "Así que vinimos a investigar…$"

LakeOfRage_Text_LanceIntro3:
    .string "Vi cómo luchabas antes,\n"
    .string "{PLAYER}.\p"
    .string "Se nota que eres un ENTRENADOR\n"
    .string "con gran habilidad.\p"
    .string "Si no te importa, ¿nos ayudas\n"
    .string "a investigar?$"

LakeOfRage_Text_LanceRadioSignal:
    .string "LANCE: ¡Excelente!\p"
    .string "Parece que los MAGIKARP del LAGO\n"
    .string "están siendo forzados a evolucionar.\p"
    .string "Una radio de PUEBLO CAOBA es\n"
    .string "la causa.\p"
    .string "Te estaremos esperando,\n"
    .string "{PLAYER}.$"

LakeOfRage_Text_LanceRefused:
    .string "Oh… Bueno, si cambias de opinión,\n"
    .string "por favor ayúdanos.$"

LakeOfRage_Text_LanceAskHelp:
    .string "LANCE: ¿Hm? ¿Vas a ayudarnos?\n"
    .string "¿Es así?$"

LakeOfRage_Text_GyaradosCry:
    .string "GYARADOS: ¡Gyashaa!$"

LakeOfRage_Text_Gramps:
    .string "¡Los GYARADOS están furiosos!\p"
    .string "¡Es un mal presagio!$"

LakeOfRage_Text_GrampsCleared:
    .string "¡Jaja! ¡Los MAGIKARP están picando!$"

LakeOfRage_Text_SuperNerd:
    .string "Oí que este lago lo hicieron\n"
    .string "GYARADOS enfurecidos.\p"
    .string "¿Habrá alguna conexión con\n"
    .string "su brote masivo actual?\l"
    .string "$"

LakeOfRage_Text_CooltrainerF:
    .string "¿Me engañaron los ojos? Vi un\n"
    .string "GYARADOS rojo en el lago...\p"
    .string "¿Pero no son los GYARADOS\n"
    .string "normalmente azules?$"


LakeOfRage_Text_FisherAndreSeen:
    .string "¡Déjame luchar con el POKéMON que\n"
    .string "acabo de capturar!$"

LakeOfRage_Text_FisherAndreBeaten:
    .string "Seré experto pescando, pero\n"
    .string "soy malísimo como entrenador...$"

LakeOfRage_Text_FisherAndreAfter:
    .string "¡No perderé como pescador! Atrapó\n"
    .string "POKéMON todo el día.$"


LakeOfRage_Text_FisherRaymondSeen:
    .string "Haga lo que haga, solo atrapo\n"
    .string "los mismos POKéMON…$"

LakeOfRage_Text_FisherRaymondBeaten:
    .string "Mi sedal está todo enredado…$"

LakeOfRage_Text_FisherRaymondAfter:
    .string "¿Por qué no puedo atrapar buenos\n"
    .string "POKéMON?$"

LakeOfRage_Text_CooltrainermAaronSeen:
    .string "Si un ENTRENADOR ve a otro,\n"
    .string "debe lanzarle un desafío.\p"
    .string "Es nuestro destino.$"

LakeOfRage_Text_CooltrainermAaronBeaten:
    .string "Uff… Buena batalla.$"

LakeOfRage_Text_CooltrainermAaronAfter:
    .string "POKéMON y ENTRENADORES se hacen\n"
    .string "fuertes luchando siempre.$"

LakeOfRage_Text_CooltrainerfLoisSeen:
    .string "¿Qué pasó con el GYARADOS\n"
    .string "rojo?\p"
    .string "¿Se fue?\p"
    .string "Rayos. ¿Vine hasta aquí\n"
    .string "en vano?\p"
    .string "Ya sé... ¡luchemos!$"

LakeOfRage_Text_CooltrainerfLoisBeaten:
    .string "¡Buen trabajo!$"

LakeOfRage_Text_CooltrainerfLoisAfter:
    .string "Ahora que lo pienso, vi una\n"
    .string "BUTTERFREE rosa.$"



LakeOfRage_EventScript_Wesley::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BLACK_BELT, LakeOfRage_EventScript_WesleyCompleted
	msgbox LakeOfRage_Text_MeetWesley, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, LakeOfRage_EventScript_WesleyNope
	case 1, LakeOfRage_EventScript_WesleyNope
	case 2, LakeOfRage_EventScript_WesleyNope
	case 3, LakeOfRage_EventScript_WesleyYes
	case 4, LakeOfRage_EventScript_WesleyNope
	case 5, LakeOfRage_EventScript_WesleyNope
	case 6, LakeOfRage_EventScript_WesleyNope
	case 7 LakeOfRage_EventScript_WesleyCancel
	case MULTI_B_PRESSED, LakeOfRage_EventScript_WesleyCancel
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyYes::
	msgbox LakeOfRage_Text_WesleyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_BELT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BLACK_BELT
	msgbox LakeOfRage_Text_WesleyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyNope::
	msgbox LakeOfRage_Text_WesleyNotWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyCancel::
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyCompleted::
	msgbox LakeOfRage_Text_WesleyWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_Text_MeetWesley:
    .string "WESLEY: Hola, ¿cómo estás?\p"
    .string "¡Soy de la familia WEEKDAY!\n"
	.string "¿Adivinas mi día favorito?$"

LakeOfRage_Text_WesleyGivesGift:
    .string "Mucho gusto. Por favor, toma un\n"
    .string "recuerdo.$"

LakeOfRage_Text_WesleyGaveGift:
    .string "WESLEY: El BLACK BELT sube el\n"
    .string "poder de los ataques lucha.$"

LakeOfRage_Text_WesleyWednesday:
    .string "WESLEY: Si me hallaste, ya habrás\n"
    .string "visto a mis hermanos y\l"
    .string "hermanas.\p"
    .string "¿O solo tuviste suerte?$"

LakeOfRage_Text_WesleyNotWednesday:
    .string "WESLEY: No exactamente...$"

LakeOfRage_EventScript_Sign1::
	msgbox LakeOfRage_Text_Sign, MSGBOX_SIGN
	end

LakeOfRage_EventScript_Sign2::
	msgbox LakeOfRage_Text_FishingGuruSign, MSGBOX_SIGN
	end

LakeOfRage_Text_Sign:
    .string "LAGO DE LA FURIA,\n"
    .string "también llamado LAGO GYARADOS.$"

LakeOfRage_Text_FishingGuruSign:
    .string "CASA DEL GURU DE PESCA$"
