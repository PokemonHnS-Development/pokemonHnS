.set LOCALID_BUGCONTEST_ATTENDANT, 11
.set LOCALID_BUGCONTEST_GIRL, 13
.set LOCALID_BUGCONTEST_BC1, 1
.set LOCALID_BUGCONTEST_BC2, 2
.set LOCALID_BUGCONTEST_BOY, 12
.set LOCALID_BUGCONTEST_BUG1, 18
.set LOCALID_BUGCONTEST_BUG2, 19
.set LOCALID_BUGCONTEST_BUG3, 20
.set LOCALID_BUGCONTEST_BUG4, 21
.set LOCALID_BUGCONTEST_ATTENDANT_SIDE, 17


NationalPark_BugContest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NationalPark_BugContest_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NationalPark_BugContest_OnFrame
	.byte 0

NationalPark_BugContest_OnTransition::
	goto_if_eq VAR_BUG_CONTEST_STATE, 3, NationalPark_BugContest_EventScript_JudgeScene
	end
	
NationalPark_BugContest_OnFrame::
	map_script_2 VAR_BUG_CONTEST_STATE, 1, NationalPark_BugContest_EventScript_Enter
	map_script_2 VAR_BUG_CONTEST_STATE, 5, NationalPark_BugContest_EventScript_EnterSide
	map_script_2 VAR_BUG_CONTEST_STATE, 3, NationalPark_BugContest_EventScript_JudgeSceneActivate
	.2byte 0


NationalPark_BugContest_EventScript_BC1::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_ContestantShaun, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_BC2::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Contestant2A, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_Belinda::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_ContestantBelinda, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_Boy::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Contestant6A, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_RelaxationSquare::
	lock
	msgbox NationalParkBugContest_Text_Sign_RelaxationSquare, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_BattleSign::
	lock
	msgbox NationalParkBugContest_Text_Sign_BattleNotice, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_TrainerTips::
	lock
	msgbox NationalParkBugContest_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_Trash::
	lock
	msgbox NationalPark_BugContest_Text_Trash, MSGBOX_SIGN
	closemessage
	release
	end

NationalPark_BugContest_EventScript_JudgeScene::
	special ShowBugContestChosenMon
	setobjectxyperm VAR_RESULT, 20, 29
	setobjectxyperm LOCALID_BUGCONTEST_BUG1, 24, 29
	setobjectxyperm LOCALID_BUGCONTEST_BUG2, 22, 29
	setobjectxyperm LOCALID_BUGCONTEST_BUG3, 18, 29
	setobjectxyperm LOCALID_BUGCONTEST_BUG4, 16, 29

	setobjectxyperm LOCALID_BUGCONTEST_GIRL, 18, 28
	setobjectxyperm LOCALID_BUGCONTEST_BC1, 22, 28
	setobjectxyperm LOCALID_BUGCONTEST_BC2, 24, 28
	setobjectxyperm LOCALID_BUGCONTEST_BOY, 16, 28
	setobjectxyperm LOCALID_BUGCONTEST_ATTENDANT, 20, 26

	setobjectmovementtype OBJ_EVENT_ID_PLAYER, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_BUGCONTEST_GIRL, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_BUGCONTEST_BC1, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_BUGCONTEST_BC2, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_BUGCONTEST_BOY, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_BUGCONTEST_ATTENDANT, MOVEMENT_TYPE_FACE_DOWN
	end

NationalPark_BugContest_EventScript_JudgeSceneActivate::
	lockall
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	goto BugContestEventScript_Judging
	end


NationalPark_BugContest_EventScript_Enter::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	setvar VAR_BUG_CONTEST_STATE, 2
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NationalPark_BugContest_EventScript_EnterSide::
	lockall
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	delay 20
	clearflag FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	addobject LOCALID_BUGCONTEST_ATTENDANT_SIDE
	setvar VAR_TEMP_1, 1
	setvar VAR_BUG_CONTEST_STATE, 2
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NationalPark_BugContest_EventScript_Trigger::
	lock
	turnobject LOCALID_BUGCONTEST_ATTENDANT, DIR_EAST
	goto NationalPark_BugContest_EventScript_RetireChoice
NationalPark_BugContest_EventScript_Attendant::
	lock
	faceplayer
	msgbox NationalParkBugContest_Text_Attendant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, BugContest_EventScript_TimesUp
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_BugContest_EventScript_RetireChoice::
	msgbox NationalParkBugContest_Text_Attendant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, BugContest_EventScript_TimesUp
	msgbox NationlParkBugContest_Text_EnjoyTheContest, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	release
	end

NationalPark_BugContest_Movement_AttendantSide:
	walk_in_place_left
	step_end

NationalPark_BugContest_Text_Trash:
	.string "No hay nada aquí.$"

NationlParkBugContest_Text_EnjoyTheContest:
	.string "ASISTENTE: ¡Disfruta el Concurso!$"

NationalParkBugContest_Text_Attendant:
	.string "ASISTENTE: ¿Quieres terminar\n"
	.string "el concurso?$"

NationalParkBugContest_Text_ContestantBelinda:
	.string "BELINDA: ¡Voy a ganar!\n"
	.string "No me molestes.$"

NationalParkBugContest_Text_Contestant2A:
	.string "ED: Mi PARASECT duerme a los\n"
	.string "POKéMON con ESPORA.$"

NationalParkBugContest_Text_ContestantShaun:
	.string "SHAUN: No me preocupa\n"
	.string "ganar.\p"
	.string "Solo busco POKéMON raros.$"

NationalParkBugContest_Text_Contestant6A:
	.string "BARRY: Debilita a los POKéMON\n"
	.string "bicho primero,\p"
	.string "luego lanza una BALL.$"

NationalParkBugContest_Text_Contestant7A:
	.string "CINDY: Amo los POKéMON bicho.\p"
	.string "Seguro que tú también.$"

NationalParkBugContest_Text_Contestant8A:
	.string "JOSH: Colecciono POKéMON bicho\n"
	.string "desde que era un bebé.\p"
	.string "¡No hay forma de que pierda!$"

NationalParkBugContest_Text_Contestant9A:
	.string "SAMUEL: Si tienes tiempo de\n"
	.string "charlar, busca POKéMON bicho.$"

NationalParkBugContest_Text_Contestant10A:
	.string "KIPP: He estudiado mucho sobre\n"
	.string "los POKéMON bicho.\p"
	.string "Seguro que voy a ganar.$"

NationalParkBugContest_Text_Sign_RelaxationSquare:
	.string "PLAZA DE RELAJACIÓN\n"
	.string "PARQUE NACIONAL$"

NationalParkBugContest_Text_Sign_BattleNotice:
	.string "¿Qué es este aviso?\p"
	.string "Lucha solo en la hierba, por favor.\p"
	.string "OFICINA DEL GUARDAPARQUE$"

NationalParkBugContest_Text_TrainerTips:
	.string "El PARQUE NACIONAL tiene distintos\n"
	.string "POKéMON durante el CONCURSO DE\l"
	.string "CAPTURA DE bichos.$"

