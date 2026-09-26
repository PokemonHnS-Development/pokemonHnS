MahoganyTown_House1_MapScripts::
	.byte 0

MahoganyTown_House1_EventScript_BlackBelt::
	msgbox MahoganyRedGyaradosHouse_Text_BlackBelt, MSGBOX_NPC
	end

MahoganyTown_House1_EventScript_Teacher::
	goto_if_lt VAR_GOLDENROD_CITY_STATE, 6, MahoganyTown_House1_EventScript_TeacherBeforeAfter
	goto_if_lt VAR_GOLDENROD_CITY_STATE, 10, MahoganyTown_House1_EventScript_TeacherDuring
MahoganyTown_House1_EventScript_TeacherBeforeAfter::
	msgbox MahoganyRedGyaradosHouse_Text_Teacher MSGBOX_NPC
	end

MahoganyTown_House1_EventScript_TeacherDuring::
	msgbox MahoganyRedGyaradosHouse_Text_Teacher_Rockets, MSGBOX_NPC
	end


MahoganyRedGyaradosHouse_Text_BlackBelt:
    .string "Oí que un GYARADOS rojo apareció\n"
    .string "en el LAGO.\p"
    .string "Es raro, pues hasta los GYARADOS\n"
    .string "comunes son raros en ese lago…$"

MahoganyRedGyaradosHouse_Text_Teacher:
    .string "¿Mi programa de radio favorito?\n"
    .string "Diría que POKéMON MUSIC.$"

MahoganyRedGyaradosHouse_Text_Teacher_Rockets:
    .string "He oído risas en la\n"
    .string "radio…\p"
    .string "Da miedo.$"
