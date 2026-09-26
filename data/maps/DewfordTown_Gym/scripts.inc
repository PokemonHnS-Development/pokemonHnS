DewfordTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_Gym_OnTransition
	.byte 0

DewfordTown_Gym_OnTransition:
	call DewfordTown_Gym_EventScript_SetFlashLevel
	end

DewfordTown_Gym_EventScript_SetFlashLevel::
	goto_if_defeated TRAINER_DICK, DewfordTown_Gym_EventScript_SetLightsOn
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 0, DewfordTown_Gym_EventScript_SetFlashLevel7
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_SetFlashLevel6
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_SetFlashLevel5
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_SetFlashLevel4
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_SetFlashLevel3
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_SetFlashLevel2
	goto DewfordTown_Gym_EventScript_SetFlashLevel1

DewfordTown_Gym_EventScript_SetLightsOn::
	setflashlevel 0
	return

@ Brightest
DewfordTown_Gym_EventScript_SetFlashLevel1::
	setflashlevel 1
	return

DewfordTown_Gym_EventScript_SetFlashLevel2::
	setflashlevel 2
	return

DewfordTown_Gym_EventScript_SetFlashLevel3::
	setflashlevel 3
	return

DewfordTown_Gym_EventScript_SetFlashLevel4::
	setflashlevel 4
	return

DewfordTown_Gym_EventScript_SetFlashLevel5::
	setflashlevel 5
	return

DewfordTown_Gym_EventScript_SetFlashLevel6::
	setflashlevel 6
	return

@ Darkest
DewfordTown_Gym_EventScript_SetFlashLevel7::
	setflashlevel 7
	return

DewfordTown_Gym_EventScript_BrightenRoom::
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	nop1
	goto_if_eq VAR_0x8000, VAR_0x8001, DewfordTown_Gym_EventScript_NoLightChange
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_AnimateFlash1Trainer
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_AnimateFlash2Trainers
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_AnimateFlash3Trainers
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_AnimateFlash4Trainers
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_AnimateFlash5Trainers
	goto_if_eq VAR_0x8000, 6, DewfordTown_Gym_EventScript_AnimateFlash6Trainers

DewfordTown_Gym_EventScript_NoLightChange::
	return

@ NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius
DewfordTown_Gym_EventScript_AnimateFlash1Trainer::
	playse SE_SWITCH
	animateflash 6
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash2Trainers::
	playse SE_SWITCH
	animateflash 5
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash3Trainers::
	playse SE_SWITCH
	animateflash 4
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash4Trainers::
	playse SE_SWITCH
	animateflash 3
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash5Trainers::
	playse SE_SWITCH
	animateflash 2
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash6Trainers::
	playse SE_SWITCH
	animateflash 1
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlashFullBrightness::
	playse SE_SWITCH
	animateflash 0
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_CountTrainersDefeated::
	setvar VAR_0x8000, 0
	goto_if_not_defeated TRAINER_TAKAO, DewfordTown_Gym_EventScript_CheckJocelyn
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckJocelyn::
	goto_if_not_defeated TRAINER_JOCELYN, DewfordTown_Gym_EventScript_CheckLaura
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLaura::
	goto_if_not_defeated TRAINER_LAURA, DewfordTown_Gym_EventScript_CheckBrenden
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckBrenden::
	goto_if_not_defeated TRAINER_BRENDEN, DewfordTown_Gym_EventScript_CheckCristian
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckCristian::
	goto_if_not_defeated TRAINER_HARVEY, DewfordTown_Gym_EventScript_CheckLilith
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLilith::
	goto_if_not_defeated TRAINER_LILITH, DewfordTown_Gym_EventScript_StopCountingTrainers
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_StopCountingTrainers::
	return

DewfordTown_Gym_EventScript_Brawly::
	trainerbattle_single TRAINER_DICK, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_BrawlyRematch
	goto_if_unset FLAG_RECEIVED_TM_BULK_UP, DewfordTown_Gym_EventScript_GiveBulkUp2
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_BrawlyDefeated::
	call DewfordTown_Gym_EventScript_AnimateFlashFullBrightness
	message DewfordTown_Gym_Text_ReceivedKnuckleBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_AZALEA_TOWN_GYM
	setflag FLAG_BADGE02_GET
	addvar VAR_GARBAGEVAR, 1
	call_if_eq VAR_GARBAGEVAR, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers
	call DewfordTown_Gym_EventScript_GiveBulkUp
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox DewfordTown_Gym_Text_RegisteredBrawly, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_BRAWLY_MATCH_CALL
	setvar VAR_ROXANNE_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	release
	end

DewfordTown_Gym_EventScript_GiveBulkUp::
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_BagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	return

DewfordTown_Gym_EventScript_GiveBulkUp2:
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	release
	end

