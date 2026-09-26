VioletCity_Mart_MapScripts::
	.byte 0

VioletCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

VioletCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Mart_EventScript_Rocker::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end
	
VioletCity_Mart_Text_Granny:
	.string "Al capturar un POKéMON,\n"
	.string "puede que sea débil.\p"
	.string "Pero con el tiempo se\n"
	.string "volverá fuerte.\p"
	.string "Es importante tratar a los\n"
	.string "POKéMON con amor.$"

VioletCity_Mart_Text_CooltrainerM:
	.string "Los POKéMON pueden llevar\n"
	.string "POCIÓN y ANTÍDOTO.\p"
	.string "Pero no parecen saber cómo\n"
	.string "usar objetos artificiales.$"
