Route37_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route37_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route37_OnTransition: 
	callnative SetTimeBasedEncounters
	end



Route37_EventScript_TwinAnn::
	trainerbattle_double TRAINER_ANN_AND_ANNE, Route37_Text_TwinsAnnAndAnne1_Seen, Route37_Text_TwinsAnnAndAnne1_Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne1_After, MSGBOX_DEFAULT
	release
	end
	
Route37_EventScript_TwinAnne::
	trainerbattle_double TRAINER_ANN_AND_ANNE, Route37_Text_TwinsAnnAndAnne2_Seen, Route37_Text_TwinsAnnAndAnne2_Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne2_After, MSGBOX_DEFAULT
	release
	end

Route37_EventScript_Greg::
	trainerbattle_single TRAINER_GREG Route37_Text_PsychicGreg_Seen, Route37_Text_PsychicGreg_Beaten
	msgbox Route37_Text_PsychicGreg_After, MSGBOX_AUTOCLOSE
	end


Route37_EventScript_Sunny::
	lock
	faceplayer
	goto_if_set FLAG_GOT_MAGNET, Route37_EventScript_SunnyCompleted
	msgbox Route37_Text_Sunny_Meet, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route37_EventScript_SunnyYes
	case 1, Route37_EventScript_SunnyNope
	case 2, Route37_EventScript_SunnyNope
	case 3, Route37_EventScript_SunnyNope
	case 4, Route37_EventScript_SunnyNope
	case 5, Route37_EventScript_SunnyNope
	case 6, Route37_EventScript_SunnyNope
	case 7 Route37_EventScript_SunnyCancel
	case MULTI_B_PRESSED, Route37_EventScript_SunnyCancel
	closemessage
	release
	end
Route37_EventScript_SunnyYes::
	msgbox Route37_Text_Sunny_GiveGift2, MSGBOX_DEFAULT
	giveitem ITEM_MAGNET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_MAGNET
	msgbox Route37_Text_Sunny_GaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route37_EventScript_SunnyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route37_EventScript_SunnyCancel::
	closemessage
	release
	end
Route37_EventScript_SunnyCompleted::
	msgbox Route37_Text_Sunny_Sunday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route37_EventScript_Sign::
	lock
	msgbox Route37_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route37_Text_TwinsAnnAndAnne1_Seen:
	.string "ANN: ¡ANNE y yo estamos en esto\n"
	.string "juntas!$"

Route37_Text_TwinsAnnAndAnne1_Beaten:
	.string "ANN y ANNE: Nnn... Es un poco\n"
	.string "demasiado fuerte.$"

Route37_Text_TwinsAnnAndAnne1_After:
	.string "ANN: Sé lo que mi hermana y mis\n"
	.string "POKéMON están pensando.$"

Route37_Text_TwinsAnnAndAnne2_Seen:
	.string "ANNE: ¡ANN y yo estamos en esto\n"
	.string "juntas!$"

Route37_Text_TwinsAnnAndAnne2_Beaten:
	.string "ANN y ANNE: Nnn... Es un poco\n"
	.string "demasiado fuerte.$"

Route37_Text_TwinsAnnAndAnne2_After:
	.string "ANNE: Sentimos lo mismo que\n"
	.string "nuestros POKéMON.$"

Route37_Text_PsychicGreg_Seen:
	.string "Un POKéMON no puede hacer nada si\n"
	.string "está dormido.\p"
	.string "¡Te mostraré lo aterrador que es!$"

Route37_Text_PsychicGreg_Beaten:
	.string "Perdí. Eso es muy triste...$"

Route37_Text_PsychicGreg_After:
	.string "Dormir o paralizar a los POKéMON\n"
	.string "son buenas técnicas de batalla.$"

Route37_Text_Sunny_Meet:
	.string "SUNNY: ¡Hola!\p"
	.string "¡Soy SUNNY, de la familia WEEKDAY!\p"
	.string "Si adivinas mi día favorito,\n"
	.string "te daré un premio.$"

Route37_Text_Sunny_GiveGift1:
	.string "¡Me dijeron que te diera esto si\n"
	.string "te veía!$"

Route37_Text_Sunny_GiveGift2:
	.string "¡Me dijeron que te diera esto si\n"
	.string "te veía!$"

Route37_Text_Sunny_GaveGift:
	.string "SUNNY: Eso...\p"
	.string "Eh...\p"
	.string "... ¿Qué era...?\p"
	.string "...\p"
	.string "¡Ah! ¡Ya me acuerdo!\p"
	.string "Un POKéMON con ataques eléctricos\n"
	.string "debería llevarlo.\p"
	.string "Mi hermana MONICA dice que potencia\n"
	.string "los ataques eléctricos!$"

Route37_Text_Sunny_Sunday:
	.string "SUNNY: Mis hermanos son\n"
	.string "MONICA, TUSCANY, WESLEY, ARTHUR,\l"
	.string "FRIEDA y SANTOS.\p"
	.string "¡Todos son mayores que yo!$"

Route37_Text_Sunny_NotSunday:
	.string "SUNNY: ¿Hoy no es domingo?\n"
	.string "Eh... ¡se me olvidó!$"

Route37_Text_Sign:
	.string "RUTA 37\n"
	.string "CIUDAD IRIS ADELANTE$"
