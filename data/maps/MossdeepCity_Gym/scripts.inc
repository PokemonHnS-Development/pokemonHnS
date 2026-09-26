MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

MossdeepCity_Gym_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower since it can collide with moving statues
	end

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MAHOGANY_TOWN_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	setvar VAR_GARBAGEVAR, 1
	setflag FLAG_GARBAGEFLAG
	setvar VAR_GARBAGEVAR, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_PRYCE_2, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
	.string "Hola, ¿cómo va todo, futuro\n"
	.string "{PLAYER} CAMPEÓN?\p"
	.string "Los LÍDERES de GIMNASIO usan\n"
	.string "POKéMON tipo PSÍQUICO.\p"
	.string "Si luchas contra ellos con\n"
	.string "tipo LUCHA o VENENO,\l"
	.string "¡te harán un daño horrible!\p"
	.string "Además, usarán ataques\n"
	.string "combinados increíbles.\p"
	.string "Para ganar, demuestra que tienes\n"
	.string "un gran vínculo con tus\l"
	.string "POKéMON. ¡A por ello!$"

MossdeepCity_Gym_Text_GymGuidePostVictory:
	.string "¡Guau, eres asombroso!\n"
	.string "¡Eres un gran ENTRENADOR!$"

MossdeepCity_Gym_Text_PrestonIntro:
	.string "¡Las batallas dependen de tu\n"
	.string "espíritu! ¡Los débiles no ganan!$"

MossdeepCity_Gym_Text_PrestonDefeat:
	.string "¡Perdí!\n"
	.string "¡Debo templar mi espíritu otra vez!$"

MossdeepCity_Gym_Text_PrestonPostBattle:
	.string "Los indecisos pierden.\n"
	.string "Esa es mi advertencia para ti.$"

MossdeepCity_Gym_Text_VirgilIntro:
	.string "¡Déjame ver tu talento!$"

MossdeepCity_Gym_Text_VirgilDefeat:
	.string "¡Tienes un talento espectacular!$"

MossdeepCity_Gym_Text_VirgilPostBattle:
	.string "Si hay prodigios en el mundo,\n"
	.string "¡nuestros LÍDERES lo son!\p"
	.string "Aunque, puede que seas más\n"
	.string "talentoso que ellos…$"

MossdeepCity_Gym_Text_BlakeIntro:
	.string "Fufufufu... ¡Mira cómo levito una\n"
	.string "POKé BALL con telequinesis!\p"
	.string "¡Wrooooooooaaaar!\n"
	.string "... ... ... ... ... ...\p"
	.string "A veces, pierdo la sincronía...$"

MossdeepCity_Gym_Text_BlakeDefeat:
	.string "¡Mis habilidades de batalla con\n"
	.string "POKéMON también fallan!$"

MossdeepCity_Gym_Text_BlakePostBattle:
	.string "La POKé BALL pesaba mucho para\n"
	.string "mi mente. Pero esta pelusa...\p"
	.string "¡Whoooooooooooooooh!\n"
	.string "... ... ... ... ...\p"
	.string "¡No, no estoy haciendo trampa!\n"
	.string "¡No soplé! ¡Lo juro!$"

MossdeepCity_Gym_Text_HannahIntro:
	.string "Si pierdes contra mí, no seas\n"
	.string "duro contigo mismo.\p"
	.string "No es que seas débil, ¡es que yo\n"
	.string "soy demasiado fuerte!$"

MossdeepCity_Gym_Text_HannahDefeat:
	.string "¡Es que eres demasiado fuerte!$"

MossdeepCity_Gym_Text_HannahPostBattle:
	.string "No me desanimaré por perder.\n"
	.string "Solo debo entrenar más duro.\p"
	.string "¡El pensamiento positivo es mi\n"
	.string "punto fuerte!$"

MossdeepCity_Gym_Text_SamanthaIntro:
	.string "Lo veo...\n"
	.string "Veo tu futuro...\p"
	.string "¡Si me vences, te diré cuál es\n"
	.string "tu futuro!$"

MossdeepCity_Gym_Text_SamanthaDefeat:
	.string "¡Me rindo!$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
	.string "Librarás batallas intensas\n"
	.string "con nuestros LÍDERES de GIMNASIO…\p"
	.string "El resultado…\n"
	.string "¡No te lo diré yo!$"

