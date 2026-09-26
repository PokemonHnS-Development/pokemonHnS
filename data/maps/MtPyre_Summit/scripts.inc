.set LOCALID_ARCHIE, 2
.set LOCALID_OLD_LADY, 3
.set LOCALID_GRUNT_1, 4
.set LOCALID_GRUNT_2, 5
.set LOCALID_GRUNT_3, 6
.set LOCALID_GRUNT_4, 7
.set LOCALID_MAXIE, 8

MtPyre_Summit_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Summit_OnTransition
	.byte 0

MtPyre_Summit_OnTransition:
	call_if_eq VAR_MT_PYRE_STATE, 2, MtPyre_Summit_EventScript_SetArchieMaxiePositions
	end

MtPyre_Summit_EventScript_SetArchieMaxiePositions::
	setobjectxyperm LOCALID_MAXIE, 23, 6
	setobjectxyperm LOCALID_ARCHIE, 22, 6
	end

MtPyre_Summit_EventScript_TeamAquaTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaExits::
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieFacePlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieFacePlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieFacePlayer2
	msgbox MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	fadedefaultbgm
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 20
	setvar VAR_MT_PYRE_STATE, 1
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_OldLadyApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_OldLadyApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_OldLadyApproachPlayer2
	msgbox MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis, MSGBOX_DEFAULT
	giveitem ITEM_MAGMA_EMBLEM
	setflag FLAG_RECEIVED_RED_OR_BLUE_ORB
	setflag FLAG_GARBAGEFLAG
	releaseall
	end

MtPyre_Summit_EventScript_ArchieFacePlayer0::
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer0
	waitmovement 0
	return

@ Archie is already facing player
MtPyre_Summit_EventScript_ArchieFacePlayer1::
	return

MtPyre_Summit_EventScript_ArchieFacePlayer2::
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer0::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer1::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer2::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

MtPyre_Summit_Movement_OldLadyApproachPlayer0:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer1:
	walk_down
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer2:
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer0:
	walk_left
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer2:
	walk_right
	walk_in_place_faster_down
	step_end

MtPyre_Summit_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, MtPyre_Summit_EventScript_OldManAfterRayquaza
	msgbox MtPyre_Summit_Text_WillYouHearOutMyTale, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManAfterRayquaza::
	msgbox MtPyre_Summit_Text_HearTheNewLegendOfHoenn, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManNewTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManTale::
	msgbox MtPyre_Summit_Text_GroudonKyogreTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_DeclineOldManTale::
	msgbox MtPyre_Summit_Text_WellThatTooIsFine, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldManNewTale::
	msgbox MtPyre_Summit_Text_HoennTrioTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldLady::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_RED_OR_BLUE_ORB, MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned
	call_if_ge VAR_MT_PYRE_STATE, 3, MtPyre_Summit_EventScript_OldLadyOrbsReturned
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, MtPyre_Summit_EventScript_OldLadyLegendariesAwake
	msgbox MtPyre_Summit_Text_OrbsHaveBeenTaken, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyOrbsReturned::
	msgbox MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs, MSGBOX_DEFAULT
	setflag FLAG_RETURNED_RED_OR_BLUE_ORB
	release
	end

MtPyre_Summit_EventScript_OldLadyLegendariesAwake::
	msgbox MtPyre_Summit_Text_GroudonKyogreAwakened, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned::
	msgbox MtPyre_Summit_Text_SuperAncientPokemonTaughtUs, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieMaxieBeginExit0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieMaxieBeginExit1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieMaxieBeginExit2
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachPlayer2
	msgbox MtPyre_Summit_Text_MaxieSilence, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachArchie0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachArchie1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachArchie2
	delay 30
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_MAXIE
	setvar VAR_MT_PYRE_STATE, 3
	releaseall
	end

MtPyre_Summit_EventScript_ArchieMaxieBeginExit0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer0
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie0
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie1
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie2
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_Movement_PlayerFaceMaxie0:
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_PlayerFaceMaxie:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_ArchieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_MaxieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0:
	delay_16
	delay_8
	walk_left
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_left
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer2:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieWatchMaxie:
	delay_16
	walk_in_place_faster_up
	step_end

