Route4_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route4_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route4_EventScript_HpUp::
	finditem ITEM_HP_UP
	end

Route4_EventScript_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route4_EventScript_Hank::
	trainerbattle_single TRAINER_HANK, Route4_Text_BirdKeeperHank_Seen, Route4_Text_BirdKeeperHank_Beaten
	msgbox Route4_Text_BirdKeeperHank_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, Route4_Text_PicnickerHope_Seen, Route4_Text_PicnickerHope_Beaten
	msgbox Route4_Text_PicnickerHope_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Sharon::
	trainerbattle_single TRAINER_SHARON, Route4_Text_PicnickerSharon_Seen, Route4_Text_PicnickerSharon_Beaten
	msgbox Route4_Text_PicnickerSharon_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Sign::
	msgbox Route4_Text_MtMoonSquareSign, MSGBOX_SIGN
	end

Route4_Text_BirdKeeperHank_Seen:
	.string "Entreno a mis POKéMON. ¿Quieres\n"
	.string "luchar conmigo?$"

Route4_Text_BirdKeeperHank_Beaten:
	.string "¡Ay! Perdí esta vez...$"

Route4_Text_BirdKeeperHank_AfterBattle:
	.string "Si quieres entrenar a un POKéMON\n"
	.string "específico, sácalo primero y luego\l"
	.string "cámbialo rápido.\p"
	.string "Así es como se hace.$"

Route4_Text_PicnickerHope_Seen:
	.string "Siento que puedo ganar.\p"
	.string "¡Veamos si tengo razón!$"

Route4_Text_PicnickerHope_Beaten:
	.string "Aww, eres demasiado fuerte.$"

Route4_Text_PicnickerHope_AfterBattle:
	.string "Oí que CLEFAIRY sale en el MT.MOON.\p"
	.string "¿Pero dónde estarán?$"

Route4_Text_PicnickerSharon_Seen:
	.string "Este...\n"
	.string "yo...$"

Route4_Text_PicnickerSharon_Beaten:
	.string "…$"

Route4_Text_PicnickerSharon_AfterBattle:
	.string "...Iré a entrenar más...$"

Route4_Text_MtMoonSquareSign:
	.string "NUEVA ENTRADA MT.MOON\n"
	.string "POR EL DESPLOME\p"
	.string "TEN CUIDADO AL PASAR$"

