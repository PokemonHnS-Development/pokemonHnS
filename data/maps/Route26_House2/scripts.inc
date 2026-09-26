Route26_House2_MapScripts::
	.byte 0

Route26_House2_EventScript_Book::
	lock
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE,Route26_House2_EventScript_BookRead
	closemessage
	release
	end

Route26_House2_EventScript_BookRead::
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route26_House2_EventScript_BookRead2
	closemessage
	release
	end
	
Route26_House2_EventScript_BookRead2::
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex3, MSGBOX_DEFAULT
	closemessage
	release
	end

DayOfWeekSiblingsHouse_Text_Pokedex1:
    .string "Hay algo escrito aquí.\p"
    .string "¿Lo lees?$"

DayOfWeekSiblingsHouse_Text_Pokedex2:
    .string "A mis hermanos y hermanas:\p"
    .string "Nos enorgullece servir a los\n"
    .string "entrenadores POKéMON.\p"
    .string "Cuando hablen con ustedes, denles\n"
    .string "algo útil.\p"
    .string "Con amor,\n"
    .string "MONICA\p"
    .string "¿Seguir leyendo?$"

DayOfWeekSiblingsHouse_Text_Pokedex3:
    .string "Lunes, MONICA\n"
    .string "RUTA 40\p"
    .string "Martes, TUSCANY\n"
    .string "RUTA 29\p"
    .string "Miércoles, WESLEY\n"
    .string "LAGO DE LA FURIA\p"
    .string "Jueves, ARTHUR\n"
    .string "RUTA 36\p"
    .string "Viernes, FRIEDA\n"
    .string "RUTA 32\p"
    .string "Sábado, SANTOS\n"
    .string "CIUDAD ENDRINO\p"
    .string "Domingo, SUNNY\n"
    .string "RUTA 37$"
