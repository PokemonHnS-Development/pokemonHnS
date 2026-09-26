BattleFrontier_Lounge4_MapScripts::
	.byte 0

BattleFrontier_Lounge4_EventScript_Woman::
	msgbox BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Cook::
	msgbox BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Man::
	msgbox BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles, MSGBOX_NPC
	end

BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring:
	.string "¿Pasarán entrevistas de\n"
	.string "ENTRENADORES fuertes hoy?$"

BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere:
	.string "Si abriera un restaurante aquí,\n"
	.string "seguro ganaría dinero.$"

BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles:
	.string "Uff…\p"
	.string "Necesito un respiro tras\n"
	.string "batallas tan intensas…\p"
	.string "Pero ni ahora dejo de planear\n"
	.string "estrategias y combos.$"

