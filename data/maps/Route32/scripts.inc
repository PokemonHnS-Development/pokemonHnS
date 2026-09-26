.set LOCALID_ROUTE32_BALDINGMAN, 1
.set LOCALID_SLOWPOKETAIL_MAN, 14


Route32_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route32_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route32_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route32_EventScript_FisherJustin::
	trainerbattle_single TRAINER_JUSTIN Route32_Text_FisherJustin_Seen, Route32_Text_FisherJustin_Beaten
	msgbox Route32_Text_FisherJustin_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherRalph::
	trainerbattle_single TRAINER_RALPH Route32_Text_FisherRalph1_Seen, Route32_Text_FisherRalph1_Beaten
	msgbox Route32_Text_FisherRalph1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherHenry::
	trainerbattle_single TRAINER_HENRY Route32_Text_FisherHenry_Seen, Route32_Text_FisherHenry_Beaten
	msgbox Route32_Text_FisherHenry_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterAlbert::
	trainerbattle_single TRAINER_ALBERT Route32_Text_YoungsterAlbert_Seen, Route32_Text_YoungsterAlbert_Beaten
	msgbox Route32_Text_YoungsterAlbert_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterGordon::
	trainerbattle_single TRAINER_GORDON Route32_Text_YoungsterGordon_Seen, Route32_Text_YoungsterGordon_Beaten
	msgbox Route32_Text_YoungsterGordon_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_CamperRoland::
	trainerbattle_single TRAINER_ROLAND Route32_Text_CamperRoland_Seen, Route32_Text_CamperRoland_Beaten
	msgbox Route32_Text_CamperRoland_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_PicnickerLiz::
	trainerbattle_single TRAINER_LIZ Route32_Text_PicnickerLiz1_Seen, Route32_Text_PicnickerLiz1_Beaten
	msgbox Route32_Text_PicnickerLiz1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_BirdkeeperPeter::
	trainerbattle_single TRAINER_PETER Route32_Text_BirdKeeperPeter_Seen, Route32_Text_BirdKeeperPeter_Beaten
	msgbox Route32_Text_BirdKeeperPeter_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_Roar::
	lock
	faceplayer
	checkitem ITEM_TM_ROAR
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_Roar2
	msgbox Route32_Text_RoarIntro, MSGBOX_DEFAULT
	giveitem ITEM_TM_ROAR
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_Roar2::
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_SlowpokeTail_TriggerLeft::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 60
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeLeft
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerMid::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 60
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeMid
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerRight::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 60
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeRight
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_Trigger::
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_SlowpokeTail_Trigger2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SLOWPOKE_TAIL, 1
	release
	end	
Route32_EventScript_SlowpokeTail_Trigger2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 16, Route32_EventScript_Movement_Left
	call_if_eq VAR_TEMP_0, 17, 	Route32_EventScript_Movement_Right
	setvar VAR_SLOWPOKE_TAIL, 1
	release
	end

Route32_EventScript_Movement_Left::
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	return 

Route32_EventScript_Movement_Right::
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	return 	

Route32_EventScript_SlowpokeTail::
	lock
	faceplayer
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_SlowpokeTail2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_SlowpokeTail2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	release
	end


Route32_EventScript_Frieda::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POISON_BARB, Route32_EventScript_FriedaCompleted
	msgbox Route32_Text_MeetFrieda, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route32_EventScript_FriedaNope
	case 1, Route32_EventScript_FriedaNope
	case 2, Route32_EventScript_FriedaNope
	case 3, Route32_EventScript_FriedaNope
	case 4, Route32_EventScript_FriedaNope
	case 5, Route32_EventScript_FriedaYes
	case 6, Route32_EventScript_FriedaNope
	case 7, Route32_EventScript_FriedaCancel
	case MULTI_B_PRESSED, Route32_EventScript_FriedaCancel
	closemessage
	release
	end
Route32_EventScript_FriedaYes::
	msgbox Route32_Text_FriedaGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_POISON_BARB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_POISON_BARB
	msgbox Route32_Text_FriedaGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_FriedaNope::
	msgbox Route32_Text_FriedaNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_FriedaCancel::
	closemessage
	release
	end
Route32_EventScript_FriedaCompleted::
	msgbox Route32_Text_FriedaFriday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_BaldingMan::
	lock
	faceplayer
	msgbox Route32_Text_CooltrainerM_Experiences, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE32_BALDINGMAN, DIR_EAST
	release
	end

