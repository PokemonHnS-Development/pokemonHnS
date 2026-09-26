.set LOCALID_R39_SHADOW, 17
.set LOCALID_R39_BAOBA, 2

Route39_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route39_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route39_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route39_EventScript_Item_TM::
	finditem ITEM_TM_BRICK_BREAK
	end

Route39_EventScript_Item_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route39_EventScript_LegendaryTrigger::
	lock
	clearflag FLAG_HIDE_ROUTE39_SHADOW
	addobject LOCALID_R39_SHADOW
	playse SE_M_RAZOR_WIND
	applymovement LOCALID_R39_SHADOW, Route39_Movement_ShadowSlideDown
	waitmovement 0
	setflag FLAG_HIDE_ROUTE39_SHADOW
	removeobject LOCALID_R39_SHADOW
	playse SE_PIN
	applymovement LOCALID_R39_BAOBA, Common_Movement_QuestionMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	turnobject LOCALID_R39_BAOBA DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER DIR_SOUTH
	delay 60

	getplayerxy VAR_TEMP_0, VAR_TEMP_1

	call_if_eq VAR_TEMP_1, 20, Route39_EventScript_BaobaMovement1
	call_if_eq VAR_TEMP_1, 21, Route39_EventScript_BaobaMovement2
	call_if_eq VAR_TEMP_1, 22, Route39_EventScript_BaobaMovement3
	call_if_eq VAR_TEMP_1, 23, Route39_EventScript_BaobaMovement4

	turnobject LOCALID_R39_BAOBA DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER DIR_WEST
Route39_EventScript_ChooseLegend::
	msgbox Route39_Text_ChooseLegend, MSGBOX_DEFAULT
	multichoice 20, 8, MULTI_GOLDSILVER, FALSE
	switch VAR_RESULT
	case 0, Route39_EventScript_LegendaryTriggerGold
	case 1, Route39_EventScript_LegendaryTriggerSilver
	case MULTI_B_PRESSED, Route39_EventScript_ChooseLegend
	release
	end

Route39_EventScript_BaobaMovement1::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba1
	waitmovement 0
	return
Route39_EventScript_BaobaMovement2::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba2
	waitmovement 0
	return
Route39_EventScript_BaobaMovement3::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba3
	waitmovement 0
	return
Route39_EventScript_BaobaMovement4::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba4
	waitmovement 0
	return

Route39_Movement_Baoba1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba4:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

Route39_EventScript_LegendaryTriggerGold::
	setvar VAR_LUGIA_OR_HOOH, 2
	goto Route39_EventScript_BaobaIntro

Route39_EventScript_LegendaryTriggerSilver::
	setvar VAR_LUGIA_OR_HOOH, 1
	goto Route39_EventScript_BaobaIntro

Route39_EventScript_BaobaIntro::
	msgbox Route39_Text_BaobaIntro, MSGBOX_DEFAULT
	playse MUS_HG_POKEGEAR_REGISTERED
	msgbox Route39_Text_Registered, MSGBOX_DEFAULT
	waitse
	msgbox Route39_Text_WillCall, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_R39_BAOBA, Route39_Movement_BaobaLeave
	waitmovement 0
	setflag FLAG_ENABLE_BAOBA_MATCH_CALL
	removeobject LOCALID_R39_BAOBA
	release
	end

Route39_Text_ChooseLegend::
	.string "BAOBA: ¡Cielos! ¿Esa sombra\n"
	.string "era de un POKéMON?\p"
	.string "¿Lograste verlo bien?\n"
	.string "No distingo qué color era...$"

Route39_Text_BaobaIntro::
	.string "Qué extraño...\p"
	.string "...¡Oh!\n"
	.string "Eso que tienes es...\l"
	.string "¡lo que llaman... una POKéDEX!\p"
	.string "No veía una hace siglos.\p"
	.string "¡Mi nombre es BAOBA!\n"
	.string "Dirigía una SAFARI ZONE en\l"
	.string "CIUDAD Fucsia, pero quedó\l"
	.string "obsoleta con las nuevas opciones\l"
	.string "de entretenimiento.\p"
	.string "Fui al extranjero para aprender\n"
	.string "tecnología y abrir una\l"
	.string "SAFARI ZONE moderna\l"
	.string "en CIUDAD ORQUIDEA.\p"
	.string "No creo que sea coincidencia\n"
	.string "que estemos hablando.\p"
	.string "¿Por qué no registramos nuestros\n"
	.string "números en el POKéGEAR?\p"
	.string "¡Te llamaré en cuanto la\n"
	.string "SAFARI ZONE abra antes de\l"
	.string "llamar a cualquier otro!$"

Route39_Text_Registered:
	.string "{PLAYER} registró a BAOBA\n"
	.string "en el POKéGEAR!$"


Route39_Text_WillCall:
	.string "BAOBA: ¡Te avisaré\n"
	.string "por el POKéGEAR pronto!$"

Route39_Movement_BaobaLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route39_Movement_ShadowSlideDown:
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

