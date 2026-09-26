FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower bc of rotating gates
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_OLIVINE_CITY_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_LOIS, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint::
	trainerbattle_single TRAINER_RAY, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_CHARLES, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_CHUCK_2, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_JIN, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
	.string "¡Hola! ¿Cómo va todo, futuro\n"
	.string "CAMPEÓN {PLAYER}?\p"
	.string "La LÍDER WINONA del GIMNASIO\n"
	.string "es experta en POKéMON VOLADORES.\p"
	.string "Te espera al fondo del GIMNASIO,\n"
	.string "tras las puertas giratorias.\p"
	.string "Espera a nuevos retadores\n"
	.string "¡que quieran alzar el vuelo!\p"
	.string "¡Bien, ve a por ello!$"

FortreeCity_Gym_Text_GymGuidePostVictory:
	.string "¡Lo lograste!\n"
	.string "¡Has logrado despegar!$"

FortreeCity_Gym_Text_JaredIntro:
	.string "¡Mira el elegante estilo de lucha\n"
	.string "de los POKéMON ave!$"

FortreeCity_Gym_Text_JaredDefeat:
	.string "Tú...\n"
	.string "Eres fuerte...$"

FortreeCity_Gym_Text_JaredPostBattle:
	.string "Un ENTRENADOR debe ser listo para\n"
	.string "superar imprevistos.\p"
	.string "¿Tienes la astucia para llegar\n"
	.string "hasta nuestra LÍDER?$"

FortreeCity_Gym_Text_EdwardoIntro:
	.string "Quienes aman los POKéMON ave\n"
	.string "aspiran a entrar en este GIMNASIO.\p"
	.string "Como miembro del GIMNASIO de\n"
	.string "FORTREE, ¡no puedo perder!$"

FortreeCity_Gym_Text_EdwardoDefeat:
	.string "Fue una carga demasiado pesada\n"
	.string "para mí...$"

FortreeCity_Gym_Text_EdwardoPostBattle:
	.string "El mundo es enorme y hay muchísimos\n"
	.string "ENTRENADORES fuertes.\p"
	.string "Seguiré entrenando para volverme\n"
	.string "aún más fuerte.$"

FortreeCity_Gym_Text_FlintIntro:
	.string "¡No hace falta que WINONA, nuestra\n"
	.string "LÍDER de GIMNASIO, te enfrente!\p"
	.string "¡Yo soy más que suficiente!$"

FortreeCity_Gym_Text_FlintDefeat:
	.string "WINONA, yo...\n"
	.string "¡Perdí!$"

FortreeCity_Gym_Text_FlintPostBattle:
	.string "WINONA es linda y fuerte.\n"
	.string "¡Es la MEJOR LÍDER!\p"
	.string "Sonrojo...$"

FortreeCity_Gym_Text_AshleyIntro:
	.string "¡WINONA me enseñó personalmente!\n"
	.string "¡No me ganarás tan fácil!$"

FortreeCity_Gym_Text_AshleyDefeat:
	.string "Me derrotaron...$"

FortreeCity_Gym_Text_AshleyPostBattle:
	.string "Gracias a WINONA, la gente de\n"
	.string "BOSQUEVERDE vive sin miedo.$"

FortreeCity_Gym_Text_HumbertoIntro:
	.string "Al luchar, el rostro de WINONA\n"
	.string "brilla con determinación...\p"
	.string "¡No dejaré que veas esa\n"
	.string "bella imagen!$"

FortreeCity_Gym_Text_HumbertoDefeat:
	.string "¡Ugh!\n"
	.string "No pude detenerte.$"

FortreeCity_Gym_Text_HumbertoPostBattle:
	.string "¡Ten más cuidado!\n"
	.string "No te distraigas mirando a WINONA\l"
	.string "¡o terminarás estrellado en el suelo!$"

FortreeCity_Gym_Text_DariusIntro:
	.string "Deberías saber que hay todo tipo\n"
	.string "de POKéMON tipo VOLADOR.\p"
	.string "Lo sabes, ¿verdad?$"

