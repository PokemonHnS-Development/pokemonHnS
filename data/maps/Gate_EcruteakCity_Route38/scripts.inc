Gate_EcruteakCity_Route38_MapScripts::
	.byte 0

Route38_EventScript_Officer::
	lock
	faceplayer
	msgbox Route38_Text_EcruteakGateOfficer, MSGBOX_DEFAULT
	closemessage
	release
	end

Route38_Text_EcruteakGateOfficer:
	.string "¿De dónde dijiste que eres?\p"
	.string "¿PUEBLO PRIMAVERA?\p"
	.string "El PROF.ELM vive por allá,\n"
	.string "¿verdad?\p"
	.string "Has recorrido mucho camino\n"
	.string "para llegar aquí.$"