Route32_EventScript_BaldingManTriggerLeft::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManTriggerMid::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 60
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_StartMid
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManTriggerRight::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 60
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movment_StartRight
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManCheck::
	goto_if_unset FLAG_HIDE_SPROUT_TOWER_SILVER, Route32_EventScript_BaldingManTower
	goto_if_unset FLAG_DEFEATED_VIOLET_GYM, Route32_EventScript_BaldingManGym
	goto_if_unset FLAG_RECEIVED_TOGEPI_EGG, Route32_EventScript_BaldingManEgg
	msgbox Route32_Text_CooltrainerM_HaveThisSeed, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setvar VAR_VIOLET_CITY_STATE, 5
	release
	end
Route32_EventScript_BaldingManTower::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_SproutTower, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end
Route32_EventScript_BaldingManGym::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_VioletGym, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end
Route32_EventScript_BaldingManEgg::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_AideIsWaiting, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end

Route32_EventScript_Potion::
	finditem ITEM_POTION
	end
Route32_EventScript_GreatBall::
	finditem ITEM_GREAT_BALL
	end
Route32_EventScript_GreatBallII::
	finditem ITEM_GREAT_BALL
	end
Route32_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

Route32_EventScript_Sign1::
	lock
	msgbox Route32_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign2::
	lock
	msgbox Route32_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign3::
	lock
	msgbox Route32_Text_Sign3, MSGBOX_SIGN
	closemessage
	release
	end

Route32_Movement_Turnback:
	walk_up
	step_end

Route32_Movement_StartMid:
	walk_left
	step_end

Route32_Movment_StartRight:
	walk_left
	walk_left
	step_end

Route32_Movement_SlowpokeLeft::
	step_end

Route32_Movement_SlowpokeMid::
	walk_right
	step_end

Route32_Movement_SlowpokeRight::
	walk_right
	walk_right
	step_end

Route32_Text_CooltrainerM_WhatsTheHurry:
	.string "¡Espera!\n"
	.string "¿Cuál es la prisa?$"

Route32_Text_CooltrainerM_AideIsWaiting:
	.string "{PLAYER}, ¿verdad?\n"
	.string "Un tipo con lentes\p"
	.string "te estaba buscando.\p"
	.string "Míralo tú mismo. Te espera en\n"
	.string "el POKéMON CENTER.$"

Route32_Text_CooltrainerM_SproutTower:
	.string "¿Fuiste a la TORRE VERDE?\n"
	.string "Si visitas CIUDAD MALVA,\p"
	.string "esperarán que entrenes ahí.\n"
	.string "Es básico para los entrenadores.\p"
	.string "¡Ve a la TORRE VERDE!$"

Route32_Text_CooltrainerM_VioletGym:
	.string "¿Fuiste al GIMNASIO POKéMON?\n"
	.string "Ahí puedes poner a prueba a tus\p"
	.string "POKéMON y a ti mismo.\n"
	.string "¡Es un rito de paso para todo\p"
	.string "entrenador!$"

Route32_Text_CooltrainerM_HaveThisSeed:
	.string "Tienes buenos POKéMON.\n"
	.string "Debe ser por el entrenamiento que\p"
	.string "les diste en CIUDAD MALVA.\n"
	.string "El entrenamiento en el GIMNASIO\p"
	.string "debió ayudar mucho. Como un\n"
	.string "recuerdo de CIUDAD MALVA, toma esto.\p"
	.string "Sube el poder de los movimientos\n"
	.string "tipo PLANTA.$"

Route32_Text_CooltrainerM_Experiences:
	.string "Tus vivencias en CIUDAD MALVA\n"
	.string "serán útiles en tu viaje.$"

Route32_Text_SlowpokeTailOffer:
	.string "¿Quieres esta deliciosa y\n"
	.string "nutritiva COLA DE SLOWPOKE?\p"
	.string "¡Solo por ahora, a\n"
	.string "¥1,000,000!\p"
	.string "¡La querrás tener!$"

Route32_Text_ThoughtKidsLoaded:
	.string "¡Tch! Pensé que los niños\n"
	.string "de ahora tenían dinero...$"

Route32_Text_RefusedSlowpokeTail:
	.string "¿No lo quieres?\n"
	.string "¡Entonces lárgate!$"

Route32_Text_FisherJustin_Seen:
	.string "¡Vaya!\p"
	.string "¡Hice que se me escapara el pez!$"

Route32_Text_FisherJustin_Beaten:
	.string "¡Plash!$"

Route32_Text_FisherJustin_After:
	.string "Calma, control... La esencia de\n"
	.string "la pesca y POKéMON es la misma.$"

Route32_Text_FisherRalph1_Seen:
	.string "Soy muy bueno tanto en la pesca\n"
	.string "como en POKéMON.\p"
	.string "¡No perderé contra un niño!$"

Route32_Text_FisherRalph1_Beaten:
	.string "¡Tch! Intenté apresurar\n"
	.string "las cosas...$"

