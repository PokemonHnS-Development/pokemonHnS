.set LOCALID_VERMILION_EUSINE, 24
.set LOCALID_VERMILION_SUICUNE, 23
.set LOCALID_VERMILION_SNORLAX, 1

VermilionCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_MapScript_OnTransition
	.byte 0

VermilionCity_MapScript_OnTransition::
	goto_if_eq VAR_SUICUNE_ENCOUNTERS, 3, VermilionCity_EventScript_SetSuicuneScene
	setflag FLAG_HIDE_VERMILION_EUSINE_SUICUNE
	end

VermilionCity_EventScript_SetSuicuneScene::
	clearflag FLAG_HIDE_VERMILION_EUSINE_SUICUNE
	end

VermilionCity_TriggerCity:: @flagheap
	setflag FLAG_VISITED_VERMILION_CITY
	setflag FLAG_HIDE_COPYCAT_CLEFAIRY_DOLL
	setflag FLAG_HIDE_CERULEAN_GYM_TRAINERS
	setflag FLAG_HIDE_CERULEAN_CAPE_ROCKET
	setflag FLAG_HIDE_CERULEAN_GYM_ROCKET
	setflag FLAG_HIDDEN_ITEM_MACHINE_PART
	setflag FLAG_HIDE_ROUTE25_MISTY
	setflag FLAG_HIDE_ROUTE25_EUSINE
	setflag FLAG_HIDE_ROUTE25_SUICUNE
	setflag FLAG_HIDE_CELADON_EUSINE
	setflag FLAG_HIDE_SEAFOAM_GYMGUY
	setflag FLAG_HIDE_VIRIDIAN_BLUE
	setflag FLAG_HIDE_ROUTE14_EUSINE
	setflag FLAG_HIDE_ROUTE14_SUICUNE
	
	clearflag FLAG_BADGE09_GET
	clearflag FLAG_BADGE10_GET
	clearflag FLAG_BADGE11_GET
	clearflag FLAG_BADGE12_GET
	clearflag FLAG_BADGE13_GET
	clearflag FLAG_BADGE14_GET
	clearflag FLAG_BADGE15_GET
	clearflag FLAG_BADGE16_GET
	clearflag FLAG_GOT_VERMILION_HP_UP
	clearflag FLAG_GOT_KANTO_RADIO
	clearflag FLAG_HIDE_VERMILION_SNORLAX
	clearflag FLAG_HIDE_FAN_CLUB_CLEFAIRY_DOLL
	clearflag FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES
	clearflag FLAG_RETURNED_MACHINE_PART
	clearflag FLAG_GOT_TM_PSYCHIC
	clearflag FLAG_GOT_HOENN_STARTER
	clearflag FLAG_GOT_UP_GRADE
	clearflag FLAG_GOT_CLEANSE_TAG
	clearflag FLAG_ROUTE25_GOT_NUGGET
	clearflag FLAG_HIDE_POWER_PLANT_ENGINEER
	clearflag FLAG_HIDE_ZAPDOS
	clearflag FLAG_HIDE_ARTICUNO
	clearflag FLAG_HIDE_MOLTRES
	clearflag FLAG_GOT_TM_REST
	clearflag FLAG_GOT_SUPER_ROD
	clearflag FLAG_HIDE_CINNABAR_BLUE
	clearflag FLAG_GOT_ROUTE2_NUGGET
	clearflag FLAG_GOT_VIRIDIAN_TM_SLUDGE_BOMB
	clearflag FLAG_GOT_ROUTE_14_AERIAL_ACE
	clearflag FLAG_HIDE_PEWTER_ROOT_FOSSIL
	clearflag FLAG_HIDE_PEWTER_CLAW_FOSSIL
	clearflag FLAG_HIDE_MTMOON_SILVER
	clearflag FLAG_GOT_TM_STEEL_WING
	clearflag FLAG_HIDE_CERULEANCAVE_GUARD
	clearflag FLAG_HIDE_MTSILVER_RED
	clearflag FLAG_HIDE_MEWTWO
	clearflag FLAG_HIDE_LATIAS
	clearflag FLAG_HIDE_LATIOS
	clearflag FLAG_HIDE_GROUDON
	clearflag FLAG_HIDE_KYOGRE
	clearflag FLAG_HIDE_RAYQUAZA
	clearflag FLAG_HIDE_SEAFOAM_BLAINE

	clearflag FLAG_HIDE_CELADON_FALKNER
	clearflag FLAG_HIDE_VIRIDIAN_BUGSY
	clearflag FLAG_HIDE_DEPTSTORE_WHITNEY
	clearflag FLAG_HIDE_BELLCHIME_MORTY
	clearflag FLAG_HIDE_CAFE_JASMINE
	clearflag FLAG_HIDE_LAKE_PRYCE
	clearflag FLAG_HIDE_DEN_CLAIR


	setvar VAR_KANTO_ROCKET_STORY_STATE, 0
	setvar VAR_BILLS_GRANDPA, 0


	setvar VAR_FAN_CLUB_CLEFAIRY, 0
	setvar VAR_FAN_CLUB_GUY, 0
	setvar VAR_CLEFAIRY_DOLL_STATE, 0
	setvar VAR_NUM_BADGES, 8
	setvar VAR_VERMILION_CITY_STATE, 1

	setvar VAR_KANTO_SAFARI_ZONE_PROGRESS, 0 @removelater
	clearflag FLAG_IN_KANTO_SAFARI_ZONE @removelater
	clearflag FLAG_IS_KANTO_CHAMPION @removelater
	setvar VAR_BAOBA_QUEST_STATE, 0 @removelater
	setvar VAR_CINNABAR_ISLAND_STATE, 0 @removelater
	setvar VAR_MT_SILVER_STATE, 0, @removelater
	setvar VAR_PALLETTOWN_LABSTATE, 0 @removelater
	clearflag FLAG_HIDE_LEAGUE_BLACKBELT @removelater
	setflag FLAG_HIDE_DOJO_FALKNER
	setflag FLAG_HIDE_DOJO_BUGSY
	setflag FLAG_HIDE_DOJO_WHITNEY
	setflag FLAG_HIDE_DOJO_MORTY
	setflag FLAG_HIDE_DOJO_CHUCK
	setflag FLAG_HIDE_DOJO_JASMINE
	setflag FLAG_HIDE_DOJO_PRYCE
	setflag FLAG_HIDE_DOJO_CLAIR
	setflag FLAG_HIDE_DOJO_BROCK
	setflag FLAG_HIDE_DOJO_MISTY
	setflag FLAG_HIDE_DOJO_SURGE
	setflag FLAG_HIDE_DOJO_ERIKA
	setflag FLAG_HIDE_DOJO_JANINE
	setflag FLAG_HIDE_DOJO_SABRINA
	setflag FLAG_HIDE_DOJO_BLAINE
	setflag FLAG_HIDE_DOJO_BLUE
	end

