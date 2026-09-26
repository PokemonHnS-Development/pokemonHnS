.set LOCALID_GRUNT, 3
.set LOCALID_DEVON_EMPLOYEE, 4
.set LOCALID_CELEBI, 17
.set LOCALID_OLD_MAN, 15
.set LOCALID_DUSCLOPS, 16

PetalburgWoods_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgWoods_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

PetalburgWoods_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_unset FLAG_EXTRA_LEGENDARIES, PetalburgWoods_SwitchToOld
	call_if_unset FLAG_SYS_GAME_CLEAR, PetalburgWoods_NoCelebiEvent
	call_if_set FLAG_SYS_GAME_CLEAR, PetalburgWoods_YesCelebiEvent
	end

PetalburgWoods_SwitchToOld::
	setmaplayoutindex LAYOUT_PETALBURG_WOODS_OLD
	setflag FLAG_OLD_MAN_AND_DUSCLOPS
	removeobject LOCALID_OLD_MAN
	removeobject LOCALID_DUSCLOPS
	return
	end

PetalburgWoods_NoCelebiEvent::
	checkflag FLAG_GARBAGEFLAG
	call_if_unset FLAG_GARBAGEFLAG, PetalburgWoods_CelebiEvent_End
	end

PetalburgWoods_YesCelebiEvent::
	checkflag FLAG_DEFEATEDCELEBI
	call_if_set FLAG_DEFEATEDCELEBI, PetalburgWoods_CelebiEvent_End
	call_if_unset FLAG_DEFEATEDCELEBI, PetalburgWoods_YesCelebiEvent2
	end

PetalburgWoods_YesCelebiEvent2::
	setflag FLAG_GARBAGEFLAG
	end

PetalburgWoods_CelebiEvent::
	lock
	playse SE_SUDOWOODO_SHAKE
	waitse
	msgbox Text_PetalburgWoods_Celebi0, MSGBOX_SIGN
	closemessage
	checkflag FLAG_GARBAGEFLAG
	call_if_unset FLAG_GARBAGEFLAG, PetalburgWoods_CelebiEvent_End
	call_if_set FLAG_GARBAGEFLAG, PetalburgWoods_CelebiEventGo
	end

PetalburgWoods_CelebiEventGo::
	applymovement OBJ_EVENT_ID_PLAYER, Movement_PetalburgWoods_Celebi1
	waitmovement 0
	msgbox Text_PetalburgWoods_Celebi1, MSGBOX_SIGN
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PetalburgWoods_CelebiEvent_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_RAIKOU, PetalburgWoods_CelebiEvent_Continue1
	msgbox Text_PetalburgWoods_Celebi_Donthave, MSGBOX_SIGN
	end

PetalburgWoods_CelebiEvent_Continue1::
	msgbox Text_PetalburgWoods_Celebi2, MSGBOX_SIGN
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PetalburgWoods_CelebiEvent_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_ENTEI, PetalburgWoods_CelebiEvent_Continue2
	msgbox Text_PetalburgWoods_Celebi_Donthave, MSGBOX_SIGN
	end

PetalburgWoods_CelebiEvent_Continue2::
	msgbox Text_PetalburgWoods_Celebi3, MSGBOX_SIGN
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PetalburgWoods_CelebiEvent_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_SUICUNE, PetalburgWoods_CelebiBattle
	msgbox Text_PetalburgWoods_Celebi_Donthave, MSGBOX_SIGN
	end

PetalburgWoods_CelebiEvent_End::
	releaseall
	end

PetalburgWoods_CelebiBattle::
	faceplayer
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Movement_PetalburgWoods_Celebi1
	waitmovement 0
	msgbox Text_PetalburgWoods_Celebi4, MSGBOX_DEFAULT
	setwildbattle SPECIES_CELEBI, 50
	waitse
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement LOCALID_CELEBI, PetalburgWoods_EventScript_CelebiMoves
	waitmovement 0
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, PetalburgWoods_CelebiEvent_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, PetalburgWoods_CelebiEvent_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, PetalburgWoods_CelebiEvent_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, PetalburgWoods_CelebiEvent_Ran
	releaseall
	end

PetalburgWoods_CelebiEvent_Won::
	applymovement LOCALID_CELEBI, PetalburgWoods_EventScript_CelebiMoves2
	waitmovement 0
	setflag FLAG_DEFEATEDCELEBI
	clearflag FLAG_GARBAGEFLAG
	end

PetalburgWoods_CelebiEvent_Ran::
	applymovement LOCALID_CELEBI, PetalburgWoods_EventScript_CelebiMoves2
	waitmovement 0
	end

