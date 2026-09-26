TinTower_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_OnTransition
	.byte 0

TinTower_OnTransition::
	setescapewarp MAP_BELLCHIME_TRAIL, 35, 42
	end

TinTower_1F_EventScript_SageA::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageA_Hooh
	msgbox TinTower_1F_Sage4_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageA_Hooh::
	msgbox TinTower_1F_Sage4_Text1, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageB_Hooh
	msgbox TinTower_1F_Sage2_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB_Hooh::
	msgbox TinTower_1F_Sage1_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageC_Hooh
	msgbox TinTower_1F_Sage6_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC_Hooh::
	msgbox TinTower_1F_Sage3_Text, MSGBOX_DEFAULT
	closemessage
	release
	end


TinTower_1F_Sage1_Text:
	.string "Según la leyenda...\n"
	.string "Cuando las almas de POKéMON y humanos\p"
	.string "se unen, del cielo desciende un\n"
	.string "POKéMON de colores arcoíris...\p"
	.string "¿Será que los POKéMON legendarios\n"
	.string "nos ponen a prueba a los humanos?$"

TinTower_1F_Sage2_Text:
	.string "Cuando la TORRE BRONCE ardió,\n"
	.string "dicen que tres POKéMON sin nombre\l"
	.string "perecieron. Fue trágico.\p"
	.string "Sin embargo...\p"
	.string "Un POKéMON de colores arcoíris...\n"
	.string "En otras palabras...\p"
	.string "HO-OH bajó del cielo y\n"
	.string "dio nueva vida a esos tres POKéMON.\p"
	.string "Ellos son...\n"
	.string "SUICUNE, ENTEI y RAIKOU.\p"
	.string "Eso es lo que cuentan.$"

TinTower_1F_Sage3_Text:
	.string "Dicen que las dos TORRES fueron\n"
	.string "construidas para fomentar la amistad\p"
	.string "y esperanza entre POKéMON y gente.\n"
	.string "Fue hace 700 años, pero ese ideal\p"
	.string "sigue siendo importante hoy día.$"

TinTower_1F_Sage4_Text1:
	.string "¡Parece que HO-OH descendió\n"
	.string "sobre esta, la TORRE CAMPANA!$"

TinTower_1F_Sage4_Text2:
	.string "Dicen que los POKéMON legendarios\n"
	.string "encarnan tres poderes...\p"
	.string "El rayo que golpeó la TORRE.\n"
	.string "El fuego que quemó la TORRE.\p"
	.string "Y la lluvia que apagó el fuego...$"

TinTower_1F_Sage6_Text2:
	.string "De los legendarios, dicen que SUICUNE\n"
	.string "es el más cercano a HO-OH.\p"
	.string "Oigo que también hay un vínculo con\n"
	.string "los POKéMON conocidos como UNOWN.\p"
	.string "Los UNOWN deben compartir un\n"
	.string "vínculo cooperativo con SUICUNE.$"

TinTower_1F_EusineHoOh_Text:
	.string "¡Lo sabía!\p"
	.string "Sabía que verías POKéMON\n"
	.string "de colores del arcoíris, <PLAYER>.\p"
	.string "Ocurrió tal como lo imaginé.\n"
	.string "Mi investigación no va mal.\p"
	.string "Seguiré estudiando POKéMON\n"
	.string "¡para ser un POKéMANIAC famoso!$"

TinTower_1F_EusineSuicune_Text:
	.string "EUSINE: ¡Genial! ¡Demasiado genial!\n"
	.string "Nunca vi una batalla tan grande.\p"
	.string "Fue realmente inspirador verlo.\n"
	.string "SUICUNE fue duro, pero tú fuiste\p"
	.string "más increíble, <PLAYER>.\n"
	.string "Oí que el poder místico de SUICUNE\p"
	.string "invoca un POKéMON color arcoíris.\n"
	.string "Tal vez, solo tal vez, lo de hoy\p"
	.string "hará que ese POKéMON aparezca.\n"
	.string "Estudiaré más las leyendas.\p"
	.string "Gracias por mostrarme esa batalla\n"
	.string "fantástica.\p"
	.string "¡Luego, <PLAYER>!$"
