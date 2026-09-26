PacifidlogTown_House5_MapScripts::
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher::
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent::
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman::
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday:
	.string "No veo la ISLA ESPEJISMO hoy...$"

PacifidlogTown_House5_Text_CanSeeMirageIslandToday:
	.string "¡Oh! ¡Cielos!\n"
	.string "¡Hoy veo la ISLA ESPEJISMO!$"

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather:
	.string "ISLA ESPEJISMO...\p"
	.string "Debe volverse visible e invisible\n"
	.string "según el clima que hace que los\l"
	.string "espejismos aparezcan.\p"
	.string "¿O realmente aparece y\n"
	.string "desaparece?\p"
	.string ". . .\p"
	.string "¿Y si es un POKéMON quien hace\n"
	.string "que la isla aparezca y\l"
	.string "desaparezca?\p"
	.string "Seguro es un POKéMON MÍTICO.$"