PetalburgWoods_EventScript_CelebiMoves:
	delay_16
	delay_16
	delay_16
	walk_down
	set_visible
	step_end

PetalburgWoods_EventScript_CelebiMoves2:
	set_invisible
	walk_up
	step_end

Text_PetalburgWoods_Celebi0:
	.string "El árbol vibra.\p"
	.string "Sientes que alguien o algo\n"
	.string "te está observando…\p"
	.string "Pero… no ves ningún POKéMON…$"

Text_PetalburgWoods_Celebi1:
	.string ". . . \p"
	.string ". . . \p"
	.string "Oyes una voz tenue.\p"
	.string "Mu..e.. .. ..e . . .OS. K. ON\p"
	.string ". . . \p"
	.string "Mu..éstrame el POKéMON RAYO…$"

Text_PetalburgWoods_Celebi2:
	.string ". . . \p"
	.string ". . . \p"
	.string "Mu..e .he .OLCANO . ..MON$"

Text_PetalburgWoods_Celebi3:
	.string ". . . \p"
	.string ". . . \p"
	.string "Mu..e t.. AU.ORA …éMON.$"

Text_PetalburgWoods_Celebi4:
	.string ". . . \p"
	.string "Algo se aproxima…\p"
	.string ". . . $"

Text_PetalburgWoods_Celebi_Donthave:
	.string ". . . \p"
	.string "..o l..'t h… i….\p"
	.string "No lo tienes…$"

Movement_PetalburgWoods_Celebi1:
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

PetalburgWoods_Dusclops::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DUSCLOPS, CRY_MODE_NORMAL
	msgbox PetalburgWoods_Text_Dusclops, MSGBOX_DEFAULT
	waitmoncry
	release
	end

PetalburgWoods_Text_Dusclops:
	.string "DUSKY: ¡Dusk, dusk!$"

PetalburgWoods_Celebi_Sign::
	faceplayer
	goto_if_unset FLAG_ROBERTO1, PetalburgWoods_Celebi_SignFirstTime
	goto_if_set FLAG_DEFEATEDCELEBI, PetalburgWoods_Celebi_SignEventFinished
	goto_if_set FLAG_SYS_GAME_CLEAR, PetalburgWoods_Celebi_SignChampion
	msgbox Text_PetalburgWoods_Celebi_Sign, MSGBOX_NPC
	end

PetalburgWoods_Celebi_SignFirstTime::
	faceplayer
	msgbox Text_PetalburgWoods_Celebi_SignFirstTime, MSGBOX_NPC
	setflag FLAG_ROBERTO1
	end

PetalburgWoods_Celebi_SignEventFinished::
	faceplayer
	msgbox Text_PetalburgWoods_Celebi_SignEventFinished, MSGBOX_NPC
	end

PetalburgWoods_Celebi_SignChampion::
	faceplayer
	msgbox Text_PetalburgWoods_Celebi_SignEventChampion, MSGBOX_NPC
	end

Text_PetalburgWoods_Celebi_Sign:
	.string "Hola, entrenador.\p"
	.string "¿Peligro? No, no te preocupes.\l"
	.string "DUSKY está patrullando.\p"
	.string "¿Y tú? ¿Cómo va tu aventura\n"
	.string "por aquí?$"

Text_PetalburgWoods_Celebi_SignFirstTime:
	.string "Oh, un joven...\p"
	.string "¿Qué haces aquí en estos\n"
	.string "bosques oscuros y sombríos?\p"
	.string ". . .\p"
	.string "Ya veo. Solo estás de paso.\p"
	.string "¿Qué? ¿Ah, yo?\p"
	.string "Solo riego el santuario del árbol\n"
	.string "como siempre he hecho.\p"
	.string "Te preguntas por qué riego un árbol\n"
	.string "que parece inocente en medio\l"
	.string "del bosque, ¿verdad?\p"
	.string "Pero verás, este árbol es especial.\n"
	.string "Aquí vive un POKéMON MÍTICO.\l"
	.string "Es el GUARDIÁN DEL BOSQUE.\p"
	.string "He regado este árbol por más de\n"
	.string "veinte años de mi vida.\p"
	.string "Te aseguro que esta historia\n"
	.string "es tan real como el aire.\l"
	.string "El GUARDIÁN es pequeño, VERDE,\l"
	.string "y mirarlo se siente...\p"
	.string "Como ver un espíritu del bosque.\n"
	.string "Lamentablemente, lo vi por última\l" 
	.string "vez hace muchísimos años...\p"
	.string "¿Dónde estará el GUARDIÁN?\p"
	.string "Quizás deba ser MÁS FUERTE para\n"
	.string "que aparezca...\p"
	.string "Me pone triste ver lo débil que\n"
	.string "me he vuelto con los años.\p"
	.string "En fin, seguiré con mi labor.\n"
	.string "Nos vemos, joven.$"