DewfordTown_Gym_EventScript_BrawlyRematch::
	trainerbattle_rematch_double TRAINER_DICK, DewfordTown_Gym_Text_BrawlyPreRematch, DewfordTown_Gym_Text_BrawlyRematchDefeat, DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons
	msgbox DewfordTown_Gym_Text_BrawlyPostRematch, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_Takao::
	trainerbattle_single TRAINER_TAKAO, DewfordTown_Gym_Text_TakaoIntro, DewfordTown_Gym_Text_TakaoDefeat, DewfordTown_Gym_EventScript_TakaoBrightenRoom
	msgbox DewfordTown_Gym_Text_TakaoPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_TakaoBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Jocelyn::
	trainerbattle_single TRAINER_JOCELYN, DewfordTown_Gym_Text_JocelynIntro, DewfordTown_Gym_Text_JocelynDefeat, DewfordTown_Gym_EventScript_JocelynBrightenRoom
	msgbox DewfordTown_Gym_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_JocelynBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Laura::
	trainerbattle_single TRAINER_LAURA, DewfordTown_Gym_Text_LauraIntro, DewfordTown_Gym_Text_LauraDefeat, DewfordTown_Gym_EventScript_LauraBrightenRoom
	msgbox DewfordTown_Gym_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LauraBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Brenden::
	trainerbattle_single TRAINER_BRENDEN, DewfordTown_Gym_Text_BrendenIntro, DewfordTown_Gym_Text_BrendenDefeat, DewfordTown_Gym_EventScript_BrendenBrightenRoom
	msgbox DewfordTown_Gym_Text_BrendenPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_BrendenBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Cristian::
	trainerbattle_single TRAINER_HARVEY, DewfordTown_Gym_Text_CristianIntro, DewfordTown_Gym_Text_CristianDefeat, DewfordTown_Gym_EventScript_CristianBrightenRoom
	msgbox DewfordTown_Gym_Text_CristianPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_CristianBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Lilith::
	trainerbattle_single TRAINER_LILITH, DewfordTown_Gym_Text_LilithIntro, DewfordTown_Gym_Text_LilithDefeat, DewfordTown_Gym_EventScript_LilithBrightenRoom
	msgbox DewfordTown_Gym_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LilithBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_AZALEA_TOWN_GYM, DewfordTown_Gym_EventScript_GymGuidePostVictory
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_GymGuidePostVictory::
	msgbox DewfordTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_GymStatueCertified::
	msgbox DewfordTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_EventScript_GymStatue::
	msgbox DewfordTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_Text_GymGuideAdvice:
	.string "Hola, ¿cómo va todo, futuro\n"
	.string "CAMPEÓN {PLAYER}?\p"
	.string "BRAWLY, LÍDER del GIMNASIO de\n"
	.string "DEWFORD, usa POKéMON LUCHA.\p"
	.string "Ir contra él con POKéMON tipo\n"
	.string "NORMAL es buscar problemas.\p"
	.string "Los POKéMON LUCHA darán un golpe\n"
	.string "duro a los POKéMON NORMAL,\l"
	.string "¡así que ten cuidado!\p"
	.string "Peor aún, el GIMNASIO es tan oscuro\n"
	.string "como el fondo del mar.\p"
	.string "Pero habrá más luz al vencer a los\n"
	.string "ENTRENADORES del camino.\p"
	.string "¡Muy bien, ve a por ello!$"

DewfordTown_Gym_Text_GymGuidePostVictory:
	.string "¡Vaya! ¡Ahora hay demasiada luz!\p"
	.string "¡Tu futuro también es brillante!$"

DewfordTown_Gym_Text_TakaoIntro:
	.string "¡La fuerza es la ley!\n"
	.string "¡Ven ya!$"

DewfordTown_Gym_Text_TakaoDefeat:
	.string "No tengo suficiente poder...$"

DewfordTown_Gym_Text_TakaoPostBattle:
	.string "¡Tu habilidad venció mi fuerza!\n"
	.string "¡Tu técnica es admirable!$"

DewfordTown_Gym_Text_JocelynIntro:
	.string "¡No hace falta que BRAWLY\n"
	.string "intervenga!\p"
	.string "¡Te aplastaré!$"

DewfordTown_Gym_Text_JocelynDefeat:
	.string "Pero... ¿cómo?\n"
	.string "¿Cómo pude perder tan fácil?$"

DewfordTown_Gym_Text_JocelynPostBattle:
	.string "No desperdiciaré esta derrota.\n"
	.string "¡Me motivará para entrenar más!\p"
	.string "Algún día seré LÍDER de GIMNASIO...\p"
	.string "¡No, seré el CAMPEÓN de la\n"
	.string "LIGA POKéMON!$"

DewfordTown_Gym_Text_LauraIntro:
	.string "¡No te atrevas a ignorarme!\n"
	.string "¡No es mi culpa si lloras!$"

DewfordTown_Gym_Text_LauraDefeat:
	.string "¡Buaaaaaaa!\n"
	.string "¡Perdí!$"

