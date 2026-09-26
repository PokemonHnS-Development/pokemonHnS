.set LOCALID_WELL_KURT, 19

SlowpokeWell_B1F_MapScripts::
	.byte 0

SlowpokeWell_B1F_EventScript_Item_Super_Potion_1::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Super_Potion_2::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Great_Ball::
	finditem ITEM_GREAT_BALL
	end

SlowpokeWell_B1F_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

SlowpokeWell_B1F_EventScript_Kurt::
	lock
	msgbox SlowpokeWell_B1F_Text_KurtIntro, MSGBOX_DEFAULT
	closemessage
	end

SlowpokeWell_B1F_EventScript_Grunt21::
	trainerbattle_single TRAINER_GRUNT_21, SlowpokeWell_B1F_Text_GruntM29Seen, SlowpokeWell_B1F_Text_GruntM29Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM29After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Grunt22F::
	trainerbattle_single TRAINER_GRUNT_22, SlowpokeWell_B1F_Text_GruntF1Seen, SlowpokeWell_B1F_Text_GruntF1Beaten
	msgbox SlowpokeWell_B1F_Text_GruntF1After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Eto::
	trainerbattle_single TRAINER_ETO, SlowpokeWell_B1F_Text_GruntM2Seen, SlowpokeWell_B1F_Text_GruntM2Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM2After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Proton::
	lock
	faceplayer
	msgbox SlowpokeWell_B1F_Text_ProtonSeen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_PROTON_1, SlowpokeWell_B1F_Text_ProtonBeaten
	msgbox SlowpokeWell_B1F_Text_ProtonAfter, MSGBOX_AUTOCLOSE
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_AZALEA_TOWN_ROCKETS
	clearflag FLAG_HIDE_KURT_1
	addobject LOCALID_WELL_KURT
	removeobject 11
	removeobject 12
	removeobject 13
	delay 120
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_WELL_KURT, SlowpokeWell_B1F_Movement_Kurt
	waitmovement 0
	msgbox SlowpokeWell_B1F_Text_KurtAfter, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_SLOWPOKE_WELL_KURT
	setflag FLAG_HIDE_KURT_1
	clearflag FLAG_HIDE_KURT_2
	clearflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setvar VAR_AZALEA_TOWN_STATE, 3
	warp MAP_AZALEA_TOWN_KURTS_HOUSE, 15, 4
	release
	end

SlowpokeWell_B1F_Movement_Kurt:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SlowpokeWell_B1F_Text_KurtIntro:
	.string "KURT: ¡Hola, {PLAYER}!\p"
	.string "El guardia huyó cuando\n"
	.string "le grité.\p"
	.string "Pero luego caí por el\n"
	.string "POZO.\p"
	.string "Caí fuerte de espalda,\n"
	.string "así que no puedo moverme.\p"
	.string "¡Rayos! Si estuviera bien, mis\n"
	.string "POKéMON los castigarían...\p"
	.string "Ah, no hay nada que hacer.\p"
	.string "{PLAYER}, ¡demuéstrales tu valor\n"
	.string "en mi lugar!$"

SlowpokeWell_B1F_Text_KurtAfter:
	.string "KURT: ¡Bien hecho, {PLAYER}!\p"
	.string "El TEAM ROCKET ha huido.\p"
	.string "Mi espalda ya está mejor.\n"
	.string "Salgamos de aquí.$"

SlowpokeWell_B1F_Text_GruntM29Seen:
	.string "¡Maldición! Vigilaba arriba\n"
	.string "cuando un viejo me gritó\l"
	.string "de repente.\p"
	.string "Me asustó tanto que\n"
	.string "caí hasta aquí.\p"
	.string "¡Descargaré mi rabia\n"
	.string "contigo ahora mismo!$"

SlowpokeWell_B1F_Text_GruntM29Beaten:
	.string "¡Arrgh! ¡HOY NO ES MI DÍA!$"

SlowpokeWell_B1F_Text_GruntM29After:
	.string "Sí, les hemos cortado la\n"
	.string "cola a los SLOWPOKE para\l"
	.string "venderlas.\p"
	.string "Todo lo hacemos por dinero.\p"
	.string "¡Así es! ¡Somos el TEAM ROCKET\n"
	.string "y haremos lo que sea por dinero!$"

SlowpokeWell_B1F_Text_ProtonSeen:
	.string "¿Qué quieres?\p"
	.string "Si interrumpes nuestro trabajo,\n"
	.string "¡no esperes piedad!$"

SlowpokeWell_B1F_Text_ProtonBeaten:
	.string "Te fue bien hoy,\n"
	.string "¡pero espera a la próxima!$"

SlowpokeWell_B1F_Text_ProtonAfter:
	.string "Sí, el TEAM ROCKET fue disuelto\n"
	.string "hace tres años.\p"
	.string "El jefe se escondió.\p"
	.string "¡Pero seguimos activos\n"
	.string "en la clandestinidad!\p"
	.string "Un obstáculo como tú no será\n"
	.string "problema para nuestra misión.\p"
	.string "¡Te aconsejo que temas mucho\n"
	.string "lo que vendrá!$"

SlowpokeWell_B1F_Text_GruntM2Seen:
	.string "¡Je-je-je!\n"
	.string "¿Que dejemos de quitar COLAS\p"
	.string "de SLOWPOKE?\n"
	.string "¡Estás loco! Si te hiciéramos\l"
	.string "caso, ¡el TEAM ROCKET caería!$"

SlowpokeWell_B1F_Text_GruntM2Beaten:
	.string "Je...\n"
	.string "Demasiado fuerte...$"

SlowpokeWell_B1F_Text_GruntM2After:
	.string "Necesitamos el dinero,\n"
	.string "¿pero vender COLAS DE SLOWPOKE?\p"
	.string "¡Es duro ser un RECLUTA ROCKET!$"

SlowpokeWell_B1F_Text_GruntF1Seen:
	.string "¿Dejar de quitar COLAS?\p"
	.string "¡Sí, claro! ¡Intenta vencernos\n"
	.string "a todos primero!$"

SlowpokeWell_B1F_Text_GruntF1Beaten:
	.string "¡Maldito mocoso!$"

SlowpokeWell_B1F_Text_GruntF1After:
	.string "¡Las COLAS crecen rápido!\p"
	.string "¿Qué tiene de malo venderlas?$"

SlowpokeWell_B1F_Text_SlowpokeWithMail:
	.string "Un SLOWPOKE sin su COLA...\p"
	.string "¿Eh? Tiene una CARTA.\n"
	.string "¿La lees?$"

SlowpokeWell_B1F_Text_SlowpokeMail:
	.string "{PLAYER} leyó la CARTA.\p"
	.string "Sé bueno y cuida la casa con\n"
	.string "el abuelo y SLOWPOKE.\p"
	.string "Con amor, Papá$"

SlowpokeWell_B1F_Text_TaillessSlowpoke:
	.string "Un SLOWPOKE con la cola cortada…$"
