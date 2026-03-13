.set LOCALID_GOLDENROD_ROOF_NERD, 1

GoldenrodCity_DepartmentStore_7F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_DepartmentStore_7F_OnTransition
	.byte 0

GoldenrodCity_DepartmentStore_7F_OnTransition:
	call_if_set FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetDay
	end

GoldenrodCity_DepartmentStore_7F_EventScript_SetNight::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7FNIGHT
	return

GoldenrodCity_DepartmentStore_7F_EventScript_SetDay::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7F
	return


GoldenrodDeptStore7_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Twin::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTwin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Nerd::
	lock
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdOhWow, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROOF_NERD, Common_Movement_ExclamationMark
	delay 20
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROOF_NERD, DIR_SOUTH
	release
	end

GoldenrodDeptStore7_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Bugcatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_RoofPokefanF:
    .string "Whew, I'm tired.\p"
    .string "I sometimes come up to the rooftop\n"
    .string "to take a break from shopping.$"

GoldenrodDeptStore_Text_RoofFisher:
    .string "Pardon? Who says an adult can't get\n"
    .string "into this?\p"
    .string "I'm going to be back every day to\n"
    .string "collect all the dolls!$"

GoldenrodDeptStore_Text_RoofTwin:
    .string "They have bargain sales here every\n"
    .string "so often.$"

GoldenrodDeptStore_Text_RoofSuperNerdOhWow:
    .string "Oh, wow!$"

GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe:
    .string "Will you quit bothering me?$"

GoldenrodDeptStore_Text_RoofPokefanM:
    .string "There's something I really want,\n"
    .string "but I don't have the necessary cash…\p"
    .string "Maybe I'll sell off the BERRIES I've\n"
    .string "collected…$"

GoldenrodDeptStore_Text_RoofTeacher:
    .string "Oh, everything is so cheap!\p"
    .string "I bought so much, my PACK's crammed!$"

GoldenrodDeptStore_Text_RoofBugCatcher:
    .string "My POKéMON always get paralyzed or\n"
    .string "poisoned when the chips are down…\p"
    .string "So I came to buy some FULL HEAL.\p"
    .string "I wonder if there's any left?$"

// ── Z-Crystal gift NPC ──────────────────────────────────────────────────────
GoldenrodDeptStore7_EventScript_ZCrystalNPC::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_FIRST_Z_CRYSTAL, GoldenrodDeptStore7_EventScript_ZCrystalNPC_Already
	msgbox GoldenrodDeptStore7_Text_ZCrystalOffer, MSGBOX_DEFAULT
	giveitem ITEM_NORMALIUM_Z
	setflag FLAG_RECEIVED_FIRST_Z_CRYSTAL
	release
	end

GoldenrodDeptStore7_EventScript_ZCrystalNPC_Already::
	msgbox GoldenrodDeptStore7_Text_ZCrystalAlready, MSGBOX_NPC
	release
	end

GoldenrodDeptStore7_Text_ZCrystalOffer:
	.string "I've traveled all the way from\n"
	.string "ALOLA carrying these Z-CRYSTALS.\p"
	.string "A POKéMON holding a Z-CRYSTAL\n"
	.string "can unleash a Z-MOVE -- a move of\l"
	.string "overwhelming power!\p"
	.string "Take this NORMALIUM Z to start.\n"
	.string "More are sold in this shop!$"

GoldenrodDeptStore7_Text_ZCrystalAlready:
	.string "Z-MOVES resonate with the bond\n"
	.string "between trainer and POKeMON.\p"
	.string "The stronger your bond,\n"
	.string "the greater the power!$"

// ── Type Z-Crystals Clerk ───────────────────────────────────────────────────
GoldenrodDeptStore7_EventScript_ZClerk1::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore7_Pokemart_TypeZCrystals
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodDeptStore7_Pokemart_TypeZCrystals:
	.2byte ITEM_NORMALIUM_Z
	.2byte ITEM_FIRIUM_Z
	.2byte ITEM_WATERIUM_Z
	.2byte ITEM_ELECTRIUM_Z
	.2byte ITEM_GRASSIUM_Z
	.2byte ITEM_ICIUM_Z
	.2byte ITEM_FIGHTINIUM_Z
	.2byte ITEM_POISONIUM_Z
	.2byte ITEM_GROUNDIUM_Z
	.2byte ITEM_FLYINIUM_Z
	.2byte ITEM_PSYCHIUM_Z
	.2byte ITEM_BUGINIUM_Z
	.2byte ITEM_ROCKIUM_Z
	.2byte ITEM_GHOSTIUM_Z
	.2byte ITEM_DRAGONIUM_Z
	.2byte ITEM_DARKINIUM_Z
	.2byte ITEM_STEELIUM_Z
	.2byte ITEM_FAIRIUM_Z
	.2byte ITEM_NONE
	release
	end

// ── Species Z-Crystals Clerk ────────────────────────────────────────────────
GoldenrodDeptStore7_EventScript_ZClerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore7_Pokemart_SpeciesZCrystals
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodDeptStore7_Pokemart_SpeciesZCrystals:
	.2byte ITEM_PIKANIUM_Z
	.2byte ITEM_EEVIUM_Z
	.2byte ITEM_SNORLIUM_Z
	.2byte ITEM_MEWNIUM_Z
	.2byte ITEM_DECIDIUM_Z
	.2byte ITEM_INCINIUM_Z
	.2byte ITEM_PRIMARIUM_Z
	.2byte ITEM_TAPUNIUM_Z
	.2byte ITEM_ULTRANECROZIUM_Z
	.2byte ITEM_NONE
	release
	end
