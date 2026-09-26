SlateportCity_House_MapScripts::
	.byte 0

SlateportCity_House_EventScript_PokefanM::
	msgbox SlateportCity_House_Text_NatureToDoWithStatGains, MSGBOX_NPC
	end

SlateportCity_House_EventScript_Girl::
	msgbox SlateportCity_House_Text_MustBeGoingToBattleTent, MSGBOX_NPC
	end

SlateportCity_House_Text_NatureToDoWithStatGains:
	.string "Mi POKéMON es natura PRESUROSO.\p"
	.string "Tiene más SPEED que mis otros\n"
	.string "POKéMON.\p"
	.string "Quizás la naturaleza influye en\n"
	.string "las estadísticas del POKéMON.$"

SlateportCity_House_Text_MustBeGoingToBattleTent:
	.string "Eres ENTRENADOR, ¿verdad?\p"
	.string "Ya que viniste a CIUDAD PORTAL,\n"
	.string "debes ir a la CARPA DE BATALLA.$"

