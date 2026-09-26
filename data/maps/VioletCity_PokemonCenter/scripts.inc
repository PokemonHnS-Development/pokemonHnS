.set LOCALID_NURSE, 1

VioletCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_Pokecenter_OnTransition
	.byte 0

VioletCity_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_VIOLET_CITY
	end

VioletCity_PokemonCenter_EventScript_Aide::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TOGEPI_EGG, VioletCity_PokemonCenter_EventScript_Aide_Received
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, VioletCity_PokemonCenter_EventScript_AideNoRoom
	msgbox VioletCity_PokeCenter_Text_ElmsAideFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end


VioletCity_PokemonCenter_EventScript_AideNoRoom::
	msgbox VioletCity_PokeCenter_Text_ElmsAideNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Refuse::
	msgbox VioletCity_PokeCenter_Text_ElmsAideRefuse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Accepted::
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, VioletCity_PokeCenter_Text_ElmsAideFullParty
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	giveegg SPECIES_TOGEPI
	setflag FLAG_RECEIVED_TOGEPI_EGG
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveItem, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE_SMALL
	setflag FLAG_HIDE_VIOLET_CITY_AIDE
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
	clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Received::
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EVentScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Man::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_Text_BookshelfWoman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_BooksAreGreat, MSGBOX_DEFAULT
	closemessage
	release
	end


VioletCity_PokeCenter_Text_ElmsAideFavor:
	.string "{PLAYER}, ¡cuánto tiempo!\p"
	.string "PROF.ELM me pidió buscarte.\p"
	.string "Tiene otro favor que pedirte.\p"
	.string "¿Te llevarías el HUEVO POKéMON?$"

VioletCity_PokeCenter_Text_ElmsAideNoRoom:
	.string "{PLAYER}, ¡cuánto tiempo!\p"
	.string "PROF.ELM me pidió buscarte.\p"
	.string "Tiene otro favor que pedirte.\p"
	.string "¿Te llevarías el HUEVO POKéMON?\p"
	.string "Ah, espera... Primero debes hacer\n"
	.string "espacio en tu equipo.$"

VioletCity_PokeCenter_Text_ElmsAideGiveEgg:
	.string "Vimos que un POKéMON no nace\n"
	.string "hasta que crece en el HUEVO.\p"
	.string "También debe estar con otros\n"
	.string "POKéMON activos para nacer.\p"
	.string "{PLAYER}, eres la única persona\n"
	.string "en quien podemos confiar.$"

VioletCity_PokeCenter_Text_ElmsAideGiveItem:
	.string "Ah, y esto ayudará al nacer.$"

VioletCity_PokeCenter_Text_ElmsAideFullParty:
	.string "Oh, no. No puedes llevar más\n"
	.string "POKéMON contigo.\p"
	.string "Esperaré aquí mientras haces\n"
	.string "espacio para el HUEVO.$"

VioletCity_PokeCenter_Text_ElmsAideRefuse:
	.string "P-pero... PROF.ELM te buscaba...$"

VioletCity_PokeCenter_Text_BooksAreGreat:
	.string "Mientras mis POKéMON sanan,\n"
	.string "me encanta leer un buen libro.$"

VioletCity_PokeCenter_Text_MobileAdapter:
	.string "Luché con un amigo en\n"
	.string "CIUDAD ORQUIDEA por enlace.\p"
	.string "Con un ADAPTADOR MÓVIL,\n"
	.string "puedes conectarte con un amigo\l"
	.string "que esté lejos.$"

VioletCity_PokeCenter_Text_GameboyKid:
	.string "Un tipo llamado BILL creó el\n"
	.string "sistema PC de POKéMON.$"

VioletCity_PokeCenter_Text_Gentleman:
	.string "Fue hace unos tres años.\p"
	.string "TEAM ROCKET hacía cosas malas\n"
	.string "con los POKéMON.\p"
	.string "Pero la justicia ganó: un chico\n"
	.string "los detuvo.$"

VioletCity_PokeCenter_Text_Youngster:
	.string "Los POKéMON son listos. No\n"
	.string "obedecen a quien no respetan.\p"
	.string "Sin las GYM BADGES correctas,\n"
	.string "harán lo que quieran.$"
