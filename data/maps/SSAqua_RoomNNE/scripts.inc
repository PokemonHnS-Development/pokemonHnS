SSAqua_RoomNNE_MapScripts::
	.byte 0

SSAqua_RoomNNE_EventScript_Sean::
	trainerbattle_single TRAINER_SEAN SSAqua_RoomNNE_Text_CooltrainermSeanSeen, SSAqua_RoomNNE_Text_CooltrainermSeanBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_EventScript_Carol::
	trainerbattle_single TRAINER_CAROL SSAqua_RoomNNE_Text_CooltrainerfCarolSeen, SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_Text_CooltrainermSeanSeen:
    .string "Iré a KANTO\n"
    .string "para probar mi nivel.$"

SSAqua_RoomNNE_Text_CooltrainermSeanBeaten:
    .string "¡Quería ganar!$"

SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle:
    .string "Entrenadores de JOHTO\n"
    .string "pueden luchar contra\l"
    .string "LÍDERES de KANTO.$"

SSAqua_RoomNNE_Text_CooltrainerfCarolSeen:
    .string "¡Entreno para\n"
    .string "ser el CAMPEÓN!$"

SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten:
    .string "¿Qué es tan diferente\n"
    .string "entre nosotros?$"

SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle:
    .string "¡Algún día voy a\n"
    .string "derrotarte!$"
