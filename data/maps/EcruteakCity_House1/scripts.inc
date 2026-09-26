EcruteakCity_House1_MapScripts::
	.byte 0

EcruteakCity_House1_EventScript_Gramps::
	lock
	faceplayer
	msgbox EcruteakLugiaSpeechHouse_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House1_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakLugiaSpeechHouse_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakLugiaSpeechHouse_Text_Gramps:
	.string "Pasó cuando yo era joven.\p"
	.string "El cielo se volvió negro. Un\n"
	.string "POKéMON volador gigante tapaba\l"
	.string "el sol.\p"
	.string "¿Qué POKéMON sería aquel?\p"
	.string "Parecía un ave y un dragón.$"

EcruteakLugiaSpeechHouse_Text_Youngster:
	.string "¿Hay un POKéMON tan grande?\p"
	.string "Si existe, debe ser poderoso.$"
