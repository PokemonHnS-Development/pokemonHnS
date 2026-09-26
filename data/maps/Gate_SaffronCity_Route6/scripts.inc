Gate_SaffronCity_Route6_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SaffronCity_OnFrame
	.byte 0

Gate_SaffronCity_Route6_EventScript_Guard::
	goto_if_eq VAR_TEMP_0, 1, Gate_SaffronCity_Route6_EventScript_Guard2
	msgbox Route6_Text_SaffronGuardWelcome, MSGBOX_NPC
	setvar VAR_TEMP_0, 1
	end
Gate_SaffronCity_Route6_EventScript_Guard2::
	msgbox Route6_Text_SaffronGuardMagnetTrain, MSGBOX_NPC
	end

Route6_Text_SaffronGuardWelcome:
	.string "¡Bienvenido a CIUDAD AZAFRÁN,\n"
	.string "hogar del MAGNET TRAIN!\p"
	.string "...Eso es lo que diría,\n"
	.string "pero el MAGNET TRAIN no\l"
	.string "está funcionando ahora.\p"
	.string "No recibe electricidad porque\n"
	.string "algo falla en la CENTRAL\l"
	.string "ELÉCTRICA.$"

Route6_Text_SaffronGuardMagnetTrain:
	.string "El MAGNET TRAIN es lo más\n"
	.string "famoso de CIUDAD AZAFRÁN.$"
