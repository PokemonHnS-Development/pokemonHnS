CliffEdgeCave_MapScripts::
	.byte 0

CliffEdgeCave_EventScript_BaldMan::
	lock
	faceplayer
	msgbox CliffEdgeCave_Text_Baldman, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeCave_Text_Baldman:
	.string "Si ves un camino dividido\n"
	.string "en una cueva, lo más probable es\l"
	.string "que uno sea el correcto y el otro\l"
	.string "sea un callejón sin salida.\p"
	.string "Pero todos quieren probar ambos.$"
