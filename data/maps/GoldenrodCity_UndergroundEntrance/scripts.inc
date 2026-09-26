GoldenrodCity_UndergroundEntrance_MapScripts::
	.byte 0


GoldenrodUnderground_EventScript_SuperNerd::
	lock
	faceplayer
	msgbox GoldenrodUnderground1_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	lock
	release
	end

GoldenrodUnderground_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodUnderground1_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	lock
	release
	end

GoldenrodUnderground1_Text_SuperNerd:
	.string "Me retaron a una batalla\n"
	.string "abajo.\p"
	.string "Está difícil allá. Mejor\n"
	.string "ten mucho cuidado.$"


GoldenrodUnderground1_Text_Teacher:
	.string "Hay tiendas abajo...\n"
	.string "Pero también hay entrenadores.\p"
	.string "Me da miedo bajar.$"
