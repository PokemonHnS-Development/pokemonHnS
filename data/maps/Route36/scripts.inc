.set LOCALID_ROUTE36_SUDOWOODO, 6
.set LOCALID_ROUTE36_ROCKSMASHGUY, 3

Route36_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route36_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route36_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route36_EventScript_RockSmashGuy::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, Route36_EventScript_RockSmashGuy2
	msgbox Route36_Text_RockSmashGuy1, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_RockSmashGuy2::
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, Route36_EventScript_RockSmashGuy3
	msgbox Route36_Text_RockSmashGuy2, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
Route36_EventScript_RockSmashGuy3::
	msgbox Route36_Text_RockSmashGuy3
	closemessage
	release
	end

Route36_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, Route36_EventScript_Lass2
	msgbox Route36_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_Lass2::
	msgbox Route36_Text_Lass2_ClearedSudowoodo, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_Arthur::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HARD_STONE, Route36_EventScript_ArthurCompleted
	msgbox Route36_Text_MeetArthur, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route36_EventScript_ArthurNope
	case 1, Route36_EventScript_ArthurNope
	case 2, Route36_EventScript_ArthurNope
	case 3, Route36_EventScript_ArthurNope
	case 4, Route36_EventScript_ArthurYes
	case 5, Route36_EventScript_ArthurNope
	case 6, Route36_EventScript_ArthurNope
	case 7, Route36_EventScript_ArthurCancel
	case MULTI_B_PRESSED, Route36_EventScript_ArthurCancel
	closemessage
	release
	end
Route36_EventScript_ArthurYes::
	msgbox Route36_Text_ArthurGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_HARD_STONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_HARD_STONE
	msgbox Route36_Text_ArthurGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_ArthurNope::
	msgbox Route36_Text_ArthurNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_ArthurCancel::
	closemessage
	release
	end
Route36_EventScript_ArthurCompleted::
	msgbox Route36_Text_ArthurThursday, MSGBOX_DEFAULT
	closemessage
	release
	end


Route36_EventScript_SudoWoodo::
	lock
	msgbox Route36_Text_OddTree, MSGBOX_DEFAULT
	checkitem ITEM_SQUIRT_BOTTLE
	goto_if_eq VAR_RESULT, TRUE, Route36_EventScript_SudoWoodoChoice
	closemessage
	release
	end
Route36_EventScript_SudoWoodoChoice::
	msgbox Route36_Text_UseSquirtbottle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route36_EventScript_SudoWoodoWater
	closemessage
	release
	end
Route36_EventScript_SudoWoodoWater::
	msgbox Route36_Text_UsedSquirtbottle, MSGBOX_DEFAULT
	playse SE_DOWNPOUR
	waitse
	closemessage
	playse SE_SUDOWOODO_SHAKE	
	applymovement LOCALID_ROUTE36_SUDOWOODO, Route36_Movement_SudoWoodo
	waitmovement 0
	faceplayer
	msgbox Route36_Text_SudowoodoAttacked	
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_ROUTE36_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 20
	@setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	@clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route36_EventScript_Defeated_Sudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route36_EventScript_RanSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route36_EventScript_RanSudowoodo
Route36_EventScript_Defeated_Sudowoodo::
	setflag FLAG_HIDE_SUDOWOODO
	removeobject LOCALID_ROUTE36_SUDOWOODO
	checkitem ITEM_HM_ROCK_SMASH
	call_if_eq VAR_RESULT, FALSE, Route36_EventScript_RockSmashGuySudoWoodo
	release
	end

Route36_EventScript_RanSudowoodo::
	turnobject LOCALID_ROUTE36_SUDOWOODO, DIR_NORTH
	release
	end

Route36_EventScript_RockSmashGuySudoWoodo:
	playse SE_PIN
	applymovement LOCALID_ROUTE36_ROCKSMASHGUY, Common_Movement_ExclamationMark
	turnobject LOCALID_ROUTE36_ROCKSMASHGUY, DIR_WEST
	waitmovement 0
	applymovement LOCALID_ROUTE36_ROCKSMASHGUY, Route36_Movement_RockSmashGuy
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitmovement 0
	return

Route36_Movement_RockSmashGuy:
	jump_in_place_left
	delay_2
	jump_in_place_left
	delay_2
	jump_in_place_left
	delay_2
	jump_in_place_left
	step_end

Route36_EventScript_Mark::
	trainerbattle_single TRAINER_MARK Route36_Text_PsychicMarkSeen, Route36_Text_PsychicMarkBeaten
	msgbox Route36_Text_PsychicMarkAfter, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_Schoolboy::
	trainerbattle_single TRAINER_ALAN Route36_Text_SchoolboyAlan1Seen, Route36_Text_SchoolboyAlan1Beaten
	msgbox Route36_Text_SchoolboyAlanAfter, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_Sign::
	lock
	msgbox Route36_Text_Sign_RuinsNorth, MSGBOX_SIGN
	closemessage
	release
	end

