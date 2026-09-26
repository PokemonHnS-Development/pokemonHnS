.set LOCALID_NURSE, 1

VerdanturfTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon:
	.string "No eres un verdadero\n"
	.string "ENTRENADOR si no tienes fe\l"
	.string "en tus POKéMON.\p"
	.string "Solo quienes creen en sus POKéMON\n"
	.string "de batalla pueden ganar\l"
	.string "hasta el final.$"

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent:
	.string "La razón por la que alguien visita\n"
	.string "VERDANTURF...\p"
	.string "Es la CARPA DE BATALLA. No hace\n"
	.string "falta decirlo.\p"
	.string "¿O viniste para ver a alguien en\n"
	.string "especial?$"

