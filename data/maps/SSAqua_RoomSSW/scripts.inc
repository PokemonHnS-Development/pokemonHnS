SSAqua_RoomSSW_MapScripts::
	.byte 0

SSAqua_RoomSSW_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE SSAqua_RoomSSW_Text_FirebreatherLyleSeen, SSAqua_RoomSSW_Text_FirebreatherLyleBeaten
	msgbox SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_EventScript_Ken::
	trainerbattle_single TRAINER_KEN SSAqua_RoomSSW_Text_BugCatcherKenSeen, SSAqua_RoomSSW_Text_BugCatcherKenBeaten
	msgbox SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_Text_FirebreatherLyleSeen:
    .string "¡Iré a KANTO para dar\n"
    .string "shows de fuego!$"

SSAqua_RoomSSW_Text_FirebreatherLyleBeaten:
    .string "Fizzle... La llama es pequeña...$"

SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle:
    .string "El fuego es débil en el mar.\n"
    .string "¿No importa? ¿En serio?$"

SSAqua_RoomSSW_Text_BugCatcherKenSeen:
    .string "¡Visitaré a mi abuela para\n"
    .string "atrapar algunos bichos!$"

SSAqua_RoomSSW_Text_BugCatcherKenBeaten:
    .string "¡Oh, vaya. ¡Eres fuerte!$"

SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle:
    .string "¡Hay muchos POKéMON en los\n"
    .string "árboles de JOHTO!$"
