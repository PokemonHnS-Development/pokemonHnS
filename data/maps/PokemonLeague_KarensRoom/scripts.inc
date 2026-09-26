PokemonLeague_KarensRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KarensRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KarensRoom_OnResume::
	setvar VAR_0x8004, 3
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KarensRoom_EventScript_Karen::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 5, PokemonLeague_KarensRoom_EventScript_KarenDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematch
	msgbox PokemonLeague_KarensRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_1, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematch::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_2, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenOnDefeat::
    clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
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
	setvar VAR_LEAGUE_STATE, 5
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenDefeated::
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KarensRoom_Text_RematchBefore:
    .string "KAREN: Ah, eres tú otra vez.\p"
    .string "Confío en que no olvidaste\n"
    .string "mi creencia:\p"
    .string "La fuerza nace de la confianza\n"
    .string "en los POKéMON.\p"
    .string "Desde nuestro último encuentro,\n"
    .string "mi vínculo con mis POKéMON\l"
    .string "se ha vuelto más fuerte.\p"
    .string "¿Listo para enfrentar un equipo\n"
    .string "con un vínculo inquebrantable?\p"
    .string "Muéstrame el poder del vínculo\n"
    .string "con tus POKéMON.$"

PokemonLeague_KarensRoom_Text_Before:
    .string "Soy KAREN, del ELITE FOUR.\p"
    .string "¿Tú eres {PLAYER}? Qué curioso.\p"
    .string "Amo los POKéMON tipo SINON.\p"
    .string "Su imagen salvaje y dura me\n"
    .string "parece muy atractiva. Y son\l"
    .string "muy fuertes.\p"
    .string "¿Crees que puedes ganarles?\n"
    .string "Intenta entretenerme.\p"
    .string "¡Vamos!$"

PokemonLeague_KarensRoom_Text_Beaten:
    .string "Vaya, eres bueno. Eso me gusta\n"
    .string "de un ENTRENADOR.$"

PokemonLeague_KarensRoom_Text_Defeat:
    .string "POKéMON fuertes.\p"
    .string "POKéMON débiles.\p"
    .string "Eso es solo una percepción\n"
    .string "egoísta de la gente.\p"
    .string "Los mejores ENTRENADORES\n"
    .string "ganan con sus favoritos.\p"
    .string "Me gusta tu estilo. Sabes\n"
    .string "lo que es importante.\p"
    .string "Sigue--el CHAMPION te espera.$"

