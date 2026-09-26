CliffEdgeGate_MapScripts::
	.byte 0

CliffEdgeGate_EventScript_Woman::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_IntroOpen, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_EventScript_Picnicker::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_Expectations, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_Text_IntroOpen:
	.string "¿Sabías que hay una SAFARI ZONE\n"
	.string "aquí a la vuelta?\p"
	.string "¡Es muy divertida!\n"
	.string "Verás muchos tipos de\l"
	.string "POKéMON, ¡y puedes atraparlos todos!\p"
	.string "No hay razón para no ir, ¿verdad?\n"
	.string "Aquí a la vuelta.$"

CliffEdgeGate_Text_Expectations:
	.string "Agradezco que todos tengan\n"
	.string "tantas ganas de ir.\p"
	.string "Pero la recepcionista parece\n"
	.string "demasiado dramática...\p"
	.string "¡No se emocionen demasiado!$"

CliffEdgeGate_EventScript_CaveSign::
	lock
	msgbox CliffEdgeGate_Text_SignOpen, MSGBOX_SIGN
	closemessage
	release
	end

CliffEdgeGate_Text_SignOpen:
	.string "¡Todo es emocionante!\n"
	.string "¡Explora y halla POKéMON salvajes!\l"
	.string "¡La ZONA SAFARI del Guardián BAOBA\l"
	.string "ya está abierta!$"

