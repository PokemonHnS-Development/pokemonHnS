.set LOCALID_MRPOKEMON, 2
.set LOCALID_ROUTE30_OAK, 3
.set LOCALID_MRPOKEMON2, 1

Route30_MrPokemonsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MrPokemonHouse_OnFrame
	.byte 0

MrPokemonHouse_OnFrame::
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 1, MrPokemonHouse_EventScript_GiveEgg
	.2byte 0

MrPokemonHouse_EventScript_GiveEgg::
	lock
	playse SE_PIN
	applymovement LOCALID_MRPOKEMON, Common_Movement_ExclamationMark	
	delay 60
	turnobject LOCALID_MRPOKEMON, DIR_SOUTH
	msgbox MrPokemonHouse_Text_Intro1, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MrPokemonHouse_Movement_MeetMrPokemon
	waitmovement 0
	msgbox MrPokemonHouse_Text_Intro2, MSGBOX_DEFAULT

	giveitem ITEM_MYSTERY_EGG

	msgbox MrPokemonHouse_Text_Intro3, MSGBOX_DEFAULT
	msgbox MrPokemonHouse_Text_Intro4, MSGBOX_DEFAULT
	turnobject LOCALID_ROUTE30_OAK, DIR_WEST
	msgbox MrPokemonHouse_Text_Intro5, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_HG_OAK, TRUE
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakToPlayer
	waitmovement 0 
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox MrPokemonHouse_Text_OakIntro, MSGBOX_DEFAULT
	

	playfanfare MUS_OBTAIN_ITEM
	message MrPokemonHouse_Text_GetDex
	waitfanfare

	
	msgbox MrPokemonHouse_Text_OakParting MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_ROUTE30_OAK
	setflag FLAG_DELIVERED_EGG
	turnobject OBJ_EVENT_ID_PLAYER DIR_NORTH
	fadedefaultbgm
	msgbox MrPokemonHouse_Text_Heal, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox MrPokemonHouse_Text_DependingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MRPOKEMON, MrPokemonHouse_Movement_MrPokemon_Leave
	waitmovement 0
	removeobject LOCALID_MRPOKEMON
	clearflag FLAG_HIDE_MRPOKEMON
	addobject LOCALID_MRPOKEMON2
	
	setvar VAR_NEWBARKTOWN_LABSTATE, 4
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
	setflag FLAG_SYS_POKEDEX_GET
	checkrandomizer
	call_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_GiveNatDexRandomizer
	clearflag FLAG_HIDE_LAB_POLICEMAN
	setvar VAR_CHERRYGROVE_CITY_STATE, 2
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY
	clearflag FLAG_HIDE_SILVER_CHERRYGROVE
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	release
	end

MrPokemonHouse_EventScript_GiveNatDexRandomizer::
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	return

MrPokemonHouse_EventScript_MrPokemon::
	lock
	faceplayer
	checkitem ITEM_RED_SCALE
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale
	msgbox MrPokemonHouse_Text_AlwaysNewDiscoveries, MSGBOX_DEFAULT
	closemessage
	release
	end

MrPokemonHouse_EventScript_MrPokemon_RedScale::
	msgbox MrPokemonHouse_Text_GimmeTheScale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted
	msgbox MrPokemonHouse_Text_Disappointed, MSGBOX_DEFAULT
	closemessage
	release
	end	

MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted::
	removeitem ITEM_RED_SCALE
	giveitem ITEM_EXP_SHARE_SMALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end


MrPokemonHouse_EventScript_Computer::
	lock
	msgbox MrPokemonHouse_Text_BrokenComputer, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Magazine::
	lock
	msgbox MrPokemonHouse_Text_ForeignMagazines, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Coins::
	lock
	msgbox MrPokemonHouse_Text_StrangeCoins, MSGBOX_SIGN
	release
	end

MrPokemonHouse_Movement_MeetMrPokemon:
	walk_up
	walk_up
	walk_right
	walk_right
	face_up
	step_end

MrPokemonHouse_Movement_OakToPlayer:
	walk_down
	face_left
	step_end

MrPokemonHouse_Movement_OakLeave:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_in_place_down
	step_end

MrPokemonHouse_Movement_MrPokemon_Leave:
	walk_up
	walk_left
	walk_left
	step_end

MrPokemonHouse_Text_Intro1:
	.string "¡Hola, hola! Tú debes ser\n"
	.string "{PLAYER}.\p"
	.string "El PROF.ELM dijo que vendrías\n"
	.string "de visita.$"

MrPokemonHouse_Text_Intro2:
	.string "Esto es lo que quiero que el\n"
	.string "PROF.ELM examine.$"