Route36_EventScript_Sign2::
	lock
	msgbox Route36_Text_Tips1, MSGBOX_SIGN
	closemessage
	release
	end

Route36_Movement_SudoWoodo:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

Route36_Text_UseSquirtbottle:
	.string "¿Usar SQUIRTBOTTLE?$"

Route36_Text_UsedSquirtbottle:
	.string "{PLAYER} usó SQUIRTBOTTLE.$"

Route36_Text_SudowoodoAttacked:
	.string "¡Al árbol raro no le gusta el\n"
	.string "SQUIRTBOTTLE!\p"
	.string "¡El árbol raro atacó!$"

Route36_Text_RockSmashGuy1:
	.string "¡Wa-hey!\p"
	.string "Iba a romper ese árbol con un\n"
	.string "golpe directo de brazo.\p"
	.string "¡Pero no pude! ¡Soy un fracaso!$"

Route36_Text_RockSmashGuy2:
	.string "¿Quitaste ese árbol maldito?\p"
	.string "¡Estoy impresionado!\n"
	.string "Quiero que tengas esto.$"

Route36_Text_RockSmashGuy3:
	.string "Resulta que es ROCK SMASH.\p"
	.string "Puedes romper rocas con un solo\n"
	.string "golpe bien dirigido.\p"
	.string "Si hay rocas en tu camino,\n"
	.string "¡solo destrúyelas!$"

Route36_Text_OddTree:
	.string "Un árbol raro bloquea el camino.$"

Route36_Text_Lass1:
	.string "¡Cuidado de noche en esta ruta!\p"
	.string "Vi un POKéMON parecido a\n"
	.string "GROWLITHE, pero tenía un aura\l"
	.string "aterradora.$"

Route36_Text_Lass2_ClearedSudowoodo:
	.string "Ese árbol raro desapareció sin\n"
	.string "rastro.\p"
	.string "¡Oh! ¿Ese árbol era en realidad un\n"
	.string "POKéMON?$"

Route36_Text_PsychicMarkSeen:
	.string "¡Voy a leer tus pensamientos!$"

Route36_Text_PsychicMarkBeaten:
	.string "¡Te leí mal!$"

Route36_Text_PsychicMarkAfter:
	.string "Sería fuerte si pudiera saber\n"
	.string "qué piensa mi oponente.$"

Route36_Text_SchoolboyAlan1Seen:
	.string "¡Gracias a mis estudios, estoy\n"
	.string "listo para cualquier POKéMON!$"

Route36_Text_SchoolboyAlan1Beaten:
	.string "¡Ups! ¿Error de cálculo?$"

Route36_Text_SchoolboyAlanAfter:
	.string "Rayos. Yo estudio cinco horas al día.\p"
	.string "Aprender es más que solo\n"
	.string "leer libros.$"

Route36_Text_MeetArthur:
	.string "ARTHUR: ¿Quién eres?\n"
	.string "Soy ARTHUR de la FAMILIA DEL DÍA.\p"
	.string "Si adivinas mi día favorito,\n"
	.string "te daré una recompensa.$"

Route36_Text_ArthurNope:
	.string "¡Casi, pero no!$"

Route36_Text_ArthurGivesGift:
	.string "Toma. Quédate con esto.$"

Route36_Text_ArthurGaveGift:
	.string "ARTHUR: Un POKéMON de tipo ROCA\n"
	.string "debería llevar eso equipado.\p"
	.string "Potencia los ataques de ROCA.$"

Route36_Text_ArthurThursday:
	.string "ARTHUR: Soy ARTHUR, el de jueves.\n"
	.string "Soy el quinto de siete hijos.$"

Route36_Text_Sign:
	.string "RUTA 36$"

Route36_Text_Sign_RuinsNorth:
	.string "RUINAS ALFA\n"
	.string "ENTRADA NORTE$"

Route36_Text_Tips1:
	.string "CONSEJOS\n"
	.string "Las stats varían, incluso en la\l"
	.string "misma especie.\p"
	.string "Al inicio pueden ser similares.\p"
	.string "Pero las diferencias crecen al\n"
	.string "subir de nivel el POKéMON.$"

Route36_Text_Tips2:
	.string "CONSEJOS\n"
	.string "Usa DIG para volver a la entrada\n"
	.string "de cualquier lugar.\p"
	.string "Es útil para explorar cuevas\n"
	.string "y otros sitios.$"
