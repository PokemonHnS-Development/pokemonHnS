Route41_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route41_MapScript_OnTransition
	.byte 0

Route41_MapScript_OnTransition::
	goto_if_eq VAR_COMPLETED_LUGIA, 4, Route41_MapScript_DoNothing
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

Route41_MapScript_DoNothing::
	end

Route41_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, Route41_Text_SwimmermCharlieSeen, Route41_Text_SwimmermCharlieBeaten
	msgbox Route41_Text_SwimmermCharlieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermCharlieSeen:
	.string "El agua está tibia aquí.\n"
	.string "Estoy relajado y ágil.\p"
	.string "¡Claro, peleemos!$"

Route41_Text_SwimmermCharlieBeaten:
	.string "¡Ay! ¡Tengo la piel arrugada!$"

Route41_Text_SwimmermCharlieAfter:
	.string "¿No es relajante flotar\n"
	.string "así nada más?$"

Route41_EventScript_George::
	trainerbattle_single TRAINER_GEORGE, Route41_Text_SwimmermGeorgeSeen, Route41_Text_SwimmermGeorgeBeaten
	msgbox Route41_Text_SwimmermGeorgeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermGeorgeSeen:
	.string "Estoy algo cansado.\n"
	.string "Si gano, préstame tu POKéMON.$"

Route41_Text_SwimmermGeorgeBeaten:
	.string "Jadeo, jadeo…$"

Route41_Text_SwimmermGeorgeAfter:
	.string "CIANWOOD está muy lejos.\p"
	.string "Pero volver a OLIVINE\n"
	.string "tampoco es fácil.\p"
	.string "¿Qué debería hacer?$"

Route41_EventScript_Berke::
	trainerbattle_single TRAINER_BERKE, Route41_Text_SwimmermBerkeSeen, Route41_Text_SwimmermBerkeBeaten
	msgbox Route41_Text_SwimmermBerkeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermBerkeSeen:
	.string "¿Ves esas islas que están\n"
	.string "bloqueadas por remolinos?\p"
	.string "¡Debe haber un secreto!$"

Route41_Text_SwimmermBerkeBeaten:
	.string "¿Cuál es el secreto de tu\n"
	.string "fuerza?$"

Route41_Text_SwimmermBerkeAfter:
	.string "Era una noche oscura y tormentosa…\p"
	.string "Vi a ese POKéMON gigante volar\n"
	.string "desde las islas.\p"
	.string "Soltaba plumas de sus\n"
	.string "alas plateadas.$"

Route41_EventScript_Kirk::
	trainerbattle_single TRAINER_KIRK, Route41_Text_SwimmermKirkSeen, Route41_Text_SwimmermKirkBeaten
	msgbox Route41_Text_SwimmermKirkAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermKirkSeen:
	.string "Las olas son fuertes aquí.\p"
	.string "Te agotan mientras\n"
	.string "nadas.$"

Route41_Text_SwimmermKirkBeaten:
	.string "¡Estoy agotado!$"

Route41_Text_SwimmermKirkAfter:
	.string "Las corrientes me impiden\n"
	.string "llegar a esa isla.$"

Route41_EventScript_Mathew::
	trainerbattle_single TRAINER_MATHEW, Route41_Text_SwimmermMathewSeen, Route41_Text_SwimmermMathewBeaten
	msgbox Route41_Text_SwimmermMathewAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermMathewSeen:
	.string "¿Buscas los secretos de las\n"
	.string "ISLAS REMOLINO?$"

Route41_Text_SwimmermMathewBeaten:
	.string "¡Vaya, tienes mucha resistencia!$"

Route41_Text_SwimmermMathewAfter:
	.string "Un secreto de ISLAS REMOLINO…\p"
	.string "¡Adentro está oscuro como la noche!$"

Route41_EventScript_Kaylee::
	trainerbattle_single TRAINER_KAYLEE, Route41_Text_SwimmerfKayleeSeen, Route41_Text_SwimmerfKayleeBeaten
	msgbox Route41_Text_SwimmerfKayleeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKayleeSeen:
	.string "Voy camino a ISLAS REMOLINO.\p"
	.string "Iré a explorar con mis amigos.$"

