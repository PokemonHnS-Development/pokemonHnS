FuchsiaCity_Mart_MapScripts::
	.byte 0

FuchsiaCity_Mart_EventScript_Fisher::
	msgbox FuchsiaMart_Text_Fisher, MSGBOX_NPC
	end

FuchsiaCity_Mart_EventScript_Woman::
	msgbox FuchsiaMart_Text_CooltrainerF, MSGBOX_NPC
	end

FuchsiaMart_Text_Fisher:
	.string "La antigua SAFARI ZONE tenía\n"
	.string "mejores recuerdos...$"

FuchsiaMart_Text_CooltrainerF:
	.string "La nieta del antiguo GUARDABOSQUES\n"
	.string "de la SAFARI ZONE vive aquí.$"
