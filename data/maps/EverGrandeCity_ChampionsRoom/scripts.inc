.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3

EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	goto_if_set FLAG_WALLACE_REMATCH, EverGrandeCity_ChampionsRoom_EventScript_WallaceRematch
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_WallaceRematch::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRETA_BF_BRAIN, EverGrandeCity_ChampionsRoom_Text_Defeat2
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated2
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated2::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit2
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit2
	waitmovement 0
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_STEVEN_REMATCH
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_GARBAGEFLAG
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit2:
	walk_up
	delay_16
	walk_up
	delay_8
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit2:
	walk_up
	delay_8
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "WALLACE: Bienvenido, {PLAYER}{KUN}.\p"
	.string "El incidente en CIUDAD ARDIENTE…\n"
	.string "Fue un trabajo estupendo, acabando\l"
	.string "con esa crisis tú solo.\p"
	.string "¡Ups!\p"
	.string "No sería justo decir que tú\n"
	.string "solo acabaste con la crisis.\p"
	.string "Superaste esa situación difícil\n"
	.string "al hacerte uno con tus POKéMON.\p"
	.string "Los ENTRENADORES criamos POKéMON\n"
	.string "dándoles objetos y enseñándoles\l"
	.string "nuevas técnicas de batalla.\p"
	.string "Pero nosotros también aprendemos\n"
	.string "muchas cosas de los POKéMON.\p"
	.string "Y aquí es donde tus logros se\n"
	.string "ponen a prueba contra lo que\l"
	.string "otros como tú han logrado.\p"
	.string "¡Ahora!\p"
	.string "¿Quién baila con más elegancia\n"
	.string "con sus POKéMON en HOENN?\p"
	.string "¡Muéstramelo aquí y ahora!$"

EverGrandeCity_ChampionsRoom_Text_IntroSpeech2:
	.string "WALLACE: Bienvenido, {PLAYER}{KUN}.\n"
	.string "Es un gusto tenerte de vuelta.\p"
	.string "A primera vista, pareces\n"
	.string "otra persona. ¿Te hiciste fuerte?\p"
	.string "Sí… Sí, así es. Oh…\n"
	.string "Esa mirada que me das…\p"
	.string "Está bien, veo que ya estás\n"
	.string "preparado para esta batalla.\p"
	.string "Veamos si puedes\n"
	.string "bailar a mi ritmo.\p"
	.string "¡Demuestra que eres el mejor\n"
	.string "ENTRENADOR POKéMON de HOENN!$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "Yo, el CAMPEÓN, caigo derrotado…\p"
	.string "Fue un trabajo maravilloso.\n"
	.string "Fuiste elegante, hasta el punto\l"
	.string "de enfurecer. ¡Fue glorioso!\p"
	.string "¡Felicidades, {PLAYER}{KUN}!\p"
	.string "¡Eres un ENTRENADOR POKéMON\n"
	.string "verdaderamente noble!$"

EverGrandeCity_ChampionsRoom_Text_Defeat2:
	.string "Yo, el CAMPEÓN, caigo derrotado…\p"
	.string "¡Otra vez! Increíble. Gran trabajo.\n"
	.string "Fuiste elegante, hasta el punto\l"
	.string "de enfurecer. ¡Fue glorioso!\p"
	.string "¡Felicidades, {PLAYER}{KUN}!\p"
	.string "¡Eres el mejor ENTRENADOR\n"
	.string "POKéMON de HOENN!$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "WALLACE: Los POKéMON que enviaste\n"
	.string "a combatir…\p"
	.string "A veces bailaban como brisa de\n"
	.string "primavera, y otras golpeaban\l"
	.string "como un rayo.\p"
	.string "Lideraste a tus POKéMON con una\n"
	.string "elegancia ligera pero segura.\p"
	.string "¡Hasta yo quedé deslumbrado por\n"
	.string "tu magistral actuación!\p"
	.string "Ahora estás en la gloriosa cima\n"
	.string "de la LIGA POKéMON.\p"
	.string "Te proclamo como el nuevo…\n"
	.string "de la región de HOENN…$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech2:
	.string "WALLACE: Los POKéMON que enviaste\n"
	.string "a combatir…\p"
	.string "Me recuerdan a los muchos bailes\n"
	.string "que aprendí por el mundo.\p"
	.string "Sus movimientos fueron brillantes\n"
	.string "y su actuación fue aún mejor.\p"
	.string "¡Estás en la gloriosa cima de la\n"
	.string "LIGA POKéMON, otra vez!\p"
	.string "Te proclamo como el nuevo\n"
	.string "CAMPEÓN de la región de HOENN…!\p"
	.string "¡Eso diría si no lo\n"
	.string "fueras ya!$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "Tengo un consejo antes de que\n"
	.string "desafíes al CAMPEÓN…$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "MAY: ¿Eh?\n"
	.string "¿Qué, qué, qué?\p"
	.string "{PLAYER}{KUN}…\n"
	.string "¿Será posible que…\l"
	.string "¿ya terminó?$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "BRENDAN: {PLAYER}!\p"
	.string "¿Quieres un consejo antes de\n"
	.string "desafiar al CAMPEÓN?…$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "BRENDAN: {PLAYER}…\p"
	.string "¿Me estás intentando decir…\n"
	.string "que venciste al CAMPEÓN?$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "PROF. BIRCH: ¿Ves?\n"
	.string "¿Qué te dije, SILVER?\p"
	.string "¿No te dije que no debías\n"
	.string "preocuparte por {PLAYER}{KUN}?\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, lo lograste.\p"
	.string "Cuando supe que venciste a tu\n"
	.string "padre en el GIMNASIO PETALBURG,\l"
	.string "pensé que tenías una oportunidad…\p"
	.string "¡Pero pensar que realmente\n"
	.string "eres el CAMPEÓN!\p"
	.string "¡Ah, sí!\p"
	.string "¿Qué pasó con tu POKéDEX?\n"
	.string "Aquí, déjame ver.$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "PROF. BIRCH: En fin,\n"
	.string "¡felicidades!\p"
	.string "¡Ahora, ve orgulloso al cuarto final!$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
	.string "WALLACE: {PLAYER}{KUN}…\p"
	.string "No, déjame decirlo bien.\p"
	.string "¡El nuevo CAMPEÓN!\p"
	.string "Ven conmigo.$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "WALLACE: Lo siento, pero…\p"
	.string "De aquí en adelante, solo los\n"
	.string "CAMPEONES pueden entrar.\p"
	.string "Tendrás que esperar afuera con\n"
	.string "el PROF. BIRCH.$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "MAY: Ugh…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "¡Es broma! ¡Está bien!\n"
	.string "¡Así es la regla!\p"
	.string "{PLAYER}{KUN}!\n"
	.string "¡De verdad, felicidades!$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "BRENDAN: ¡¿Qué?! … … … … …\n"
	.string "… … … … … … … …\p"
	.string "No hay nada que hacer si es la regla.\p"
	.string "{PLAYER}, ¡bien hecho!\n"
	.string "¡Felicidades!$"

