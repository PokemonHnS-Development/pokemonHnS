.set LOCALID_NURSE, 1
.set LOCALID_ECRUTEAK_BILL, 6

EcruteakCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_PokemonCenter_OnTransition
	.byte 0

EcruteakCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_ECRUTEAK_CITY
	end

EcruteakCity_PokemonCenter_EventScript_Bill::
	lock
	delay 30
	playse SE_PC_OFF
	delay 55
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill1, MSGBOX_DEFAULT
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill2, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, EcruteakCity_PokemonCenter_EventScript_BillLeaveBot
	call_if_eq VAR_FACING, DIR_WEST, EcruteakCity_PokemonCenter_EventScript_BillLeaveTop
	playse SE_EXIT
	setflag FLAG_HIDE_ECRUTEAK_BILL
	removeobject LOCALID_ECRUTEAK_BILL
	setflag FLAG_SYS_PC_BILL
	clearflag FLAG_HIDE_GOLDENROD_BILL
	release
	end

EcruteakCity_PokemonCenter_EventScript_BillFaceDown::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_SOUTH
	return

EcruteakCity_PokemonCenter_EventScript_BillFaceRight::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_EAST
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveTop::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillTop
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveBot::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillBot
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_Hiker::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Woman::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_Movement_BillTop:
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
	step_end

EcruteakCity_PokemonCenter_Movement_BillBot:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end


EcruteakCity_PokemonCenter1F_Text_Bill1:
	.string "Hola, soy BILL. ¿Y tú quién eres?\p"
	.string "Hmm, {PLAYER}, ¿eh?\n"
	.string "Llegas en el momento justo.$"

EcruteakCity_PokemonCenter1F_Text_Bill2:
	.string "Acabo de ajustar mi\n"
	.string "SISTEMA DE ALMACENAMIENTO POKéMON.\p"
	.string "¿Sabes esa PC que usas para guardar\n"
	.string "tus POKéMON?\p"
	.string "¡Yo mismo la desarrollé!\p"
	.string "Ahora que instalé esta,\n"
	.string "mi PC funciona en todos los\l"
	.string "CENTROS POKéMON de JOHTO y KANTO.\p"
	.string "Debo volver rápido a\n"
	.string "CIUDAD TRIGAL y ver a mi familia.\l"
	.string "¡Visítame cuando quieras!\p"
	.string "¡Adiós!$"

EcruteakCity_PokemonCenter1F_Text_PokefanM:
	.string "Cómo bailan las CHICAS KIMONO es\n"
	.string "maravilloso.\p"
	.string "Igual que la forma en que usan a\n"
	.string "sus POKéMON.$"

EcruteakCity_PokemonCenter1F_Text_PokefanM_Mobile:
	.string "Seguro quieres luchar contra más\n"
	.string "gente, ¿verdad?\p"
	.string "Parece que hay un lugar donde se\n"
	.string "reúnen los ENTRENADORES.\p"
	.string "¿Que dónde?\p"
	.string "Está un poco después de CIUDAD OLIVO.$"

EcruteakCity_PokemonCenter1F_Text_CooltrainerF:
	.string "MORTY, el LÍDER de GIMNASIO, es\n"
	.string "genial.\p"
	.string "Sus POKéMON también son muy fuertes.$"

EcruteakCity_PokemonCenter1F_Text_GymGuide:
	.string "LAGO DE LA FURIA…\p"
	.string "La aparición de un grupo\n"
	.string "de GYARADOS…\p"
	.string "Huelo una conspiración. ¡Lo sé!$"

