.set LOCALID_MUSEUM_ROOTFOSSIL, 5
.set LOCALID_MUSEUM_CLAWFOSSIL, 6

PewterCity_Museum_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Lab_OnTransition
	.byte 0

PewterCity_Museum_1F_EventScript_RootFossil::
	finditem ITEM_ROOT_FOSSIL
	setflag FLAG_HIDE_PEWTER_ROOT_FOSSIL
	removeobject LOCALID_MUSEUM_ROOTFOSSIL
	end

PewterCity_Museum_1F_EventScript_ClawFossil::
	finditem ITEM_CLAW_FOSSIL
	setflag FLAG_HIDE_PEWTER_CLAW_FOSSIL
	removeobject LOCALID_MUSEUM_CLAWFOSSIL
	end

PewterCity_Museum_1F_EventScript_Receptionist::
	msgbox PewterCity_Museum_1F_Text_Recptionist, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_FossilWoman::
	goto_if_set FLAG_HIDE_PEWTER_CLAW_FOSSIL, PewterCity_Museum_1F_EventScript_FossilWoman2
	goto_if_set FLAG_HIDE_PEWTER_ROOT_FOSSIL, PewterCity_Museum_1F_EventScript_FossilWoman2
	goto_if_ge VAR_TEMP_2, 1, PewterCity_Museum_1F_EventScript_FossilWoman2
	msgbox PewterCity_Museum_1F_Text_FossilWoman, MSGBOX_NPC
	setvar VAR_TEMP_2, 1
	end

PewterCity_Museum_1F_EventScript_FossilWoman2::
	msgbox PewterCity_Museum_1F_Text_FossilWomanAfter, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_Oldman::
	msgbox PewterCity_Museum_1F_Text_Oldman, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_Bones::
	msgbox PewterCity_Museum_1F_Text_Bones, MSGBOX_SIGN
	end

PewterCity_Museum_1F_Text_Recptionist:
	.string "¡Bienvenido!\p"
	.string "Te aviso que los especímenes\n"
	.string "grandes se llevaron a otros\l"
	.string "museos para exhibirlos.\p"
	.string "¡Por ahora, la entrada es\n"
	.string "gratis!\p"
	.string "Adelante, pasa.$"

PewterCity_Museum_1F_Text_FossilWoman:
	.string "Debes ser un gran ENTRENADOR.\p"
	.string "No necesitamos los fósiles\n"
	.string "que están allá en el mostrador.\p"
	.string "Un hombre raro de pelo plateado\n"
	.string "dejó muchísimos aquí.\p"
	.string "Tómalos si quieres.$"

PewterCity_Museum_1F_Text_FossilWomanAfter:
	.string "Solemos compartir datos con los\n"
	.string "estudiosos de RUINAS ALFA.\p"
	.string "¡Incluso compartimos fósiles\n"
	.string "por la PC!$"

PewterCity_Museum_1F_Text_Oldman:
	.string "Debo estar agradecido por mi\n"
	.string "larga vida.\p"
	.string "¡Jamás pensé que vería los\n"
	.string "huesos de un dragón!$"

PewterCity_Museum_1F_Text_Bones:
	.string "Huesos de un antiguo POKéMON\n"
	.string "dragón.$"
