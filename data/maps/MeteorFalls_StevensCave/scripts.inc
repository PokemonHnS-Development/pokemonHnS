.set LOCALID_STEVEN, 1

MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_STEVEN_REMATCH, MeteorFalls_StevensCave_EventScript_StevenRematch
	goto_if_set FLAG_DEFEATED_RED, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RED
	setflag FLAG_SIDNEY_REMATCH
	setflag FLAG_PHOEBE_REMATCH
	setflag FLAG_GLACIA_REMATCH
	setflag FLAG_DRAKE_REMATCH
	setflag FLAG_WALLACE_REMATCH
	release
	end

MeteorFalls_StevensCave_EventScript_StevenRematch::
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst2, MSGBOX_DEFAULT
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_HG_VS_CHAMPION
	trainerbattle_no_intro TRAINER_STEVEN2, MeteorFalls_StevensCave_Text_StevenDefeat2
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue2, MSGBOX_DEFAULT
	clearflag FLAG_STEVEN_REMATCH
	goto_if_unset FLAG_ARCEUS_EGG_GIVE MeteorFalls_StevensCave_EventScript_StevenArceusEvent
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_EventScript_StevenArceusEvent::
	msgbox MeteorFalls_StevensCave_Text_ArceusEvent1, MSGBOX_DEFAULT
	setflag FLAG_ARCEUS_EGG_GIVE
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_ARCEUS
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MeteorFalls_StevensCave_EventScript_StevenArceusEventToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MeteorFalls_StevensCave_EventScript_StevenArceusEventToPC
	release
	end

MeteorFalls_StevensCave_EventScript_StevenArceusEventToParty::
	call Common_EventScript_GetGiftMonPartySlot
	msgbox MeteorFalls_StevensCave_Text_ArceusEvent2, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_EventScript_StevenArceusEventToPC::
	call Common_EventScript_TransferredToPC
	msgbox MeteorFalls_StevensCave_Text_ArceusEvent2, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ArceusEvent1:
	.string "And… I would like to give you\n"
	.string "something I found while digging\l"
	.string "around. It's a strange egg.\p"
	.string "I've been carrying it for many\n"
	.string "weeks but it doesn't hatch.\p"
	.string "You're a better TRAINER than me,\n"
	.string "so maybe you can make it hatch.$"

MeteorFalls_StevensCave_Text_ArceusEvent2:
	.string "I wonder which POKéMON lays its\n"
	.string "eggs between rocks and goes away…\p"
	.string "Maybe it's an ancient POKéMON?\p"
	.string "Fufufu… who knows…$"

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "STEVEN: Oh, wow, {PLAYER}{KUN}.\n"
	.string "I'm amazed you knew where to find me.\p"
	.string "Do you, uh…maybe think of me as\n"
	.string "just a rock maniac?\p"
	.string "No, that can't be right.\p"
	.string "We battled alongside each other at\n"
	.string "the SOOTOPOLIS SPACE CENTER.\p"
	.string "You should have a very good idea\n"
	.string "about how good I am.\p"
	.string "Okay, {PLAYER}{KUN}, if you're going to mount\n"
	.string "a serious challenge, expect the worst!$"

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst2:
	.string "STEVEN: Oh, hey, {PLAYER}{KUN}.\p"
	.string "You're back. WALLACE told me that\n"
	.string "you have defeated him and all the\l"
	.string "ELITE FOUR again. That's amazing!\p"
	.string "I also got stronger. Can you give me\n"
	.string "a serious challenge again?\p"
	.string "Okay, {PLAYER}{KUN}, let's go for it!$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "You…\n"
	.string "I had no idea you'd become so strong…$"

MeteorFalls_StevensCave_Text_StevenDefeat2:
	.string "You…\n"
	.string "No one can surpass you now.$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "STEVEN: Come to think of it, ever since\n"
	.string "our paths first crossed in GRANITE\l"
	.string "CAVE in DEWFORD, I had this feeling.\p"
	.string "I thought that you would eventually\n"
	.string "become the CHAMPION.\p"
	.string "My predictions usually come true.\p"
	.string "And where will you go from here?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Fufufu, what about this?\p"
	.string "You should start by challenging the\n"
	.string "ELITE FOUR again. I heard they got\l"
	.string "way stronger. What do you think?$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue2:
	.string "STEVEN: Come to think of it, ever since\n"
	.string "our paths first crossed in GRANITE\l"
	.string "CAVE in DEWFORD, I had this feeling.\p"
	.string "I thought that you would eventually\n"
	.string "become stronger than me.\p"
	.string "My predictions usually come true.\p"
	.string "And where will you go from here?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Fufufu, even I couldn't tell you that.$"
