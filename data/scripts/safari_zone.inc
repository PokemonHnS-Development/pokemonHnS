SafariZone_EventScript_OutOfBallsMidBattle::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	goto_if_set FLAG_IN_KANTO_SAFARI_ZONE, SafariZone_EventScript_ExitKanto
	setwarp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE, 9, 3
	end

SafariZone_EventScript_Exit::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	goto_if_set FLAG_IN_KANTO_SAFARI_ZONE, SafariZone_EventScript_ExitKanto
	warp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE, 9, 3
	waitstate
	end

SafariZone_EventScript_ExitKanto::
	clearflag FLAG_IN_KANTO_SAFARI_ZONE
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 5, 6
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
	releaseall
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit:
	.string "¿Quieres salir de la ZONA SAFARI\n"
	.string "ahora mismo?$"

SafariZone_Text_TimesUp:
	.string "¡Ding-dong! ¡Se acabó el tiempo!\n"
	.string "Tu juego SAFARI ha terminado.$"

SafariZone_Text_OutOfBalls:
	.string "Te quedaste sin SAFARI BALLS.\n"
	.string "Tu juego SAFARI ha terminado.$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "¿Quieres poner un {POKEBLOCK}\n"
	.string "en el ALIMENTADOR {POKEBLOCK}?$"

SafariZone_Text_PokeblockStillHere:
	.string "El {STR_VAR_1} que dejaste\n"
	.string "antes todavía está aquí.$"

SafariZone_Text_PokeblockWasPlaced:
	.string "El {STR_VAR_1} fue colocado\n"
	.string "en el ALIMENTADOR {POKEBLOCK}.$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "¡Bienvenido a la ZONA SAFARI!\p"
	.string "Aquí verás muchos tipos de\n"
	.string "POKéMON raros de JOHTO.\p"
	.string "Los verás en estado salvaje\n"
	.string "en sus hábitats naturales.\p"
	.string "Además, abrimos las puertas a los\n"
	.string "ENTRENADORES POKéMON.\p"
	.string "¡Te animamos a capturar POKéMON\n"
	.string "para siempre!\p"
	.string "¡Entra y disfruta la ZONA SAFARI!$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "¡Bienvenido a la ZONA SAFARI!\n"
	.string "¿Es tu primera vez aquí?$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "¡Entra y disfruta la SAFARI ZONE!$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "Al entrar a la SAFARI ZONE, recibes\n"
	.string "30 SAFARI BALLS para capturar\l"
	.string "POKéMON.\p"
	.string "El juego termina si te quedas sin\n"
	.string "SAFARI BALLS o si caminas\l"
	.string "500 pasos.\p"
	.string "¡Entra y disfruta la SAFARI ZONE!$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "¡Bienvenido a la SAFARI ZONE!\p"
	.string "¡Captura todo por solo ¥500!\n"
	.string "¿Quieres jugar un SAFARI Game?$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "Está bien.\n"
	.string "¡Vuelve a jugar otro día!$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "No tienes suficiente dinero.\n"
	.string "Lo siento.$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "Serían ¥500, por favor.$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "Aquí tienes tus SAFARI BALLS.$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER} recibió 30 SAFARI BALLS.$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "Te avisaremos cuando tu juego\n"
	.string "termine.\p"
	.string "¡Hasta entonces, diviértete!\n"
	.string "¡Ve a tu excursión salvaje!$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_PCIsFull:
	.string "¡Disculpa!\n"
	.string "Tu PC BOX está llena.$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "¡Disculpa!\n"
	.string "No tienes un ESTUCHE {POKEBLOCK}.\p"
	.string "Tu juego SAFARI será más\n"
	.string "útil si usas {POKEBLOCK}S.\p"
	.string "Vuelve con un ESTUCHE {POKEBLOCK}.\p"
	.string "Puedes hallar un ESTUCHE {POKEBLOCK} en\n"
	.string "la SAFARI ZONE de JOHTO.$"

SafariZone_South_Text_StillHaveTimeExit:
	.string "Aún te queda tiempo. ¿Quieres\n"
	.string "salir de la SAFARI ZONE ahora?$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "¡Disfruta el resto de tu\n"
	.string "aventura salvaje!$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "Está bien.\p"
	.string "Recuperaré tus SAFARI BALLS\n"
	.string "restantes.\p"
	.string "Gracias por jugar.\n"
	.string "Esperamos verte pronto.$"

SafariZone_South_Text_GoodLuck:
	.string "¡Buena suerte!\p"
	.string "Si necesitas algo, no dudes\n"
	.string "en decírmelo, ¡por favor!$"

