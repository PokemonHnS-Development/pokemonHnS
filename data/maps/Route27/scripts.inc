.set LOCALID_ROUTE27_FATMAN, 1

Route27_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route27_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route27_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route27_EventScript_BaobaCall::
	pokenavcall BlackthornCity_Text_BaobaCall
	waitmessage
	delay 30
	setflag FLAG_SAFARI_ZONE_WEST_EXPANSION
    setvar VAR_ROUTE27_BAOBA_CALL, 1
	end

Route27_EventScript_FirstSteps::
    lock
    playse SE_PIN
    setflag FLAG_VISITED_KANTO
    applymovement2 LOCALID_ROUTE27_FATMAN, Common_Movement_ExclamationMark
    turnobject LOCALID_ROUTE27_FATMAN, DIR_WEST
    delay 30
    getplayerxy VAR_TEMP_0, VAR_TEMP_1
    call_if_eq VAR_TEMP_1, 24, Route27_EventScript_FirstStepsWalkTop
    call_if_eq VAR_TEMP_1, 25, Route27_EventScript_FirstStepsWalkBot

    msgbox Route27_Text_FisherHey, MSGBOX_DEFAULT
    msgbox Route27_Text_FisherMessage, MSGBOX_DEFAULT
    closemessage
    turnobject LOCALID_ROUTE27_FATMAN, DIR_SOUTH

    @integrated flagheap
    setflag FLAG_HIDE_VICTORY_ROAD_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_MARY_OAK
    
    clearflag FLAG_GOT_TM_SANDSTORM
    clearflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
    clearflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD

    setvar VAR_ROUTE27_STATE, 1
    release
    end

Route27_EventScript_FirstStepsWalkTop::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkTop
    waitmovement 0
    return
Route27_EventScript_FirstStepsWalkBot::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkBot
    waitmovement 0
    return

Route27_Movement_WalkTop:
    face_left
    walk_left
    step_end

Route27_Movement_WalkBot:
    walk_down
    walk_left
    step_end

Route27_EventScript_Item_Moonstone::
    finditem ITEM_MOON_STONE
    end

Route27_EventScript_Item_RareCandy::
    finditem ITEM_RARE_CANDY
    end

Route27_EventScript_Item_SolarBeam::
    finditem ITEM_TM_SOLAR_BEAM
    end

Route27_EventScript_Item_Revive::
    finditem ITEM_REVIVE
    end

Route27_EventScript_Fatman::
    msgbox Route27_Text_FisherMessage, MSGBOX_NPC
    end

Route27_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE Route27_Text_CooltrainermBlakeSeen, Route27_Text_CooltrainermBlakeBeaten
	msgbox Route27_Text_CooltrainermBlakeAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Brian::
	trainerbattle_single TRAINER_BRIAN Route27_Text_CooltrainermBrianSeen, Route27_Text_CooltrainermBrianBeaten
	msgbox Route27_Text_CooltrainermBrianAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Reena::
	trainerbattle_single TRAINER_REENA Route27_Text_CooltrainerfReenaSeen, Route27_Text_CooltrainerfReenaBeaten
	msgbox Route27_Text_CooltrainerfReenaAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Megan::
	trainerbattle_single TRAINER_MEGAN Route27_Text_CooltrainerfMeganSeen, Route27_Text_CooltrainerfMeganBeaten
	msgbox Route27_Text_CooltrainerfMeganAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Gilbert::
	trainerbattle_single TRAINER_GILBERT Route27_Text_PsychicGilbertSeen, Route27_Text_PsychicGilbertBeaten
	msgbox Route27_Text_PsychicGilbertAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Jose::
	trainerbattle_single TRAINER_JOSE Route27_Text_BirdKeeperJoseSeen, Route27_Text_BirdKeeperJoseBeaten
	msgbox Route27_Text_BirdKeeperJoseAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Scott::
	trainerbattle_single TRAINER_SCOTT Route27_Text_FisherScottSeen, Route27_Text_FisherScottBeaten
	msgbox Route27_Text_FisherScottAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_TohjoFallsSign::
    msgbox TohjoFalls_Text_Sign, MSGBOX_SIGN
    end

