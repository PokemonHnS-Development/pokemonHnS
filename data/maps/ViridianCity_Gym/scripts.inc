ViridianCity_Gym_MapScripts::
	.byte 0

ViridianCity_Gym_EventScript_Blue::
	lock
	faceplayer
	
	@ if Blue is already at dojo, just do defeated dialogue
	goto_if_unset FLAG_HIDE_DOJO_BLUE, ViridianCity_Gym_EventScript_Blue_Defeated
	@ if Blue is not already at dojo, but player is kanto champion, send him to dojo
	goto_if_set FLAG_IS_KANTO_CHAMPION, ViridianCity_Gym_EventScript_BlueGotoDojo
	@ if player is not champion yet, just do defeated dialogue
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_Blue_Defeated
	
	msgbox ViridianCity_Gym_Text_LeaderBlue_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLUE, ViridianCity_Gym_Text_LeaderBlue_Win
	message ViridianCity_Gym_Text_ReceivedEarthBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox ViridianCity_Gym_Text_LeaderBlue_After, MSGBOX_DEFAULT
	setflag FLAG_BADGE16_GET
	setflag FLAG_DEFEATED_VIRIDIAN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 16
	call Common_EventScript_SetGymTrainers
	giveitem ITEM_TM_BULK_UP
	msgbox ViridianCity_Gym_Text_BulkUpSpeech, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_LEAGUE_BLACKBELT
	setflag FLAG_HIDE_CERULEANCAVE_GUARD
	release
	end

ViridianCity_Gym_EventScript_Blue_Defeated::
	msgbox ViridianCity_Gym_Text_LeaderBlue_Epilogue, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_Gym_EventScript_BlueGotoDojo::
	msgbox ViridianCity_Gym_Text_BlueGotoDojo, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_DOJO_BLUE
	release
	end

ViridianCity_Gym_Text_BlueGotoDojo:
	.string "BLUE: Back for more already?\p"
	.string "If you want another shot at me,\n"
	.string "come to the FIGHTING DOJO!$"

ViridianCity_Gym_Text_LeaderBlue_Before:
	.string "BLUE: Yo! Finally got here, huh?\p"
	.string "I wasn't in the mood at CINNABAR,\p"
	.string "but now I'm ready to battle you.\p"
	.string "…\p"
	.string "You're telling me you conquered all\n"
	.string "the GYMS in JOHTO?\p"
	.string "Heh! JOHTO's GYMS must be pretty\n"
	.string "pathetic then.\p"
	.string "Hey, don't worry about it.\p"
	.string "I'll know if you are good or not by\n"
	.string "battling you right now.\p"
	.string "Ready, JOHTO CHAMP?$"

ViridianCity_Gym_Text_LeaderBlue_Win:
	.string "BLUE: What?\p"
	.string "How the heck did I lose to you?\p"
	.string "…\p"
	.string "Tch, all right… Here, take this--it's\n"
	.string "EARTHBADGE.$"

ViridianCity_Gym_Text_ReceivedEarthBadge:
	.string "{PLAYER} received EARTHBADGE.$"

ViridianCity_Gym_Text_BulkUpSpeech:
    .string "That TM contains BULK UP.\p"
    .string "It lets a POKéMON become an\n"
    .string "unstoppable force and an\l"
	.string "immovable object all at once!\p"
    .string "Don't let anyone tell you\n"
    .string "that you have to choose\l"
	.string "between offense and defense.$"

ViridianCity_Gym_Text_LeaderBlue_After:
	.string "BLUE: …\p"
	.string "All right, I was wrong. You're the\n"
	.string "real deal. You are a good TRAINER.\p"
	.string "But I'm going to beat you someday.\p"
	.string "Don't you forget it!$"

ViridianCity_Gym_Text_LeaderBlue_Epilogue:
	.string "BLUE: Listen, you.\p"
	.string "You'd better not lose until I beat\n"
	.string "you. Got it?$"


ViridianCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_GymGuyAfter
	msgbox ViridianCity_Gym_Text_Guide, MSGBOX_NPC
	end

ViridianCity_Gym_EventScript_GymGuyAfter::
	msgbox ViridianCity_Gym_Text_Guide_Win, MSGBOX_NPC
	end

ViridianCity_Gym_Text_Guide:
	.string "Yo, CHAMP in making!\p"
	.string "How's it going? Looks like you're on\n"
	.string "a roll.\p"
	.string "The GYM LEADER is a guy who battled\n"
	.string "the CHAMPION three years ago.\p"
	.string "He's no pushover.\p"
	.string "Give it everything you've got!$"

ViridianCity_Gym_Text_Guide_Win:
	.string "Man, you are truly tough…\p"
	.string "That was a heck of an inspirational\n"
	.string "battle. It brought tears to my eyes.$"


ViridianCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE16_GET, ViridianCity_Gym_EventScript_GymStatuePostVictory
	msgbox ViridianCity_Gym_Text_GymStatue
	releaseall
	end

ViridianCity_Gym_EventScript_GymStatuePostVictory::
	msgbox ViridianCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

ViridianCity_Gym_Text_GymStatue::
    .string "VIRIDIAN POKéMON GYM\n"
    .string "LEADER: BLUE\p"
	.string "WINNING TRAINERS:\n"
	.string "BLUE, RED$"

ViridianCity_Gym_Text_GymStatuePlayerWon::
    .string "VIRIDIAN POKéMON GYM\n"
    .string "LEADER: BLUE\p"
    .string "WINNING TRAINERS:\n"
	.string "BLUE, RED, {PLAYER}$"

