.set LOCALID_RIVAL_ON_BIKE, 7
.set LOCALID_RIVAL, 8

LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_GOLDENROD_CITY
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_GARBAGEVAR, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_GARBAGEVAR, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_RIVAL, 11, 9
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_GARBAGEFLAG
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_GARBAGEFLAG
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_GARBAGEVAR, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	goto_if_unset FLAG_MINTS_ENABLED, LavaridgeTown_EventScript_MayGiveGoGogglesNoMints
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_MayGiveGoGogglesNoMints::
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDadNoMints, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_GARBAGEVAR, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement OBJ_EVENT_ID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "MAY: {PLAYER}{KUN}! ¡Tanto tiempo!\p"
	.string "¿Eh? Mientras iba a las termas,\n"
	.string "ganaste la MEDALLA de LAVARIDGE.\p"
	.string "Debes haber atrapado\n"
	.string "buenos POKéMON…\l"
	.string "No, creo que los entrenaste.\p"
	.string "Creo que estaría bien que\n"
	.string "tengas esto.$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "MAY: Con esos GO-GOGGLES, no\n"
	.string "tendrás problemas en el desierto\l"
	.string "cerca de la RUTA 111.\p"
	.string "Pero, vaya, {PLAYER}{KUN}…\n"
	.string "Retando GIMNASIOS…\p"
	.string "¡Te esfuerzas para no perder\n"
	.string "contra mí, apuesto que sí!\p"
	.string "{PLAYER}{KUN}, creo que debo retar a\n"
	.string "tu papá en el GIMNASIO PETALBURG.\p"
	.string "¡Ah, y mira los NATURE MINTS\n"
	.string "en la FLORISTERÍA!\p"
	.string "¡Nos vemos!$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "BRENDAN: {PLAYER}, hola, hace tiempo.\n"
	.string "¿Cómo te va?\p"
	.string "Hmm…\n"
	.string "Tienes buenas MEDALLAS.\p"
	.string "Muy bien, entonces.\n"
	.string "Toma esto.$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "BRENDAN: Guárdalos si planeas ir al\n"
	.string "desierto cerca de la\l"
	.string "RUTA 111.\p"
	.string "Debe haber POKéMON que viven\n"
	.string "solo en el desierto.\l"
	.string "Podrías buscarlos por ahí.\p"
	.string "En cuanto a mí…\n"
	.string "Pienso retar a NORMAN,\l"
	.string "el LÍDER del GIMNASIO PETALBURG.\p"
	.string "A diferencia tuya, {PLAYER}, tu papá\n"
	.string "parece ser muy fuerte.\p"
	.string "¡Ah, y mira los NATURE MINTS\n"
	.string "en la FLORISTERÍA!\p"
	.string "¡Nos vemos!$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDadNoMints:
	.string "MAY: Con esos GO-GOGGLES, no\n"
	.string "tendrás problemas en el desierto\l"
	.string "cerca de la RUTA 111.\p"
	.string "Pero, vaya, {PLAYER}{KUN}…\n"
	.string "Retando GIMNASIOS…\p"
	.string "¡Te esfuerzas para no perder\n"
	.string "contra mí, apuesto que sí!\p"
	.string "{PLAYER}{KUN}, creo que debo retar a\n"
	.string "tu papá en el GIMNASIO PETALBURG.$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "Tengo aquí un HUEVO.\p"
	.string "Esperaba que naciera cubriéndolo con\n"
	.string "arena caliente en las termas.\l"
	.string "Pero eso no parece ser suficiente…\p"
	.string "He oído que sería mejor si estuviera\n"
	.string "junto a POKéMON y que lo\l"
	.string "llevaran consigo.\p"
	.string "Eres ENTRENADOR, ¿verdad?\n"
	.string "Tus POKéMON irradian vitalidad.\p"
	.string "Entonces, ¿qué dices?\n"
	.string "¿Llevarás este HUEVO para que nazca?$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
	.string "¡Bien! ¡Espero que camines mucho con\n"
	.string "este HUEVO!$"

LavaridgeTown_Text_ReceivedTheEgg:
	.string "{PLAYER} recibió el HUEVO.$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "Oh? Tienes demasiados POKéMON.\n"
	.string "No hay espacio para este HUEVO…$"

LavaridgeTown_Text_AsYouWishThen:
	.string "Como quieras, entonces…\p"
	.string "Si cambias de opinión sobre\n"
	.string "eclosionar este HUEVO, volveré.$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "A veces, se encuentra un HUEVO en la\n"
	.string "GUARDA POKéMON.\p"
	.string "O al menos eso dice el rumor.$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "Usamos el agua caliente que queremos,\n"
	.string "y las fuentes nunca se secan.\p"
	.string "¿No es mágico?\p"
	.string "Estas fuentes salen cerca de volcanes.\n"
	.string "El magma calienta el agua bajo la\l"
	.string "tierra y sube\l"
	.string "como fuente termal.$"

LavaridgeTown_Text_PokemonNippedBackside:
	.string "Estar enterrado en esta arena es…\n"
	.string "Suspiro…\p"
	.string "Tan cálido y celestial…\p"
	.string "¿Eh? ¡Gyaah! ¡Ay!\p"
	.string "¡Un POKéMON me mordió el trasero!$"

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "Oh, ¿te gustan las fuentes termales?\p"
	.string "Es sorprendente para alguien tan\n"
	.string "joven como tú.$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "Me baño en las fuentes cada día.\p"
	.string "Quiero ser una LÍDER de GIMNASIO\n"
	.string "bella y fuerte como FLANNERY.$"

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "Si meten POKéMON en las fuentes,\n"
	.string "sería muy extraño.\p"
	.string "Podría ser un baño eléctrico, de\n"
	.string "burbujas o hasta de lava…$"

LavaridgeTown_Text_HotSpringsClaims:
	.string "Dicen que estas aguas termales\n"
	.string "calman la tensión nerviosa,\l"
	.string "alivian dolores musculares, resuelven\l"
	.string "problemas románticos y atraen\l"
	.string "el dinero…$"

LavaridgeTown_Text_TownSign:
	.string "PUEBLO LAVARIDGE\p"
	.string "“CENTRO POKéMON TERMAL\n"
	.string "¡Un lugar excelente para relajarse!”$"

LavaridgeTown_Text_GymSign:
	.string "GIMNASIO POKéMON LAVARIDGE\n"
	.string "LÍDER: FLANNERY\l"
	.string "“¡Una pasión ardiente que quema!”$"

LavaridgeTown_Text_HerbShopSign:
	.string "TIENDA DE HIERBAS POKéMON\n"
	.string "“¡Sabor amargo, mejor cura!”$"

