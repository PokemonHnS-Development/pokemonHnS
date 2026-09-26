.set LOCALID_CELADON_ERIKA, 15

CeladonCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_EventScript_CityEnter
	.byte 0

CeladonCity_EventScript_CityEnter::
	setflag FLAG_VISITED_CELADON_CITY
	end

CeladonCity_EventScript_Erika::
    lock
    faceplayer
    msgbox CeladonCity_Text_Erika, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_FOUNTAIN_ERIKA
    removeobject LOCALID_CELADON_ERIKA
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_ERIKA
    release
    end

CeladonCity_Text_Erika:
    .string "Oh, {PLAYER}.\n"
	.string "¿No es linda la fuente hoy?\p"
	.string "Si quieres otra batalla,\n"
	.string "estaré en el DOJO DE LUCHA.$"

CeladonCity_EventScript_Fatman::
	msgbox CeladonCity_Text_Fisher, MSGBOX_NPC
	end
CeladonCity_EventScript_Poliwrath::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
	msgbox CeladonCity_Text_Poliwrath, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CeladonCity_EventScript_Teacher1::
	msgbox CeladonCity_Text_Teacher1, MSGBOX_NPC
	end

CeladonCity_EventScript_GrimerGramps::
	msgbox CeladonCity_Text_Gramps1, MSGBOX_NPC
	end

CeladonCity_EventScript_CreepGramps::
	msgbox CeladonCity_Text_Gramps2, MSGBOX_NPC
	end

CeladonCity_EventScript_Youngster::
	msgbox CeladonCity_Text_Youngster1, MSGBOX_NPC
	end

CeladonCity_EventScript_Youngster2::
	msgbox CeladonCity_Text_Youngster2, MSGBOX_NPC
	end

CeladonCity_EventScript_Teacher2::
	msgbox CeladonCity_Text_Teacher2, MSGBOX_NPC
	end

CeladonCity_EventScript_Lass::
	msgbox CeladonCity_Text_Lass, MSGBOX_NPC
	end

CeladonCity_Text_Fisher:
	.string "Este POLIWRATH es mi compañero.\p"
	.string "Me pregunto si evolucionará\n"
	.string "en un POKéMON rana.$"

CeladonCity_Text_Poliwrath:
	.string "POLIWRATH: ¡Croac!$"

CeladonCity_Text_Teacher1:
	.string "Perdí en las tragamonedas otra vez…\p"
	.string "Nosotras también jugamos ahora.\p"
	.string "Tú también deberías probarlas.$"

CeladonCity_Text_Gramps1:
	.string "Han aparecido GRIMER últimamente.\p"
	.string "¿Ves el estanque frente a la\n"
	.string "casa? GRIMER viven ahí ahora.\p"
	.string "¿De dónde vinieron? Es un\n"
	.string "problema serio…$"

CeladonCity_Text_Gramps2:
	.string "¡Nihihi! ¡Este GIMNASIO es genial!\n"
	.string "¡Solo se permiten chicas aquí!$"

CeladonCity_Text_Youngster1:
	.string "¿Quieres saber un secreto?\p"
	.string "La MANSIÓN CELADON tiene una\n"
	.string "puerta trasera oculta.$"

CeladonCity_Text_Youngster2:
	.string "Hay un concurso de comida\n"
	.string "en el restaurante.\p"
	.string "Solo de verlos comer me siento\n"
	.string "hinchada…$"

CeladonCity_Text_Teacher2:
	.string "TIENDAS CELADON tiene la mayor\n"
	.string "y mejor selección de productos.\p"
	.string "Si no lo hallas ahí, no lo\n"
	.string "hallarás en ningún lugar.\p"
	.string "Vaya... parezco un vendedor.$"

CeladonCity_Text_Lass:
	.string "Mirar al suelo mientras caminaba\n"
	.string "me mareó.$"

CeladonCity_EventScript_CitySign::
	msgbox CeladonCity_Text_Sign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GymSign::
	msgbox CeladonGym_Text_Sign, MSGBOX_SIGN
	end

CeladonCity_EventScript_StoreSign::
	msgbox CeladonCity_Text_DeptStoreSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_MansionSign::
	msgbox CeladonCity_Text_MansionSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GameCornerSign::
	msgbox CeladonCity_Text_GameCornerSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_TrainerTips::
	msgbox CeladonCity_Text_TrainerTips, MSGBOX_SIGN
	end

CeladonCity_Text_Sign:
	.string "CIUDAD CELADON\p"
	.string "La Ciudad de los Sueños Arcoíris$"

CeladonGym_Text_Sign:
	.string "LÍDER DEL GIMNASIO DE CELADON:\n"
	.string "ERIKA\p"
	.string "La Princesa Amante de la Naturaleza$"

CeladonCity_Text_DeptStoreSign:
	.string "¡Halla lo que busques en las\n"
	.string "TIENDAS CELADON!$"

CeladonCity_Text_MansionSign:
	.string "MANSIÓN CELADON$"

CeladonCity_Text_GameCornerSign:
	.string "Diversión para todo el mundo--\n"
	.string "CASINO DE CELADON$"

CeladonCity_Text_TrainerTips:
	.string "CONSEJOS\p"
	.string "La DEF. ESP. protege al POKéMON\n"
	.string "de ataques ESPECIALES como el\n"
	.string "fuego y el agua.\p"
	.string "¡Compra tus objetos en TIENDAS\n"
	.string "CELADON!$"
