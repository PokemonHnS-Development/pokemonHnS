Route33_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route33_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route33_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route33_EventScript_HikerAnthony::
	trainerbattle_single TRAINER_ANTHONY, Route33_Text_HikerAnthony2Seen, Route33_Text_HikerAnthony2Beaten
	msgbox Route33_Text_HikerAnthony2After, MSGBOX_AUTOCLOSE
	end

Route33_EventScript_Lass::
	lock
	faceplayer
	msgbox Route33_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route33_Text_HikerAnthony2Seen:
	.string "Crucé el túnel,\n"
	.string "¡pero aún tengo mucha\l"
	.string "energía!$"

Route33_Text_HikerAnthony2Beaten:
	.string "¡Vaya! ¡Tienes más ganas\n"
	.string "que yo!$"

Route33_Text_HikerAnthony2After:
	.string "Los EXCURSIONISTAS damos\n"
	.string "lo mejor en las montañas.$"

Route33_Text_HikerAnthonyDunsparce:
	.string "Oye, ¿tienes un DUNSPARCE?\p"
	.string "Yo también atrapé uno.\p"
	.string "Míralo bien con la luz.\n"
	.string "¡Tiene una cara graciosa!$"

Route33_Text_Lass:
	.string "Jadeo, jadeo...\p"
	.string "Esa cueva era más grande\n"
	.string "de lo que esperaba.\p"
	.string "Me cansé buscando a\n"
	.string "MARILL, así que salí.$"
