.set LOCALID_STEVEN, 1

MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_STEVEN_REMATCH, MeteorFalls_StevensCave_EventScript_StevenRematch
	goto_if_set FLAG_DEFEATED_RED, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RED
	setflag FLAG_SIDNEY_REMATCH
	setflag FLAG_PHOEBE_REMATCH
	setflag FLAG_GLACIA_REMATCH
	setflag FLAG_DRAKE_REMATCH
	setflag FLAG_WALLACE_REMATCH
	release
	end

MeteorFalls_StevensCave_EventScript_StevenRematch::
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst2, MSGBOX_DEFAULT
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_HG_VS_CHAMPION
	trainerbattle_no_intro TRAINER_STEVEN2, MeteorFalls_StevensCave_Text_StevenDefeat2
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue2, MSGBOX_DEFAULT
	clearflag FLAG_STEVEN_REMATCH
	goto_if_unset FLAG_ARCEUS_EGG_GIVE MeteorFalls_StevensCave_EventScript_StevenArceusEvent
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_EventScript_StevenArceusEvent::
	msgbox MeteorFalls_StevensCave_Text_ArceusEvent1, MSGBOX_DEFAULT
	setflag FLAG_ARCEUS_EGG_GIVE
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_ARCEUS
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MeteorFalls_StevensCave_EventScript_StevenArceusEventToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MeteorFalls_StevensCave_EventScript_StevenArceusEventToPC
	release
	end

MeteorFalls_StevensCave_EventScript_StevenArceusEventToParty::
	call Common_EventScript_GetGiftMonPartySlot
	msgbox MeteorFalls_StevensCave_Text_ArceusEvent2, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_EventScript_StevenArceusEventToPC::
	call Common_EventScript_TransferredToPC
	msgbox MeteorFalls_StevensCave_Text_ArceusEvent2, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ArceusEvent1:
	.string "Y... quiero darte algo que hallé\n"
	.string "excavando por aquí. Es un HUEVO\l"
	.string "extraño.\p"
	.string "Lo llevo conmigo hace semanas\n"
	.string "pero no eclosiona.\p"
	.string "Eres mejor ENTRENADOR que yo,\n"
	.string "quizás logres que nazca.$"

MeteorFalls_StevensCave_Text_ArceusEvent2:
	.string "Me pregunto qué POKéMON pone sus\n"
	.string "HUEVOS entre rocas y se va...\p"
	.string "¿Será un POKéMON antiguo?\p"
	.string "Fufufu... quién sabe...$"

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "STEVEN: Oh, vaya, {PLAYER}{KUN}.\n"
	.string "Me asombra que supieras hallarme.\p"
	.string "¿Acaso... piensas que soy solo\n"
	.string "un maníaco de las rocas?\p"
	.string "No, eso no puede ser.\p"
	.string "Luchamos juntos en el CENTRO\n"
	.string "ESPACIAL DE SOOTOPOLIS.\p"
	.string "Deberías saber muy bien\n"
	.string "lo fuerte que soy.\p"
	.string "Bien, {PLAYER}{KUN}, si buscas un\n"
	.string "reto serio, ¡espera lo peor!$"

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst2:
	.string "STEVEN: Oh, hola, {PLAYER}{KUN}.\p"
	.string "Has vuelto. WALLACE me dijo que\n"
	.string "le venciste a él y a todo el\l"
	.string "ALTO MANDO otra vez. ¡Increíble!\p"
	.string "Yo también soy más fuerte. ¿Me das\n"
	.string "un reto serio otra vez?\p"
	.string "¡Bien, {PLAYER}{KUN}, vamos a ello!$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "Tú...\n"
	.string "No sabía que serías tan fuerte...$"

MeteorFalls_StevensCave_Text_StevenDefeat2:
	.string "Tú...\n"
	.string "Nadie puede superarte ahora.$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "STEVEN: Ahora que lo pienso, desde\n"
	.string "que nos vimos en la CUEVA GRANITO\l"
	.string "de DEWFORD, tuve este presentimiento.\p"
	.string "Pensé que eventualmente\n"
	.string "te volverías el CAMPEÓN.\p"
	.string "Mis predicciones suelen cumplirse.\p"
	.string "¿A dónde irás ahora?\p"
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ...\p"
	.string "Fufufu, ¿qué tal esto?\p"
	.string "Deberías retar al ALTO MANDO\n"
	.string "otra vez. Oí que son mucho\l"
	.string "más fuertes. ¿Qué te parece?$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue2:
	.string "STEVEN: Ahora que lo pienso, desde\n"
	.string "que nos vimos en la CUEVA GRANITO\l"
	.string "de DEWFORD, tuve este presentimiento.\p"
	.string "Pensé que eventualmente\n"
	.string "serías más fuerte que yo.\p"
	.string "Mis predicciones suelen cumplirse.\p"
	.string "¿A dónde irás ahora?\p"
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ...\p"
	.string "Fufufu, ni yo sabría decirte eso.$"
