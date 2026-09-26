BattleFrontier_Lounge2_MapScripts::
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMultiLink
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro::
	.string "¡Hola! En noticias sobre la\n"
	.string "BATTLE FRONTIER, soy el n.º 1.\p"
	.string "Puedes verme como el\n"
	.string "MANÍACO DE LA FRONTERA.\p"
	.string "Solo confirmo, eres ENTRENADOR,\n"
	.string "¿no es así?\p"
	.string "Compartiré las mejores noticias\n"
	.string "de la BATTLE FRONTIER.$"

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord::
	.string "¡Hola! ¿Vienes a preguntarme\n"
	.string "lo más reciente? ¡Está bien!$"

@ Unused
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight::
	.string "¿Y bien? ¿Y bien? ¿Y bien?\p"
	.string "Seguro mi información ha sido\n"
	.string "muy útil para ti, ¿verdad?$"

BattleFrontier_Lounge2_Text_FacilityIsHottest::
	.string "Veamos ahora…\p"
	.string "Parece que {STR_VAR_1}\n"
	.string "es el lugar más popular.$"

BattleFrontier_Lounge2_Text_BattleTowerIsHottest::
	.string "Veamos ahora…\p"
	.string "Parece que la BATTLE TOWER\n"
	.string "{STR_VAR_1} es la más popular.$"

BattleFrontier_Lounge2_Text_SalonMaidenIsThere::
	.string "¡Apuesto que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama FRONTIER BRAINS está ahí.\p"
	.string "Es una misteriosa ENTRENADORA\n"
	.string "llamada SALON MAIDEN quien manda.$"

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons::
	.string "¿Luchaste contra SALON MAIDEN?\p"
	.string "Al medir a su oponente,\n"
	.string "aparentemente usa estos POKéMON:\p"
	.string "Un POKéMON PSI de tipo PSÍQUICO,\n"
	.string "un POKéMON VOLCANO de tipo FUEGO,\l"
	.string "y un POKéMON DURMIENTE tipo NORMAL.$"

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons::
	.string "¿Luchaste contra SALON MAIDEN\n"
	.string "cuando está seria?\p"
	.string "Cuando lucha al máximo,\n"
	.string "aparentemente usa estos POKéMON:\p"
	.string "Un POKéMON EON DRAGÓN y PSÍQUICO,\n"
	.string "un POKéMON THUNDER de tipo ELÉCTRICO,\l"
	.string "y un POKéMON DURMIENTE tipo NORMAL.$"

BattleFrontier_Lounge2_Text_DomeAceIsThere::
	.string "¡Seguro no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama FRONTIER BRAINS está ahí.\p"
	.string "Es el extravagante DOME ACE,\n"
	.string "quien dirige el lugar.$"

BattleFrontier_Lounge2_Text_DomeAceSilverMons::
	.string "¿Luchaste contra el DOME ACE?\p"
	.string "Cuando no se toma en serio al rival,\n"
	.string "usa estos tres POKéMON:\p"
	.string "Un POKéMON DRAGÓN y VOLADOR,\n"
	.string "un POKéMON AGUA y TIERRA,\l"
	.string "y un POKéMON FUEGO y VOLADOR.$"

BattleFrontier_Lounge2_Text_DomeAceGoldMons::
	.string "¿Luchaste contra el DOME ACE\n"
	.string "cuando está serio?\p"
	.string "Cuando demuestra su estrategia,\n"
	.string "usa estos tres POKéMON:\p"
	.string "Un POKéMON DRAGÓN y VOLADOR,\n"
	.string "un POKéMON AGUA y TIERRA,\l"
	.string "y un POKéMON ACERO y PSÍQUICO.\l"
	.string "Es el IRON LEG.$"

BattleFrontier_Lounge2_Text_FactoryHeadIsThere::
	.string "¡Seguro no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama FRONTIER BRAINS está ahí.\p"
	.string "Es el extraño FACTORY HEAD,\n"
	.string "quien dirige el lugar.$"

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons::
	.string "¿Ya luchaste contra el\n"
	.string "FACTORY HEAD?\p"
	.string "Déjame pensar... Al combatir,\n"
	.string "usa tres POKéMON de alquiler.\p"
	.string "Lucha bajo las mismas condiciones\n"
	.string "que tú.$"

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons::
	.string "¿Luchaste contra el FACTORY HEAD\n"
	.string "cuando está serio?\p"
	.string "Cuando lucha en serio,\n"
	.string "aún usa tres POKéMON de alquiler.\p"
	.string "Lucha bajo las mismas condiciones\n"
	.string "que tú.$"

BattleFrontier_Lounge2_Text_PikeQueenIsThere::
	.string "¡Seguro no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama FRONTIER BRAINS está ahí.\p"
	.string "Es la temible PIKE QUEEN,\n"
	.string "quien dirige el lugar.$"

BattleFrontier_Lounge2_Text_PikeQueenSilverMons::
	.string "¿Luchaste contra la PIKE QUEEN\n"
	.string "antes?\p"
	.string "Dicen que si está de buen humor,\n"
	.string "usa estos tres POKéMON:\p"
	.string "Un POKéMON VENENO tipo serpiente,\n"
	.string "un POKéMON BICHO y ROCA,\l"
	.string "y un POKéMON tipo AGUA.$"

