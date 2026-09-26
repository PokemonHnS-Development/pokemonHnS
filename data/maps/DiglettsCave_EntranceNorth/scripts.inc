.set LOCALID_DIGLETT_BROCK, 1

DiglettsCave_EntranceNorth_MapScripts::
	.byte 0


DiglettsCave_EntranceNorth_EventScript_Brock::
    lock
    faceplayer
    msgbox DiglettsCave_EntranceNorth_Text_Brock, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_DIGLETT_BROCK
    removeobject LOCALID_DIGLETT_BROCK
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_BROCK
    release
    end

DiglettsCave_EntranceNorth_Text_Brock:
    .string "BROCK: Los espacios pequeños entre\n"
    .string "rocas dan paz,\l"
    .string "¿no estás de acuerdo?\p"
	.string "Si quieres otra batalla, estaré\n"
	.string "en el DOJO DE LUCHA.$"




