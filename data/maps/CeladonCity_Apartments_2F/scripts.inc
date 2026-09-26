CeladonCity_Apartments_2F_MapScripts::
	.byte 0

CeladonCity_Apartments_2F_EventScript_Computer::
	lock
	playse SE_PC_ON
	msgbox CeladonMansion2F_Text_Computer
	playse SE_PC_OFF
	waitse
	release
	end

CeladonCity_Apartments_2F_EventScript_Sign::
	msgbox CeladonMansion2F_Text_DevOfficeSign, MSGBOX_SIGN
	end

CeladonMansion2F_Text_Computer:
	.string "{PLAYER} encendió la PC.\p"
	.string "…\p"
	.string "Alguien estaba escribiendo\n"
	.string "un correo electrónico.\p"
	.string "…Espero que visites KANTO.\p"
	.string "Creo que te sorprenderá\n"
	.string "cuánto han cambiado las cosas.\p"
	.string "Verás muchos POKéMON que\n"
	.string "no son nativos de JOHTO.\p"
	.string "Para el PRODUCTOR\p"
	.string "…$"

CeladonMansion2F_Text_DevOfficeSign:
	.string "OFICINA DE DESARROLLO HEART & SOUL$"

CeladonMansion2F_EventScript_LilDill::
	msgbox CeladonMansion2F_Text_LilDill, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_InfiniteBacon::
	msgbox CeladonMansion2F_Text_InfiniteBacon, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_TixoRebel::
	msgbox CeladonMansion2F_Text_TixoRebel, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_Phant::
	msgbox CeladonMansion2F_Text_Phant, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_Exclsior::
	msgbox CeladonMansion2F_Text_Exclsior, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_DaniRainbow::
    msgbox CeladonMansion2F_Text_DaniRaibow, MSGBOX_NPC
    end

CeladonMansion2F_Text_LilDill:
	.string "Hola a todos, Parche 15--\p"
	.string "Perdón, quiero decir...\p"
	.string "¡Hola, soy el DIRECTOR DEL JUEGO!\p"
	.string "Hice los mapas, los tilesets,\n"
	.string "los scripts y mucho más.\p"
	.string "No lo habría logrado sin los\n"
	.string "devs y los playtesters.\p"
	.string "¡Gracias por jugar! Espero que\n"
	.string "disfrutes POKéMON HEART & SOUL.$"

CeladonMansion2F_Text_InfiniteBacon:
	.string "¡Trabajamos para rehacer este juego\n"
	.string "en pokeemerald expansion!$"

CeladonMansion2F_Text_TixoRebel:
	.string "¿Oíste sobre THE EGGENING?\n"
	.string "¡Era un bug del playtest\l"
	.string "que volvía POKéMON en\l"
	.string "HUEVOS al azar!\p"
	.string "¡Yo desarrollé la solución!$"

CeladonMansion2F_Text_Phant:
	.string "¡Amo los DEMAKES!\p"
	.string "¿Jugaste SWORD AND SHIELD\n"
	.string "ULTIMATE PLUS - ENGLISH?\l"
	.string "¡Yo lo traduje!\p"
	.string "Para mi próximo DEMAKE,\n"
	.string "¡creo que haré ALOLA!$"

CeladonMansion2F_Text_Exclsior:
	.string "¡Hice sprites de surf únicos\n"
	.string "para cada POKéMON!\p"
	.string "Como el proyecto es OPEN SOURCE,\n"
	.string "¡tú también puedes añadir cosas!$"

CeladonMansion2F_Text_DaniRaibow:
	.string "¡Hola!\p"
	.string "Soy bueno hallando problemas\n"
	.string "y puedo arreglar los pequeños.\p"
    .string "¿Quieres un chiste?\p"
    .string "Lance quiso enseñar a DRAGONITE\n"
    .string "el movimiento DRAGON BREATH.\p"
    .string "Pero DRAGONITE iba muy rápido\n"
    .string "con EXTREMESPEED; ¡no pudo\l"
    .string "atraparlo!$"
