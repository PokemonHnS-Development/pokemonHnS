.set LOCALID_WALLYS_DAD, 1

PetalburgCity_WallysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp:
	map_script_2 VAR_GARBAGEVAR, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame:
	map_script_2 VAR_GARBAGEVAR, 4, PetalburgCity_WallysHouse_EventScript_GiveHMSurf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHMSurf::
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_GARBAGEVAR, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad::
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally::
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally:
	.string "Tú eres...\n"
	.string "Ah, debes ser {PLAYER}{KUN}, ¿verdad?\p"
	.string "Gracias por jugar con WALLY hace\n"
	.string "un momento.\p"
	.string "Ha sido débil y enfermizo desde\n"
	.string "que era un bebé.\p"
	.string "Lo enviamos con mis parientes en\n"
	.string "PUEBLO VERDANTE un tiempo.\p"
	.string "El aire es mucho más limpio allá\n"
	.string "que aquí.\p"
	.string "¿Qué dices? ¿Dónde está WALLY?\n"
	.string "Ya se ha ido, nuestro WALLY.\p"
	.string "Me pregunto ¿a dónde habrá\n"
	.string "llegado ya?$"

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing:
	.string "¿Cómo estará nuestro WALLY?$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs:
	.string "{PLAYER}{KUN}! Perdona que te\n"
	.string "hayamos traído así.\p"
	.string "Pero WALLY ha mejorado mucho\n"
	.string "en PUEBLO VERDANTE.\p"
	.string "¡Te lo debemos todo a ti!\p"
	.string "Cuando WALLY salió, lo ayudaste a\n"
	.string "atrapar un POKéMON, ¿verdad?\p"
	.string "Creo que eso hizo a WALLY\n"
	.string "muy feliz.\p"
	.string "De hecho, no solo a WALLY.\n"
	.string "A mí, su padre, también me alegró.\p"
	.string "Feliz de que tenga un amigo\n"
	.string "tan genial como tú.\p"
	.string "No es un soborno ni nada, pero\n"
	.string "me gustaría que tuvieras esto.$"

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces:
	.string "Si tu POKéMON sabe SURF, podrás\n"
	.string "ir a todo tipo de lugares.$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon:
	.string "WALLY volverá pronto a casa.\n"
	.string "Tengo muchas ganas de verlo.$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity:
	.string "¿Eh? ¿Viste a WALLY en\n"
	.string "CIUDAD VERAZ?\p"
	.string "Oh, {PLAYER}{KUN}, no seas tonto.\p"
	.string "Estará sano, pero no puede ir\n"
	.string "tan lejos solo\l"
	.string "por su cuenta.$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy:
	.string "WALLY estaba muy feliz al decirnos\n"
	.string "que atrapó un POKéMON.\p"
	.string "Hacía siglos que no lo veía\n"
	.string "sonreír así.$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling:
	.string "Quiero que guardes este secreto\n"
	.string "de mi esposo...\p"
	.string "Pero WALLY dejó PUEBLO VERDANTE\n"
	.string "sin avisar a nadie.\p"
	.string "Sabes, WALLY es débil, pero tiene\n"
	.string "una voluntad sorprendente.\p"
	.string "¡Seguro que volverá sano y salvo\n"
	.string "algún día!$"

