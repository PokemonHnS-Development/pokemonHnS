CianwoodHouse1_MapScripts::
	.byte 0

CianwoodHouse1_EventScript_Hermit::
	lock
	faceplayer
	msgbox CianwoodCity_Text_OldManIntro MSGBOX_DEFAULT
	goto_if_eq VAR_LUGIA_OR_HOOH, 2, CianwoodHouse1_EventScript_HermitHooh
	checkitem ITEM_TIDAL_BELL
	goto_if_eq VAR_RESULT, TRUE, CianwoodHouse1_EventScript_HermitTidalBell
	msgbox CianwoodCity_Text_WhirlIslandsStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitTidalBell::
	msgbox CianwoodCity_Text_TidalBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitHooh::
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, TRUE, CianwoodHouse1_EventScript_HermitClearBell
	msgbox CianwoodCity_Text_BellTowerStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitClearBell::
	msgbox CianwoodCity_Text_ClearBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_OldManIntro:
	.string "No recuerdo la última vez\n"
	.string "que alguien vino a visitarme.\p"
	.string "De joven, yo también fui un\n"
	.string "ENTRENADOR POKéMON.\l"
	.string "Intenté llegar a la torre y\l"
	.string "bucear en el océano.\p"
	.string "Me esforcé mucho en muchas\n"
	.string "cosas.\p"
	.string "Bueno, ahora me lo tomo con calma,\n"
	.string "oyendo las olas y el viento\l"
	.string "en esta playa.$"

CianwoodCity_Text_BellTowerStory:
	.string "¿Has oído hablar de la TORRE LATÓN\n"
	.string "en CIUDAD IRIS?\p"
	.string "Hay unas Campanas Cristalinas\n"
	.string "en lo alto de la torre.\p"
	.string "No hacen ni un solo ruido\n"
	.string "con vientos fuertes.\p"
	.string "Solo hay una forma de hacer que\n"
	.string "suenen.\p"
	.string "Es obtener otra CAMPANA CRISTAL\n"
	.string "igual a las que están en lo alto\l"
	.string "de la torre.\p"
	.string "La busqué cuando era joven.\n"
	.string "Pero nunca conseguí una...$"

CianwoodCity_Text_WhirlIslandsStory:
	.string "¿Has oído hablar de ISLAS REMOLINO?\p"
	.string "Hay unas Campanas Mareales\n"
	.string "en la base de su cascada.\p"
	.string "No hacen ni un solo ruido\n"
	.string "con las olas rompiendo.\p"
	.string "Solo hay una forma de hacer que\n"
	.string "suenen.\p"
	.string "Es obtener otra Campana Mareal\n"
	.string "igual a las que están en la base\l"
	.string "de la cascada.\p"
	.string "La busqué cuando era joven.\n"
	.string "Pero nunca conseguí una...$"

CianwoodCity_Text_ClearBellReaction:
	.string "¡Oh! ¿Lograste conseguir una\n"
	.string "CAMPANA CRISTAL?\p"
	.string "El viejo sueño de mi vida...\n"
	.string "Ya veo...\p"
	.string "Lo lograste...\n"
	.string "...\l"
	.string "...¡Puedo oírlo!\p"
	.string "El tañido de las campanas al viento\n"
	.string "que viene desde la dirección de la\l"
	.string "TORRE LATÓN...$"

CianwoodCity_Text_TidalBellReaction:
	.string "¡Oh! ¿Lograste conseguir una\n"
	.string "Campana Mareal?\p"
	.string "El viejo sueño de mi vida...\n"
	.string "Ya veo...\p"
	.string "Lo lograste...\n"
	.string "...\l"
	.string "...¡Puedo oírlo!\p"
	.string "El tañido de las campanas en la brisa\n"
	.string "marina que viene desde la dirección\l"
	.string "de las ISLAS REMOLINO...$"
