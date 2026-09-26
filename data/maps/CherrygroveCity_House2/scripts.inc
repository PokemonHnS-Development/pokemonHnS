CherrygroveCity_House2_MapScripts::
	.byte 0

CherrygroveCity_House2_EventScript_GuideGent::
	lock
	faceplayer
	msgbox CherrygroveCity_GuideHouse_Text_GuideGent, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GuideHouse_Text_GuideGent:
	.string "Cuando era niño, ¡era un\n"
	.string "gran ENTRENADOR!\p"
	.string "Toma un consejo:\n"
	.string "¡Atrapa muchos POKéMON!\p"
	.string "¡Trátalos a todos con cariño!$"
