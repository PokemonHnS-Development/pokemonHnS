Gate_MahoganyTown_Route43_MapScripts::
	.byte 0

Gate_MahoganyTown_Route43_EventScript_Cop::
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 11, Gate_MahoganyTown_Route43_EventScript_CopAfter
	msgbox Route43MahoganyGate_Text_Officer, MSGBOX_NPC
	end

Gate_MahoganyTown_Route43_EventScript_CopAfter::
	msgbox Route43MahoganyGate_Text_Officer_RocketsCleared, MSGBOX_NPC
	end

Route43MahoganyGate_Text_Officer:
    .string "Solo gente que va al LAGO de la\n"
    .string "FURIA ha pasado por aquí.$"

Route43MahoganyGate_Text_Officer_RocketsCleared:
    .string "Nadie va al LAKE OF RAGE\n"
    .string "en estos días.$"