Text_PetalburgWoods_Celebi_SignEventFinished:
	.string ". . . \p"
	.string "¡No puedo creer lo que veo!\n"
	.string "¿Luchaste contra el GUARDIÁN!?\p"
	.string "Jamás olvidaré este momento.\n"
	.string "Seguiré regando este santuario\l"
	.string "hasta que regrese en el futuro.$"

Text_PetalburgWoods_Celebi_SignEventChampion:
	.string "Hola de nuevo, joven.\p"
	.string "Algo ha estado pasando con el\n"
	.string "árbol GUARDIÁN.\p"
	.string "He oído unos murmullos\n"
	.string "cerca de él por muchas horas.\p"
	.string "Algo sobre POKéMON de RAYO, VOLCÁN\n"
	.string "y AURORA…\p"
	.string "Espera… conozco esas descripciones…\n"
	.string "¿Tres bestias? Pero…\p"
	.string "¿No son de esta región? ¿De dónde\n"
	.string "vienen? ¿GIOTO? ¿HOJO? ¿JONO? ¿JOHTO?\p"
	.string "Y si están aquí, en HOENN…\n"
	.string "¿Quizás se ocultan en lugares según\l"
	.string "sus descripciones?\p"
	.string "Si tienes tiempo, podrías\n"
	.string "echar un vistazo. ¿Qué opinas?$"

PetalburgWoods_EventScript_DevonResearcherLeft::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TONY, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TONY, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro::
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle::
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_GRUNT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull::
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish::
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_DEVON_EMPLOYEE
	setvar VAR_GARBAGEVAR, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround:
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft:
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance:
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer:
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed::
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1::
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2::
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_RIVAL_CYNDAQUIL_4, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_RIVAL_CYNDAQUIL_4
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_RIVAL_CYNDAQUIL_4
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2::
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_RIVAL_CYNDAQUIL_4
	release
	end

PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_RIVAL_CYNDAQUIL_4, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound:
	.string "Hmmm...\n"
	.string "No he encontrado ninguno...$"

PetalburgWoods_Text_HaveYouSeenShroomish:
	.string "Hola, ¿has visto algún POKéMON\n"
	.string "llamado SHROOMISH por aquí?\p"
	.string "Realmente amo a ese POKéMON.$"

PetalburgWoods_Text_IWasGoingToAmbushYou:
	.string "Iba a tenderte una emboscada, pero tú\n"
	.string "tenías que demorarte en BOSQUE PETALIA\l"
	.string "una eternidad, ¿verdad?\p"
	.string "¡Me harté de esperar, aquí estoy!$"

PetalburgWoods_Text_HandOverThosePapers:
	.string "¡Tú! ¡INVESTIGADOR DE DEVON!\p"
	.string "¡Dame esos papeles!$"

PetalburgWoods_Text_YouHaveToHelpMe:
	.string "¡Aiyeeeh!\p"
	.string "Eres un ENTRENADOR POKéMON, ¿no?\n"
	.string "¡Tienes que ayudarme, por favor!$"

PetalburgWoods_Text_NoOneCrossesTeamAqua:
	.string "¿Eh? ¿Qué crees que haces?\n"
	.string "¿Qué, vas a protegerlo?\p"
	.string "¡Nadie que se cruce con el TEAM AQUA\n"
	.string "tendrá piedad, ni siquiera un niño!\p"
	.string "¡Ven y lucha conmigo!$"

PetalburgWoods_Text_YoureKiddingMe:
	.string "¡No puede ser! ¡Eres fuerte!$"

PetalburgWoods_Text_YouveGotSomeNerve:
	.string "Grrr... ¡Tienes agallas al\n"
	.string "meterte con el TEAM AQUA!\l"
	.string "¡Ven y lucha conmigo otra vez!\p"
	.string "Quisiera decir eso, pero me quedé\n"
	.string "sin POKéMON...\p"
	.string "Y oye, nosotros del TEAM AQUA\n"
	.string "buscamos algo en PORTO SALADO.\p"
	.string "¡Te dejaré ir hoy!$"

