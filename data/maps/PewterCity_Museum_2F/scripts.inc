PewterCity_Museum_2F_MapScripts::
	.byte 0


PewterCity_Museum_2F_EventScript_Nerd::
	msgbox PewterCity_Museum_2F_Text_Nerd, MSGBOX_NPC
	end

PewterCity_Museum_2F_EventScript_Daughter::
	lock
	msgbox PewterCity_Museum_2F_Text_AskedDaddyToCatchPikachu, MSGBOX_DEFAULT
	release
	end

PewterCity_Museum_2F_EventScript_Dad::
	lock
	msgbox PewterCity_Museum_2F_Text_PikachuSoonIPromise, MSGBOX_DEFAULT
	release
	end

PewterCity_Museum_2F_EventScript_Meteor::
	msgbox PewterCity_Museum_2F_Text_MeteoriteThatFellOnMtMoon, MSGBOX_SIGN
	end

PewterCity_Museum_2F_Text_Nerd:
	.string "Dicen que meteoritos cayeron\n"
	.string "en ISLA NACIMIENTO.\p"
	.string "Nos encantaría exhibirlos aquí\n"
	.string "en nuestro museo, pero...\p"
	.string "Dicen que emiten una energía\n"
	.string "extraña y no pueden ser\l"
	.string "trasladados...$"

PewterCity_Museum_2F_Text_AskedDaddyToCatchPikachu::
    .string "¡Quiero un PIKACHU!\n"
    .string "¡Es tan lindo!\p"
    .string "¡Le pedí a mi papá que atrape uno!$"

PewterCity_Museum_2F_Text_PikachuSoonIPromise::
    .string "¡Sí, pronto un PIKACHU, lo prometo!$"

PewterCity_Museum_2F_Text_SpaceShuttle::
    .string "Transbordador Espacial$"

PewterCity_Museum_2F_Text_MeteoriteThatFellOnMtMoon::
    .string "Un meteorito que cayó en MT. MOON.\n"
    .string "Se cree que es una MOON STONE.$"
