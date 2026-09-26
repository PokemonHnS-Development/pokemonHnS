.set LOCALID_BLACKTHORN_SAGE, 7
.set LOCALID_BLACKTHORN_BOY, 2

BlackthornCity_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BlackthornCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, BlackthornCity_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

BlackthornCity_OnLoad::
	goto_if_unset FLAG_BADGE05_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset FLAG_BADGE06_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset FLAG_BADGE07_GET, BlackThornCity_EventScript_MoveGymBoy
	end

BlackThornCity_EventScript_MoveGymBoy::
	setobjectxyperm LOCALID_BLACKTHORN_BOY, 24, 27
	end

BlackthornCity_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 4, BlackthornCity_EventScript_Call
	.2byte 0

BlackthornCity_EventScript_CityEnter:: 
	setflag FLAG_VISITED_BLACKTHORN_CITY
	callnative SetTimeBasedEncounters
	end

BlackthornCity_EventScript_Call::
	lock
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar VAR_BLACKTHORN_CITY_STATE, 5
	setvar VAR_NEWBARKTOWN_LABSTATE, 7
	release
	end

BlackthornCity_Text_BaobaCall:
	.string "GUARDIA BAOBA: {PLAYER}!\p"
	.string "Soy el GUARDIA BAOBA.\p"
	.string "Llamo para decirte que\n"
	.string "¡la SAFARI ZONE se expandió!\p"
	.string "¡Ven a visitarnos!$"

BlackthornCity_Text_ElmCall:
	.string "PROF.ELM: ¿Hola, {PLAYER}?\p"
	.string "Tengo algo aquí para ti.\n"
	.string "¿Puedes pasar por mi LAB?\p"
	.string "¡Nos vemos luego!$"

BlackThornCity_EventScript_Sage::
	lock
	faceplayer
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_SageRefuse
	msgbox BlackthornGrampsGrantsEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_SageRefuse::
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_Trigger_Sage::
	lock
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_EAST
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER Common_Movement_WalkDown1
	waitmovement 0
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_SOUTH
	release
	end

BlackthornCity_EventScript_GymBoy::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset FLAG_BADGE06_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset FLAG_BADGE07_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_GymBoyBefore
	msgbox BlackthornCity_Text_ClairIsBeaten, MSGBOX_DEFAULT
	closemessage
	release
	end	

BlackThornCity_EventScript_GymBoyNotReady::
	msgbox BlackthornCity_Text_ClairNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_GymBoyBefore::
	msgbox BlackthornCity_Text_ClairIsIn, MSGBOX_DEFAULT
	closemessage
	release
	end	

BlackthornCity_EventScript_BlackBelt::
	msgbox BlackBeltText_VoicesInMyHead, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF::
	msgbox BlackthornCooltrainerF1Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_Youngster::
	msgbox BlackthornYoungsterText, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF2::
	msgbox BlackthornCooltrainerF2Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_CitySign::
	msgbox BlackthornCitySignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_GymSign::
	msgbox BlackthornGymSignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_MoveHouseSign::
	msgbox BlackthornCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

BlackthornCity_EventScript_DragonsDenSign::
	msgbox BlackthornCity_Text_DragonDenSign, MSGBOX_SIGN
	end

BlackthornCity_EventScript_Santos::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SPELL_TAG, BlackthornCity_EventScript_SantosCompleted
	msgbox BlackthornCity_MeetSantosText, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, BlackthornCity_EventScript_SantosNope
	case 1, BlackthornCity_EventScript_SantosNope
	case 2, BlackthornCity_EventScript_SantosNope
	case 3, BlackthornCity_EventScript_SantosNope
	case 4, BlackthornCity_EventScript_SantosNope
	case 5, BlackthornCity_EventScript_SantosNope
	case 6, BlackthornCity_EventScript_SantosYes
	case 7 BlackthornCity_EventScript_SantosCancel
	case MULTI_B_PRESSED, BlackthornCity_EventScript_SantosCancel
	closemessage
	release
	end