MossdeepCity_Gym_Text_MauraIntro:
	.string "Los caminos que recorriste…\n"
	.string "Lo que has experimentado…\p"
	.string "¡Ven a mí con todo lo que\n"
	.string "has aprendido!$"

MossdeepCity_Gym_Text_MauraDefeat:
	.string "¡Has recorrido un camino glorioso!$"

MossdeepCity_Gym_Text_MauraPostBattle:
	.string "Un futuro brillante espera a quien\n"
	.string "trabajó con diligencia.\p"
	.string "Para quien fue perezoso, solo hay\n"
	.string "desesperación al final.\p"
	.string "Cosechas lo que siembras…$"

MossdeepCity_Gym_Text_SylviaIntro:
	.string "¡Aun arriesgando mi vida, ganaré\n"
	.string "esta batalla!$"

MossdeepCity_Gym_Text_SylviaDefeat:
	.string "Lo que haces…\n"
	.string "Me horroriza…$"

MossdeepCity_Gym_Text_SylviaPostBattle:
	.string "Cómo te atreves a vencerme…\p"
	.string "No será mi culpa si algo\n"
	.string "terrible te sucede…$"

MossdeepCity_Gym_Text_NateIntro:
	.string "Jo jo jo.\p"
	.string "Necesitas que te muestre lo tenaz\n"
	.string "que es el tipo PSÍQUICO.$"

MossdeepCity_Gym_Text_NateDefeat:
	.string "¡Oh! ¡Vaya, vaya!\n"
	.string "¡Tu estilo de combate es fantástico!$"

MossdeepCity_Gym_Text_NatePostBattle:
	.string "Yo... no dejo que la derrota me\n"
	.string "afecte, por muy mal que esté.$"

MossdeepCity_Gym_Text_KathleenIntro:
	.string "¡Deja que te muestre un momento\n"
	.string "terrible y horroroso!$"

MossdeepCity_Gym_Text_KathleenDefeat:
	.string "¡N-nooooo!$"

MossdeepCity_Gym_Text_KathleenPostBattle:
	.string "¡Tu vitalidad es contagiosa!\n"
	.string "¡Aléjate de mí rápido!$"

MossdeepCity_Gym_Text_CliffordIntro:
	.string "Ya no estoy en mi mejor momento, pero\n"
	.string "no me trates con condescendencia.$"

MossdeepCity_Gym_Text_CliffordDefeat:
	.string "¡Ah, rebosas con el poder\n"
	.string "de la juventud!$"

MossdeepCity_Gym_Text_CliffordPostBattle:
	.string "Parece que no pude superar\n"
	.string "tu energía juvenil.$"

MossdeepCity_Gym_Text_MaceyIntro:
	.string "¡No pasarás hasta el final!\n"
	.string "¡No mientras yo esté aquí!$"

MossdeepCity_Gym_Text_MaceyDefeat:
	.string "¿Cómo puedes ser tan\n"
	.string "ridículamente fuerte?$"

MossdeepCity_Gym_Text_MaceyPostBattle:
	.string "¡Bah! Serás fuerte, pero no eres\n"
	.string "apto para el tipo PSÍQUICO!\p"
	.string "¡Tu forma de luchar es brutal!$"

MossdeepCity_Gym_Text_NicholasIntro:
	.string "¡Roaaar! ¡Prueba el poder de mis\n"
	.string "POKéMON en combate!$"

MossdeepCity_Gym_Text_NicholasDefeat:
	.string "¡Oh!\n"
	.string "¡Me vencieron!$"

MossdeepCity_Gym_Text_NicholasPostBattle:
	.string "¡Bien! Ahora crearé un poder de\n"
	.string "POKéMON invencible.$"

MossdeepCity_Gym_Text_TateAndLizaIntro:
	.string "TATE: Jeje... ¿Te sorprendiste?\p"
	.string "LIZA: Jiji... ¿Te sorprendiste?\p"
	.string "TATE: ¿Que haya dos LÍDERES de GYM?\n"
	.string "LIZA: ¿Que haya dos LÍDERES de GYM?\p"
	.string "TATE: ¡Somos gemelos!\n"
	.string "LIZA: ¡Somos gemelas!\p"
	.string "TATE: No hace falta hablar porque...\n"
	.string "LIZA: Cada uno puede saber qué...\p"
	.string "TATE: El otro está pensando...\n"
	.string "LIZA: ¡Todo en nuestra mente!\p"
	.string "TATE: Esta combinación nuestra...\n"
	.string "LIZA: ¿Podrás vencerla?$"