Route27_Text_FisherHey:
    .string "¡Hola!$"

Route27_Text_FisherMessage:
    .string "¿Sabes lo que acabas de hacer?\p"
    .string "Has dado tu primer paso en\n"
    .string "KANTO.\p"
    .string "Mira tu MAPA del POKéGEAR.$"

Route27_Text_CooltrainermBlakeSeen:
    .string "Te ves bastante fuerte.\n"
    .string "¡Batalla conmigo!$"

Route27_Text_CooltrainermBlakeBeaten:
    .string "¡Ay!$"

Route27_Text_CooltrainermBlakeAfter:
    .string "Si vences en este duro viaje,\n"
    .string "¡la verdad será revelada!\p"
    .string "Je, perdón, solo quería decir\n"
    .string "algo genial.$"

Route27_Text_CooltrainermBrianSeen:
    .string "¿Hm? Eres bueno, ¿verdad?$"

Route27_Text_CooltrainermBrianBeaten:
    .string "¡Tal como pensé!$"

Route27_Text_CooltrainermBrianAfter:
    .string "Un buen entrenador reconoce a\n"
    .string "otros buenos entrenadores.$"

Route27_Text_CooltrainerfReenaSeen:
    .string "No subestimes a los POKéMON\n"
    .string "salvajes de esta zona.$"

Route27_Text_CooltrainerfReenaBeaten:
    .string "¡Oh! ¡Eres demasiado fuerte!$"

Route27_Text_CooltrainerfReenaAfter:
    .string "Eres solo un niño, pero tú\n"
    .string "tampoco debes subestimarse.$"

Route27_Text_CooltrainerfMeganSeen:
    .string "Rara vez alguien viene aquí.\p"
    .string "¿Entrenas por tu cuenta?$"

Route27_Text_CooltrainerfMeganBeaten:
    .string "¡Oh! ¡Eres muy fuerte!$"

Route27_Text_CooltrainerfMeganAfter:
    .string "Estudio POKéMON antes y después\n"
    .string "de evolucionar.\p"
    .string "La evolución los hace\n"
    .string "más fuertes.\p"
    .string "Pero las formas evolucionadas\n"
    .string "aprenden ataques más tarde.$"

Route27_Text_PsychicGilbertSeen:
    .string "¡No digas nada!\p"
    .string "Adivinaré qué estás pensando.\p"
    .string "Mmmmmmm…\p"
    .string "¡Lo tengo! ¡Vas camino a la\n"
    .string "LIGA POKéMON!$"

Route27_Text_PsychicGilbertBeaten:
    .string "¡Eres demasiado para mí!$"

Route27_Text_PsychicGilbertAfter:
    .string "Con tu habilidad, te irá bien en\n"
    .string "la LIGA.\p"
    .string "Eso dice mi premonición.$"

Route27_Text_BirdKeeperJoseSeen:
    .string "¡Pío! ¡Pío! ¡Piopío!$"

Route27_Text_BirdKeeperJoseBeaten:
    .string "¡Pío!$"

Route27_Text_BirdKeeperJoseAfter:
    .string "Los CUIDADORES imitan silbidos\n"
    .string "para mandar a sus POKéMON.$"

TohjoFalls_Text_Sign:
    .string "CASCADA TOHJO\p"
    .string "EL VÍNCULO ENTRE KANTO Y JOHTO$"

Route27_Text_FisherScottSeen:
    .string "¡Me siento genial hoy!\p"
    .string "Siento que podría vencer hasta al\n"
    .string "¡CAMPEÓN DE LA LIGA!$"

Route27_Text_FisherScottBeaten:
    .string "¡No! ¡No en esta batalla!$"

Route27_Text_FisherScottAfter:
    .string "Como al pescar, todo termina\n"
    .string "en POKéMON si te rindes.$"
