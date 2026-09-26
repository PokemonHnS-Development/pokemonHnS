.set LOCALID_WOMAN_1, 19
.set LOCALID_MAN_1, 20

LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

LilycoveCity_OnTransition:
	callnative SetTimeBasedEncounters
	setflag FLAG_VISITED_SAFFRON_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_GARBAGEFLAG
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_GymSign::
	msgbox LilycoveCity_Text_GymSign, MSGBOX_SIGN
	end

LilycoveCity_Text_GymSign:
	.string "GIMNASIO DE ENTRENAMIENTO.\p"
	.string "¡Maximiza el potencial de tus\n"
	.string "POKéMON fácilmente!$"

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_GARBAGEFLAG
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
	.string "MAY: ¡Hola!\n"
	.string "{PLAYER}{KUN}, ¿tú también compras?\p"
	.string "Compré muchos MUÑECOS y\n"
	.string "POSTERS.\p"
	.string "Claro, también atrapé muchos\n"
	.string "POKéMON y los estoy criando\l"
	.string "bien.\p"
	.string "De hecho, me preocupa si tú estás\n"
	.string "criando bien a tus POKéMON, {PLAYER}{KUN}.\p"
	.string "Lucharé contigo para que me\n"
	.string "muestres tus POKéMON, {PLAYER}{KUN}.$"

LilycoveCity_Text_MayNotRaisingPokemon:
	.string "MAY: ¿Por qué? {PLAYER}{KUN}, ¿no has\n"
	.string "estado criando a tus POKéMON?\p"
	.string "Eso no es muy bueno para un\n"
	.string "ENTRENADOR…$"

LilycoveCity_Text_MayBattleMe:
	.string "MAY: ¡Vamos, lucha conmigo para que\n"
	.string "vea tus POKéMON!$"

LilycoveCity_Text_MayWontBeBeaten:
	.string "MAY: ¡Los POKéMON que crié no serán\n"
	.string "vencidos por los tuyos, {PLAYER}{KUN}!$"

LilycoveCity_Text_MayDefeat:
	.string "… … … … … … … …\p"
	.string "Recuerdo la batalla que tuve contigo,\n"
	.string "{PLAYER}{KUN}, en la RUTA 103.\p"
	.string "Esa batalla te ayudó a ser así de\n"
	.string "fuerte, {PLAYER}{KUN}, ¿verdad?$"

LilycoveCity_Text_MayGoingBackToLittleroot:
	.string "MAY: Pienso volver a\n"
	.string "PUEBLO RAÍZ pronto.\p"
	.string "Atrapé un buen grupo de POKéMON\n"
	.string "y mi POKéDEX avanza, así que\l"
	.string "iré a casa a mostrárselo a mi papá.$"

LilycoveCity_Text_MayYouGoingToCollectBadges:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p"
	.string "¿Ganar todas las MEDALLAS y enfrentar\n"
	.string "la LIGA POKéMON?\p"
	.string "Bueno, mientras buscas MEDALLAS,\n"
	.string "{PLAYER}{KUN}, yo trabajaré en mi\l"
	.string "POKéDEX. ¡La completaré antes que tú!\p"
	.string "¡Nos vemos!$"

LilycoveCity_Text_MayYouGoingToPokemonLeague:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p"
	.string "¿Aceptarás el desafío de la\n"
	.string "POKéMON LEAGUE?\p"
	.string "¿O vas a completar tu\n"
	.string "POKéDEX?\p"
	.string "Perdí contra ti en batalla,\n"
	.string "¡pero completaré mi POKéDEX antes!\p"
	.string "¡Nos vemos!$"

LilycoveCity_Text_MayYouGoingToBattleFrontier:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p"
	.string "¿Aceptarás el desafío de la\n"
	.string "BATTLE FRONTIER?\p"
	.string "¿O vas a completar tu\n"
	.string "POKéDEX?\p"
	.string "Perdí contra ti en combate,\n"
	.string "¡pero completaré mi POKéDEX antes!\p"
	.string "¡Nos vemos!$"