MrPokemonHouse_Text_GotEgg:
	.string "{PLAYER} recibió HUEVO MISTERIO.$"

MrPokemonHouse_Text_Intro3:
	.string "Conozco a una pareja que tiene\n"
	.string "una GUARDERÍA POKéMON.\p"
	.string "Ellos me dieron ese HUEVO.\p"
	.string "Me intrigó, así que le envié\n"
	.string "correo al PROF.ELM.\p"
	.string "Para la evolución POKéMON,\n"
	.string "el PROF.ELM es la autoridad.$"


MrPokemonHouse_Text_Intro4:
	.string "Hasta el PROF.OAK reconoce\n"
	.string "eso aquí.$"

MrPokemonHouse_Text_Intro5:
	.string "Si mi suposición es correcta,\n"
	.string "el PROF.ELM lo sabrá.$"

MrPokemonHouse_Text_Heal:
	.string "¿Vuelves con el PROF.ELM?\p"
	.string "Toma. Tu POKéMON debería\n"
	.string "descansar un poco.$"

MrPokemonHouse_Text_DependingOnYou:
	.string "¡Cuento contigo!$"

MrPokemonHouse_Text_AlwaysNewDiscoveries:
	.string "¡La vida es maravillosa!\n"
	.string "Siempre hay nuevos descubrimientos.$"

MrPokemonHouse_Text_OakIntro:
	.string "OAK: ¡Ajá! ¡Tú eres {PLAYER}!\p"
	.string "¡Soy OAK! Investigador POKéMON.\p"
	.string "Visitaba a mi viejo amigo\n"
	.string "MR. POKéMON.\p"
	.string "Supe que hacías un recado\n"
	.string "para el PROF.ELM, así que esperé.\p"
	.string "¡Oh! ¿Qué es esto? ¡Un POKéMON raro!\p"
	.string "Veamos...\n"
	.string "¡Hm, ya veo!\p"
	.string "Entiendo por qué el PROF.ELM te\n"
	.string "dio un POKéMON para este recado.\p"
	.string "Para investigadores como el\n"
	.string "PROF.ELM y yo, son nuestros amigos.\p"
	.string "Él vio que tratarías a tu\n"
	.string "POKéMON con amor y cuidado.\p"
	.string "...¡Ah!\p"
	.string "Pareces alguien confiable. ¿Te\n"
	.string "gustaría ayudarme?\p"
	.string "Mira, es la última versión de\n"
	.string "la POKéDEX.\p"
	.string "Registra datos de POKéMON que\n"
	.string "hayas visto o capturado.\p"
	.string "¡Es una enciclopedia tecnológica!\p"
	.string "Muestra hábitats, evoluciones\n"
	.string "y sus movimientos.$"

MrPokemonHouse_Text_GetDex:
	.string "¡{PLAYER} recibió la POKéDEX!$"

MrPokemonHouse_Text_OakParting:
	.string "¡Busca muchos POKéMON y\n"
	.string "completa esa POKéDEX!\p"
	.string "Pero me he quedado demasiado tiempo.\p"
	.string "Debo ir a CIUDAD TRIGAL\n"
	.string "para mi programa de radio.\p"
	.string "{PLAYER}, ¡cuento contigo!$"

MrPokemonHouse_Text_GimmeTheScale:
	.string "¿Hm? ¡Esa ESCAMA! ¿Qué es?\n"
	.string "¿Un GYARADOS rojo?\p"
	.string "¡Es raro! Yo, yo lo quiero...\p"
	.string "{PLAYER}, ¿te gustaría\n"
	.string "intercambiarlo?\p"
	.string "Te ofrezco este EXP.SHARE\n"
	.string "que recibí del PROF.OAK.$"

MrPokemonHouse_Text_Disappointed:
	.string "Qué decepcionante.\n"
	.string "Es que es algo muy raro.$"

MrPokemonHouse_Text_ExpShare:
	.string "También tengo un objeto\n"
	.string "especial para ti.$"

MrPokemonHouse_Text_ForeignMagazines:
	.string "Está lleno de revistas\n"
	.string "extranjeras.\p"
	.string "Ni siquiera puedo leer los títulos...$"

MrPokemonHouse_Text_BrokenComputer:
	.string "Es una computadora grande.\n"
	.string "Hmm. Está rota.$"

MrPokemonHouse_Text_StrangeCoins:
	.string "¡Un montón de monedas raras!\p"
	.string "Tal vez sean de otro\n"
	.string "país…$"

MrPokemonHouse_Text_GotExpShare:
	.string "{PLAYER} ¡recibió EXP. SHARE!$"
