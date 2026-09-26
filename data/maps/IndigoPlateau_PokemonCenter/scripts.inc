.set LOCALID_NURSE, 1
.set LOCALID_INDIGOPLATEAU_ABRA, 6

IndigoPlateau_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, IndigoPlateau_PokemonCenter_OnFrame 
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_Pokecenter_OnTransition
	.byte 0

IndigoPlateau_PokemonCenter_OnFrame::
	map_script_2 VAR_LEAGUE_STATE, 0, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 2, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 3, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 4, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 5, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 6, IndigoPlateau_PokemonCenter_Enter
	.2byte 0

IndigoPlateau_PokemonCenter_Enter::
	setflag FLAG_VISITED_INDIGO_PLATEAU
	setvar VAR_LEAGUE_STATE, 1
	end

IndigoPlateau_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU
	end


IndigoPlateau_EventScript_Cooltrainer::
	msgbox IndigoPlateau_Text_CooltrainerM, MSGBOX_NPC
	end

IndigoPlateau_EventScript_BlackBelt::
	msgbox IndigoPlateau_Text_Blackbelt, MSGBOX_NPC
	end

IndigoPlateau_EventScript_ShigyNinja::
	msgbox IndigoPlateau_Text_ShigyNinja, MSGBOX_NPC
	end

IndigoPlateau_Text_ShigyNinja:
	.string "¡Felicidades por llegar aquí!\p"
	.string "He visto a muchos ENTRENADORES\n"
	.string "pasar por aquí estos años, y\l"
	.string "todos son muy especiales.\p"
	.string "¡Debes estar orgulloso de ti\n"
	.string "por llegar tan lejos!\p"
	.string "¡Ahora, ve por ellos!$"

IndigoPlateau_Text_Blackbelt:
	.string "La LIGA POKéMON no acepta\n"
	.string "nuevos retadores ahora.\p"
	.string "Vuelve más tarde.$"

IndigoPlateau_Text_CooltrainerM:
    .string "En la LIGA POKéMON, serás\n"
    .string "probado por el ALTO MANDO.\p"
    .string "Debes vencerlos a todos. Si\n"
    .string "pierdes, ¡deberás empezar de cero!$"

IndigoPlateau_EventScript_Silver::
	lock
	faceplayer 
	goto_if_set FLAG_DAILY_BEAT_SILVER, IndigoPlateau_EventScript_SilverBeat
	msgbox IndigoPlateau_Text_RivalEntrance1, MSGBOX_DEFAULT
	call_if_eq VAR_STARTER_MON, 0, IndigoPlateau_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, IndigoPlateau_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, IndigoPlateau_Silver_Battle_Chikorita
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	setflag FLAG_DAILY_BEAT_SILVER
	release
	end

IndigoPlateau_EventScript_SilverBeat::
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_7, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_7, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_7, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Text_RivalEntrance1:
    .string "Espera.\p"
    .string "¿Vas a retar a la LIGA POKéMON\n"
    .string "ahora mismo?\p"
    .string "Eso no pasará.\p"
    .string "Mis POKéMON bien entrenados\n"
    .string "te darán una paliza.\p"
    .string "{PLAYER}!\n"
    .string "¡Te desafío!$"

IndigoPlateau_Text_RivalWin:
    .string "…\p"
    .string "Vale... perdí…$"

IndigoPlateau_Text_RivalAfter:
    .string "…Rayos… sigo sin ganar…\p"
    .string "Tengo que pensar más en mis\n"
    .string "POKéMON…\p"
    .string "¡Hmph! ¡Intenta no perder!$"

IndigoPlateau_EventScript_Psychic::
	lock
	faceplayer
	msgbox IndigoPlateau_Text_TeleportGuy1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, IndigoPlateau_EventScript_PsychicTeleport
	msgbox IndigoPlateau_Text_TeleportGuyNo, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_EventScript_PsychicTeleport::
	msgbox IndigoPlateau_Text_TeleportGuyYes, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playbgm MUS_HG_NEW_BARK, TRUE
	delay 60
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	applymovement2 LOCALID_INDIGOPLATEAU_ABRA, IndigoPLateau_Movement_Abra
	waitmovement 0
	fadescreen FADE_TO_WHITE
	warpteleport MAP_NEW_BARK_TOWN, 20, 12
	release
	end
	
IndigoPLateau_Movement_Abra:
	jump_in_place_right
	jump_in_place_right
	step_end

IndigoPlateau_EventScript_Abra::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox IndigoPlateau_Text_Abra, MSGBOX_DEFAULT
	waitmoncry
	release
	end

IndigoPlateau_Text_TeleportGuy1:
    .string "¡Ah! ¿Retarás al ALTO MANDO?\n"
    .string "¿Seguro que estás listo?\p"
    .string "Si necesitas entrenar más,\n"
    .string "mi ABRA puede ayudarte.\p"
    .string "Puede TELETRANSPORTARTE a casa.\p"
    .string "¿Quieres volver a casa ahora?$"

IndigoPlateau_Text_TeleportGuyYes:
    .string "Vale, vale. Imagina tu casa en tu\n"
    .string "mente…$"

IndigoPlateau_Text_TeleportGuyNo:
    .string "¡Está bien! ¡Mucha suerte!$"

IndigoPlateau_Text_Abra:
    .string "ABRA: Aabra…$"
