PacifidlogTown_House4_MapScripts::
	.byte 0

PacifidlogTown_House4_EventScript_LittleGirl::
	msgbox PacifidlogTown_House4_Text_SkyPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Woman::
	msgbox PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Boy::
	lock
	faceplayer
	msgbox PacifidlogTown_House4_Text_WhereDidYouComeFrom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PacifidlogTown_House4_EventScript_Yes
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House4_EventScript_No
	end

PacifidlogTown_House4_EventScript_Yes::
	msgbox PacifidlogTown_House4_Text_YesTown, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_EventScript_No::
	msgbox PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon:
	.string "Dicen que vieron un POKéMON\n"
	.string "volando sobre HOENN.\p"
	.string "¿Vuela todo el tiempo?\n"
	.string "¿No necesita descansar en algún lado?$"

PacifidlogTown_House4_Text_SkyPokemon:
	.string "¡Un POKéMON del cielo!\n"
	.string "¡Un POKéMON del cielo!$"

PacifidlogTown_House4_Text_WhereDidYouComeFrom:
	.string "¿De dónde vienes?$"

PacifidlogTown_House4_Text_YesTown:
	.string "¿Sí?\n"
	.string "¿PUEBLO SÍ?\p"
	.string "Nunca he oído hablar de un lugar así.$"

PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere:
	.string "¿No? Eso no tiene sentido.\n"
	.string "Tienes que venir de algún lugar.\p"
	.string "¡Oh! ¡Espera! No me digas que\n"
	.string "naciste en el fondo del mar?$"

