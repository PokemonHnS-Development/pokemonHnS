GoldenrodCity_BillsHouse_MapScripts::
	.byte 0

GoldenrodCity_BillsHouse_EventScript_Sister::
	lock
	faceplayer
	msgbox BillHouse_Text_SisterStorageSystem, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_SYS_PC_BILL, GoldenrodCity_BillsHouse_EventScript_Mom2
	msgbox BillHouse_Text_MomBeforeEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom2::
	msgbox BillHouse_Text_MomAfterEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Bill::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_EEVEE, GoldenrodCity_BillsHouse_EventScript_Bill_Eevee
	msgbox BillHouse_Text_PopWontWork, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Bill_Eevee::
	msgbox BillHouse_Text_TakeThisEevee, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_BillsHouse_EventScript_Bill_Refused
	msgbox BillHouse_Text_CountingOnYou, MSGBOX_DEFAULT

	@HnS named gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EEVEE
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE
	givenamedmon 3
	call Common_EventScript_GiftMonNamed

    

	setflag FLAG_GOT_EEVEE
	msgbox BillHouse_Text_EeveeMayEvolve, MSGBOX_DEFAULT
	closemessage
	release
	end


GoldenrodCity_BillsHouse_EventScript_Bill_Refused::
	msgbox BillHouse_Text_NoEevee, MSGBOX_DEFAULT
	closemessage
	release
	end

BillHouse_Text_TakeThisEevee:
    .string "BILL: ¡Hola, {PLAYER}! Hazme un favor\n"
    .string "y llévate a este EEVEE.\p"
    .string "Lo dejaron a mi cargo mientras\n"
    .string "trabajaba en mi sistema.\p"
    .string "Alguien debe cuidarlo, pero no me\n"
    .string "gusta estar al aire libre.\p"
    .string "¿Puedo contar contigo para jugar\n"
    .string "con él, {PLAYER}?$"

BillHouse_Text_CountingOnYou:
    .string "BILL: ¡Sabía que lo lograrías!\p"
    .string "¡Así se hace! ¡Eres el mejor!\p"
    .string "Bien, cuento contigo.\p"
    .string "¡Cuídalo mucho!$"

BillHouse_Text_ReceivedEevee:
    .string "¡{PLAYER} recibió a EEVEE!$"

BillHouse_Text_EeveeMayEvolve:
    .string "BILL: El PROF.ELM dice que EEVEE\n"
    .string "puede evolucionar de formas nuevas.$"

BillHouse_Text_PartyFull:
    .string "Espera. No puedes llevar más\n"
    .string "POKéMON contigo.$"

BillHouse_Text_NoEevee:
    .string "Oh... ¿Y ahora qué hago?$"

BillHouse_Text_PopWontWork:
    .string "BILL: Mi padre no trabaja. Solo\n"
    .string "se pasa el día perdiendo el tiempo.\p"
    .string "Se está volviendo un dolor de cabeza…$"

BillHouse_Text_MomBeforeEcruteak:
    .string "¿Coleccionas POKéMON? Mi hijo\n"
    .string "BILL es un experto.\p"
    .string "Lo llamaron al CENTRO POKéMON\n"
    .string "de CIUDAD IRIS.\p"
    .string "Mi esposo se fue al GAME CORNER\n"
    .string "sin que nadie lo llamara…$"

BillHouse_Text_MomAfterEcruteak:
    .string "Mi esposo fue conocido alguna vez\n"
    .string "como POKéMANIAC.\p"
    .string "BILL debió salir a su\n"
    .string "padre.$"

BillHouse_Text_SisterUsefulNumber:
    .string "¿Eres un ENTRENADOR?\p"
    .string "Tengo un número de teléfono\n"
    .string "útil para ti.$"

BillHouse_Text_RecordedBillsNumber:
    .string "{PLAYER} registró el número de BILL.$"

BillHouse_Text_SisterRefusedNumber:
    .string "Mi hermano creó el sistema de\n"
    .string "almacén POKéMON.\p"
    .string "Iba a darte el número de\n"
    .string "BILL…$"

BillHouse_Text_SisterPhoneFull:
    .string "No puedes registrar más números.$"

BillHouse_Text_SisterStorageSystem:
    .string "Mi hermano BILL creó el sistema de\n"
    .string "almacén PC POKéMON.$"
