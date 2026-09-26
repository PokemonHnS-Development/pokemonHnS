Route46_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route46_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route46_EventScript_Bailey::
	trainerbattle_single TRAINER_BAILEY, Route46_Text_HikerBaileySeen, Route46_Text_HikerBaileyBeaten
	msgbox Route46_Text_HikerBaileyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Ted::
	trainerbattle_single TRAINER_TED, Route46_Text_CamperTedSeen, Route46_Text_CamperTedBeaten
	msgbox Route46_Text_CamperTedAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Erin::
	trainerbattle_single TRAINER_ERIN, Route46_Text_PicnickerErinSeen, Route46_Text_PicnickerErinBeaten
	msgbox Route46_Text_PicnickerErinAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Sign::
	lock
	msgbox Route46_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route46_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

Route46_Text_HikerBaileySeen:
	.string "¡Bien! ¡Te mostraré el\n"
	.string "poder de los POKéMON de montaña!$"

Route46_Text_HikerBaileyBeaten:
	.string "¡Piedad! ¡Me has demostrado\n"
	.string "tu poder!$"

Route46_Text_HikerBaileyAfterBattle:
	.string "Se acabó. No me importa.\n"
	.string "Los EXCURSIONISTAS somos así.$"

Route46_Text_CamperTedSeen:
	.string "¡Yo también crío POKéMON!\p"
	.string "¿Luchas conmigo?$"

Route46_Text_CamperTedBeaten:
	.string "¿Qué...?$"

Route46_Text_CamperTedAfterBattle:
	.string "Hice lo mejor que pude, pero\n"
	.string "fallé.\p"
	.string "Sin excusas, admito que perdí.$"

Route46_Text_PicnickerErinSeen:
	.string "¡Yo también crío POKéMON!\p"
	.string "¿Luchas conmigo?$"

Route46_Text_PicnickerErinBeaten:
	.string "¡Rayos!$"

Route46_Text_PicnickerErinAfterBattle:
	.string "He ido a muchos GIMNASIOS, pero el\n"
	.string "de CIUDAD TRIGAL es mi favorito.\p"
	.string "¡Está lleno de flores lindas!$"

Route46_Text_PicnickerErin2Beaten:
	.string "¡Ay... siempre termino perdiendo!\p"
	.string "¡Tendré que esforzarme más!\n"
	.string "Gracias por luchar conmigo\n"
	.string "una y otra vez.\p"
	.string "Toma el regalo de la\n"
	.string "otra vez.$"

Route46_Text_Sign:
	.string "RUTA 46\n"
	.string "CAMINO DE MONTAÑA ADELANTE$"