Route41_Text_SwimmerfKayleeBeaten:
	.string "¿Así es como se hace?$"

Route41_Text_SwimmerfKayleeAfter:
	.string "Se dice que hay un gran\n"
	.string "POKéMON bajo ISLAS REMOLINO.\p"
	.string "¿Qué será?$"

Route41_EventScript_Susie::
	trainerbattle_single TRAINER_SUSIE, Route41_Text_SwimmerfSusieSeen, Route41_Text_SwimmerfSusieBeaten
	msgbox Route41_Text_SwimmerfSusieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfSusieSeen:
	.string "Te ves muy elegante\n"
	.string "montando tu POKéMON.$"

Route41_Text_SwimmerfSusieBeaten:
	.string "Estoy destrozado…$"

Route41_Text_SwimmerfSusieAfter:
	.string "¿No había una canción famosa\n"
	.string "de un chico montando un LAPRAS?$"

Route41_EventScript_Denise::
	trainerbattle_single TRAINER_DENISE, Route41_Text_SwimmerfDeniseSeen, Route41_Text_SwimmerfDeniseBeaten
	msgbox Route41_Text_SwimmerfDeniseAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfDeniseSeen:
	.string "¡El clima es tan hermoso\n"
	.string "que estoy distraído!$"

Route41_Text_SwimmerfDeniseBeaten:
	.string "¡Ohhh!$"

Route41_Text_SwimmerfDeniseAfter:
	.string "El sol es fatal para la piel.\p"
	.string "Pero no uso bloqueador.\p"
	.string "No quiero contaminar el agua.$"

Route41_EventScript_Kara::
	trainerbattle_single TRAINER_KARA, Route41_Text_SwimmerfKaraSeen, Route41_Text_SwimmerfKaraBeaten
	msgbox Route41_Text_SwimmerfKaraAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKaraSeen:
	.string "Si necesitas descansar,\n"
	.string "solo flota en el agua.\p"
	.string "Recuperarás el aliento\n"
	.string "para seguir con fuerza.$"

Route41_Text_SwimmerfKaraBeaten:
	.string "¡Oh! Tienes más energía que yo.$"

Route41_Text_SwimmerfKaraAfter:
	.string "Oí rugidos desde lo profundo\n"
	.string "de las ISLAS.$"

Route41_EventScript_Wendy::
	trainerbattle_single TRAINER_WENDY, Route41_Text_SwimmerfWendySeen, Route41_Text_SwimmerfWendyBeaten
	msgbox Route41_Text_SwimmerfWendyAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfWendySeen:
	.string "De noche, los STARYU se juntan\n"
	.string "cerca de la superficie.$"

Route41_Text_SwimmerfWendyBeaten:
	.string "Ay, Dios mío...$"

Route41_Text_SwimmerfWendyAfter:
	.string "Los grupos de STARYU brillan\n"
	.string "al mismo tiempo.\p"
	.string "Es tan bello que asusta.$"

Route41_EventScript_Tentacruel1::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_0, 2, Route41_EventScript_TentacruelAttack1
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_0, 1
	release
	end
Route41_EventScript_TentacruelAttack1::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_NO_SHINY
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_0, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel2::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_1, 2, Route41_EventScript_TentacruelAttack2
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_1, 1
	release
	end
Route41_EventScript_TentacruelAttack2::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel3::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_2, 2, Route41_EventScript_TentacruelAttack3
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_2, 1
	release
	end
Route41_EventScript_TentacruelAttack3::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel4::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_3, 2, Route41_EventScript_TentacruelAttack4
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_3, 1
	release
	end
Route41_EventScript_TentacruelAttack4::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_3, 0
	closemessage
	release
	end

Route41_Text_Tentacruel:
	.string "TENTACRUEL: Cruooo...$"

Route41_Text_TentacruelAttack:
	.string "TENTACRUEL: ¡CRUOOOOOO!$"

Route41_Text_TentacruelHeal:
	.string "¡TENTACRUEL usó RECUPERAR!\n"
	.string "¡Se ha curado por completo!$"
