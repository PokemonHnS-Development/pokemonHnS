.set LOCALID_SUDOWOODO, 14

BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Engineer5::
	msgbox BattleFrontier_OutsideWest_Text_Reparations5, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Engineer6::
	msgbox BattleFrontier_OutsideWest_Text_Reparations6, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Engineer7::
	msgbox BattleFrontier_OutsideWest_Text_Reparations7, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Engineer8::
	msgbox BattleFrontier_OutsideWest_Text_Reparations8, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_Reparations5:
	.string "Casi terminamos las reparaciones.\p"
    .string "MACHAMP ha ayudado mucho\n"
    .string "moviendo las rocas pesadas.$"

BattleFrontier_OutsideWest_Text_Reparations6:
    .string "¡Cuidado donde pisas!\n"
    .string "El suelo sigue inestable.\p"
    .string "Menos mal que el equipo MACHOKE\n"
    .string "nos ayuda a limpiar los escombros.$"

BattleFrontier_OutsideWest_Text_Reparations7:
    .string "Esos puentes de madera son la única\n"
    .string "forma de cruzar mientras reparamos.$"

BattleFrontier_OutsideWest_Text_Reparations8:
    .string "La cueva es inestable, así que hicimos\n"
    .string "puentes de madera temporales.\p"
    .string "Son resistentes... creo.$"

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "¡Esta es la BATTLE TOWER!\n"
	.string "¡Mantén tu racha como el mejor\l"
	.string "ENTRENADOR!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "¡Este es el BATTLE PALACE!\n"
	.string "¡No quites la vista de las batallas!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "¡Esta es la BATTLE ARENA!\n"
	.string "¡Que vengan los mejores equipos!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "¡Esta es la BATTLE PYRAMID!\n"
	.string "¡Avanza en la Búsqueda de Batalla!$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "RANKING DEL BATTLE FRONTIER\n"
	.string "¡Busca romper nuevos récords!$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "CANJE DE BATTLE POINTS\n"
	.string "¡Canjea tus Puntos de Batalla y\l"
	.string "comercia con otros ENTRENADORES!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "¡Guau!\n"
	.string "¡Es enorme!\p"
	.string "La BATTLE TOWER es especial.\n"
	.string "Es distinta a las demás.$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "Mi gran ambición es conquistar tanto\n"
	.string "la BATTLE FRONTIER como la LIGA\l"
	.string "POKéMON.\p"
	.string "Y si mi sueño se hace realidad...\p"
	.string "¡Le pediré a MIMI, la vecina,\n"
	.string "que sea mi amiga!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "¡La BATTLE PYRAMID es muy dura!\n"
	.string "¡No logro llegar a la cima!\p"
	.string "Como no tengo opciones, tal vez\n"
	.string "pueda subir por fuera...$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "Prospero en la oscuridad...\n"
	.string "Sí... ¿Qué es digno de mí?\l"
	.string "Nada más que la BATTLE PYRAMID...\p"
	.string "¿Qué dices de vagar en las sombras\n"
	.string "y en total desesperación?$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "No dormí en una semana, ¡pero\n"
	.string "armé el equipo definitivo!\p"
	.string "No me veo perdiendo, en serio.\n"
	.string "¡Asaltaremos la BATTLE ARENA!$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "¿SCOTT también te trajo aquí?\p"
	.string "¿No?\p"
	.string "¡Pero seguro sabes quién es!\p"
	.string "¿Qué pasa con ese tipo?\p"
	.string "Parece que sabe detectar\n"
	.string "ENTRENADORES con talento, pero...\p"
	.string "Jamás lo he visto luchar\n"
	.string "en persona.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "¡ZIGG!\n"
	.string "¡Confío en ti, amiguito!\p"
	.string "¡Si ganas, le daré a mi ZIGG los\n"
	.string "dulces que más le gusten!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "ZIGZAGOON parece distraído…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "Dicen que soy un entrometido,\n"
	.string "pero no puedo evitarlo.\p"
	.string "¡Tu gorra está torcida!\n"
	.string "¡Ay, no, basura en el suelo!\l"
	.string "¡Uy, ya casi es hora de cenar!\p"
	.string "No sé si podré limitarme a mirar\n"
	.string "en el BATTLE PALACE…$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "Quizá no luzca impresionante ahora,\n"
	.string "pero una vez vencí a un LÍDER GYM.\p"
	.string "Quién sabe, tal vez debería buscar\n"
	.string "la gloria otra vez.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "Soy rápido en mi BIKE, y eso aplica\n"
	.string "también a mi forma de luchar.\p"
	.string "¡Gano los combates en un abrir\n"
	.string "y cerrar de ojos!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "Soy mejor que mi papá\n"
	.string "en los POKéMON.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "¡Vamos, mi tesoro!\n"
	.string "¡Consigue victorias para papá!\p"
	.string "Eres igual que tu madre,\n"
	.string "¡así que dominarás!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "No fue fácil llegar aquí,\n"
	.string "pero oí de una chica hermosa\l"
	.string "en la BATTLE ARENA.\p"
	.string "En vez de ella, ¿sabes qué\n"
	.string "encontré?\p"
	.string "¡Un montón de artistas marciales\n"
	.string "sudorosos, apestosos y primitivos!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "A veces veo a un anciano que parece\n"
	.string "muy importante entrar ahí.\p"
	.string "Tiene unos POKéMON increíbles.\n"
	.string "Aunque parece muy amable.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "¿La conoces?\n"
	.string "¿La leyenda de la BATTLE PYRAMID?\p"
	.string "Cuando un TRAINER confiado llega\n"
	.string "a la cima dorada,\l"
	.string "aparecerá un hombre entre hombres.\p"
	.string "¿No conoces la leyenda?\n"
	.string "¡Pues claro que no!\l"
	.string "¡Me la acabo de inventar!\p"
	.string "¿Qué se supone que significa?\n"
	.string "¡Eso no lo sé, amigo mío!$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "¡Cielos! ¡No puede ser!\n"
	.string "¡Nunca había perdido antes!\p"
	.string "¡Pero me barrieron sin piedad\n"
	.string "y sin ninguna esperanza!\p"
	.string "¡¿Y luego me dicen que no tengo\n"
	.string "talento?! ¡Rayos!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "Este chico se topó con un TRAINER\n"
	.string "terrible mientras estaba en el\l"
	.string "reto de la BATTLE TOWER.\p"
	.string "Míralo ahora...\p"
	.string "Ten cuidado si decides ir a la\n"
	.string "BATTLE TOWER.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "¡Sí!\n"
	.string "¡Al fin tengo suficientes Puntos!\p"
	.string "¡Creo que canjearé otros por un\n"
	.string "MUÑECO gigante de peluche!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "¡Oh, sí, genial!\n"
	.string "¡Así que este es el RANKING HALL!\p"
	.string "Quiero pasar a la historia como\n"
	.string "un súper campeón y que mi nombre\l"
	.string "quede registrado aquí.$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "A tu lado, puedo hacer cualquier cosa.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "¡Ay, cariño, eres maravilloso!\p"
	.string "¡Ay, ya no puedo esperar más!\p"
	.string "¡Vamos a una SALA DE BATALLA MULTI\n"
	.string "en este mismo instante!\p"
	.string "Si nos unimos en el SALÓN DE BATALLA,\n"
	.string "nuestro amor vencerá a todos\l"
	.string "los que encontremos.\p"
	.string "¡Todo caerá como fichas de dominó\n"
	.string "ante nosotros, cariño!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "La BATTLE FRONTIER no es solo\n"
	.string "para ENTRENADORES fuertes.\p"
	.string "Parece que invitaron a mucha gente\n"
	.string "con habilidades especiales.\p"
	.string "Ese hombre, SCOTT...\p"
	.string "Quizás creó este lugar para un\n"
	.string "objetivo más grande...$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "Disculpa, joven.\n"
	.string "¿Tienes buena vista?\p"
	.string "Hay un árbol raro más adelante y,\n"
	.string "a mis ojos, parece moverse.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "Disculpa, joven.\n"
	.string "¿Tienes buena memoria?\p"
	.string "Siento que alguna vez hubo un\n"
	.string "árbol raro por aquí.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "Yo...\n"
	.string "¡Lo vi!\p"
	.string "¡Había un POKéMON pegajoso con\n"
	.string "cola larga más adelante!\p"
	.string "¡Se ocultaba bajo una roca y\n"
	.string "no dejaba de mirarme!$"
