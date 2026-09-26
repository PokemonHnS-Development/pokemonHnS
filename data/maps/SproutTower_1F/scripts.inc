SproutTower_1F_MapScripts::
	.byte 0

SproutTower_1F_EventScript_SageChow::
	trainerbattle_single TRAINER_CHOW, SproutTower_Text_SageChow_Seen, SproutTower_Text_SageChow_Beaten
	msgbox SproutTower_Text_SageChow_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_1F_EventScript_Sage1::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Sage1, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Sage2::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Sage2, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Granny::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Teacher::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_ItemParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

SproutTower_Text_SageChow_Seen:
	.string "Vigilamos esta torre.\p"
	.string "Aquí expresamos gratitud\n"
	.string "para honrar a los POKéMON.$"

SproutTower_Text_SageChow_Beaten:
	.string "¡Gr-Gracias!$"

SproutTower_Text_SageChow_AfterBattle:
	.string "Los seres vivos coexisten\n"
	.string "cooperando entre sí.\p"
	.string "Siempre debemos estar\n"
	.string "agradecidos por esto.$"

SproutTower_Text_1F_Sage1:
	.string "Solo si llegas a la cima\n"
	.string "obtendrás una MO.$"

SproutTower_Text_1F_Sage2:
	.string "La TORRE VERDE se construyó\n"
	.string "para entrenar POKéMON.$"

SproutTower_Text_1F_Granny:
	.string "Un BELLSPROUT de más de 30m\n"
	.string "de alto...\p"
	.string "Dicen que se convirtió en el\n"
	.string "pilar central de aquí.$"

SproutTower_Text_1F_Teacher:
	.string "¿Ves que el pilar tiembla?\p"
	.string "Hay gente entrenando arriba.$"

SproutTower_Text_1F_Statue:
	.string "Una estatua POKéMON...\p"
	.string "Se ve muy distinguida.$"