PetalburgWoods_Text_ThatWasAwfullyClose:
	.string "Uff...\n"
	.string "¡Eso estuvo muy cerca!\p"
	.string "Gracias a ti, no me robó\n"
	.string "estos papeles importantes.\p"
	.string "¡Toma una GREAT BALL como\n"
	.string "agradecimiento!$"

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro:
	.string "¿No dijo ese matón del TEAM AQUA\n"
	.string "que buscaban algo en\l"
	.string "PORTO SALADO también?$"

PetalburgWoods_Text_ICantBeWastingTime:
	.string "¡Oh, no! ¡Es una crisis!\n"
	.string "¡No puedo perder tiempo!$"

PetalburgWoods_Text_YoureLoadedWithItems:
	.string "Llevas demasiados objetos.\n"
	.string "No puedo darte esta SUPER BALL.$"

PetalburgWoods_Text_GoBugPokemonTeam:
	.string "¡Atrapé muchos POKéMON!\p"
	.string "¡Vamos, vamos, vamos!\n"
	.string "¡Mi equipo de POKéMON bicho!$"

PetalburgWoods_Text_ICouldntWin:
	.string "Tengo todos estos POKéMON,\n"
	.string "pero no pude ganar…$"

PetalburgWoods_Text_ImOutOfPokeBalls:
	.string "Atrapé muchos POKéMON.\n"
	.string "Ya no tengo POKé BALLS.$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon:
	.string "Si llevas POKéMON bicho a la\n"
	.string "escuela, ¡serás popular al instante!$"

PetalburgWoods_Text_CantBePopularIfILose:
	.string "No seré popular si pierdo.$"

PetalburgWoods_Text_PeopleRespectYou:
	.string "Si tienes un POKéMON bicho grande,\n"
	.string "la gente te respetará por ello.$"

PetalburgWoods_Text_IWantRematch1:
	.string "¡Quiero revancha cuando mis\n"
	.string "POKéMON bicho crezcan!\p"
	.string "¡Te registraré en mi POKéNAV!$"

PetalburgWoods_Text_IWantRematch2:
	.string "¡Quiero revancha cuando mis\n"
	.string "POKéMON bicho crezcan!\p"
	.string "¡Te registraré en mi POKéNAV!$"

PetalburgWoods_Text_MyPokemonHaveGrown:
	.string "Mis POKéMON BUG ya crecieron.\n"
	.string "Volveré a ser popular.$"

PetalburgWoods_Text_CantBePopularIfLose:
	.string "No seré popular si pierdo.$"

PetalburgWoods_Text_IveBeenTrainingHard:
	.string "Eres popular si tienes\n"
	.string "POKéMON fuertes, ¿verdad?\l"
	.string "Por eso he entrenado duro.$"

PetalburgWoods_Text_StayOutOfTallGrass:
	.string "¡Hola!\n"
	.string "¿Tus POKéMON están bien?\p"
	.string "Si son débiles y quieres\n"
	.string "evitar batallas, no vayas\l"
	.string "por la hierba alta.$"

PetalburgWoods_Text_HiddenItemsExplanation:
	.string "A veces hay cosas en el\n"
	.string "suelo aunque no se vean.\p"
	.string "Por eso siempre miro bien\n"
	.string "por dónde camino.$"

PetalburgWoods_Text_TryUsingThisItem:
	.string "¡Oh, genial!\n"
	.string "¡Es la MEDALLA del GIMNASIO RUSTBORO!\p"
	.string "Debes ser un ENTRENADOR.\n"
	.string "Prueba a usar este objeto.$"

PetalburgWoods_Text_MiracleSeedExplanation:
	.string "Es una SEMILLA MILAGRO.\n"
	.string "Si un POKéMON la lleva, sus\l"
	.string "movimientos PLANTA son más fuertes.\p"
	.string "Además de esta, creo que hay\n"
	.string "otros objetos útiles para que\l"
	.string "los POKéMON los lleven.$"

PetalburgWoods_Text_TrainerTipsExperience:
	.string "CONSEJOS\p"
	.string "Cualquier POKéMON que salga aunque\n"
	.string "sea una vez gana puntos de EXP.\p"
	.string "Para subir a uno débil, ponlo a la\n"
	.string "izquierda de tu equipo.\p"
	.string "Al empezar la batalla, cámbialo.\n"
	.string "Ganará EXP sin correr\l"
	.string "ningún peligro.$"

PetalburgWoods_Text_TrainerTipsPP:
	.string "CONSEJOS\p"
	.string "Además de los HP, los POKéMON\n"
	.string "tienen PP para usar sus ataques\l"
	.string "durante la batalla.\p"
	.string "Si un POKéMON se queda sin PP, llévalo\n"
	.string "a un CENTRO POKéMON.$"