VermilionCity_EventScript_OldSeaMap::
	finditem ITEM_OLD_SEA_MAP
	end

VermilionCity_TriggerSuicuneTop::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	delay 60
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_PlayerWalkToRailTop
	delay 60
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineWalkToRail
	waitmovement LOCALID_VERMILION_EUSINE
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_EventScript_SuicuneEpisode
VermilionCity_TriggerSuicuneMid::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	delay 60
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_PlayerWalkToRailMid
	delay 60
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineWalkToRail
	waitmovement LOCALID_VERMILION_EUSINE
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_EventScript_SuicuneEpisode
VermilionCity_TriggerSuicuneBot::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	delay 60
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_Suicune1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_PlayerWalkToRailBot
	delay 60
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineWalkToRail
	waitmovement LOCALID_VERMILION_EUSINE
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_EventScript_SuicuneEpisode

VermilionCity_EventScript_SuicuneEpisode::
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_SuicuneLeave
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	msgbox VermilionCity_Text_Eusine, MSGBOX_DEFAULT
	turnobject LOCALID_VERMILION_EUSINE, DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox VermilionCity_Text_Eusine2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineLeave
	waitmovement 0
	removeobject LOCALID_VERMILION_EUSINE
	removeobject LOCALID_VERMILION_SUICUNE
	setflag FLAG_HIDE_VERMILION_EUSINE_SUICUNE

	setvar VAR_SUICUNE_ENCOUNTERS, 4
	clearflag FLAG_HIDE_ROUTE14_SUICUNE
	release
	end

