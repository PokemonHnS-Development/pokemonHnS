RustboroCity_House3_MapScripts::
	.byte 0

RustboroCity_House3_EventScript_OldMan::
	msgbox RustboroCity_House3_Text_IGivePerfectlySuitedNicknames, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWoman::
	msgbox RustboroCity_House3_Text_NamingPikachuPekachu, MSGBOX_NPC
	end

@ Misspelling on purpose, see nickname
RustboroCity_House3_EventScript_Pekachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox RustboroCity_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_House3_Text_IGivePerfectlySuitedNicknames:
	.string "A mis POKéMON les pongo\n"
	.string "apodos muy adecuados!\p"
	.string "Es mi forma de expresar, eh...\n"
	.string "¡originalidad, sí, eso es!$"

RustboroCity_House3_Text_NamingPikachuPekachu:
	.string "¿Pero llamar PEKACHU a un\n"
	.string "PIKACHU? No tiene sentido.\p"
	.string "Supongo que es bueno usar un nombre\n"
	.string "fácil de entender, pero...$"

RustboroCity_House3_Text_Pekachu:
	.string "PEKACHU: ¡Peka!$"

