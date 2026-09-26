.set LOCALID_SPROUT_TOWER_SILVER, 5

SproutTower_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SproutTower_3F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

SproutTower_3F_OnTransition: 
	callnative SetTimeBasedEncounters
	end


SproutTower_3F_EventScript_SageJin::
	trainerbattle_single TRAINER_JIN SproutTower_Text_SageJin_Seen, SproutTower_Text_SageJin_Beaten
	msgbox SproutTower_Text_SageJin_AfterBattle, MSGBOX_AUTOCLOSE
	end


SproutTower_3F_EventScript_SageNeal::
	trainerbattle_single TRAINER_NEAL SproutTower_Text_SageNeal_Seen, SproutTower_Text_SageNeal_Beaten
	msgbox SproutTower_Text_SageNeal_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_SageTroy::
	trainerbattle_single TRAINER_TROY SproutTower_Text_SageTroy_Seen, SproutTower_Text_SageTroy_Beaten
	msgbox SproutTower_Text_SageTroy_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_Painting::
	lock
	msgbox SproutTower_Text_3F_Painting, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_3F_EventScript_Potion::
	finditem ITEM_POTION
	end

SproutTower_3F_EventScript_EscapeRope::
	finditem ITEM_ESCAPE_ROPE
	end

SproutTower_3F_EventScript_TriggerSceneLeft::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_Silver1
	waitmovement 0
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SPROUT_TOWER_SILVER, Common_Movement_ExclamationMark	
	delay 60
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_SilverLeft
	waitmovement 0
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	delay 30
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement LOCALID_SPROUT_TOWER_SILVER SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_SPROUT_TOWER_SILVER
	removeobject LOCALID_SPROUT_TOWER_SILVER
	delay 55
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	fadedefaultbgm
	setvar VAR_SPROUT_TOWER, 1
	release
	end

SproutTower_3F_EventScript_TriggerSceneRight::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_Silver1
	waitmovement 0
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SPROUT_TOWER_SILVER, Common_Movement_ExclamationMark	
	delay 60
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_SilverRight
	waitmovement 0
	waitmovement 0
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement LOCALID_SPROUT_TOWER_SILVER SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_SPROUT_TOWER_SILVER
	removeobject LOCALID_SPROUT_TOWER_SILVER
	delay 55
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	fadedefaultbgm
	setvar VAR_SPROUT_TOWER, 1
	release
	end

SproutTower_3F_EventScript_SageLi::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, SproutTower_3F_EventScript_SageLi_Beaten
	msgbox SproutTower_Text_SageLi_Seen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_LI, SproutTower_Text_SageLi_Beaten
	msgbox SproutTower_Text_SageLi_TakeFlash, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox SproutTower_Text_SageLi_FlashExplain, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_EventScript_SageLi_Beaten::
	msgbox SproutTower_Text_SageLi_AfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_Movement_Silver1:
	walk_fast_up
	walk_fast_up
	step_end

SproutTower_3F_Movement_SilverLeft:
	face_down
	delay_16
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_SilverRight:
	face_down
	delay_16
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_EscapeRope:
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	step_end

SproutTower_Text_ElderLecturesRival:
	.string "ANCIANO: Eres muy hábil\n"
	.string "como entrenador.\p"
	.string "Como prometí, aquí tienes la MO.\p"
	.string "Pero déjame decirte: debes\n"
	.string "tratar mejor a tus POKéMON.\p"
	.string "Tu forma de luchar es demasiado\n"
	.string "dura.\p"
	.string "Los POKéMON no son armas...$"

SproutTower_Text_RivalOnlyCaresStrong:
	.string "…\n"
	.string "…¡Bah!\p"
	.string "Dice ser el ANCIANO, pero\n"
	.string "es débil.\p"
	.string "Tiene sentido.\p"
	.string "Jamás perdería ante tontos que\n"
	.string "hablan de ser buenos con POKéMON.\p"
	.string "Solo me importan los POKéMON\n"
	.string "fuertes que pueden ganar.\p"
	.string "No me importan en absoluto\n"
	.string "los POKéMON débiles.$"

SproutTower_Text_RivalUsedEscapeRope:
	.string "¡{RIVAL} usó CUERDA ESCAPE!$"

SproutTower_Text_SageLi_Seen:
	.string "¡Qué bueno que hayas venido!\p"
	.string "La TORRE VERDOR es un lugar de\n"
	.string "entrenamiento.\p"
	.string "Gente y POKéMON prueban sus\n"
	.string "lazos para crear un futuro juntos\l"
	.string "y brillante.\p"
	.string "Yo soy la prueba final.\p"
	.string "¡Permíteme revisar el vínculo\n"
	.string "entre tus POKéMON y tú!$"

SproutTower_Text_SageLi_Beaten:
	.string "¡Ah, excelente!$"

SproutTower_Text_SageLi_TakeFlash:
	.string "Tú y tus POKéMON no tendrán\n"
	.string "problemas usando este movimiento.\p"
	.string "Toma esta MO FLASH.$"

SproutTower_Text_SageLi_FlashExplain:
	.string "FLASH ilumina hasta el lugar\n"
	.string "más oscuro de todos.\p"
	.string "Para usarlo fuera de combate,\n"
	.string "necesitas la MEDALLA de MALVA.$"

SproutTower_Text_SageLi_AfterBattle:
	.string "Espero que aprendas y crezcas\n"
	.string "en tu viaje.$"

SproutTower_Text_SageJin_Seen:
	.string "Entreno para hallar la iluminación\n"
	.string "¡en los POKéMON!$"

SproutTower_Text_SageJin_Beaten:
	.string "Mi entrenamiento está incompleto…$"

SproutTower_Text_SageJin_AfterBattle:
	.string "Al hacerse fuertes los POKéMON,\n"
	.string "el ENTRENADOR también.\p"
	.string "No, espera. Al hacerse fuerte\n"
	.string "el ENTRENADOR, también lo hacen\l"
	.string "los POKéMON.$"

SproutTower_Text_SageTroy_Seen:
	.string "Déjame ver cuánto confías en\n"
	.string "tus POKéMON.$"

SproutTower_Text_SageTroy_Beaten:
	.string "¡Sí, tu confianza es real!$"

SproutTower_Text_SageTroy_AfterBattle:
	.string "No está lejos del ANCIANO.$"

SproutTower_Text_SageNeal_Seen:
	.string "La MO de ELDER ilumina hasta\n"
	.string "la oscuridad total.$"

SproutTower_Text_SageNeal_Beaten:
	.string "¡Mi cabeza es la que brilla!$"

SproutTower_Text_SageNeal_AfterBattle:
	.string "Que haya luz en tu\n"
	.string "viaje.$"

SproutTower_Text_3F_Painting:
	.string "Es una pintura poderosa de un\n"
	.string "BELLSPROUT.$"
