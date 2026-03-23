CeladonCity_GameCorner_MapScripts::
	.byte 0

CeladonGameCorner_EventScript_PokefanM::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_PokefanM, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Teacher::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Teacher, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_FishingGuru::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_FishingGuru, MSGBOX_NPC
	closemessage
	release
	end

CeladonGameCorner_EventScript_Fisher1::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Fisher1, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Fisher2::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Fisher2, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_GymGuide::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_GymGuide, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Gramps::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Gramps, MSGBOX_NPC
	closemessage
	release
	end

CeladonGameCorner_EventScript_PokefanF::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonGameCorner_Text_PokefanM:
	.string "The slot machines are all state\n"
	.string "of the art.$"

CeladonGameCorner_Text_Teacher:
	.string "It's this machine I want.\p"
	.string "It cleaned me out yesterday, so it\n"
	.string "should pay out today.$"

CeladonGameCorner_Text_FishingGuru:
	.string "I think this slot machine will pay\n"
	.string "out…\p"
	.string "The odds vary among machines.$"

CeladonGameCorner_Text_Fisher1:
	.string "Gahahaha!\p"
	.string "The coins just keep coming in!\p"
	.string "Hm? What, kid? You want to play?\p"
	.string "I'll share my luck with you!$"

CeladonGameCorner_Text_Fisher2:
	.string "Gahahaha!\p"
	.string "It makes me feel good to do nice\n"
	.string "things for other people!$"

CeladonGameCorner_Text_GymGuide:
	.string "Hey! CHAMP in making!\p"
	.string "Are you playing the slots too?\p"
	.string "I'm trying to get enough coins for\n"
	.string "a prize POKéMON.\p"
	.string "But I don't have enough coins yet…$"

CeladonGameCorner_Text_PokefanF:
    .string "Roulette…\p"
    .string "I prefer it over the slots because\n"
    .string "it's easier to figure the odds.\p"
    .string "But the payout is much lower.$"

CeladonGameCorner_Text_Gramps:
	.string "Hmmm… The odds are surely\n"
	.string "better putting it all on blue,\l"
	.string "but... what to do?$"

CeladonGameCorner_Text_Woman:
    .string "I can't stop winning!$"
