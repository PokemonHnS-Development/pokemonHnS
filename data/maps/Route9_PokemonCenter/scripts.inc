.set LOCALID_NURSE, 1

Route9_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Route9_PokemonCenter_EventScript_Engineer1::
	msgbox Route9_PokemonCenter_Text_Engineer1, MSGBOX_NPC
	end

Route9_PokemonCenter_EventScript_Engineer2::
	msgbox Route9_PokemonCenter_Text_Engineer2, MSGBOX_NPC
	end

Route9_PokemonCenter_Text_Engineer1:
	.string "A veces los ingenieros venimos\n"
	.string "aquí en el descanso. O solo para\l"
	.string "huir del GERENTE.\p"
	.string "Ese tipo está loco.$"

Route9_PokemonCenter_Text_Engineer2:
	.string "La CENTRAL ELÉCTRICA es remota,\n"
	.string "así que viajo lejos por trabajo.$"
