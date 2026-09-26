SSAqua_RoomSE_MapScripts::
	.byte 0

SSAqua_RoomSE_EventScript_Colin::
	trainerbattle_single TRAINER_COLIN SSAqua_RoomSE_Text_PokefanmColinSeen, SSAqua_RoomSE_Text_PokefanmColinBeaten
	msgbox SSAqua_RoomSE_Text_PokefanmColinAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_EventScript_Meg::
	trainerbattle_double TRAINER_MEG_AND_PEG, SSAqua_RoomSE_Text_TwinsMegandpeg1Seen, SSAqua_RoomSE_Text_TwinsMegandpeg1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox SSAqua_RoomSE_Text_TwinsMegandpeg1After, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_EventScript_Peg::
	trainerbattle_double TRAINER_MEG_AND_PEG, SSAqua_RoomSE_Text_TwinsMegandpeg2Seen, SSAqua_RoomSE_Text_TwinsMegandpeg2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox SSAqua_RoomSE_Text_TwinsMegandpeg2After, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_Text_PokefanmColinSeen:
    .string "¡Hola! ¿Quieres luchar\n"
    .string "conmigo?$"

SSAqua_RoomSE_Text_PokefanmColinBeaten:
    .string "¡Eres fuerte!$"

SSAqua_RoomSE_Text_PokefanmColinAfter:
    .string "¿Viajas solo?\n"
    .string "¿Tu mamá no está preocupada?$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Seen:
    .string "¿Crees que soy un bebé?\n"
    .string "¡Eso no es justo!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Beaten:
    .string "¡Oh! ¡Perdimos!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1After:
    .string "¡Bebé es un nombre grosero\n"
    .string "para decirnos a las chicas!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Seen:
    .string "¡No soy un bebé!\n"
    .string "¡No es amable decirle eso a una dama!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Beaten:
    .string "¡Oh! ¡Perdimos!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2After:
    .string "¡A veces los niños son más\n"
    .string "listos que los adultos!$"