MossdeepCity_Gym_Text_TateAndLizaDefeat:
	.string "TATE: ¡¿Qué?! Nuestra combinación...\n"
	.string "LIZA: ¡Fue destrozada!\p"
	.string "TATE: No hay remedio. Ganaste...\n"
	.string "LIZA: Toma esto en reconocimiento.$"

MossdeepCity_Gym_Text_ReceivedMindBadge:
	.string "{PLAYER} recibió la INSIGNIA MENTE\n"
	.string "de TATE y LIZA.$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
	.string "TATE: La INSIGNIA MENTE sube el\n"
	.string "ATQ. ESP. y DEF. ESP. de POKéMON.\p"
	.string "LIZA: También permite usar la MO\n"
	.string "BUCEO fuera de combate.\p"
	.string "TATE: También deberías llevarte esto.$"

MossdeepCity_Gym_Text_ExplainCalmMind:
	.string "TATE: Esa MT04 contiene...\n"
	.string "LIZA: ¡CALMA MENTAL!\p"
	.string "TATE: Sube el ATQ. ESP. y...\n"
	.string "LIZA: ¡Sube la DEF. ESP.!\p"
	.string "TATE: Es un movimiento perfecto...\n"
	.string "LIZA: ¡Para POKéMON PSÍQUICOS!\p"
	.string "... ... ... ... ... ...$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
	.string "Se registró a los LÍDERES TATE y LIZA\n"
	.string "en el POKéNAV.$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
	.string "TATE: Parece que el vínculo entre tú\n"
	.string "y tu POKéMON es más fuerte que el\l"
	.string "vínculo que tenemos como gemelos.\p"
	.string "LIZA: ¡Te volverás aún más fuerte!\n"
	.string "Peleamos contigo, así que lo sabemos.$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
	.string "TATE: Jeje... ¿Te sorprendiste?\p"
	.string "LIZA: ¿Que haya dos LÍDERES de GYM?\p"
	.string "TATE: Ups, solo tienes un...\n"
	.string "LIZA: POKéMON que puede luchar.\p"
	.string "TATE: ¡No podemos luchar así!\p"
	.string "LIZA: Si quieres retarnos,\n"
	.string "trae más POKéMON.$"

MossdeepCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON CIUDAD FONDO MAR$"

MossdeepCity_Gym_Text_GymStatueCertified:
	.string "GYM POKéMON DE CIUDAD FONDO MAR\p"
	.string "ENTRENADORES DE LIZA Y TATE:\n"
	.string "{PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
	.string "TATE: POKéMON…\n"
	.string "LIZA: POKéMON…\p"
	.string "TATE: Al cambiar el equipo…\n"
	.string "LIZA: El estilo de lucha cambia.\p"
	.string "TATE: Pero yo…\n"
	.string "LIZA: Pero yo…\p"
	.string "TATE: ¡Siempre estaré con LIZA!\n"
	.string "LIZA: ¡Siempre estaré con TATE!\p"
	.string "TATE: Nuestra combinación…\n"
	.string "LIZA: ¡Te la mostraremos otra vez!$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
	.string "TATE: Tú y tus POKéMON…\n"
	.string "LIZA: ¡Parecen hermanos!$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
	.string "TATE: Puedes derribarnos,\n"
	.string "¡pero nunca nos rendiremos!\p"
	.string "LIZA: Porque nosotros dos,\n"
	.string "¡siempre nos apoyamos!$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "TATE: Has vuelto…\n"
	.string "LIZA: Has vuelto…\p"
	.string "TATE: Para una revancha.\n"
	.string "LIZA: Para una revancha.\p"
	.string "TATE: Pero…\n"
	.string "LIZA: Para el combate…\p"
	.string "TATE: ¡Traes solo un POKéMON!\n"
	.string "LIZA: ¡Traes solo un POKéMON!\p"
	.string "TATE: Necesitamos que traigas…\n"
	.string "LIZA: Dos POKéMON la próxima vez.$"
