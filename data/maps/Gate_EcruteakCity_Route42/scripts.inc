Gate_EcruteakCity_Route42_MapScripts::
	.byte 0

Gate_EcruteakCity_Route42_EventScript_Policeman::
	lock
	faceplayer
	msgbox Route42_Text_EcruteakGateOfficer, MSGBOX_DEFAULT
	closemessage
	release
	end

Route42_Text_EcruteakGateOfficer:
	.string "EL MT.MORTAR es como un laberinto\n"
	.string "por dentro.\p"
	.string "Ten cuidado. No te pierdas\n"
	.string "allí dentro.$"

