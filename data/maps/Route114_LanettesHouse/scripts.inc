Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_BillS_HOUSE
	end

Route114_LanettesHouse_EventScript_Bill::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_Bill, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_BILL
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_Bill
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "Bill: ¡Oh! {PLAYER}{KUN}!\p"
	.string "Siento que todo esté tan desordenado…\n"
	.string "Cuando me concentro en investigar,\l"
	.string "las cosas quedan así…\p"
	.string "Es vergonzoso… Por favor, guarda\n"
	.string "el secreto a cambio de esto.$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "¿Quieres consejos sobre mi sistema\n"
	.string "de almacenamiento de POKéMON?\p"
	.string "Organiza tus BOXES para saber\n"
	.string "qué POKéMON hay en cada una.$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "Son notas de BILL.\n"
	.string "Hay datos sobre las BOXES.\p"
	.string "BOXES para 30 POKéMON cada una.\p"
	.string "Cada TRAINER podrá guardar\n"
	.string "450 POKéMON en la PC.\p"
	.string "¿Seguir leyendo?$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "Se debe añadir un sistema de marcas\n"
	.string "para organizar mejor los POKéMON.\p"
	.string "El nombre y fondo de cada BOX\n"
	.string "serán editables para agradar a\l"
	.string "los POKéMON guardados.\p"
	.string "¿Seguir leyendo?$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "Al guardar un POKéMON, debe ir a la\n"
	.string "BOX revisada por última vez.\p"
	.string "Si esa BOX está llena, el POKéMON\n"
	.string "se guardará en la siguiente BOX.\p"
	.string "O sea, al revisar una BOX, esta se\n"
	.string "selecciona automáticamente como la BOX\l"
	.string "donde se enviarán los POKéMON.$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "{PLAYER} cerró el cuaderno.$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "Hay un e-mail de alguien en\n"
	.string "la PC.\p"
	.string "“… … … … … … …\p"
	.string "“Tu Sistema de Almacenaje es más\n"
	.string "cómodo que el mío.\p"
	.string "“Tiene funciones muy útiles\n"
	.string "que lo hacen divertido y práctico.\p"
	.string "“Me enorgullece haber ayudado\n"
	.string "en su desarrollo.\p"
	.string "“Espero que sigas investigando\n"
	.string "los Sistemas de Almacenaje.\p"
	.string "“De BILL\n"
	.string "… … … … … … … …”$"

