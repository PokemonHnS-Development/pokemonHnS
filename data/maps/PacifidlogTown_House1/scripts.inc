PacifidlogTown_House1_MapScripts::
	.byte 0

PacifidlogTown_House1_EventScript_Man::
	msgbox PacifidlogTown_House1_Text_RegiStory, MSGBOX_NPC
	end

PacifidlogTown_House1_EventScript_Woman::
	msgbox PacifidlogTown_House1_Text_SixDotsOpenThreeDoors, MSGBOX_NPC
	end

PacifidlogTown_House1_Text_RegiStory:
	.string "En HOENN hay cinco POKéMON que\n"
	.string "representan el poder de la roca,\l"
	.string "el hielo, el acero, la electricidad\l"
	.string "y la energía dragón.\p"
	.string "Dicen que cada uno se oculta en lo\n"
	.string "profundo de las cuevas.\p"
	.string "Eso es lo que escuché cuando era\n"
	.string "solo un niño.$"

PacifidlogTown_House1_Text_SixDotsOpenThreeDoors:
	.string "“Seis puntos abren cinco puertas”.\p"
	.string "Mi abuelo decía eso, pero no sé\n"
	.string "qué quería decir.$"

