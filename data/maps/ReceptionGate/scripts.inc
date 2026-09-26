.set LOCALID_INDIGOJUNCTION_POLICEMAN, 1
.set LOCALID_INDIGOJUNCTION_JANINE, 4

ReceptionGate_MapScripts::
	.byte 0

ReceptionGate_EventScript_Janine::
    lock
    faceplayer
    msgbox ReceptionGate_Text_Janine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_ROUTE22_JANINE
    removeobject LOCALID_INDIGOJUNCTION_JANINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_JANINE
    release
    end

ReceptionGate_Text_Janine:
    .string "JANINE: Voy a casa de mi papá\n"
    .string "para llevarle el almuerzo.\p"
    .string "El ALTO MANDO no descansa\n"
    .string "ni de día ni de noche. Es duro,\l"
    .string "¿sabes?\p"
    .string "Si quieres otra batalla,\n"
    .string "estaré en el DOJO más tarde.$"


ReceptionGate_EventScript_Officer::
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_NPC
    end

ReceptionGate_Trigger::
    lock
    playse SE_PIN
    applymovement LOCALID_INDIGOJUNCTION_POLICEMAN, Common_Movement_ExclamationMark
    delay 20
    goto_if_lt VAR_ECRUTEAK_CITY_THEATER, 8, ReceptionGate_EventScript_Kimono
    msgbox VictoryRoadGate_Text_Officer, MSGBOX_DEFAULT
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    setvar VAR_ROUTE27_STATE, 2
    release
    end

ReceptionGate_EventScript_Kimono::
    msgbox VictoryRoadGate_Text_Kimono, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end 

ReceptionGate_EventScript_NotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end

ReceptionGate_EventScript_SilverGuard::
    msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
    end
ReceptionGate_EventScript_KantoGuard::
    msgbox VictoryRoadGate_Text_RightBlackBelt, MSGBOX_NPC
    end

VictoryRoadGate_Text_Officer:
    .string "Solo ENTRENADORES que se hayan\n"
    .string "probado a sí mismos pasarán.$"

VictoryRoadGate_Text_Kimono:
    .string "Lo siento, el camino está cerrado\n"
    .string "hasta que alguien se encargue de\l"
    .string "ese POKéMON LEGENDARIO...$"

VictoryRoadGate_Text_NotEnoughBadges:
    .string "No tienes todas las MEDALLAS\n"
    .string "de JOHTO.\p"
    .string "Lo siento, pero no puedo dejarte\n"
    .string "pasar.$"

VictoryRoadGate_Text_EightBadges:
    .string "¡Oh! ¡Las ocho MEDALLAS de JOHTO!\p"
    .string "¡Por favor, pasa adelante!$"

VictoryRoadGate_Text_LeftBlackBelt:
    .string "Este camino va al MT.SILVER.\p"
    .string "Verás POKéMON muy fuertes\n"
    .string "por allá.$"

VictoryRoadGate_Text_RightBlackBelt:
    .string "¿Vas a la POKéMON LEAGUE?\p"
    .string "El ELITE FOUR es tan fuerte que\n"
    .string "da miedo, ¡y te están esperando!$"