BlackthornCity_EventScript_SantosYes::
	msgbox BlackthornCity_SantosGivesGiftText, MSGBOX_DEFAULT
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SPELL_TAG
	msgbox BlackthornCity_SantosGaveGiftText, MSGBOX_DEFAULT
	closemessage
	release
	end
BlackthornCity_EventScript_SantosNope::
	msgbox BlackthornCity_SantosNopeText, MSGBOX_DEFAULT
	closemessage
	release
	end
BlackthornCity_EventScript_SantosCancel::
	closemessage
	release
	end
BlackthornCity_EventScript_SantosCompleted::
	msgbox BlackthornCity_SantosSaturdayText, MSGBOX_DEFAULT
	closemessage
	release
	end


BlackthornCity_Text_ClairNotReady:
	.string "CLAIR, nuestra LÍDER de GYM, ha\n"
	.string "seguido tu progreso.\p"
	.string "Pero solo lucha contra entrenadores\n"
	.string "que tengan 7 medallas.$"

BlackthornCity_Text_ClairIsIn:
	.string "CLAIR, nuestra LÍDER de GYM, te\n"
	.string "está esperando.\p"
	.string "Pero sería imposible que un\n"
	.string "entrenador común ganara.$"

BlackthornCity_Text_ClairIsBeaten:
	.string "¿Venciste a CLAIR?\p"
	.string "¡Es increíble!\p"
	.string "Nunca oí que perdiera contra\n"
	.string "alguien que no fuera LANCE.$"

BlackthornGrampsRefusesEntryText:
	.string "No. Solo entrenadores elegidos\n"
	.string "pueden entrenar aquí.\p"
	.string "Por favor, vete.$"

BlackthornGrampsGrantsEntryText:
	.string "Si CLAIR lo permite, su abuelo\n"
	.string "--nuestro MASTER-- también.\p"
	.string "Puedes entrar.$"

BlackBeltText_VoicesInMyHead:
	.string "¡Arooo! ¡Voces en mi cabeza!\p"
	.string "¿Eh? ¡Estoy oyendo mi radio!$"

BlackthornCooltrainerF1Text:
	.string "¿Vas a hacer que tu POKéMON\n"
	.string "recuerde algunos movimientos?$"

BlackthornYoungsterText:
	.string "Los maestros dragón vienen de la\n"
	.string "CIUDAD ENDRINO.$"

BlackthornCity_MeetSantosText:
	.string "SANTOS: …\p"
	.string "Soy SANTOS, de la familia semanal.\p"
	.string "Adivina quién soy.$"

BlackthornCity_SantosGivesGiftText:
	.string "Puedes quedarte con esto…$"

BlackthornCity_SantosGaveGiftText:
	.string "SANTOS: …\p"
	.string "ETIQUETA MÁGICA…\p"
	.string "Potencia ataques tipo FANTASMA…\p"
	.string "Te dará miedo…$"

BlackthornCity_SantosSaturdayText:
	.string "SANTOS: …\p"
	.string "Nos vemos otro sábado…\p"
	.string "Ya no tendré más regalos…$"

BlackthornCity_SantosNopeText:
	.string "SANTOS: No.$"

BlackthornCooltrainerF2Text:
	.string "¡Vaya, pasaste por la RUTA HIELO?\p"
	.string "¡Debes ser un ENTRENADOR experto!$"

BlackthornCitySignText:
	.string "CIUDAD ENDRINO\p"
	.string "Refugio tranquilo en la montaña$"

BlackthornGymSignText:
	.string "GIMNASIO POKéMON CIUDAD ENDRINO\n"
	.string "LÍDER: CLAIR\p"
	.string "Maestra de los POKéMON Dragón$"

BlackthornCity_Text_MoveDeletersHouseSign:
	.string "CASA DE LOS HERMANOS MOVE$"

BlackthornCity_Text_DragonDenSign:
	.string "CUEVA DRAGÓN ADELANTE$"

