.set LOCALID_NURSE, 1
.set LOCALID_FOLLOWER, 0xFE

OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse::
	applymovement LOCALID_FOLLOWER, Common_Movement_Enter_Pokeball
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy::
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable::
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC:
	.string "Esa PC de la esquina es\n"
	.string "para cualquier ENTRENADOR POKéMON.\p"
	.string "Claro que tú también\n"
	.string "puedes usarla.$"

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat:
	.string "¡Los CENTROS POKéMON son geniales!\p"
	.string "Usa sus servicios todo lo que\n"
	.string "quieras, ¡y todo es gratis!\l"
	.string "¡No tienes de qué preocuparte!$"

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable:
	.string "El CLUB WIRELESS POKéMON del\n"
	.string "segundo piso es muy reciente.\p"
	.string "Dicen que todavía le están\n"
	.string "haciendo ajustes.$"

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub:
	.string "El CLUB WIRELESS POKéMON del\n"
	.string "segundo piso es muy reciente.\p"
	.string "Intercambié POKéMON enseguida.$"