VermilionCity_EventScript_Teacher::
	msgbox VermilionCity_Text_Teacher, MSGBOX_NPC
	end

VermilionCity_EventScript_Oldman::
	msgbox VermilionCity_Text_MachopOwner, MSGBOX_NPC
	end

VermilionCity_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, CRY_MODE_NORMAL
	msgbox VermilionCity_Text_Machop1, MSGBOX_DEFAULT
	waitmoncry
	msgbox VermilionCity_Text_Machop2, MSGBOX_DEFAULT
	release
	end

VermilionCity_EventScript_Nerd::
	msgbox VermilionCity_Text_SuperNerd, MSGBOX_NPC
	end

VermilionCity_EventScript_Snorlax::
	lock
	goto_if_set FLAG_GOT_KANTO_RADIO, VermilionCity_EventScript_SnorlaxWakeUp
	msgbox VermilionCity_Text_SnorlaxSleeping, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_EventScript_SnorlaxWakeUp::
	playse MUS_HG_RADIO_POKE_FLUTE
	msgbox VermilionCity_Text_RadioNearSnorlax, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_SNORLAX, 50
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, VermilionCity_EventScript_SnorlaxRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_VERMILION_SNORLAX
	removeobject 8
	removeobject 9
	removeobject 10
	removeobject 11
	setflag FLAG_HIDE_VERMILION_SNORLAX
	fadescreenswapbuffers FADE_FROM_BLACK
	setflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD
	release
	end

VermilionCity_EventScript_SnorlaxRan::
	release
	end

VermilionCity_EventScript_BadgeGuy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_VERMILION_HP_UP, VermilionCity_EventScript_BadgeGuyAfter
	goto_if_ge VAR_NUM_BADGES, 16, VermilionCity_EventScript_BadgeGuyAll
	goto_if_ge VAR_NUM_BADGES, 12, VermilionCity_EventScript_BadgeGuyMost
	goto_if_ge VAR_NUM_BADGES, 9, VermilionCity_EventScript_BadgeGuySome
	msgbox VermilionCity_Text_BadgeGuy_Trainer, MSGBOX_DEFAULT
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuySome::
	msgbox VermilionCity_Text_BadgeGuy_SomeBadges, MSGBOX_DEFAULT
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuyMost::
	msgbox VermilionCity_Text_BadgeGuy_MostBadges, MSGBOX_DEFAULT
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuyAll::
	msgbox VermilionCity_Text_BadgeGuy_AllBadges, MSGBOX_DEFAULT
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_VERMILION_HP_UP
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuyAfter::
	msgbox VermilionCity_Text_BadgeGuy_BattleEdge, MSGBOX_DEFAULT
	closemessage
	release
	end


VermilionCity_Movement_Suicune1:
	jump_in_place_left
	jump_in_place_left
	jump_in_place_left
	step_end

VermilionCity_Movement_PlayerWalkToRailTop:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	step_end
VermilionCity_Movement_PlayerWalkToRailMid:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	step_end
VermilionCity_Movement_PlayerWalkToRailBot:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

VermilionCity_Movement_EusineWalkToRail:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	step_end

VermilionCity_Movement_SuicuneLeave:
	jump_in_place_left
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