LilycoveCity_Text_BrendanShoppingLetsBattle:
	.string "BRENDAN: ¡Hola, es {PLAYER}!\p"
	.string "Hago un recado para mi papá.\n"
	.string "No, no voy a comprar MUÑECAS.\p"
	.string "En fin, ha pasado tiempo.\p"
	.string "¿Batallamos para ver quién ha\n"
	.string "entrenado mejor a sus POKéMON?$"

LilycoveCity_Text_BrendanNoConfidence:
	.string "BRENDAN: ¿Qué pasa?\n"
	.string "¿No tienes confianza?$"

LilycoveCity_Text_BrendanBattleMe:
	.string "BRENDAN: ¿Batallamos para ver quién\n"
	.string "entrenó mejor a sus POKéMON?$"

LilycoveCity_Text_BrendanWontBeBeaten:
	.string "BRENDAN: Ay, pero ya sabes que no\n"
	.string "voy a perder contra {PLAYER}.$"

LilycoveCity_Text_BrendanDefeat:
	.string "Humph...\n"
	.string "Has entrenado mucho.\p"
	.string "Eso duele... yo empecé antes\n"
	.string "que tú como ENTRENADOR...$"

LilycoveCity_Text_BrendanGoingBackToLittleroot:
	.string "BRENDAN: Yo...\n"
	.string "pienso volver a PUEBLO RAÍZ.\p"
	.string "Ayudo a mi papá con su POKéDEX.\n"
	.string "Va muy bien, así que debo\l"
	.string "ir a mostrárselo.$"

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
	.string "{PLAYER}, ¿qué vas a hacer?\p"
	.string "¿Juntar las MEDALLAS de GIMNASIO y\n"
	.string "ir a la LIGA POKéMON?\p"
	.string "Tal vez yo también lo haga…\p"
	.string "Bueno, en fin, ¡ánimo!$"

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
	.string "{PLAYER}, ¿qué vas a hacer?\p"
	.string "Siendo tan fuerte, ¿irás al\n"
	.string "desafío de la LIGA POKéMON?\p"
	.string "Je, incluso yo, si entreno más a mis\n"
	.string "POKéMON, seré más fuerte que tú,\l"
	.string "{PLAYER}.\p"
	.string "Bueno, en fin, ¡ánimo!$"

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
	.string "{PLAYER}, ¿qué vas a hacer?\p"
	.string "¿Aceptarás el desafío de la\n"
	.string "BATTLE FRONTIER?\p"
	.string "¿O vas a completar tu\n"
	.string "POKéDEX?\p"
	.string "Eres fuerte, deberías pensar en la\n"
	.string "BATTLE FRONTIER.\p"
	.string "Je, si entreno más a mis POKéMON,\n"
	.string "seré más fuerte que tú, {PLAYER}.\p"
	.string "Tal vez debería ir a la BATTLE\n"
	.string "FRONTIER.\p"
	.string "Bueno, en fin, ¡ánimo!$"

LilycoveCity_Text_MovedLootIntoHideoutToday:
	.string "Fufufu…\p"
	.string "Hoy movimos más botín a nuestro\n"
	.string "ESCONDITE secreto…\p"
	.string "¡¿Quién eres?!\n"
	.string "¡Solo hablaba conmigo mismo!$"

LilycoveCity_Text_ChanceToDoBigThings:
	.string "Soy un RECLUTA, no sé qué piensa\n"
	.string "el JEFE…\p"
	.string "¡Pero en el TEAM AQUA tendré la\n"
	.string "oportunidad de hacer cosas grandes!\p"
	.string "¡¿Quién eres?!\n"
	.string "¡Solo hablaba conmigo mismo!$"

LilycoveCity_Text_DontGoNearCaveInCove:
	.string "¡Oye, tú!\p"
	.string "¡No te acerques a la cueva de la cala!\p"
	.string "¿Por qué? ¡No necesito darte razones!\n"
	.string "¡Soy adulto, así que hazme caso!$"

LilycoveCity_Text_IfWorldBecomesOurs:
	.string "Si este mundo entero es nuestro,\n"
	.string "del TEAM AQUA, será un lugar más\l"
	.string "feliz para los POKéMON también.$"