DewfordTown_Gym_Text_LauraPostBattle:
	.string "Lucho en la oscuridad para hacer mi\n"
	.string "corazón más fuerte.\p"
	.string "Pero como está tan oscuro, nunca\n"
	.string "veo la cara de BRAWLY…$"

DewfordTown_Gym_Text_LilithIntro:
	.string "Ufufu…\n"
	.string "¿Estás dando tumbos en la oscuridad?$"

DewfordTown_Gym_Text_LilithDefeat:
	.string "Oh, tú…\n"
	.string "¡No quiero conocerte!$"

DewfordTown_Gym_Text_LilithPostBattle:
	.string "¡Mereces seguir perdido y terminar\n"
	.string "de vuelta en la entrada!$"

DewfordTown_Gym_Text_BrendenIntro:
	.string "¡Te mostraré el valor de\n"
	.string "un marino!$"

DewfordTown_Gym_Text_BrendenDefeat:
	.string "¿Cómo pasó esto?\n"
	.string "¡No es propio de mí perder así!$"

DewfordTown_Gym_Text_BrendenPostBattle:
	.string "¡Oh, sí! Eres digno de ver a\n"
	.string "nuestro LÍDER de GIMNASIO.$"

DewfordTown_Gym_Text_CristianIntro:
	.string "Si quieres pasar, ¡tendrás que\n"
	.string "superarme a mí!$"

DewfordTown_Gym_Text_CristianDefeat:
	.string "¡Grrrr!\n"
	.string "¡Es demasiado fuerte!$"

DewfordTown_Gym_Text_CristianPostBattle:
	.string "¡Ganaste!\n"
	.string "¡Ve por esa MEDALLA!$"

DewfordTown_Gym_Text_BrawlyIntro:
	.string "¡Soy BRAWLY!\n"
	.string "¡LÍDER del GIMNASIO de DEWFORD!\p"
	.string "Me forjé en las olas bravas de aquí\n"
	.string "y me hice fuerte en la cueva\l"
	.string "más oscura!\p"
	.string "¿Así que quieres retarme?\n"
	.string "¡Veamos de qué estás hecho!$"

DewfordTown_Gym_Text_BrawlyDefeat:
	.string "¡Vaya, guau! ¡Hiciste un impacto\n"
	.string "mucho mayor de lo que esperaba!\p"
	.string "¡Me arrasaste!\p"
	.string "Está bien, me venciste.\n"
	.string "¡Toma esta MEDALLA de GIMNASIO!$"

DewfordTown_Gym_Text_ReceivedKnuckleBadge:
	.string "{PLAYER} recibió la MEDALLA NUDO\n"
	.string "de BRAWLY.$"

DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis:
	.string "La MEDALLA NUDO hace que los POKéMON\n"
	.string "hasta el nivel 30, incluso los de\l"
	.string "intercambio, te obedezcan.\p"
	.string "Además, podrás usar la MO\n"
	.string "FLASH fuera de combate.\p"
	.string "Si quieres, usa también esta\n"
	.string "MÁQUINA TÉCNICA.$"

DewfordTown_Gym_Text_ExplainBulkUp:
	.string "Esa MT08 contiene BULK UP.\p"
	.string "Sube los stats de ATAQUE\n"
	.string "y DEFENSA.\p"
	.string "… … … … … …$"

DewfordTown_Gym_Text_RegisteredBrawly:
	.string "LÍDER BRAWLY registrado\n"
	.string "en el POKéNAV.$"

DewfordTown_Gym_Text_BrawlyPostBattle:
	.string "¡Tu talento será una ola gigante\n"
	.string "que causará asombro entre los\l"
	.string "ENTRENADORES algún día!$"

DewfordTown_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE PUEBLO DEWFORD$"

DewfordTown_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE PUEBLO DEWFORD\p"
	.string "ENTRENADORES DE BRAWLY:\n"
	.string "{PLAYER}$"

DewfordTown_Gym_Text_BrawlyPreRematch:
	.string "BRAWLY: Una ola puede retroceder,\n"
	.string "pero siempre vuelve a la orilla.\p"
	.string "Una ola de talento como el tuyo...\n"
	.string "¡Sabía que volverías!\p"
	.string "¡Muéstrame cuánto más has\n"
	.string "crecido!$"

DewfordTown_Gym_Text_BrawlyRematchDefeat:
	.string "¡Guau!\n"
	.string "¡Me inundaste otra vez!$"

DewfordTown_Gym_Text_BrawlyPostRematch:
	.string "BRAWLY: Luchar es vasto y profundo.\n"
	.string "No se ve el fondo.\l"
	.string "¡Es como el mar de HOENN!$"

DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons:
	.string "BRAWLY: Una ola puede retroceder, pero\n"
	.string "siempre vuelve a la orilla.\p"
	.string "Una ola de talento como la tuya...\n"
	.string "¡Sabía que volverías!\p"
	.string "¿Oh? Solo tienes un POKéMON\n"
	.string "que puede luchar.\p"
	.string "Lo siento, pero vuelve con al menos\n"
	.string "dos POKéMON.$"
