PokemonLeague_KogasRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KogasRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KogasRoom_OnResume::
	setvar VAR_0x8004, 1
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KogasRoom_EventScript_Koga::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 3, PokemonLeague_KogasRoom_EventScript_KogaDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KogasRoom_EventScript_KogaRematch
	msgbox PokemonLeague_KogasRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KOGA_1, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaRematch::
	msgbox PokemonLeague_KogasRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KOGA_2, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaOnDefeat::
	clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KogasRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x28E, FALSE
	setmetatile 6, 2, 0x296, FALSE	
	playse SE_BANG
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar VAR_LEAGUE_STATE, 3
	release
	end

PokemonLeague_KogasRoom_EventScript_KogaDefeated::
	msgbox PokemonLeague_KogasRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KogasRoom_Text_RematchBefore:
    .string "KOGA: ¡Fwahahahaha!\p"
    .string "Vuelves, valiente retador.\p"
    .string "Mis artes ninja han mejorado.\p"
    .string "Nuevas trampas te esperan.\p"
    .string "Veneno, sueño y más...\n"
    .string "¡Prepárate!\p"
    .string "¡Fwahahahaha!\p"
    .string "¡Muéstrame cuánto creciste!$"

PokemonLeague_KogasRoom_Text_Before:
    .string "¡Fwahahahaha!\p"
    .string "Soy KOGA, del ALTO MANDO.\p"
    .string "¡Vivo en las sombras, soy ninja!\p"
    .string "Mi estilo te confundirá\n"
    .string "y te destruirá.\p"
    .string "Confusión, sueño, veneno...\p"
    .string "¡Serás la víctima de mi\n"
    .string "siniestra técnica!\p"
    .string "¡Fwahahahaha!\p"
    .string "POKéMON no es solo fuerza bruta,\n"
    .string "¡ya lo verás!$"

PokemonLeague_KogasRoom_Text_Beaten:
    .string "¡Ah!\n"
    .string "¡Has demostrado tu valor!$"

PokemonLeague_KogasRoom_Text_Defeat:
    .string "Te sometí a todo lo que\n"
    .string "pude reunir.\p"
    .string "Pero fallé. Debo pulir\n"
    .string "mis habilidades.\p"
    .string "¡Ve a la siguiente sala y pon\n"
    .string "a prueba tu capacidad!$"
