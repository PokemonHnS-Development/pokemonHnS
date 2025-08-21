@ attempting to separate out elm scripting from birch
ProfElm_EventScript_UpdateLocation::
	goto_if_set FLAG_SYS_GAME_CLEAR, ProfElm_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 0, ProfElm_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 1, ProfElm_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 2, ProfElm_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 3, ProfElm_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 4, ProfElm_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 5, ProfElm_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 6, ProfElm_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 7, ProfElm_EventScript_MoveToLab
	return

ProfElm_EventScript_RatePokedexOrRegister::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, ProfElm_EventScript_GoFindMrPokemon
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 4, ProfElm_EventScript_Robbery
	goto ProfElm_EventScript_AskRatePokedex
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfElm
	release
	end

ProfElm_EventScript_GoFindMrPokemon::
	msgbox gBirchDexRatingText_GoFindMrPokemon MSGBOX_DEFAULT
	release
	end

ProfElm_EventScript_Robbery::
	msgbox gBirchDexRatingText_Robbery MSGBOX_DEFAULT
	release
	end

ProfElm_EventScript_AskRatePokedex::
	msgbox gBirchDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ProfElm_EventScript_DeclineRating
	call ProfElm_EventScript_RatePokedex
	release
	end

ProfElm_EventScript_DeclineRating::
	msgbox gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfElm_EventScript_ShowRatingMessage::
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfElm_EventScript_RatePokedex::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	msgbox gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfElm_EventScript_ShowRatingMessage
	goto_if_eq VAR_0x800A, 0, Common_EventScript_NopReturn  @ National dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num National seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num National caught
	msgbox gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return
