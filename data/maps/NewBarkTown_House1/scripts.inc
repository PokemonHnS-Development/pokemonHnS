NewBarkTown_House1_MapScripts::
	.byte 0

NewBarkTown_House1_EventScript_Mother::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_Neighbor, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_EventScript_Daughter::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_NeighborsDaughter, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_Text_NeighborsDaughter:
	.string "PIKACHU es un POKéMON evolucionado.\p"
	.string "Me asombraron los hallazgos\n"
	.string "del PROF.ELM.\p"
	.string "Es famoso por su investigación\n"
	.string "de la evolución POKéMON.\p"
	.string "…ay…\p"
	.string "Ojalá pudiera ser investigadora\n"
	.string "como él…$"


NewBarkTown_House1_Text_Neighbor:
	.string "Mi hija está empeñada en ser\n"
	.string "asistente del PROF.ELM.\p"
	.string "¡Le encantan los POKéMON!\p"
	.string "Pero a mí también.$"

