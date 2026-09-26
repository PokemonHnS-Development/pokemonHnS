BugContest_EventScript_Start::
	end

BugContest_EventScript_WhiteOut::
	lockall
	delay 200
	msgbox BugContest_Text_WhiteOut, MSGBOX_DEFAULT
	closemessage
	goto BugContest_EventScript_End
	end

BugContest_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	msgbox BugContest_Text_TimesUp, MSGBOX_DEFAULT
	closemessage
	waitse
	getpartysize
	goto_if_eq VAR_RESULT, 1, BugContest_EventScript_Didntcatch
	fadescreen FADE_TO_BLACK
	setvar VAR_BUG_CONTEST_STATE, 3
	
	msgbox BugContest_Text_Judging0, MSGBOX_DEFAULT
	closemessage
	BugContest_EventScript_TimesUp2::
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BugContest_EventScript_WrongChoiceMon
	goto_if_eq VAR_0x8004, 0, BugContest_EventScript_WrongChoiceMon
	fadescreen FADE_TO_BLACK
	warp MAP_NATIONAL_PARK_BUG_CONTEST, 5
	delay 90
	end

BugContest_EventScript_WrongChoiceMon::
	msgbox BugContest_Text_WrongChoiceMon, MSGBOX_DEFAULT
	goto BugContest_EventScript_TimesUp2
	end

BugContestEventScript_Judging::
	msgbox BugContest_Text_Judging1, MSGBOX_DEFAULT
	closemessage
	special JudgeBugContestMon
	call_if_eq VAR_RESULT, 1, BugContest_EventScript_First
	call_if_eq VAR_RESULT, 2, BugContest_EventScript_Second
	call_if_eq VAR_RESULT, 3, BugContest_EventScript_Third
	special TransferBugContestMon
	delay 20
	giveitem VAR_0x8005
	msgbox BugContest_Text_TransferAndReturn, MSGBOX_DEFAULT
	playse SE_SUCCESS
	waitse
	msgbox BugContest_Text_TakePartInFuture, MSGBOX_DEFAULT
	closemessage
	goto BugContest_EventScript_End
	end

BugContest_EventScript_Didntcatch::
	msgbox BugContest_Text_DidntCatch, MSGBOX_DEFAULT
	playse SE_SUCCESS
	closemessage
	fadescreen FADE_TO_BLACK
	goto BugContest_EventScript_End
	end

BugContest_EventScript_First::
	msgbox BugContest_Text_First1, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_First2, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_First3, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	closemessage
	return

BugContest_EventScript_Second::
	msgbox BugContest_Text_Second1, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Second2, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Second3, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	closemessage
	return

BugContest_EventScript_Third::
	msgbox BugContest_Text_Third1, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Third2, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BERRY
	waitfanfare
	msgbox BugContest_Text_Third3, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	closemessage
	return

BugContest_EventScript_End::
	special HealPlayerParty
	special LoadPlayerParty
	special ExitBugContestMode
	setvar VAR_BUG_CONTEST_STATE, 0
	special RemoveSafariBalls
	goto_if_eq VAR_TEMP_1, 1, BugContest_EventScript_SideEnd
	warp MAP_GATE_NATIONAL_PARK, 7, 2
	releaseall
	end

BugContest_EventScript_SideEnd::
	warp MAP_GATE_NATIONAL_PARK, 35, 7
	releaseall
	end

BugContest_Text_Judging0::
	.string "El concurso ha terminado.\n"
	.string "Elige el POKéMON que quieras\l"
	.string "conservar y que sea juzgado.$"

BugContest_Text_Judging1::
	.string "Ahora juzgaremos al POKéMON\n"
	.string "que atrapaste.\p"
	.string "...................\n"
	.string "...................\p"
	.string "¡Ya tenemos ganadores! ¿Estás\n"
	.string "listo para esto?$"

BugContest_Text_WrongChoiceMon:
	.string "Elige el POKéMON que quieras\n"
	.string "conservar y que sea juzgado.$"

BugContest_Text_DidntCatch:
	.string "¡Oh no! No atrapaste un POKéMON.\n"
	.string "Has perdido la competencia.\p"
	.string "Tu equipo será devuelto ahora.$"

BugContest_Text_TimesUp:
	.string "¡Ding-dong! ¡Se acabó el tiempo!$"

BugContest_Text_WhiteOut:
	.string "{PLAYER} no tiene POKéMON útiles.\n"
	.string "{PLAYER} perdió el concurso.$"

BugContest_Text_First1:
	.string "El tercer lugar es para COOLTRAINER\n"
	.string "BELINDA, ¡quien atrapó un\l"
	.string "BUTTERFREE inquieto!$"
BugContest_Text_First2:
	.string "El segundo lugar es para BUGCATCHER\n"
	.string "SHAUN, ¡quien atrapó un\l"
	.string "PINSIR retorciéndose!$"
BugContest_Text_First3:
	.string "El ganador del concurso de bichos\n"
	.string "es...\p"
	.string "{PLAYER}, ¡quien atrapó unos\n"
	.string "{STR_VAR_1}!$"

BugContest_Text_Second1:
	.string "El segundo es COOLTRAINER\n"
	.string "BELINDA, ¡quien atrapó un\l"
	.string "BUTTERFREE inquieto!$"
BugContest_Text_Second2:
	.string "El segundo es {PLAYER}, quien\n"
	.string "¡atrapó un {STR_VAR_1} inquieto!$"
BugContest_Text_Second3:
	.string "El ganador del concurso de insectos\n"
	.string "es...\p"
	.string "¡EL CAZABICHOS SHAUN, que atrapó\n"
	.string "un enorme PINSIR!$"


BugContest_Text_Third1:
	.string "El tercero es {PLAYER}, quien\n"
	.string "¡atrapó un {STR_VAR_1} inquieto!$"
BugContest_Text_Third2:
	.string "El segundo es el COOLTRAINER\n"
	.string "BELINDA, ¡quien atrapó un\l"
	.string "BUTTERFREE agitado!$"
BugContest_Text_Third3:
	.string "El ganador del concurso de insectos\n"
	.string "es...\p"
	.string "¡SHAUN, que atrapó un enorme\n"
	.string "PINSIR!$"

BugContest_Text_TakePartInFuture:
	.string "¡Gracias por participar!\n"
	.string "Esperamos que participes en el\l"
	.string "futuro.$"

BugContest_Text_TransferAndReturn:
	.string "El POKéMON BUG elegido irá\n"
	.string "al PC y recuperarás a tu\l"
	.string "equipo ahora mismo.$"
