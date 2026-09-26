Route2_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route2_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route2_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route2_EventScript_Rob::
	trainerbattle_single TRAINER_ROB, Route2_Text_BugCatcherRob_Seen, Route2_Text_BugCatcherRob_Beaten
	msgbox Route2_Text_BugCatcherRob_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route2_EventScript_Ed::
	trainerbattle_single TRAINER_ED, Route2_Text_BugCatcherEd_Seen, Route2_Text_BugCatcherEd_Beaten
	msgbox Route2_Text_BugCatcherEd_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route2_EventScript_Doug::
	trainerbattle_single TRAINER_DOUG, Route2_Text_BugCatcherDoug_Seen, Route2_Text_BugCatcherDoug_Beaten
	msgbox Route2_Text_BugCatcherDoug_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route2_EventScript_Sign::
	msgbox Route2_Text_Sign, MSGBOX_SIGN
	end

Route2_EventScript_CaveSign::
	msgbox Route2_Text_DiglettsCaveSign, MSGBOX_SIGN
	end

Route2_EventScript_Carbos::
    finditem ITEM_CARBOS
    end

Route2_EventScript_Nugget::
    finditem ITEM_NUGGET
    end

Route2_Text_BugCatcherRob_Seen:
	.string "Mis POKéMON bicho son fuertes.\n"
	.string "¡Prepárate para perder!$"

Route2_Text_BugCatcherRob_Beaten:
	.string "Me dieron una paliza...$"

Route2_Text_BugCatcherRob_AfterBattle:
	.string "Buscaré POKéMON bicho\n"
	.string "más fuertes.$"

Route2_Text_BugCatcherEd_Seen:
	.string "¿Si caminas por el pasto con\n"
	.string "shorts, te haces cortes?$"

Route2_Text_BugCatcherEd_Beaten:
	.string "¡Ay, ay, ay!$"

Route2_Text_BugCatcherEd_AfterBattle:
	.string "¡Arderán mucho cuando te\n"
	.string "des un baño!$"

Route2_Text_BugCatcherDoug_Seen:
	.string "¿Las chicas odian los POKéMON bicho?$"

Route2_Text_BugCatcherDoug_Beaten:
	.string "¡No sirve!$"

Route2_Text_BugCatcherDoug_AfterBattle:
	.string "Los POKéMON bicho son como peluches\n"
	.string "cuando aprietas su panza.\p"
	.string "¡Me encanta cómo se sienten!$"

Route2_Text_Sign:
	.string "RUTA 2\p"
	.string "C. VERIDIAN - C. PLATEA$"

Route2_Text_DiglettsCaveSign:
	.string "CUEVA DIGLETT$"

