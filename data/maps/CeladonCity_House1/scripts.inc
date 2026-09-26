CeladonCity_House1_MapScripts::
	.byte 0

CeladonCity_House1_EventScript_Chef::
	msgbox CeladonCity_House1_Text_ChefEatathon, MSGBOX_NPC
	end

CeladonCity_House1_EventScript_Fisher1::
	lock
	msgbox CeladonCity_House1_Text_Fisher1Snarfle, MSGBOX_DEFAULT
	faceplayer
	msgbox CeladonCity_House1_Text_Fisher1Concentration, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_WEST
	release
	end

CeladonCity_House1_EventScript_Fisher2::
	lock
	msgbox CeladonCity_House1_Text_Fisher2GulpChew, MSGBOX_DEFAULT
	faceplayer
	msgbox CeladonCity_House1_Text_Fisher2Quantity, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_EAST
	release
	end

CeladonCity_House1_EventScript_Fisher3::
	lock
	msgbox CeladonCity_House1_Text_Fisher3MunchMunch, MSGBOX_DEFAULT
	faceplayer
	msgbox CeladonCity_House1_Text_Fisher3GoldenrodIsBest, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_EAST
	release
	end

CeladonCity_House1_EventScript_Teacher::
	lock
	msgbox CeladonCity_House1_Text_TeacherCrunchCrunch, MSGBOX_DEFAULT
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_House1_EventScript_TeacherCoincase
	msgbox CeladonCity_House1_Text_TeacherKeepEating, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_WEST
	release
	end

CeladonCity_House1_EventScript_TeacherCoincase::
	msgbox CeladonCity_House1_Text_TeacherNoCoinCase, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_WEST
	release
	end

CeladonCity_House1_EventScript_Sign::
	msgbox CeladonCity_House1_Text_EatathonContestPoster, MSGBOX_SIGN
	end

CeladonCity_House1_Text_ChefEatathon:
	.string "¡Hola!\p"
	.string "Hacemos un concurso de comida.\p"
	.string "No podemos atenderte ahora.\n"
	.string "Lo siento.$"

CeladonCity_House1_Text_Fisher1Snarfle:
	.string "...Ñam, mastico...$"

CeladonCity_House1_Text_Fisher1Concentration:
	.string "¡No me hables!\p"
	.string "¡Romperás mi concentración!$"

CeladonCity_House1_Text_Fisher2GulpChew:
	.string "...Glup... Mastico...$"

CeladonCity_House1_Text_Fisher2Quantity:
	.string "¡Prefiero cantidad que calidad!\p"
	.string "¡Soy feliz si estoy lleno!$"

CeladonCity_House1_Text_Fisher3MunchMunch:
	.string "Munch, munch...$"

CeladonCity_House1_Text_Fisher3GoldenrodIsBest:
	.string "La comida es buena, pero\n"
	.string "CIUDAD TRIGAL tiene la mejor\l"
	.string "de todas.$"

CeladonCity_House1_Text_TeacherCrunchCrunch:
	.string "Crunch... Crunch...$"

CeladonCity_House1_Text_TeacherNoCoinCase:
	.string "Nadie aquí te dará un ESTUCHE\n"
	.string "DE MONEDAS. Busca en JOHTO.$"

CeladonCity_House1_Text_TeacherKeepEating:
	.string "Crunch... Crunch...\p"
	.string "¡Puedo seguir comiendo!\p"
	.string "¡Más, CHEF!$"

CeladonCity_House1_Text_EatathonContestPoster:
	.string "¡Concurso de comer! ¡Sin tiempo!\p"
	.string "¡Una batalla sin fin! ¡El que más\n"
	.string "coma gana todo gratis!$"

