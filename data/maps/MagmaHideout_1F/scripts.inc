MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	goto_if_set FLAG_DEFEATED_ENTEI, MagmaHideout_End
	goto_if_set FLAG_UNLOCK_DOGS, MagmaHideout_Entei_CryFaint
	end

MagmaHideout_Entei_CryFaint::
	playmoncry SPECIES_ENTEI, CRY_MODE_FAINT
	release
	end

MagmaHideout_End::
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_RICHARDO, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "Cuando TEAM MAGMA pasa lista, nos\n"
	.string "dan tareas de guardia según el\l"
	.string "orden en que nos formamos.\p"
	.string "¡Por eso estoy aquí en el rincón!\n"
	.string "¡Siempre llego tarde al pase!$"

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "¡Yo siempre llego tarde a los\n"
	.string "entrenamientos!\p"
	.string "Odio decirlo, pero soy un miedoso…$"

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "Está bien, trataré de esforzarme\n"
	.string "un poco más de ahora en adelante…$"

MagmaHideout_1F_Text_Grunt2Intro:
	.string "Nuestro líder nos dijo de excavar en\n"
	.string "MT. CHIMNEY, ¡así que cavamos!\p"
	.string "Y mientras cavábamos, nos encontramos\n"
	.string "¡algo que nos dejó pasmados!\p"
	.string "¿Qué encontramos?\p"
	.string "¡Fuhahaha!\n"
	.string "¡Te lo diré si me vences!$"

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "¡Arrgh!\n"
	.string "¡Me derrotaron!$"

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "Al final no te lo diré.\n"
	.string "¡Lo sabrás al llegar!\p"
	.string "Es mejor dejar las sorpresas\n"
	.string "para el final, ¿no crees?$"

