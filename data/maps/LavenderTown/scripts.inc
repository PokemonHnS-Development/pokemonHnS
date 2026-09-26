LavenderTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_EventScript_CityEnter
	.byte 0

LavenderTown_EventScript_CityEnter::
	setflag FLAG_VISITED_LAVENDER_TOWN
	end

LavenderTown_EventScript_PokefanM::
	msgbox LavenderTown_Text_PokefanM, MSGBOX_NPC
	end

LavenderTown_EventScript_Teacher::
	msgbox LavenderTown_Text_Teacher, MSGBOX_NPC
	end

LavenderTown_EventScript_Gramps::
	msgbox LavenderTown_Text_Gramps, MSGBOX_NPC
	end

LavenderTown_EventScript_Youngster::
	msgbox LavenderTown_Text_Youngster, MSGBOX_NPC
	end

LavenderTown_EventScript_TownSign::
	msgbox LavenderTown_Text_Sign, MSGBOX_SIGN
	end

LavenderTown_EventScript_RadioTowerSign::
	msgbox LavenderTown_Text_KantoRadioStationSign, MSGBOX_SIGN
	end

LavenderTown_EventScript_VolunteerSign::
	msgbox LavenderTown_Text_VolunteerPokemonHouseSign, MSGBOX_SIGN
	end

LavenderTown_EventScript_SoulHouseSign::
	msgbox LavenderTown_Text_SoulHouseSign, MSGBOX_SIGN
	end

LavenderTown_Text_PokefanM:
	.string "Es un gran edificio, ¿eh?\p"
	.string "Es la TORRE RADIO de KANTO.$"

LavenderTown_Text_Teacher:
	.string "KANTO tiene muy buenos programas.$"

LavenderTown_Text_Gramps:
	.string "Vienen de todas partes para dar\n"
	.string "respetos a las almas\l"
	.string "de los POKéMON.$"

LavenderTown_Text_Youngster:
	.string "Necesitas una POKé FLUTE para\n"
	.string "despertar POKéMON.\p"
	.string "¡Todo ENTRENADOR debe saberlo!$"

LavenderTown_Text_Sign:
	.string "PUEBLO LAVANDA\p"
	.string "El Noble Pueblo Púrpura$"

LavenderTown_Text_KantoRadioStationSign:
	.string "ESTACIÓN RADIO KANTO\p"
	.string "¡Tus programas favoritos al aire\n"
	.string "todo el día!$"

LavenderTown_Text_VolunteerPokemonHouseSign:
	.string "CASA DE VOLUNTARIOS POKéMON\n"
	.string "DE LAVANDA$"

LavenderTown_Text_SoulHouseSign:
	.string "CASA DE LAS ALMAS\p"
	.string "Que las almas de los POKéMON\n"
	.string "descansen en paz$"
