.set LOCALID_CINNABAR_BLUE, 1
.set LOCALID_CINNABAR_BLAINE, 12

CinnabarIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0
	
CinnabarIsland_OnTransition:
	setflag FLAG_VISITED_CINNABAR_ISLAND
	callnative SetTimeBasedEncounters
	end

CinnabarIsland_EventScript_Blaine::
    lock
    faceplayer
    msgbox CinnabarIsland_Text_Blaine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_CINNABAR_BLAINE
    removeobject LOCALID_CINNABAR_BLAINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_BLAINE
    release
    end

CinnabarIsland_Text_Blaine:
    .string "BLAINE: ¡No me rendiré\n"
	.string "hasta el día que reconstruya\l"
	.string "el GIMNASIO CANELA!\p"
	.string "Estaré en el DOJO DE LUCHA\n"
	.string "hasta entonces.$"



CinnabarIsland_EventScript_Blue::
	lock
	faceplayer
	goto_if_eq VAR_NUM_BADGES, 15, CinnabarIsland_EventScript_BlueActive
	msgbox CinnabarIsland_Text_BlueBefore, MSGBOX_NPC
	release
	end

CinnabarIsland_EventScript_BlueActive::
	msgbox CinnabarIsland_Text_Blue, MSGBOX_NPC
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CINNABAR_BLUE
	removeobject LOCALID_CINNABAR_BLUE
	clearflag FLAG_HIDE_VIRIDIAN_BLUE
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end


CinnabarIsland_Text_BlueBefore:
	.string "¿Quién eres?\p"
	.string "Bueno, es obvio que eres\n"
	.string "un ENTRENADOR...\p"
	.string "Mi nombre es BLUE.\p"
	.string "Fui el CAMPEÓN, aunque\n"
	.string "fue solo por poco tiempo...\p"
	.string "Ese entrometido RED me venció...\p"
	.string "En fin, ¿qué quieres? ¿Quieres\n"
	.string "desafiarme o algo así?\p"
	.string "...Odio decirlo, pero no estoy\n"
	.string "de humor para luchar ahora.\p"
	.string "Mira bien a tu alrededor...\p"
	.string "Un volcán erupciona y, así\n"
	.string "de simple, un pueblo desaparece.\p"
	.string "Podemos ganar o perder en\n"
	.string "POKéMON. Pero si la naturaleza\l"
	.string "tiembla, perdemos en un segundo.\p"
	.string "...\p"
	.string "Así son las cosas...\p"
	.string "Pero, aun así, soy ENTRENADOR.\p"
	.string "Si veo a un rival fuerte, me\n"
	.string "dan ganas de luchar.\p"
	.string "Si quieres luchar conmigo,\n"
	.string "necesitas 15 medallas primero.\p"
	.string "Te enfrentaré entonces.$"

CinnabarIsland_Text_Blue:
	.string "¿Quién eres?\p"
	.string "Bueno, es obvio que eres\n"
	.string "un ENTRENADOR...\p"
	.string "Mi nombre es BLUE.\p"
	.string "Fui el CAMPEÓN, aunque\n"
	.string "fue solo por poco tiempo...\p"
	.string "Ese entrometido RED me venció...\p"
	.string "En fin, ¿qué quieres? ¿Quieres\n"
	.string "desafiarme o algo así?\p"
	.string "...Odio decirlo, pero no estoy\n"
	.string "de humor para luchar ahora.\p"
	.string "Mira bien a tu alrededor...\p"
	.string "Un volcán erupciona y, así\n"
	.string "de simple, un pueblo desaparece.\p"
	.string "Podemos ganar o perder en\n"
	.string "POKéMON. Pero si la naturaleza\l"
	.string "tiembla, perdemos en un segundo.\p"
	.string "...\p"
	.string "Así son las cosas...\p"
	.string "Pero, aun así, soy ENTRENADOR.\p"
	.string "Si veo a un rival fuerte, me\n"
	.string "dan ganas de luchar.\p"
	.string "Si quieres luchar conmigo, ve\n"
	.string "al GIMNASIO VERDIANTE.\p"
	.string "Te enfrentaré entonces.$"

CinnabarIsland_EventScript_Sign::
	msgbox CinnabarIsland_Text_Sign, MSGBOX_SIGN
	end

CinnabarIsland_EventScript_GymSign::
	msgbox CinnabarIsland_Text_GymSign, MSGBOX_SIGN
	end

CinnabarIsland_Text_GymSign:
	.string "Hay un aviso aquí...\p"
	.string "El GIMNASIO CANELA se mudó a\n"
	.string "las ISLAS ESPUMA.\p"
	.string "BLAINE$"

CinnabarIsland_Text_Sign:
	.string "ISLA CANELA\p"
	.string "El Pueblo Ardiente del Deseo$"