Route39_EventScript_Woman::
	lock
	faceplayer
	msgbox Route39_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_Text_Woman:
	.string "Esa sombra... ¿Quizás era un\n"
	.string "PIDGEY gigante?$"

Route39_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox Route39_Text_Miltank, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route39_Text_Miltank:
	.string "MILTANK: ¡Mooo!$"

Route39_EventScript_Eugene::
	trainerbattle_single TRAINER_EUGENE, Route39_Text_SailorEugeneSeen, Route39_Text_SailorEugeneBeaten
	msgbox Route39_Text_SailorEugeneAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_SailorEugeneSeen:
	.string "Acabo de volver a CIUDAD OLIVO.\p"
	.string "¿Qué tal una batalla POKéMON?$"

Route39_Text_SailorEugeneBeaten:
	.string "¡Awaaargh!$"

Route39_Text_SailorEugeneAfter:
	.string "Mis POKéMON fueron capturados y\n"
	.string "criados fuera.\p"
	.string "Son mis compañeros en\n"
	.string "esos largos viajes.$"

Route39_EventScript_Derek::
	trainerbattle_single TRAINER_DEREK, Route39_Text_PokefanMDerekSeen, Route39_Text_PokefanMDerekBeaten
	msgbox Route39_Text_PokefanMDerekAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanMDerekSeen:
	.string "¡Es un buen momento para presumir\n"
	.string "de mi PIKACHU!$"

Route39_Text_PokefanMDerekBeaten:
	.string "No tuve tiempo de presumir\n"
	.string "a PIKACHU…$"

Route39_Text_PokefanMDerekAfter:
	.string "¡No voy a escuchar tus\n"
	.string "presunciones!\p"
	.string "¡Los POKé FANS no escuchamos\n"
	.string "a los presumidos!$"

Route39_EventScript_Ruth::
	trainerbattle_single TRAINER_RUTH, Route39_Text_PokefanFRuthSeen, Route39_Text_PokefanFRuthBeaten
	msgbox Route39_Text_PokefanFRuthAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFRuthSeen:
	.string "Qué lindos POKéMON.\p"
	.string "¡Mostremos nuestros POKéMON\n"
	.string "al mismo tiempo!$"

Route39_Text_PokefanFRuthBeaten:
	.string "No me importa perder.$"

Route39_Text_PokefanFRuthAfter:
	.string "¿Sabes sobre los POKéMON\n"
	.string "bebé?\p"
	.string "¡Apuesto a que son adorables!$"

Route39_EventScript_Norman::
	trainerbattle_single TRAINER_NORMAN, Route39_Text_PsychicNormanSeen, Route39_Text_PsychicNormanBeaten
	msgbox Route39_Text_PsychicNormanAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PsychicNormanSeen:
	.string "Déjame ver de qué son capaces\n"
	.string "tus POKéMON.$"

Route39_Text_PsychicNormanBeaten:
	.string "Ooh, tus POKéMON tienen\n"
	.string "potencial.$"

Route39_Text_PsychicNormanAfter:
	.string "¿Sabes que los POKéMON tienen\n"
	.string "habilidades distintas?\p"
	.string "Las personas son iguales.\n"
	.string "Todos tienen un\l"
	.string "potencial diferente.$"

Route39_EventScript_Jamie::
	trainerbattle_single TRAINER_JAMIE, Route39_Text_PokefanFJaimeSeen, Route39_Text_PokefanFJaimeBeaten
	msgbox Route39_Text_PokefanFJaimeAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFJaimeSeen:
	.string "Llegaste en el momento\n"
	.string "indicado.\p"
	.string "¡Luchemos!$"

Route39_Text_PokefanFJaimeBeaten:
	.string "Oh, qué decepción…$"

Route39_Text_PokefanFJaimeAfter:
	.string "Conocí a UMBREON de noche\n"
	.string "aquí en la RUTA 39.\p"
	.string "No sé por qué, pero parece\n"
	.string "que le gusta que lo\l"
	.string "entrene aquí.\p"
	.string "Se vuelve más amigable\n"
	.string "entrenando aquí que\l"
	.string "en cualquier otro lugar.$"

Route39_EventScript_Sign1::
	lock
	msgbox Route39_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_Sign:
	.string "RUTA 39\p"
	.string "CIUDAD OLIVO - CIUDAD IRIS$"

Route39_EventScript_Sign2::
	lock
	msgbox Route39_Text_MoomooFarmSign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_MoomooFarmSign:
	.string "GRANJA MOOMOO\p"
	.string "Prueba nuestra leche fresca$"

Route39_EventScript_Sign3::
	lock
	msgbox Route39_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_TrainerTips:
	.string "CONSEJOS\p"
	.string "Usa CABEZAZO en los árboles\n"
	.string "para sacar POKéMON.\p"
	.string "Diferentes POKéMON\n"
	.string "caen de los árboles.\p"
	.string "¡Usa CABEZAZO en cualquier\n"
	.string "árbol que veas!$"
