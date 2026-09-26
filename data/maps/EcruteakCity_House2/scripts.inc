EcruteakCity_House2_MapScripts::
	.byte 0

Ecruteak_Text_ItemfinderAdventure:
	.string "Ah. ¿Estás de aventura con\n"
	.string "tus POKéMON?\p"
	.string "Bueno, ¿qué es una aventura sin\n"
	.string "buscar tesoros?\p"
	.string "¿Tengo razón o no?$"

Ecruteak_Text_ItemfinderTrueSpirit:
	.string "¡Bien! Entiendes el verdadero\n"
	.string "espíritu de la aventura.\p"
	.string "¡Me gusta! Toma esto.$"

Ecruteak_Text_ItemfinderExplanation:
	.string "Hay muchos objetos ocultos\n"
	.string "que no se ven a simple vista.\p"
	.string "Usa ITEMFINDER para ver si hay\n"
	.string "objetos cerca de ti.\p"
	.string "No muestra el lugar exacto,\n"
	.string "así que deberás buscar tú mismo.\p"
	.string "Ah, sí... oí que hay objetos en\n"
	.string "la TORRE QUEMADA de CIUDAD IRIS.$"

Ecruteak_Text_ItemfinderToEachHisOwn:
	.string "Oh... cada quien con lo suyo...$"

EcruteakCity_House2_EventScript_ItemFinderMan::
	lock
	faceplayer
	msgbox Ecruteak_Text_ItemFinderMan, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House2_EventScript_Book::
	lock
	msgbox Ecruteak_Text_HistoryBook, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_Book2
	closemessage
	release
	end

EcruteakCity_House2_EventScript_Book2::
	msgbox Ecruteak_Text_TwoTowers, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_Book3
	release
	end

EcruteakCity_House2_EventScript_Book3::
	msgbox Ecruteak_Text_ThreeMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Ecruteak_Text_ItemFinderMan::
	.string "CIUDAD IRIS es muy antigua.\n"
	.string "Muchas generaciones pasaron\l"
	.string "su historia en libros como estos.$"

Ecruteak_Text_HistoryBook:
	.string "HISTORIA DE CIUDAD IRIS\p"
	.string "¿Quieres leerlo?$"

Ecruteak_Text_TwoTowers:
	.string "En CIUDAD IRIS había dos torres.\p"
	.string "Cada torre era el nido de\n"
	.string "poderosos POKéMON voladores.\p"
	.string "Pero una de las torres se quemó\n"
	.string "por completo.\p"
	.string "No se ha visto a esos POKéMON\n"
	.string "desde entonces...\p"
	.string "¿Sigues leyendo?$"

Ecruteak_Text_ThreeMon:
	.string "CIUDAD IRIS también tuvo tres\n"
	.string "POKéMON que corrían por el pueblo.\p"
	.string "Dicen que nacieron del agua,\n"
	.string "el rayo y el fuego.\p"
	.string "Pero no pudieron contener su\n"
	.string "excesivo poder.\p"
	.string "Dicen que los tres corrieron\n"
	.string "como el viento hacia el campo.$"
