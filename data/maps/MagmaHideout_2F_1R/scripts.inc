MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_NARD, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:
	.string "¿Qué, qué, qué?\p"
	.string "¡Solo miembros del TEAM MAGMA\n"
	.string "deben estar aquí!\p"
	.string "Pero no llevas el uniforme del\n"
	.string "TEAM MAGMA...\p"
	.string "¡Eres sospechoso!\n"
	.string "¡Lucha conmigo!$"

MagmaHideout_2F_1R_Text_Grunt14Defeat:
	.string "Aiyiyi…\n"
	.string "Mi orgullo en el TEAM MAGMA…$"

MagmaHideout_2F_1R_Text_Grunt14PostBattle:
	.string "Si tienes frío, deberías\n"
	.string "unirte al TEAM MAGMA.$"

MagmaHideout_2F_1R_Text_Grunt3Intro:
	.string "¡Detente ahí mismo!\p"
	.string "¿Esperas que me quede callado\n"
	.string "y te deje pasar así nomás?$"

MagmaHideout_2F_1R_Text_Grunt3Defeat:
	.string "¡Oh, vaya!\n"
	.string "¡Me rindo!$"

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
	.string "Quizás hubiera sido mejor si\n"
	.string "te hubiera dejado pasar...$"

MagmaHideout_2F_1R_Text_Grunt4Intro:
	.string "¡Ajajá!\n"
	.string "¡Un intruso!$"

MagmaHideout_2F_1R_Text_Grunt4Defeat:
	.string "¡Graaaah!$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
	.string "Ya he perdido.\p"
	.string "¿De verdad debo seguir dando\n"
	.string "vueltas en círculo?$"

MagmaHideout_2F_1R_Text_Grunt5Intro:
	.string "¡Oh, oh!\n"
	.string "¡Un intruso!$"

MagmaHideout_2F_1R_Text_Grunt5Defeat:
	.string "Murmullo...$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
	.string "En realidad, no soy experto...$"

