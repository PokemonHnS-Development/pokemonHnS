Gate_Route31_VioletCity_MapScripts::
	.byte 0

Gate_Route31_VioletCity_EventScript_Policeman::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_Text_Policeman:
	.string "¡Hola! ¿Visitaste la\n"
	.string "TORRE VERDOR?$"

Gate_Route31_VioletCity_Text_CooltrainerF:
	.string "Vi al POKéMON más lindo de\n"
	.string "todos.\p"
	.string "¡Se parecía mucho a PIKACHU!$"
