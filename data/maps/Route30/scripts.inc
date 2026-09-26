.set LOCALID_ROUTE_30_JOEY, 6

Route30_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route30_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route30_OnFrame
	.byte 0

Route30_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route30_OnFrame::
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 2, Route30_EventScript_ElmCall_Trigger
	.2byte 0
	
Route30_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route30_EventScript_Boy2
	msgbox Route30_Text_YoungsterDirectionsToMrPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Boy2::
	lock
	faceplayer
	msgbox Route30_Text_YoungsterEveryoneIsBattling, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Girl::
	lock
	faceplayer
	msgbox Route30_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Youngster_Joey_Fighting::
	lock
	msgbox Route30_Text_UseTackle, 	MSGBOX_AUTOCLOSE
	waitmessage
	playse SE_PIN
	applymovement LOCALID_ROUTE_30_JOEY, Common_Movement_QuestionMark
	delay 30
	faceplayer
	msgbox Route30_Text_ThisIsABigBattle, MSGBOX_AUTOCLOSE
	waitmessage
	turnobject LOCALID_ROUTE_30_JOEY DIR_NORTH
	release
	end


Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_Youngster_Mikey::
	trainerbattle_single TRAINER_MIKEY, Route30_Text_YoungsterMikeySeen, Route30_Text_YoungsterMikeyBeaten
	msgbox Route30_Text_YoungsterMikeyAfter, MSGBOX_AUTOCLOSE
	end
	
Route30_EventScript_Bugcatcher_Don::
	trainerbattle_single TRAINER_DON, Route30_Text_BugCatcherDonSeen, Route30_Text_BugCatcherDonBeaten
	msgbox Route30_Text_BugCatcherDonAfter, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_ElmCall_Trigger::
	lock
	pokenavcall Route30_Text_Elm_Disaster
	waitmessage
	delay 30
	setvar VAR_CHERRYGROVE_CITY_STATE, 3
	release
	end

Route30_EventScript_Sign::
	lock
	msgbox Route30_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route30_EventScript_TrainerTips::
	lock
	msgbox Route30_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end	

Route30_EventScript_Poliwag::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWAG, CRY_MODE_NORMAL
	msgbox Route30_Text_Poliwag, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route30_EventScript_Mailbox::
	msgbox Route30_Text_Mailbox, MSGBOX_SIGN
	end

Route30_Text_Mailbox:
	.string "Casa del SR.POKéMON$"

Route30_Text_UseTackle:
	.string "¡Ve, RATTATA!\p"
	.string "¡PLACAGE!$"

Route30_Text_ThisIsABigBattle:
	.string "¿Qué? ¡Es una gran batalla!\n"
	.string "¡Déjame en paz!$"

Route30_Text_YoungsterJoey1Seen:
	.string "Perdí, así que busco más\n"
	.string "POKéMON.\p"
	.string "¡Espera! ¡Te ves débil! Vamos,\n"
	.string "¡a luchar!$"

Route30_Text_YoungsterJoey1Beaten:
	.string "¡Ay! ¡Perdí otra vez!\n"
	.string "¡Maldición!$"

Route30_Text_YoungsterJoey1After:
	.string "¿Necesito más POKéMON para\n"
	.string "luchar mejor?\p"
	.string "¡No! Me quedo con este\n"
	.string "pase lo que pase!$"

Route30_Text_YoungsterMikeySeen:
	.string "Eres entrenador POKéMON,\n"
	.string "¿verdad?\p"
	.string "¡Entonces tienes que luchar!$"

Route30_Text_YoungsterMikeyBeaten:
	.string "Qué extraño.\n"
	.string "Antes gané.$"

Route30_Text_YoungsterMikeyAfter:
	.string "Ser un buen entrenador es\n"
	.string "muy difícil.\p"
	.string "Lucharé contra otros\n"
	.string "para mejorar.$"

Route30_Text_BugCatcherDonSeen:
	.string "¡En vez de un POKéMON bicho,\n"
	.string "encontré un entrenador!$"

Route30_Text_BugCatcherDonBeaten:
	.string "¡Argh! ¡Eres muy fuerte!$"

Route30_Text_BugCatcherDonAfter:
	.string "Me quedé sin POKé BALLS al\n"
	.string "atrapar POKéMON.\p"
	.string "Debí comprar más…$"

Route30_Text_YoungsterDirectionsToMrPokemon:
	.string "¿La casa del SR. POKéMON?\n"
	.string "Está un poco más adelante.$"

Route30_Text_YoungsterEveryoneIsBattling:
	.string "¡Todos se divierten\n"
	.string "luchando!\p"
	.string "¡Tú también deberías!$"

Route30_Text_CooltrainerF:
	.string "No soy entrenador.\p"
	.string "Pero si miras a uno a los\n"
	.string "ojos, prepárate para luchar.$"

Route30_Text_Sign:
	.string "RUTA 30\p"
	.string "CIUDAD MALVA - CIUDAD CEREZO$"

Route30_Text_MrPokemonsHouseDirectionsSign:
	.string "CASA DEL SR. POKéMON\n"
	.string "¡SIGUE DE FRENTE!$"

Route30_Text_MrPokemonsHouseSign:
	.string "CASA DEL SR. POKéMON$"

Route30_Text_TrainerTips:
	.string "CONSEJOS ENTRENADOR\p"
	.string "¡No robes POKéMON\n"
	.string "de otros!\p"
	.string "¡Lanza las POKé BALLS\n"
	.string "solo a POKéMON salvajes!$"

Route30_Text_YoungsterJoeyGiveHPUp:
	.string "Perdí otra vez...\n"
	.string "¡Vaya, eres fuerte!\p"
	.string "Ah, casi olvido que\n"
	.string "debía darte esto.\p"
	.string "Úsalo para ser más fuerte,\n"
	.string "¿está bien?\p"
	.string "Yo también seré más fuerte.$"

Route30_Text_Elm_Disaster:
	.string "PROF.ELM: ¿H-hola? {PLAYER}? ¡Es\n"
	.string "un desastre!\p"
	.string "¡Uh, es simplemente terrible!\p"
	.string "¿Qué debo hacer? Es...\n"
	.string "Oh, no...\p"
	.string "¡Por favor, vuelve ahora!$"


Route30_Text_Poliwag:
	.string "POLIWAG: ¡Wag waag!$"