BattleFrontier_Lounge2_Text_PikeQueenGoldMons::
	.string "¿Has luchado contra la REINA PIKE\n"
	.string "cuando habla en serio?\p"
	.string "Dicen que cuando está muy molesta\n"
	.string "usa estos tres POKéMON:\p"
	.string "Un FANG SNAKE de tipo VENENO,\n"
	.string "un IRON SNAKE ACERO y TIERRA,\l"
	.string "y un ATROCIOUS de tipo AGUA\l"
	.string "y VOLADOR.$"

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere::
	.string "¡Seguro no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama FRONTIER BRAINS está ahí.\p"
	.string "Es la linda ARENA TYCOON,\n"
	.string "quien dirige el lugar.$"

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons::
	.string "¿Luchaste contra la ARENA TYCOON\n"
	.string "antes?\p"
	.string "Cuando evalúa la habilidad rival,\n"
	.string "se dice que usa estos POKéMON:\p"
	.string "Un SINGLE HORN Bicho y Lucha,\n"
	.string "un MOONLIGHT tipo SINIESTRO,\l"
	.string "y un SHED de Bicho y Fantasma.$"

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons::
	.string "¿Luchaste contra la TYCOON\n"
	.string "cuando está seria?\p"
	.string "Cuando lucha en serio,\n"
	.string "usa supuestamente estos POKéMON:\p"
	.string "Un POKéMON MOONLIGHT tipo SIN DIEZ,\n"
	.string "un SHADOW tipo FANTASMA y VENENO\l"
	.string "y un POKéMON MUSHROOM tipo\l"
	.string "PLANTA y LUCHA.$"

BattleFrontier_Lounge2_Text_PalaceMavenIsThere::
	.string "¡Seguro no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama FRONTIER BRAINS está ahí.\p"
	.string "Es el siniestro PALACE MAVEN,\n"
	.string "quien dirige el lugar.$"

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons::
	.string "¿Luchaste contra el PALACE MAVEN\n"
	.string "antes?\p"
	.string "Cuando prueba el espíritu rival,\n"
	.string "dicen que usa estos POKéMON:\p"
	.string "Un BAT Veneno y Volador,\n"
	.string "un LAZY tipo NORMAL, y un\l"
	.string "TRANSPORT de Agua y Hielo.$"

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons::
	.string "¿Luchaste contra el PALACE MAVEN\n"
	.string "cuando está serio?\p"
	.string "Cuando lucha con todo su poder,\n"
	.string "dicen que usa estos POKéMON:\p"
	.string "Un POKéMON LEGENDARIO de Fuego,\n"
	.string "un LAZY tipo NORMAL,\l"
	.string "y un AURORA tipo AGUA.$"

BattleFrontier_Lounge2_Text_PyramidKingIsThere::
	.string "¡Seguro no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama FRONTIER BRAINS está ahí.\p"
	.string "Es el ardiente PYRAMID KING,\n"
	.string "quien dirige el lugar.$"

BattleFrontier_Lounge2_Text_PyramidKingSilverMons::
	.string "¿Has luchado contra el REY PIRÁMIDE\n"
	.string "antes?\p"
	.string "Para medir el poder del rival,\n"
	.string "usa estos POKéMON:\p"
	.string "Un ROCK PEAK de tipo ROCA,\n"
	.string "un ICEBERG de tipo HIELO,\l"
	.string "y un IRON de tipo ACERO.$"

BattleFrontier_Lounge2_Text_PyramidKingGoldMons::
	.string "¿Has luchado contra el REY PIRÁMIDE\n"
	.string "cuando va en serio?\p"
	.string "Cuando está lleno de energía,\n"
	.string "usa estos POKéMON:\p"
	.string "Un POKéMON Hielo y Volador,\n"
	.string "uno Eléctrico y Volador,\l"
	.string "y un POKéMON de tipo Fuego\l"
	.string "y Volador.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1::
	.string "Hay varios sitios donde puedes\n"
	.string "tener COMBATES DOBLES.\p"
	.string "¡Pero las SALAS DE COMBATE DOBLE\n"
	.string "de la TORRE DE COMBATE son básicas!\p"
	.string "Ahí aprenderás cómo se juegan los\n"
	.string "COMBATES DOBLES en la BATTLE\l"
	.string "FRONTIER.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2::
	.string "Ten cuidado en los combates aquí.\p"
	.string "He oído que hay ENTRENADORES con\n"
	.string "estrategias creadas solo para\l"
	.string "COMBATES DOBLES.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3::
	.string "Cuando domines los COMBATES DOBLES\n"
	.string "aquí, deberías pensar en retar\l"
	.string "otros lugares que ofrezcan\l"
	.string "COMBATES DOBLES.$"

BattleFrontier_Lounge2_Text_MultiBattleAdvice::
	.string "Todo tipo de ENTRENADORES vienen al\n"
	.string "BATTLE SALON.\p"
	.string "¡Piensa que podrías encontrar a\n"
	.string "tus amigos o seguidores!\l"
	.string "¡Mira con atención!$"

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice::
	.string "Si estás con un amigo, ve a la\n"
	.string "SALA DE MULTI COMBATE.\p"
	.string "Si juegas con un amigo fuerte,\n"
	.string "¡espera rivales muy difíciles!$"

BattleFrontier_Lounge2_Text_NewsGatheringPower::
	.string "¡Qué poder para obtener noticias!\n"
	.string "¡Mi mentor es incomparable!$"

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation::
	.string "¡Qué gran poder de observación!\n"
	.string "¡Mi mentor es el mejor!$"

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion::
	.string "¡Qué gran poder de persuasión!\n"
	.string "¡Mi mentor es el mejor!$"

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe::
	.string "...¿Qué es este lugar?\n"
	.string "Me da miedo...$"

