GoldenrodCity_House2_MapScripts::
	.byte 0

GoldenrodCity_House2_EventScript_Man::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Man, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_House2_EventScript_Woman::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodPPSpeechHouse_Text_Man:
    .string "Una vez en batalla, mi\n"
    .string "POKéMON no pudo atacar.\p"
    .string "Los PUNTOS DE PODER, o PP, de sus\n"
    .string "movimientos se agotaron.$"

GoldenrodPPSpeechHouse_Text_Lass:
    .string "A veces, un POKéMON sano puede\n"
    .string "no poder usar sus movimientos.\p"
    .string "Si pasa, cúralo en un\n"
    .string "CENTRO POKéMON o usa un objeto.$"
