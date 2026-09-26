Route11_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route11_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route11_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route11_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN Route11_Text_YoungsterOwenSeen, Route11_Text_YoungsterOwenBeaten
	msgbox Route11_Text_YoungsterOwenAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Jason::
	trainerbattle_single TRAINER_JASON Route11_Text_YoungsterJasonSeen, Route11_Text_YoungsterJasonBeaten
	msgbox Route11_Text_YoungsterJasonAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Herman::
	trainerbattle_single TRAINER_HERMAN Route11_Text_PsychicHermanSeen, Route11_Text_PsychicHermanBeaten
	msgbox Route11_Text_PsychicHermanAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Fidel::
	trainerbattle_single TRAINER_FIDEL Route11_Text_PsychicFidelSeen, Route11_Text_PsychicFidelBeaten
	msgbox Route11_Text_PsychicFidelAfterBattle, MSGBOX_AUTOCLOSE
	end


Route11_EventScript_Engineer::
	msgbox Route11_Text_Engineer, MSGBOX_NPC
	end

Route11_Text_Engineer:
	.string "Vi un POKéMON extraño trepando\n"
	.string "en los árboles, pero no parecía\l"
	.string "un MANKEY...$"

Route11_Text_YoungsterOwenSeen:
	.string "No se hace trampa en POKéMON.\p"
	.string "¡Mantengamos el juego limpio!$"

Route11_Text_YoungsterOwenBeaten:
	.string "¿Eh? ¿Cómo pasó esto?$"

Route11_Text_YoungsterOwenAfterBattle:
	.string "Luché con honor y honestidad.\n"
	.string "honor.\p"
	.string "No me arrepiento de nada.$"

Route11_Text_YoungsterJasonSeen:
	.string "Me pica y me da cosquillas usar\n"
	.string "shorts en la hierba.$"

Route11_Text_YoungsterJasonBeaten:
	.string "¡Aiyaaah! ¡Me aplastaron!$"

Route11_Text_YoungsterJasonAfterBattle:
	.string "Atraparé más POKéMON en la\n"
	.string "hierba.$"

Route11_Text_PsychicHermanSeen:
	.string "…$"

Route11_Text_PsychicHermanBeaten:
	.string "…$"

Route11_Text_PsychicHermanAfterBattle:
	.string "…\p"
	.string "Perdí con los ojos cerrados…$"

Route11_Text_PsychicFidelSeen:
	.string "Puedo verlo...\p"
	.string "Todo lo que hay en ti...$"

Route11_Text_PsychicFidelBeaten:
	.string "No preví tu poder...$"

Route11_Text_PsychicFidelAfterBattle:
	.string "Fuerza en la convicción...\p"
	.string "Eres fuerte porque crees\n"
	.string "en tus POKéMON.$"

Route11_Text_Sign:
	.string "RUTA 11$"