VermilionCity_Movement_EusineLeave:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VermilionCity_Text_Eusine:
	.string "EUSINE: That was so close!\n"
	.string "I though I could corner it by\l"
	.string "ambushing it here.\p"
	.string "But running on the water is beyond\n"
	.string "me.\p"
	.string "Still, I am starting to see\n"
	.string "a pattern.\p"
	.string "SUICUNE prefers water!\p"
	.string "That means...$"

VermilionCity_Text_Eusine2:
	.string "Sorry {PLAYER}, I've got to go!$"

VermilionCity_Text_Teacher:
	.string "VERMILION PORT is KANTO's seaside\n"
	.string "gateway.\p"
	.string "Luxury liners from around the\n"
	.string "world dock here.$"

VermilionCity_Text_MachopOwner:
	.string "My POKéMON is preparing the land\n"
	.string "for construction.\p"
	.string "But I have no money to start the\n"
	.string "project…$"

VermilionCity_Text_Machop1:
	.string "MACHOP: Guooh gogogoh!$"

VermilionCity_Text_Machop2:
	.string "A MACHOP is growling while\n"
	.string "stomping the ground flat.$"

VermilionCity_Text_SuperNerd:
	.string "There are eight GYMS in KANTO.\p"
	.string "That big building is VERMILION's\n"
	.string "POKéMON GYM.$"

VermilionCity_Text_SnorlaxSleeping:
	.string "SNORLAX is snoring peacefully…$"

VermilionCity_Text_RadioNearSnorlax:
	.string "The POKéGEAR was placed near the\n"
	.string "sleeping SNORLAX…\p"
	.string "…\p"
	.string "SNORLAX woke up!$"

VermilionCity_Text_BadgeGuy_Trainer:
	.string "Skilled trainers gather in KANTO.\p"
	.string "GYM LEADERS are especially strong.\p"
	.string "They won't be easy to defeat.$"

VermilionCity_Text_BadgeGuy_SomeBadges:
	.string "You've started to collect KANTO\n"
	.string "GYM BADGES?\p"
	.string "Don't you agree that the trainers\n"
	.string "here are tough?$"

VermilionCity_Text_BadgeGuy_MostBadges:
	.string "I guess you'll be finished with\n"
	.string "your conquest of KANTO GYMS soon.\p"
	.string "Let me know if you get all eight\n"
	.string "BADGES.$"

VermilionCity_Text_BadgeGuy_AllBadges:
	.string "Congratulations!\p"
	.string "You got all the KANTO GYM BADGES.\p"
	.string "I've got a reward for your efforts.$"

VermilionCity_Text_BadgeGuy_BattleEdge:
	.string "Having a variety of POKéMON types\n"
	.string "should give you an edge in battle.\p"
	.string "I'm sure the KANTO GYM BADGES will\n"
	.string "help you.$"

VermilionCity_EventScript_CitySign::
	msgbox VermilionCity_Text_Sign, MSGBOX_SIGN
	end
VermilionCity_EventScript_GymSign::
	msgbox VermilionCity_Text_GymSign, MSGBOX_SIGN
	end
VermilionCity_EventScript_FanClubSign::
	msgbox VermilionCity_Text_FanClubSign, MSGBOX_SIGN
	end
VermilionCity_EventScript_DiglettsCaveSign::
	msgbox VermilionCity_Text_DiglettsCaveSign, MSGBOX_SIGN
	end

VermilionCity_Text_Sign:
	.string "VERMILION CITY\p"
	.string "The Port of Exquisite Sunsets$"

VermilionCity_Text_GymSign:
	.string "VERMILION CITY\n"
	.string "POKéMON GYM\p"
	.string "LEADER: LT.SURGE\p"
	.string "The Lightning American$"

VermilionCity_Text_FanClubSign:
	.string "POKéMON FAN CLUB\p"
	.string "All POKéMON Fans Welcome!$"

VermilionCity_Text_DiglettsCaveSign:
	.string "DIGLETT'S CAVE$"

VermilionCity_Text_PortSign:
	.string "VERMILION PORT\n"
	.string "ENTRANCE$"
