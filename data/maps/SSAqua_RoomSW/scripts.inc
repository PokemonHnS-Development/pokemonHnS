SSAqua_RoomSW_MapScripts::
	.byte 0

SSAqua_RoomSW_EventScript_Cassie::
	trainerbattle_single TRAINER_CASSIE SSAqua_RoomSW_Text_BeautyCassieSeen, SSAqua_RoomSW_Text_BeautyCassieBeaten
	msgbox SSAqua_RoomSW_Text_BeautyCassieAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_EventScript_Clyde::
	trainerbattle_single TRAINER_CLYDE SSAqua_RoomSW_Text_GuitaristClydeSeen, SSAqua_RoomSW_Text_GuitaristClydeBeaten
	msgbox SSAqua_RoomSW_Text_GuitaristClydeAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_Text_BeautyCassieSeen:
    .string "Trato de olvidar mis penas.\n"
    .string "¡Luchemos!$"

SSAqua_RoomSW_Text_BeautyCassieBeaten:
    .string "Mi corazón llora…$"

SSAqua_RoomSW_Text_BeautyCassieAfterBattle:
    .string "Un viaje es lo mejor para curar\n"
    .string "un corazón roto.\p"
    .string "Pero un viaje en BARCO RÁPIDO es\n"
    .string "muy corto para sufrir.$"

SSAqua_RoomSW_Text_GuitaristClydeSeen:
    .string "Iré a presentar mis canciones a la\n"
    .string "ESTACIÓN DE RADIO de CIUDAD TRIGAL.$"

SSAqua_RoomSW_Text_GuitaristClydeBeaten:
    .string "¡Vaya! ¡Distorsión total!$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattleMobile:
    .string "Iba a debutar en la\n"
    .string "BATTLE TOWER…\p"
    .string "Debo volver a VERMILION y\n"
    .string "entrenar de nuevo…$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattle:
    .string "Hablando de la ESTACIÓN DE RADIO,\n"
    .string "¿cuál es el número suerte semanal?$"
