Route29_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route29_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route29_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1 
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	end

Route29_Text_PressAorB:
	.string "Presiona A o B para dejar de ver.$"

Route29_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route29_EventScript_OldMan2
	msgbox Route29_Text_OldMan1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan2::
	msgbox Route29_Text_OldMan2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route29_EventScript_OldMan_Tutorial
	waitmessage
	msgbox Route29_Text_OldManDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan_Tutorial::
	msgbox Route29_Text_OldManExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Lass::
	lock
	faceplayer
	msgbox Route29_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route29_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end


Route29_EventScript_Tuscany::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SILK_SCARF, Route29_EventScript_TuscanyCompleted
	msgbox Route29_Text_MeetTuscany, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route29_EventScript_TuscanyNope
	case 1, Route29_EventScript_TuscanyNope
	case 2, Route29_EventScript_TuscanyYes
	case 3, Route29_EventScript_TuscanyNope
	case 4, Route29_EventScript_TuscanyNope
	case 5, Route29_EventScript_TuscanyNope
	case 6, Route29_EventScript_TuscanyNope
	case 7 Route29_EventScript_TuscanyCancel
	case MULTI_B_PRESSED, Route29_EventScript_TuscanyCancel
	closemessage
	release
	end
Route29_EventScript_TuscanyYes::
	msgbox Route29_Text_TuscanyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SILK_SCARF
	msgbox Route29_Text_TuscanyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyCancel::
	closemessage
	release
	end
Route29_EventScript_TuscanyCompleted::
	msgbox Route29_Text_TuscanyTuesday, MSGBOX_DEFAULT
	closemessage
	release
	end



Route29_EventScript_Girl::
	lock
	faceplayer
	msgbox Route29_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_NIGHT_POKEMON, Route29_EventScript_Boy2
	msgbox Route29_Text_Boy_WaitingForDay, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy2::
	msgbox Route29_Text_Boy_WaitingForNight, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Sign::
	lock
	msgbox Route29_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route29_EventScript_ItemPotion::
	finditem ITEM_POTION
	end

Route29_Text_OldMan1:
	.string "Los POKéMON se ocultan en el pasto.\n"
	.string "¿Quién sabe cuándo saldrán... $"

Route29_Text_OldMan2:
	.string "Te he visto un par de veces.\n"
	.string "¿Cuántos POKéMON has capturado?\p"
	.string "¿Quieres que te explique\n"
	.string "cómo capturar POKéMON?$"

Route29_Text_OldManExplanation:
	.string "Si los debilitas primero,\n"
	.string "los POKéMON son más fáciles.\p"
	.string "¡Luego lanza una BALL de\n"
	.string "tu mochila! Cualquier BALL sirve.\p"
	.string "Si quieres aprender más,\n"
	.string "¡ve a la ACADEMIA de CIUDAD MALVA!\p"
	.string "Los alumnos saben mucho\n"
	.string "sobre los POKéMON.$"

Route29_Text_OldManDeclined:
	.string "Oh. Está bien, entonces.\p"
	.string "Revisa cada ruta para hallar\n"
	.string "distintos tipos de POKéMON.\p"
	.string "¡Tu POKéDEX también muestra\n"
	.string "dónde encontrarlos!\p"
	.string "Si quieres aprender más,\n"
	.string "¡ve a la ACADEMIA de CIUDAD MALVA!\p"
	.string "Los alumnos saben mucho sobre\n"
	.string "los POKéMON.$"

Route29_Text_Youngster:
	.string "Hola. ¿Cómo están tus POKéMON?\p"
	.string "Si están débiles y no listos\n"
	.string "para luchar, evita el pasto.$"

Route29_Text_Lass:
	.string "¿Ves esos salientes?\n"
	.string "Da miedo saltar desde ahí.\p"
	.string "Pero puedes ir a PUEBLO PRIMAVERA\n"
	.string "sin caminar por el pasto.$"

Route29_Text_Girl:
	.string "Quería tomar un descanso,\n"
	.string "así que guardé mi progreso.$"

Route29_Text_Boy_WaitingForDay:
	.string "Espero POKéMON que aparecen\n"
	.string "solo más tarde en el día.$"

Route29_Text_Boy_WaitingForNight:
	.string "Espero POKéMON que aparecen\n"
	.string "solo por la noche.$"

Route29_Text_MeetTuscany:
	.string "TUSCANY: Creo que es la primera\n"
	.string "vez que nos vemos, ¿verdad?\p"
	.string "Soy TUSCANY de la FAMILIA DÍA.\p"
	.string "Si adivinas mi día favorito,\n"
	.string "te daré una recompensa.$"

Route29_Text_TuscanyNope:
	.string "¡Casi, pero no!$"

Route29_Text_TuscanyGivesGift:
	.string "¡Sí! Para presentarnos,\n"
	.string "acepta este regalo, un PAÑUELO\l"
	.string "DE SEDA.$"

Route29_Text_TuscanyGaveGift:
	.string "TUSCANY: ¿No crees que es\n"
	.string "muy adorable?\p"
	.string "Potencia los movimientos\n"
	.string "tipo NORMAL.\p"
	.string "Seguro que te será útil.$"

Route29_Text_TuscanyTuesday:
	.string "TUSCANY: ¿Conoces a MONICA,\n"
	.string "mi hermana mayor?\p"
	.string "¿O a mi hermano WESLEY?\p"
	.string "Soy el tercero de siete\n"
	.string "hijos.$"

Route29_Text_Sign1:
	.string "RUTA 29\p"
	.string "CIUDAD CEREZO - PUEBLO PRIMAVERA$"

