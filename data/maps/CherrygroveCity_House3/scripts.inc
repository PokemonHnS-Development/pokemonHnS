CherrygroveCity_House3_MapScripts::
	.byte 0

CherrygroveCity_House3_EventScript_Boy::
	lock
	faceplayer
	msgbox CherrygroveCity_EvolutionHouse_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_House3_EventScript_Girl::
	lock
	faceplayer
	msgbox CherrygroveCity_EvolutionHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_EvolutionHouse_Text_Youngster:
	.string "Los POKéMON ganan experiencia en\n"
	.string "batalla y cambian su forma.$"

CherrygroveCity_EvolutionHouse_Text_Lass:
	.string "¿Cambian los POKéMON?\p"
	.string "¡Me sorprendería que alguno\n"
	.string "hiciera eso!$"