LilycoveCity_Text_WailmerLeapOutOfWater:
	.string "¡Allí! ¡WAILMER!\n"
	.string "¡Salta del agua ahora!$"

LilycoveCity_Text_GetLostMessingUpTraining:
	.string "¿Eh? ¿Qué quieres?\p"
	.string "Arruinas nuestro entrenamiento,\n"
	.string "¿así que puedes largarte?$"

LilycoveCity_Text_ContestHallInTown:
	.string "Hay un CONTEST HALL de POKéMON\n"
	.string "en este pueblo.\p"
	.string "Eso significa que vendrán POKéMON\n"
	.string "bien criados de todo el país.\p"
	.string "¡Mi corazón late de emoción!$"

LilycoveCity_Text_StrangeCaveInCove:
	.string "¿Viste esa cueva extraña en la\n"
	.string "cala al borde del pueblo?$"

LilycoveCity_Text_GoingToMoveDeleterForHMs:
	.string "Enseñaré nuevos movimientos a mis\n"
	.string "POKéMON para un CONCURSO.\p"
	.string "Iré con el BORRADOR DE MOVIMIENTOS\n"
	.string "para que olvide las MO$"

LilycoveCity_Text_ImFromKanto:
	.string "Vengo de KANTO.\p"
	.string "La región de HOENN es hermosa con\n"
	.string "su agua y naturaleza verde.\p"
	.string "¿Eh? Espera un segundo...\p"
	.string "¿Habrá POKéMON raros que vivan\n"
	.string "solo en esta zona?$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
	.string "El TEAM AQUA entrena sus\n"
	.string "WAILMER en la cala.\p"
	.string "¡Nosotros, los MARINEROS, no podemos\n"
	.string "sacar los botes con ellos ahí!$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
	.string "¡Ahoy! ¿Te enteraste?\p"
	.string "¡Alguien echó al TEAM AQUA\n"
	.string "de nuestro camino!\p"
	.string "Sacaron a los WAILMER de la cala,\n"
	.string "¡ya podemos usar los botes!$"

LilycoveCity_Text_SomeoneStoleMyPokemon:
	.string "Dormía tranquilo en la posada\n"
	.string "al sonido de las olas...\p"
	.string "¡Cuando alguien robó mi POKéMON!\p"
	.string "¿Quién fue el secuestrador?\n"
	.string "¿El TEAM AQUA? ¿Fue el TEAM AQUA?$"

LilycoveCity_Text_MissingPokemonCameBack:
	.string "Mi POKéMON perdido...\n"
	.string "¡Volvió sin que me diera cuenta!$"

LilycoveCity_Text_ImArtDealer:
	.string "Soy COMERCIANTE DE ARTE.\p"
	.string "Compro y vendo bellas artes,\n"
	.string "especialmente pinturas.\p"
	.string "Oí que el MUSEO de aquí tiene\n"
	.string "obras magníficas en exhibición...$"

LilycoveCity_Text_SeaRemainsForeverYoung:
	.string "Aunque envejezcamos y nos arruguemos,\n"
	.string "el mar siempre es joven con\l"
	.string "el brillo vívido de la vida...\p"
	.string "Fwohoho fwohohohoho...$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
	.string "Hace sesenta años mi esposo me\n"
	.string "propuso matrimonio aquí.\l"
	.string "El mar sigue tan bello como siempre.\p"
	.string "Mufufufu mufufufufufu...$"

LilycoveCity_Text_TeamAquaRenovatedCavern:
	.string "Hm, ¿conoces la cueva peculiar\n"
	.string "de esta caleta?\p"
	.string "Era una formación natural,\n"
	.string "pero el TEAM AQUA llegó\l"
	.string "e hizo sus reformas.\p"
	.string "Se hacen llamar el\n"
	.string "¡nature-loving TEAM AQUA!\p"
	.string "¡Pero lo que hacen y dicen\n"
	.string "no coinciden para nada!$"

