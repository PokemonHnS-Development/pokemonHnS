.set LOCALID_NURSE, 1

RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_ProbopassEvo::
	msgbox RustboroCity_PokemonCenter_1F_ProbopassEvo_Text, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_ProbopassEvo_Text:
	.string "NOSEPASS evoluciona y cambia\n"
	.string "su tipo a ROCA y ACERO.\p"
	.string "Pero para evolucionar, debe\n"
	.string "estar expuesto a un campo\l"
	.string "magnético fuerte.\p"
	.string "Es difícil hallar un lugar así\n"
	.string "en HOENN, así que los científicos\l"
	.string "vieron que si NOSEPASS lleva\l"
	.string "una PIEDRA TRUENO, evoluciona\l"
	.string "más fácil al duplicar\l"
	.string "su propio campo magnético.\p"
	.string "Me pregunto de qué están hechas\n"
	.string "las PIEDRAS TRUENO.$"

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "Mi POKéMON es ingenuo y el de mi\n"
	.string "amigo es alegre.\p"
	.string "¡Es fascinante que los POKéMON\n"
	.string "tengan personalidades!$"

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "Como las personas, hay POKéMON\n"
	.string "macho y hembra.\p"
	.string "Pero nadie sabe exactamente en qué\n"
	.string "se diferencian.$"

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "¡El vecino me dio una MO!\p"
	.string "La usé para enseñar a mi POKéMON a\n"
	.string "usar CORTE en árboles delgados.$"

