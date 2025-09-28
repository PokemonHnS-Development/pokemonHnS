ChangeDeoxysFormNormal::
	setvar 0x8000, SPECIES_DEOXYS_ATTACK
	setvar 0x8001, SPECIES_DEOXYS_DEFENSE
	setvar 0x8002, 0
	setvar 0x8005, SPECIES_DEOXYS_SPEED
	msgbox ChangeDeoxysForm_Text_NormalForm, MSGBOX_DEFAULT
	closemessage
	special CheckPkm
	goto_if_eq VAR_RESULT, TRUE, ChangeDeoxysForm
	goto_if_eq VAR_RESULT, FALSE, ChangeDeoxysForm_End_Nothing_Happened
	end

ChangeDeoxysFormDefense::
	setvar 0x8000, SPECIES_DEOXYS_ATTACK
	setvar 0x8001, 0
	setvar 0x8002, SPECIES_DEOXYS
	setvar 0x8005, SPECIES_DEOXYS_SPEED
	msgbox ChangeDeoxysForm_Text_DefenseForm, MSGBOX_DEFAULT
	closemessage
	special CheckPkm
	goto_if_eq VAR_RESULT, TRUE, ChangeDeoxysForm
	goto_if_eq VAR_RESULT, FALSE, ChangeDeoxysForm_End_Nothing_Happened
	end

ChangeDeoxysFormAttack::
	setvar 0x8000, 0
	setvar 0x8001, SPECIES_DEOXYS_DEFENSE
	setvar 0x8002, SPECIES_DEOXYS
	setvar 0x8005, SPECIES_DEOXYS_SPEED
	msgbox ChangeDeoxysForm_Text_AttackForm, MSGBOX_DEFAULT
	closemessage
	special CheckPkm
	goto_if_eq VAR_RESULT, TRUE, ChangeDeoxysForm
	goto_if_eq VAR_RESULT, FALSE, ChangeDeoxysForm_End_Nothing_Happened
	end

ChangeDeoxysFormSpeed::
	setvar 0x8000, SPECIES_DEOXYS_ATTACK
	setvar 0x8001, SPECIES_DEOXYS_DEFENSE
	setvar 0x8002, SPECIES_DEOXYS
	setvar 0x8005, 0
	msgbox ChangeDeoxysForm_Text_SpeedForm, MSGBOX_DEFAULT
	closemessage
	special CheckPkm
	goto_if_eq VAR_RESULT, TRUE, ChangeDeoxysForm
	goto_if_eq VAR_RESULT, FALSE, ChangeDeoxysForm_End_Nothing_Happened
	end

ChangeDeoxysForm::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, ChangeDeoxysForm_Movement
	waitmovement 0
	delay 60
	msgbox ChangeDeoxysForm_Text_Beginning, MSGBOX_DEFAULT
	goto ChangeDeoxysForm_Start
ChangeDeoxysForm_End:
	msgbox ChangeDeoxysForm_Text_End, MSGBOX_DEFAULT
	callnative UpdateFollowingPokemon
	releaseall
	end

ChangeDeoxysForm_Start::
	msgbox ChangeDeoxysForm_Text_Select, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq ChangeDeoxysForm_End
	compare VAR_RESULT, YES
	goto_if_eq ChangeDeoxysForm_Start_Select_Pokemon

ChangeDeoxysForm_Start_Select_Pokemon::
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq ChangeDeoxysForm_End
	special TryChangeDeoxysForm
	compare VAR_RESULT, TRUE
	goto_if_eq ChangeDeoxysForm_Success
	compare VAR_RESULT, FALSE
	goto_if_eq ChangeDeoxysForm_End_Wrong_Pokemon
	goto ChangeDeoxysForm_End

ChangeDeoxysForm_Success:
	playmoncry SPECIES_DEOXYS, 0
	msgbox ChangeDeoxysForm_Text_Success, MSGBOX_DEFAULT
	waitmoncry
	waitbuttonpress
	goto ChangeDeoxysForm_End

ChangeDeoxysForm_End_Wrong_Pokemon::
	msgbox ChangeDeoxysForm_Text_End_Wrong_Pokemon, MSGBOX_DEFAULT
	releaseall
	end

ChangeDeoxysForm_End_Nothing_Happened::
	delay 20
	msgbox ChangeDeoxysForm_Text_End, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

ChangeDeoxysForm_Text_NormalForm:
	.string "Looks like a NORMAL meteorite.\n"
	.string "It has a rough, dry surface.$"

ChangeDeoxysForm_Text_DefenseForm:
	.string "Looks like a STURDY meteorite.\n"
	.string "Seems unbreakeable, like a diamond.$"

ChangeDeoxysForm_Text_AttackForm:
	.string "Looks like a POWERFUL meteorite.\n"
	.string "It's hot to the touch.$"

ChangeDeoxysForm_Text_SpeedForm:
	.string "Looks like a LIGHTWEIGHT meteorite.\n"
	.string "I can lift it very easily!$"

ChangeDeoxysForm_Text_Beginning:
	.string "One of my POKéMON reacted to the it!$"

ChangeDeoxysForm_Text_End:
	.string "I should get going.$"

ChangeDeoxysForm_Text_End_Wrong_Pokemon:
	.string "My POKéMON enjoyed touching the\n"
	.string "meteorite more than I expected!\p"
	.string "But nothing happened…\n"
	.string "I should get going.$"

ChangeDeoxysForm_Text_Select:
	.string "Should I let any of my POKéMON\n"
	.string "touch this meteorite?$"

ChangeDeoxysForm_Text_Success:
	.string "Something has happened to DEOXYS!$"

ChangeDeoxysForm_Movement:
	emote_question_mark
	step_end