LilycoveCity_Text_TeamAquaLotGoneForGood:
	.string "Esa cueva en la caleta...\p"
	.string "No lo noté al principio,\n"
	.string "pero ahora está vacía.\p"
	.string "Ese TEAM AQUA debe\n"
	.string "haberse ido para siempre.$"

LilycoveCity_Text_CitySign:
	.string "CIUDAD VERAZON\p"
	.string "Donde termina la tierra y\n"
	.string "comienza el mar.$"

LilycoveCity_Text_ContestHallSign:
	.string "SALA DE CONCURSOS POKéMON\n"
	.string "¡El punto de encuentro TRAINERS!$"

LilycoveCity_Text_MotelSign:
	.string "MOTEL COVE LILY\p"
	.string "“Recuérdanos como COVE LILY de\n"
	.string "CIUDAD VERALUNA.”$"

LilycoveCity_Text_MuseumSign:
	.string "MUSEO DE VERALUNA\p"
	.string "“¡Colección de Obras Maestras de\n"
	.string "POKéMON en exhibición!”$"

LilycoveCity_Text_MuseumSignPlayersExhibit:
	.string "MUSEO DE VERALUNA\p"
	.string "“¡Colección de POKéMON de {PLAYER}\n"
	.string "en exhibición!”$"

LilycoveCity_Text_HarborSignUnderConstruction:
	.string "PUERTO DE CIUDAD VERALUNA\p"
	.string "“El ferry S.S. TIDAL se construye\n"
	.string "en CIUDAD PORTUAL.\p"
	.string "“El servicio comenzará\n"
	.string "muy pronto.”$"

LilycoveCity_Text_HarborSign:
	.string "PUERTO DE CIUDAD VERALUNA\p"
	.string "“Disfruta un crucero delicioso en\n"
	.string "el ferry S.S. TIDAL.”$"

LilycoveCity_Text_TrainerFanClubSign:
	.string "CLUB DE FANS DE ENTRENADORES\p"
	.string "Hay nombres de ENTRENADORES escritos\n"
	.string "por todo el cartel…$"

LilycoveCity_Text_DepartmentStoreSign:
	.string "TIENDAS DE CIUDAD VERALUNA\p"
	.string "“¡Lleno de productos geniales y\n"
	.string "emoción!\p"
	.string "“¡El lugar ideal para hallar lo que\n"
	.string "necesitas!”$"

LilycoveCity_Text_MoveDeletersHouseSign:
	.string "CASA DEL BORRADOR\p"
	.string "Borra movimientos de POKéMON.$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
	.string "¿Sabes de la máquina\n"
	.string "BERRY BLENDER?$"

LilycoveCity_Text_FasterSpinBetterPokeblocks:
	.string "La gente debe trabajar unida para que\n"
	.string "gire más rápido.\p"
	.string "He oído que mientras más rápido gire,\n"
	.string "mejores {POKEBLOCK}S obtendrás.$"

LilycoveCity_Text_ExplainBerryBlender:
	.string "Sirve para hacer un dulce\n"
	.string "llamado {POKEBLOCK}.\p"
	.string "Si le das un buen {POKEBLOCK} a un\n"
	.string "POKéMON, su estado mejorará mucho.$"

LilycoveCity_Text_HeardTowerCalledSkyPillar:
	.string "Oí que hay una torre en alguna\n"
	.string "ruta marina.\p"
	.string "Dicen que se llama SKY PILLAR.$"

LilycoveCity_Text_SawTallTowerOnRoute131:
	.string "Vi una torre alta por algún lugar\n"
	.string "de la RUTA 131.\p"
	.string "¿Será posible que sea esa…?$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
	.string "Llegamos aquí en nuestra\n"
	.string "luna de miel.\p"
	.string "Vimos un POKéMON tipo DRAGÓN\n"
	.string "volando muy alto en el cielo.\p"
	.string "¿Viven POKéMON así de geniales en\n"
	.string "la región de HOENN?$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
	.string "En nuestra luna de miel, juramos ver\n"
	.string "muchos POKéMON raros.\p"
	.string "Nos alegró ver uno tan raro apenas\n"
	.string "llegamos aquí.\p"
	.string "¡O sea, estamos muy felices!$"
