NewBarkTown_House2_MapScripts::
	.byte 0


NewBarkTown_House2_EventScript_ElmsWife::
	lock
	faceplayer
	msgbox NewBarkTown_House2_Text_ElmsWife, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House2_EventScript_ElmsSon::
	lock
	faceplayer
	msgbox NewBarkTown_House2_Text_ElmsSon, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House2_Text_ElmsWife:
	.string "¡Hola, {PLAYER}! Mi marido anda\n"
	.string "tan ocupado… espero que esté bien.\p"
	.string "Cuando se mete en sus\n"
	.string "investigaciones POKéMON, hasta\l"
	.string "se olvida de comer.$"

NewBarkTown_House2_Text_ElmsSon:
	.string "Cuando sea grande, voy a\n"
	.string "ayudar a mi papá!\p"
	.string "¡Seré un gran profesor\n"
	.string "de POKéMON!$"
