PokemonLeague_BrunosRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_BrunosRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_BrunosRoom_OnResume::
	setvar VAR_0x8004, 2
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_BrunosRoom_EventScript_Bruno::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 4, PokemonLeague_BrunosRoom_EventScript_BrunoDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_BrunosRoom_EventScript_BrunoRematch
	msgbox PokemonLeague_BrunosRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_BRUNO_1, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoRematch::
	msgbox PokemonLeague_BrunosRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_BRUNO_2, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat::
	clearflag FLAG_TEMP_5	
	msgbox PokemonLeague_BrunosRoom_Text_Defeat, MSGBOX_DEFAULT
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
	setvar VAR_LEAGUE_STATE, 4
	release
	end

PokemonLeague_BrunosRoom_EventScript_BrunoDefeated::
	msgbox PokemonLeague_BrunosRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_BrunosRoom_Text_RematchBefore:
    .string "BRUNO: Bienvenido, joven\n"
    .string "guerrero.\p"
    .string "Con un entrenamiento riguroso,\n"
    .string "somos más fuertes.\p"
    .string "Mi voluntad es ahora más firme\n"
    .string "e inquebrantable.\p"
    .string "¿Estás listo para un desafío\n"
    .string "aún mayor?\p"
    .string "Muéstrame los resultados de tu\n"
    .string "entrenamiento.\p"
    .string "¡Hoo hah!$"

PokemonLeague_BrunosRoom_Text_Before:
    .string "Soy BRUNO, del ELITE FOUR.\p"
    .string "Entreno al límite porque creo en\n"
    .string "nuestro potencial.\p"
    .string "Así es como nos hicimos fuertes.\p"
    .string "¿Podrás resistir nuestro poder?\p"
    .string "¿Hm? No tienes miedo. Te veo\n"
    .string "decidido. ¡Ideal para luchar!\p"
    .string "¿Listo, {PLAYER}? ¡Te rendirás\n"
    .string "ante nuestro gran poder!\p"
    .string "¡Hoo hah!$"

PokemonLeague_BrunosRoom_Text_Beaten:
    .string "¿Por qué? ¿Cómo pudimos perder?$"

PokemonLeague_BrunosRoom_Text_Defeat:
    .string "Al perder, no tengo derecho a\n"
    .string "decir nada...\p"
    .string "¡Ve a tu siguiente desafío!$"