MtPyre_Summit_Movement_PlayerWatchMaxie:
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie0:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie1:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie2:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_EventScript_Grunt1::
	trainerbattle_single TRAINER_THERESA, MtPyre_Summit_Text_Grunt1Intro, MtPyre_Summit_Text_Grunt1Defeat
	msgbox MtPyre_Summit_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt2::
	trainerbattle_single TRAINER_TIM, MtPyre_Summit_Text_Grunt2Intro, MtPyre_Summit_Text_Grunt2Defeat
	msgbox MtPyre_Summit_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt3::
	trainerbattle_single TRAINER_TIMOTHY, MtPyre_Summit_Text_Grunt3Intro, MtPyre_Summit_Text_Grunt3Defeat
	msgbox MtPyre_Summit_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt4::
	trainerbattle_single TRAINER_TOBY, MtPyre_Summit_Text_Grunt4Intro, MtPyre_Summit_Text_Grunt4Defeat
	msgbox MtPyre_Summit_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_Text_Grunt1Intro:
	.string "¡No! ¡Esos tontos del TEAM MAGMA\n"
	.string "llegaron antes que nosotros!\p"
	.string "¡No podemos quedar atrás!$"

MtPyre_Summit_Text_Grunt1Defeat:
	.string "Pensé que eras uno de los MAGMA\n"
	.string "que regresaba por aquí...$"

MtPyre_Summit_Text_Grunt1PostBattle:
	.string "Sí, eres fuerte...\n"
	.string "¡Pero somos muchos!$"

MtPyre_Summit_Text_Grunt2Intro:
	.string "¡Ja!\n"
	.string "¡Qué mala suerte!\p"
	.string "Si hubieras venido antes, solo\n"
	.string "lucharías contra el TEAM MAGMA.\p"
	.string "¡Pero ahora te toca enfrentarte\n"
	.string "a los más fuertes!$"

MtPyre_Summit_Text_Grunt2Defeat:
	.string "Urgh... debí dejar que lucharas\n"
	.string "contra el TEAM MAGMA primero...$"

MtPyre_Summit_Text_Grunt2PostBattle:
	.string "¡No sabes nada!\n"
	.string "¿Entonces por qué nos molestas?$"

MtPyre_Summit_Text_Grunt3Intro:
	.string "Tú...\n"
	.string "Te vimos en el MT. CHIMNEY.\p"
	.string "No eres de ningún TEAM,\n"
	.string "¿entonces qué haces aquí?$"

MtPyre_Summit_Text_Grunt3Defeat:
	.string "Si vas a molestar a alguien,\n"
	.string "que sea al TEAM MAGMA...$"

MtPyre_Summit_Text_Grunt3PostBattle:
	.string "¡Je, no importa!\n"
	.string "¡Ganamos algo de tiempo!\p"
	.string "¡El JEFE ya debió llevarse lo que\n"
	.string "buscaba!$"

MtPyre_Summit_Text_Grunt4Intro:
	.string "¡Oh, ya lo sé!\n"
	.string "¡Quisiste entrar al TEAM MAGMA,\l"
	.string "pero no te aceptaron!\p"
	.string "¡No creas que te dejaremos entrar\n"
	.string "al TEAM AQUA!$"

MtPyre_Summit_Text_Grunt4Defeat:
	.string "Si quieres entrar al TEAM AQUA con\n"
	.string "tantas ganas, lo pensaremos…$"

MtPyre_Summit_Text_Grunt4PostBattle:
	.string "Tenemos una gran combinación entre\n"
	.string "nosotros y nuestro líder.$"

MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo:
	.string "ARCHIE: MAXIE del TEAM MAGMA nos\n"
	.string "ganó, pero logramos lo que queríamos.\p"
	.string "El ORBE ROJO del MT. PYRE…\n"
	.string "¡Yo, ARCHIE, ya lo tengo conmigo!\p"
	.string "Fufufu… ¡Ahora nuestro objetivo\n"
	.string "final se hará realidad!\p"
	.string "¡Bien, EQUIPO!\n"
	.string "¡Retirada!$"

MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis:
	.string "Oh, no…\n"
	.string "Esto no puede pasar…\p"
	.string "No solo el ORBE AZUL, sino que\n"
	.string "también se llevaron el ORBE ROJO…\p"
	.string "El ORBE AZUL y el ROJO nunca deben\n"
	.string "separarse. Van juntos.\p"
	.string "¿Qué planean esos hombres con los\n"
	.string "dos ORBES?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Ah, sí. ¿Fue el TEAM MAGMA quien\n"
	.string "tomó el ORBE AZUL primero?\p"
	.string "Bueno, con las prisas, dejaron\n"
	.string "esto aquí.\p"
	.string "No imaginaba qué podría ser\n"
	.string "exactamente.\p"
	.string "Quiero que te lo quedes.\n"
	.string "Tal vez sea útil de alguna forma.$"

MtPyre_Summit_Text_OrbsHaveBeenTaken:
	.string "El ORBE AZUL y el ROJO tomados por\n"
	.string "esos hombres siniestros…\p"
	.string "No deben estar separados…\n"
	.string "Temo que pase algo terrible…$"

