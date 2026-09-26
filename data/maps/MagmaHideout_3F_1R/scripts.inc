MagmaHideout_3F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_3F_1R_OnTransition
	.byte 0

MagmaHideout_3F_1R_OnTransition:
	goto_if_set FLAG_UNLOCK_DOGS, MagmaHideout_3F_1R_SwitchToModern
	end

MagmaHideout_3F_1R_SwitchToModern::
	setmaplayoutindex LAYOUT_MAGMA_HIDEOUT_3F_1R_MODERN
	goto_if_set FLAG_DEFEATED_ENTEI, MagmaHideout_End
	goto MagmaHideout_Entei_CryStrong
	end

MagmaHideout_Entei_CryStrong::
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	release
	end

MagmaHideout_3F_1R_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro:
	.string "¿Qué hice para merecer este puesto\n"
	.string "de guardia?\p"
	.string "¡Me arde la oreja izquierda!$"

MagmaHideout_3F_1R_Text_Grunt9Defeat:
	.string "Me estoy agotando por el calor…$"

MagmaHideout_3F_1R_Text_Grunt9PostBattle:
	.string "¿No crees raro que usemos capuchas\n"
	.string "en este volcán lleno de magma?$"

MagmaHideout_3F_1R_Text_Grunt16Intro:
	.string "Nos unimos para ayudar al líder a\n"
	.string "lograr su fantástica visión.\p"
	.string "No importa si eres del TEAM AQUA\n"
	.string "o un niño que pasaba por aquí.\p"
	.string "¡Nadie nos interrumpe y sale\n"
	.string "impune de esto!$"

MagmaHideout_3F_1R_Text_Grunt16Defeat:
	.string "¡Oh, no!\n"
	.string "¡No se puede confiar en ti!$"

MagmaHideout_3F_1R_Text_Grunt16PostBattle:
	.string "Escúchame.\n"
	.string "¡El TEAM MAGMA tiene razón!\p"
	.string "No escuches al TEAM AQUA.\n"
	.string "¡No creas sus mentiras!$"