Route32_Text_FisherRalph1_After:
	.string "La pesca es una pasión\n"
	.string "de por vida.\p"
	.string "¡Los POKéMON son amigos eternos!$"

Route32_Text_FisherHenry_Seen:
	.string "¿Mis POKéMON? ¡Recién capturados!$"

Route32_Text_FisherHenry_Beaten:
	.string "¿SALPICADURA?$"

Route32_Text_FisherHenry_After:
	.string "Los POKéMON recién capturados\n"
	.string "no valen nada ante los criados.$"

Route32_Text_YoungsterAlbert_Seen:
	.string "No te había visto por aquí.\n"
	.string "¿Crees que eres muy fuerte?$"

Route32_Text_YoungsterAlbert_Beaten:
	.string "¡Eres fuerte!$"

Route32_Text_YoungsterAlbert_After:
	.string "Intentaré ser el mejor con mis\n"
	.string "favoritos.\p"
	.string "No usaré los mismos POKéMON\n"
	.string "fuertes que todos los demás.$"

Route32_Text_YoungsterGordon_Seen:
	.string "¡Hallé buenos POKéMON\n"
	.string "en la hierba!\p"
	.string "¡Creo que me servirán!$"

Route32_Text_YoungsterGordon_Beaten:
	.string "Rayos. Creí que ganaría.$"

Route32_Text_YoungsterGordon_After:
	.string "La hierba está llena de\n"
	.string "cosas pegajosas.$"

Route32_Text_CamperRoland_Seen:
	.string "Esa mirada... Es intrigante.$"

Route32_Text_CamperRoland_Beaten:
	.string "Hmmm. Esto es decepcionante.$"

Route32_Text_CamperRoland_After:
	.string "Si no quieres luchar,\n"
	.string "evita el contacto visual.$"

Route32_Text_PicnickerLiz1_Seen:
	.string "Ajá. Sí, y ya sabes...\p"
	.string "¿Perdón? ¿Luchar? Estoy al teléfono.\n"
	.string "Está bien. Pero que sea rápido.$"

Route32_Text_PicnickerLiz1_Beaten:
	.string "¡Oh! ¡Tengo que desahogar\n"
	.string "mi ira!$"

Route32_Text_PicnickerLiz1_After:
	.string "Yo también estaba charlando.$"

Route32_Text_BirdKeeperPeter_Seen:
	.string "¡Esa MEDALLA! ¡Es de CIUDAD MALVA!\n"
	.string "¿Venciste a FALKNER?$"

Route32_Text_BirdKeeperPeter_Beaten:
	.string "Sé cuáles son mis debilidades.$"

Route32_Text_BirdKeeperPeter_After:
	.string "Debo entrenar otra vez en el\n"
	.string "GIMNASIO de CIUDAD MALVA.$"

Route32_Text_RoarIntro:
	.string "¡WROOOOAR! ¡LA GENTE HUYE CUANDO\n"
	.string "RUJO! ¡PERO TÚ VINISTE!\p"
	.string "¡ESO ME GUSTA! ¡AHORA RECIBE ESTO!$"

Route32_Text_RoarOutro:
	.string "¡WROOOOAR! ¡ES RUGE!\p"
	.string "¡HASTA LOS POKéMON HUYEN DE UN\n"
	.string "BUEN RUGE!$"

Route32_Text_MeetFrieda:
	.string "FRIEDA: ¡Yahoo!\p"
	.string "¡Soy FRIEDA de la FAMILIA SEMANA!\n"
	.string "¡Mucho gusto!\p"
	.string "Si adivinas mi día favorito,\n"
	.string "te daré un premio.$"

Route32_Text_FriedaGivesGift:
	.string "¡Toma este PUA VENENO!$"

Route32_Text_FriedaGaveGift:
	.string "FRIEDA: Dáselo a un POKéMON\n"
	.string "con movimientos tipo VENENO.\p"
	.string "¡Oh!\p"
	.string "¡Es genial!\p"
	.string "¡Te sorprenderá cuánto mejora\n"
	.string "los ataques de veneno!$"

Route32_Text_FriedaFriday:
	.string "FRIEDA: ¡Hola! ¿Qué día te\n"
	.string "gusta?\p"
	.string "A mí me encanta el viernes. ¡No\n"
	.string "hay duda!\p"
	.string "¿No crees que es genial también?$"

Route32_Text_FriedaNope:
	.string "FRIEDA: ¡Ese no es!$"

Route32_Text_Sign1:
	.string "RUTA 32\p"
	.string "CIUDAD MALVA - PUEBLO AZALEA$"

Route32_Text_Sign2:
	.string "RUINAS ALFA\n"
	.string "ENTRADA ESTE$"

Route32_Text_Sign3:
	.string "CUEVA UNIÓN\n"
	.string "ADELANTE$"
