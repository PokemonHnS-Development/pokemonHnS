.set LOCALID_NURSE, 1
.set LOCALID_Bill, 4

FallarborTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FallarborTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

FallarborTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FallarborTown_PokemonCenter_1F_EventScript_Girl::
	msgbox FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_Bill::
	lock
	faceplayer
	msgbox FallarborTown_PokemonCenter_1F_Text_BillGreeting, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_NORTH, FallarborTown_PokemonCenter_1F_EventScript_BillExitNorth
	case DIR_WEST, FallarborTown_PokemonCenter_1F_EventScript_BillExitWest
	end

FallarborTown_PokemonCenter_1F_EventScript_BillExitNorth::
	applymovement LOCALID_Bill, FallarborTown_PokemonCenter_1F_Movement_BillExitNorth
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_BillExited
	end

FallarborTown_PokemonCenter_1F_EventScript_BillExitWest::
	applymovement LOCALID_Bill, FallarborTown_PokemonCenter_1F_Movement_BillExitWest
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_BillExited
	end

FallarborTown_PokemonCenter_1F_EventScript_BillExited::
	playse SE_SLIDING_DOOR
	removeobject LOCALID_Bill
	clearflag FLAG_GARBAGEFLAG
	release
	end

FallarborTown_PokemonCenter_1F_Movement_BillExitNorth:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Movement_BillExitWest:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Text_BillGreeting:
	.string "Oh, hola.\n"
	.string "¿Quién eres?\p"
	.string "Bien, te llamas {PLAYER}{KUN}.\n"
	.string "Veo que eres un ENTRENADOR.\p"
	.string "Eso significa que usas el Sistema\n"
	.string "de Almacenamiento que creé.\p"
	.string "Llegué a esa conclusión mediante\n"
	.string "un simple proceso deductivo.\p"
	.string "Hablaste conmigo porque querías\n"
	.string "acceder a algo en esta PC.\p"
	.string "Oh, lo siento. Soy Bill.\p"
	.string "En serio, gusto en conocerte. Es\n"
	.string "genial que uses el Almacenamiento.\p"
	.string "Si puedes, visítame en mi casa.\n"
	.string "Está en la RUTA 114.$"

FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown:
	.string "¿Cómo serían los POKéMON hace\n"
	.string "muchísimo tiempo?\p"
	.string "Tal vez el MANÍACO FÓSIL al borde\n"
	.string "del pueblo lo sepa.$"

FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees:
	.string "En los campos de FALLARBOR, plantamos\n"
	.string "árboles fuertes que crecen bien\l"
	.string "incluso en ceniza volcánica.$"

