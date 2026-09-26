LavaridgeTown_House_MapScripts::
	.byte 0

LavaridgeTown_House_EventScript_OldMan::
	msgbox LavaridgeTown_House_Text_WifeWarmingEggInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_House_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox LavaridgeTown_House_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LavaridgeTown_House_Text_WifeWarmingEggInHotSprings:
	.string "Mi esposa calienta un HUEVO en las\n"
	.string "aguas termales. Esto fue lo que dijo.\p"
	.string "Dejó dos POKéMON en la GUARDERÍA.\n"
	.string "¡Y así descubrieron ese HUEVO!$"

LavaridgeTown_House_Text_Zigzagoon:
	.string "ZIGZAGOON: ¡Pshoo!$"