MtPyre_Summit_Text_GroudonKyogreAwakened:
	.string "Cielos…\p"
	.string "¿Dices que GROUDON y KYOGRE\n"
	.string "han despertado?\p"
	.string "Dicen que el ORBE AZUL y el\n"
	.string "ORBE ROJO calmaron la furia de\l"
	.string "los dos POKéMON…\p"
	.string "También dicen que el dueño real de\n"
	.string "los ORBES aún existe.\p"
	.string "Pero nadie sabe quién, o qué es\n"
	.string "exactamente el dueño.\p"
	.string "Podría ser un humano o un POKéMON,\n"
	.string "pero nadie lo sabe.$"

MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs:
	.string "Los dos hombres que llevaron los ORBS\n"
	.string "regresaron para devolverlos solos.\p"
	.string "Esos hombres...\n"
	.string "Tal vez no sean tan malos...$"

MtPyre_Summit_Text_SuperAncientPokemonTaughtUs:
	.string "Las formas de la tierra, el mar,\n"
	.string "y el cielo...\p"
	.string "Dicen que son las identidades de\n"
	.string "los POKéMON ancestrales...\p"
	.string "Así como los humanos y los\n"
	.string "POKéMON viven, nuestro mundo,\l"
	.string "también está vivo...\p"
	.string "Los POKéMON ancestrales nos\n"
	.string "han enseñado eso...$"

MtPyre_Summit_Text_WillYouHearOutMyTale:
	.string "En el MT. PYRE calmamos los espíritus\n"
	.string "de los POKéMON que partieron…\p"
	.string "Es un lugar alto desde donde se\n"
	.string "ve todo HOENN…\p"
	.string "Los espíritus de los POKéMON\n"
	.string "deben hallar consuelo aquí…\p"
	.string "¿Es coincidencia que estés aquí…\p"
	.string "¿Oirás mi historia? Una historia\n"
	.string "contada en la región de HOENN?$"

MtPyre_Summit_Text_GroudonKyogreTale:
	.string "Pasó hace mucho, mucho tiempo…\p"
	.string "El mundo sufrió un feroz\n"
	.string "choque entre los POKéMON de tierra\l"
	.string "y los POKéMON del mar…\p"
	.string "Los POKéMON de tierra alzaron\n"
	.string "montañas y crearon continentes…\p"
	.string "Los POKéMON del mar alzaron\n"
	.string "olas y esculpieron los océanos…\p"
	.string "Su feroz duelo no tenía fin.\p"
	.string "El mundo fue envuelto en\n"
	.string "infernos y tormentas viciosas.\p"
	.string "El ORBE AZUL y el ORBE ROJO\n"
	.string "pusieron fin a la calamidad.\p"
	.string "La luz de los dos ORBES\n"
	.string "calmó a los adversarios.\p"
	.string "Ya dóciles, se hundieron en\n"
	.string "el mar, donde finalmente\l"
	.string "desaparecieron…$"

MtPyre_Summit_Text_WellThatTooIsFine:
	.string "Ya veo...\n"
	.string "Bueno, eso también está bien...$"

MtPyre_Summit_Text_MaxieSilence:
	.string "MAXIE: {PLAYER}…\p"
	.string "… … … … … …\n"
	.string "… … … … … …$"

MtPyre_Summit_Text_HearTheNewLegendOfHoenn:
	.string "Mi rol es pasar las leyendas\n"
	.string "de HOENN a futuras generaciones.\p"
	.string "Y la crisis que acabó en\n"
	.string "SOOTOPOLIS reescribió una...\p"
	.string "¿Tienes tiempo de escuchar la nueva\n"
	.string "leyenda de HOENN?$"

MtPyre_Summit_Text_HoennTrioTale:
	.string "Pasó hace mucho, mucho tiempo…\p"
	.string "El mundo sufrió un feroz\n"
	.string "choque entre los POKéMON de tierra\l"
	.string "y los POKéMON del mar…\p"
	.string "Los POKéMON de tierra alzaron\n"
	.string "montañas y crearon continentes…\p"
	.string "Los POKéMON del mar alzaron\n"
	.string "olas y formaron los océanos…\p"
	.string "Su feroz duelo no tenía fin.\p"
	.string "El mundo fue envuelto en fuegos\n"
	.string "masivos y tormentas feroces.\p"
	.string "Fue entonces que el POKéMON del\n"
	.string "cielo descendió de una tormenta.\p"
	.string "El POKéMON, de un verde brillante,\n"
	.string "calmó a los dos POKéMON furiosos.\p"
	.string "Cumplido su deber, el POKéMON verde\n"
	.string "voló hacia el lejano azul…$"