SafariZone_South_Text_Boy:
	.string "¿Sabías esto?\p"
	.string "Si pones un {POKEBLOCK} en esa caja,\n"
	.string "los POKéMON se acercarán.$"

SafariZone_South_Text_Man:
	.string "Quiero ir más profundo, pero\n"
	.string "olvidé traer mi BICICLETA.\p"
	.string "Siento que hay POKéMON raros\n"
	.string "en las zonas alejadas.$"

SafariZone_Southwest_Text_Woman:
	.string "A veces, lanzo un {POKEBLOCK} a un\n"
	.string "POKéMON y lo ignora.\p"
	.string "¿Tendrá los POKéMON gustos y\n"
	.string "disgustos con la comida?$"

SafariZone_Northwest_Text_Man:
	.string "Jadeo... Jadeo...\n"
	.string "Llegué... hasta aquí... pero...\p"
	.string "Estoy agotado... No tengo\n"
	.string "energía para capturar POKéMON...$"

SafariZone_North_Text_Fisherman:
	.string "Busco POKéMON de AGUA que no\n"
	.string "se ven en HOENN.\p"
	.string "¿Tienes idea de dónde está el lago?$"

SafariZone_North_Text_Man:
	.string "¡Atraparé muchos POKéMON raros\n"
	.string "aquí para cambiarlos con mis amigos!$"

SafariZone_South_Text_Youngster:
	.string "Puse un {POKEBLOCK} en el COMEDERO de {POKEBLOCK}.\n"
	.string "Pero parece que desapareció.\p"
	.string "Creo que algún POKéMON se la comió\n"
	.string "sin que me diera cuenta.$"

Route121_SafariZoneGate_SafariZoneEntrance_Text_TrainerTip:
	.string "¡CONSEJO DE ENTRENADOR SAFARI!\p"
	.string "Lanza {POKEBLOCK}S a los POKéMON\n"
	.string "para que no huyan tanto.$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "“Descansa tus pies cansados.”\n"
	.string "CASA DE DESCANSO$"

SafariZone_RestHouse_Text_Youngster:
	.string "No tengo {POKEBLOCK}S, pero atrapé\n"
	.string "bastantes POKéMON.\p"
	.string "Mejorarás tus chances de captura si\n"
	.string "te acercas más a ellos\l"
	.string "antes de lanzar la SAFARI BALL.$"

SafariZone_RestHouse_Text_PsychicM:
	.string "Si usas {POKEBLOCK}S, los POKéMON\n"
	.string "salvajes no huirán tan rápido.\p"
	.string "No sirve dar {POKEBLOCK}S a POKéMON\n"
	.string "que no huyen fácilmente.$"

SafariZone_RestHouse_Text_FatMan:
	.string "Si pones un {POKEBLOCK} en el COMEDERO,\n"
	.string "los POKéMON se sentirán atraídos.\p"
	.string "Creo que POKéMON de cierta naturaleza\n"
	.string "buscan un {POKEBLOCK} específico.$"

SafariZone_South_Text_AreaOffLimits1:
	.string "Esta zona sigue en construcción.\n"
	.string "¡Está prohibido pasar, lo siento!$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "La expansión de la ZONA SAFARI\n"
	.string "ya ha terminado.\p"
	.string "Esperamos que disfrutes la nueva zona.$"

SafariZone_South_Text_AreaOffLimits2:
	.string "Esta zona sigue en construcción.\n"
	.string "¡Está prohibido pasar, lo siento!$"

SafariZone_Southeast_Text_LittleGirl:
	.string "¡Guau! ¡Genial! ¡Nunca había visto\n"
	.string "estos POKéMON antes!$"

SafariZone_Southeast_Text_FatMan:
	.string "Los POKéMON de esta zona son todos\n"
	.string "nuevos para mí.\p"
	.string "¡Y puedo capturar estos POKéMON\n"
	.string "tan raros! ¡Genial!$"

SafariZone_Southeast_Text_RichBoy:
	.string "Los POKéMON de aquí parecen ser\n"
	.string "de algún lugar fuera de HOENN.$"

SafariZone_Northeast_Text_Boy:
	.string "Solo me quedan unas SAFARI BALL.\p"
	.string "Me cuesta decidir qué POKéMON\n"
	.string "debería capturar.$"

SafariZone_Northeast_Text_Woman:
	.string "Oí que se puede ver a PIKACHU aquí.\n"
	.string "¿Dónde podrá estar?$"

SafariZone_Northeast_Text_Girl:
	.string "¡Rayos!\n"
	.string "¡No logro capturar nada!\p"
	.string "¡Desperdiciaré la entrada si no\n"
	.string "atrapó algo!$"
