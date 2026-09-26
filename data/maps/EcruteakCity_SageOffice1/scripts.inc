.set LOCALID_SAGEOFFICE_SAGE, 3

EcruteakCity_SageOffice1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_SageOffice1_OnTransition
	.byte 0

EcruteakCity_SageOffice1_OnTransition::
	goto_if_set FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice1_EventScript_SageAside
	end

EcruteakCity_SageOffice1_EventScript_SageAside::
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	end

EcruteakCity_SageOffice1_EventScript_Sign::
	msgbox EcruteakCity_SageOffice1_Text_Sign, MSGBOX_SIGN
	end

EcruteakCity_SageOffice1_Text_Sign:
	.string "La campana de hojalata suena clara\n"
	.string "para quienes están bajo la torre.$"

EcruteakCity_SageOffice2_EventScript_SageA::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice2_EventScript_SageA4
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_SageOffice2_EventScript_SageA2
	msgbox EcruteakTinTowerEntrance_Text_SageNoBadge, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA2::
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell1, MSGBOX_DEFAULT
	waitmessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_SAGEOFFICE_SAGE, Common_Movement_ExclamationMark
	delay 60
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SAGEOFFICE_SAGE, EcruteakCity_SageOffice2_Movement_StandAside
	waitmovement 0
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	setflag FLAG_HIDE_TINTOWER_GUARD
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA3::
	msgbox EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA4::
	msgbox EcruteakTinTowerEntrance_Text_SageDone, MSGBOX_DEFAULT
	closemessage
	release
	end
	
EcruteakCity_SageOffice2_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 10, EcruteakCity_SageOffice2_EventScript_B2
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, EcruteakCity_SageOffice2_EventScript_B2
	msgbox EcruteakTinTowerEntrance_Text_WanderingSage, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_B2::
	msgbox EcruteakTinTowerEntrance_Text_WanderingSageClearBell, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageC::
	lock
	faceplayer
	msgbox EcruteakTinTowerEntrance_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_Movement_StandAside:
	walk_left
	face_down
	step_end

EcruteakTinTowerEntrance_Text_SageNoBadge:
	.string "La TORRE LATÓN es prohibida para\n"
	.string "indignos. Lo siento, pero debes\l"
	.string "irte.$"

EcruteakTinTowerEntrance_Text_SageWithBadge:
	.string "La TORRE LATÓN es prohibida sin la\n"
	.string "MEDALLA del GIMNASIO de CIUDAD IRIS.\p"
	.string "¡Ah!\p"
	.string "¡La MEDALLA de CIUDAD IRIS! Por\n"
	.string "favor, adelante.$"

EcruteakTinTowerEntrance_Text_SageNoClearBell:
	.string "Ha ocurrido un evento trascendental.\p"
	.string "Perdone, pero debo pedirle que\n"
	.string "se retire.\p"
	.string "...Lo que calma el alma...\p"
	.string "El TRÍO SABIO dice cosas muy\n"
	.string "difíciles de entender...$"

EcruteakTinTowerEntrance_Text_SageHearsClearBell1:
	.string "Ha ocurrido un evento trascendental.\p"
	.string "Perdone, pero debo pedirle que\n"
	.string "se retire.\p"
	.string "..............................$"
EcruteakTinTowerEntrance_Text_SageHearsClearBell2:
	.string "¡Ah!\p"
	.string "¡El sonido de esa CAMPANA CLARA!\p"
	.string "¡Es... es sublime!\p"
	.string "¡Nunca había oído un sonido tan\n"
	.string "hermoso!\p"
	.string "El toque de la campana indica el\n"
	.string "alma de quien la lleva.\p"
	.string "Tú...\p"
	.string "Tú podrías cruzar la\n"
	.string "TORRE LATÓN.\p"
	.string "Por favor, continúa.$"

EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn:
	.string "Por favor, continúa.$"

EcruteakTinTowerEntrance_Text_SageDone:
	.string "El toque de la campana indica el\n"
	.string "alma de quien la lleva.\p"
	.string "Tú...\n"
	.string "Realmente eres digno.$"

EcruteakTinTowerEntrance_Text_WanderingSage:
	.string "La TORRE LATÓN es una torre de\n"
	.string "nueve pisos de belleza divina.\p"
	.string "Calma el alma de todo aquel\n"
	.string "que la ve.$"

EcruteakTinTowerEntrance_Text_WanderingSageClearBell:
	.string "¡La TORRE LATÓN tembló! ¡Un POKéMON\n"
	.string "debe haber vuelto a la cima!$"

EcruteakTinTowerEntrance_Text_Gramps:
	.string "Dos torres... Dos POKéMON...\p"
	.string "Pero al arder una, ambos\n"
	.string "POKéMON volaron sin regresar.$"
