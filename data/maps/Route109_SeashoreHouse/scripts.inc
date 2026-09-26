Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
	giveitem ITEM_SODA_POP
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
	.string "Soy el dueño de la CASA COSTERA.\n"
	.string "¡Pero llámame SR. MAR!\p"
	.string "Lo que más amo es ver batallas de\n"
	.string "POKéMON intensas.\p"
	.string "¡Deja que vea que tu corazón arde!\p"
	.string "Si vences a todos los ENTRENADORES\n"
	.string "aquí, premiaré tu esfuerzo.$"

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
	.string "¡Muéstrame combates intensos!\p"
	.string "¡Manejo esta CASA COSTERA solo por\n"
	.string "esa razón!$"

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
	.string "¡Estás que ardes!\n"
	.string "¡Esas batallas fueron fuego!\l"
	.string "¡Estoy más que satisfecho!\p"
	.string "Por mostrarme tu racha ardiente,\n"
	.string "quiero que te lleves esto.\p"
	.string "¡Son seis botellas de REFRESCO!$"

Route109_SeashoreHouse_Text_BagFull:
	.string "Oh, pero tu MOCHILA está llena.\n"
	.string "Yo guardaré esto por ti.$"

Route109_SeashoreHouse_Text_WantToBuySodaPop:
	.string "¿Quieres comprar REFRESCO?\n"
	.string "¡A los POKéMON les encanta!\p"
	.string "¡Solo ¥300 la botella!\n"
	.string "¡Compra algunos!$"

Route109_SeashoreHouse_Text_HereYouGo:
	.string "¡Aquí tienes!$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
	.string "No tienes dinero.$"

Route109_SeashoreHouse_Text_ThatsTooBad:
	.string "¿No?\n"
	.string "Qué mal.$"

Route109_SeashoreHouse_Text_DwayneIntro:
	.string "Si buscas batalla en la\n"
	.string "CASA DE LA COSTA, ¡no hallarás un\l"
	.string "TRAINER más ardiente que yo!$"

Route109_SeashoreHouse_Text_DwayneDefeated:
	.string "¡Fue una batalla ardiente!\n"
	.string "¡Acepto mi derrota, amigo!$"

Route109_SeashoreHouse_Text_DwaynePostBattle:
	.string "Cuando estoy en PORTALUANA, disfruto\n"
	.string "batallas ardientes y SODAS frías!$"

Route109_SeashoreHouse_Text_JohannaIntro:
	.string "Las batallas aburridas no valen nada.\p"
	.string "¡Las batallas ardientes fortalecen a\n"
	.string "TRAINERS y POKéMON!$"

Route109_SeashoreHouse_Text_JohannaDefeated:
	.string "¡Eso estuvo ardiente!$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
	.string "Uff, tengo mucha sed.\n"
	.string "Tal vez tome una SODA.$"

Route109_SeashoreHouse_Text_SimonIntro:
	.string "Te mostraré lo geniales que son\n"
	.string "mis POKéMON, ¡así que no llores!$"

Route109_SeashoreHouse_Text_SimonDefeated:
	.string "...Perdí, pero no lloraré...$"

Route109_SeashoreHouse_Text_SimonPostBattle:
	.string "Si un POKéMON supiera el movimiento\n"
	.string "para llevarme sobre el agua en su\l"
	.string "lomo, no usaría este flotador.$"

