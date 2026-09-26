LavenderTown_SoulHouse_MapScripts::
	.byte 0

LavenderTownSoulHouse_EventScript_MrFuji::
	msgbox MrFuji_Text_Main, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Lass::
	msgbox SoulHouse_Text_Lass, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Teacher::
	msgbox SoulHouse_Text_Teacher, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Granny::
	msgbox SoulHouse_Text_Granny, MSGBOX_NPC
	end

MrFuji_Text_Main:
	.string "SR.FUJI: Bienvenido.\p"
	.string "Hmm... Parece que crías a tus\n"
	.string "POKéMON con mucha bondad y\l"
	.string "cariño.\p"
	.string "Los amantes de los POKéMON vienen\n"
	.string "aquí a rendir respeto a los\l"
	.string "POKéMON que partieron.\p"
	.string "Por favor, ofrece tus condolencias\n"
	.string "a las almas de esos POKéMON.\p"
	.string "Seguro que eso los hará\n"
	.string "felices.$"

SoulHouse_Text_Teacher:
	.string "Creo que hay otras tumbas de\n"
	.string "POKéMON por aquí.\p"
	.string "Hay muchas cámaras donde solo el\n"
	.string "SR.FUJI puede entrar.$"

SoulHouse_Text_Lass:
	.string "Vine con mi mamá a visitar las\n"
	.string "tumbas de los POKéMON...$"

SoulHouse_Text_Granny:
	.string "Los POKéMON que vivieron conmigo...\p"
	.string "Los amaba como si fueran mis\n"
	.string "nietos...$"