FortreeCity_Gym_Text_DariusDefeat:
	.string "¡Parece que sabes lo que haces!$"

FortreeCity_Gym_Text_DariusPostBattle:
	.string "Sí, me has vencido.\n"
	.string "¡Pero ten cuidado! Los POKéMON de la\l"
	.string "LÍDER WINONA van muy en serio.$"

FortreeCity_Gym_Text_WinonaIntro:
	.string "Soy WINONA. Soy la LÍDER del\n"
	.string "GIMNASIO POKéMON de BOSQUEVERDE.\p"
	.string "Me he vuelto una con los POKéMON\n"
	.string "AVES y he surcado los cielos…\p"
	.string "Por dura que sea la batalla, hemos\n"
	.string "triunfado con elegancia…\p"
	.string "¡Mira la coreografía elegante de los\n"
	.string "POKéMON AVES y la mía!$"

FortreeCity_Gym_Text_WinonaDefeat:
	.string "Jamás vi a un ENTRENADOR\n"
	.string "mandar POKéMON con más gracia\l"
	.string "que tú…\p"
	.string "Por tu gran destreza,\n"
	.string "te doy esta MEDALLA de GIMNASIO.$"

FortreeCity_Gym_Text_ReceivedFeatherBadge:
	.string "{PLAYER} recibió la MEDALLA PLUMA\n"
	.string "de WINONA.$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
	.string "Con la MEDALLA PLUMA, los POKéMON\n"
	.string "hasta el NIV 70, incluso los de\l"
	.string "intercambio, te obedecerán.\p"
	.string "También podrás usar la MO la MO\n"
	.string "VUELO fuera de combate,\p"
	.string "aunque el POKéMON no la conozca.\p"
	.string "El único requisito es que el\n"
	.string "POKéMON sea de TIPO VOLADOR.\p"
	.string "Y esto…\n"
	.string "Esto es un regalo mío.$"

FortreeCity_Gym_Text_ExplainAerialAce:
	.string "La MT40 tiene AS ACE.\p"
	.string "Su velocidad...\n"
	.string "Ningún POKéMON podrá evitarlo.\p"
	.string "... ... ... ... ... ...$"

FortreeCity_Gym_Text_RegisteredWinona:
	.string "Líder de GIMNASIO WINONA\n"
	.string "registrada en el POKéNAV.$"

FortreeCity_Gym_Text_WinonaPostBattle:
	.string "Aunque perdí, seguiré siendo\n"
	.string "devota a los POKéMON ave.$"

FortreeCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON CIUDAD BOSQUE$"

FortreeCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD BOSQUE\p"
	.string "ENTRENADORES DE WINONA:\n"
	.string "{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch:
	.string "WINONA: Los humanos no escapamos\n"
	.string "de la gravedad en el suelo.\p"
	.string "¡Pero buscando la excelencia,\n"
	.string "tenemos el poder de volar!\p"
	.string "Has llegado a la cima como el\n"
	.string "actual CAMPEÓN.\p"
	.string "¡Permíteme ver tu poder en\n"
	.string "todo su vuelo!$"

FortreeCity_Gym_Text_WinonaRematchDefeat:
	.string "No pude alcanzar tu altura otra vez...$"

FortreeCity_Gym_Text_WinonaPostRematch:
	.string "WINONA: Aunque haya perdido,\n"
	.string "mi corazón sigue intacto.\p"
	.string "Podré elevarme y volar de nuevo\n"
	.string "una y otra vez.\p"
	.string "¡Estoy convencida de ello!$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
	.string "WINONA: Los humanos nunca escapamos\n"
	.string "a la gravedad del suelo.\p"
	.string "¡Pero buscando la excelencia,\n"
	.string "tenemos el poder de volar!\p"
	.string "Has llegado a la cima como\n"
	.string "el actual CAMPEÓN.\p"
	.string "¡Permíteme ver tu poder\n"
	.string "en pleno vuelo!\p"
	.string "Oh, no... ¿Solo tienes un\n"
	.string "POKéMON contigo?\p"
	.string "Vuelve con al menos dos\n"
	.string "POKéMON, por favor.$"
