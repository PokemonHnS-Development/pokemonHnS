.set LOCALID_CELADON_FALKNER, 5

CeladonCity_DepartmentStore_5F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept5_EventScript_Gent::
	msgbox CeladonDeptStore5F_Text_Gentleman, MSGBOX_NPC
	end
CeladonDept5_EventScript_Sailor::
	msgbox CeladonDeptStore5F_Text_Sailor, MSGBOX_NPC
	end
CeladonDept5_EventScript_Teacher::
	msgbox CeladonDeptStore5F_Text_Teacher, MSGBOX_NPC
	end
CeladonDept5_EventScript_Directory::
	msgbox CeladonDeptStore5F_Text_Directory, MSGBOX_SIGN
	end

CeladonDeptStore5_EventScript_Falkner::
	lock
	faceplayer
	msgbox CeladonDeptStore5_Text_Falkner, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CELADON_FALKNER
	removeobject LOCALID_CELADON_FALKNER
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_FALKNER
	release
	end

CeladonDeptStore5_Text_Falkner:
	.string "{PLAYER}. I didn't expect to see\n"
	.string "you here.\p"
	.string "I'm picking up gear for my\n"
	.string "bird POKéMON.\p"
	.string "If you want to face me again, I'll\n"
	.string "be at the DOJO in SAFFRON CITY.$"

CeladonDeptStore5F_Text_Gentleman:
	.string "I want to buy some items that\n"
	.string "raise POKéMON stats, but I don't\l"
	.string "have enough money…$"

CeladonDeptStore5F_Text_Sailor:
	.string "I want PP UP, so I can raise the\n"
	.string "PP of moves. But you can't buy it…$"

CeladonDeptStore5F_Text_Teacher:
	.string "Using items on them makes POKéMON\n"
	.string "happy.\p"
	.string "They hate certain items, though…$"

CeladonDeptStore5F_Text_Directory:
	.string "5F: DRUG STORE & MEGA STONE SHOP$"

// ── Mega Ring gift NPC ──────────────────────────────────────────────────────
CeladonDept5_EventScript_MegaRingNPC::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MEGA_RING, CeladonDept5_EventScript_MegaRingNPC_Already
	msgbox CeladonDept5_Text_MegaRingOffer, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	setflag FLAG_RECEIVED_MEGA_RING
	release
	end

CeladonDept5_EventScript_MegaRingNPC_Already::
	msgbox CeladonDept5_Text_MegaRingAlready, MSGBOX_NPC
	release
	end

CeladonDept5_Text_MegaRingOffer:
	.string "Trainer! I've been looking for\n"
	.string "someone worthy.\p"
	.string "This MEGA RING channels the bond\n"
	.string "between trainer and POKéMON.\p"
	.string "Wear it, and your POKéMON can\n"
	.string "MEGA EVOLVE in battle if they hold\l"
	.string "the right MEGA STONE!$"

CeladonDept5_Text_MegaRingAlready:
	.string "The bond between you and your\n"
	.string "POKéMON grows stronger every day.$"

// ── Kanto Mega Stones Clerk (Venusaur → Mewtwo) ────────────────────────────
CeladonDept5_EventScript_MegaClerk1::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonDept5_Pokemart_KantoMegaStones
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
CeladonDept5_Pokemart_KantoMegaStones:
	.2byte ITEM_VENUSAURITE
	.2byte ITEM_CHARIZARDITE_X
	.2byte ITEM_CHARIZARDITE_Y
	.2byte ITEM_BLASTOISINITE
	.2byte ITEM_BEEDRILLITE
	.2byte ITEM_PIDGEOTITE
	.2byte ITEM_ALAKAZITE
	.2byte ITEM_SLOWBRONITE
	.2byte ITEM_GENGARITE
	.2byte ITEM_KANGASKHANITE
	.2byte ITEM_PINSIRITE
	.2byte ITEM_GYARADOSITE
	.2byte ITEM_AERODACTYLITE
	.2byte ITEM_MEWTWONITE_X
	.2byte ITEM_MEWTWONITE_Y
	.2byte ITEM_NONE
	release
	end

// ── Johto/Hoenn Mega Stones Clerk + Primal Orbs ────────────────────────────
CeladonDept5_EventScript_MegaClerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonDept5_Pokemart_JohtoHoennMegaStones
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
CeladonDept5_Pokemart_JohtoHoennMegaStones:
	.2byte ITEM_AMPHAROSITE
	.2byte ITEM_STEELIXITE
	.2byte ITEM_SCIZORITE
	.2byte ITEM_HERACRONITE
	.2byte ITEM_HOUNDOOMINITE
	.2byte ITEM_TYRANITARITE
	.2byte ITEM_SCEPTILITE
	.2byte ITEM_BLAZIKENITE
	.2byte ITEM_SWAMPERTITE
	.2byte ITEM_GARDEVOIRITE
	.2byte ITEM_SABLEYITE
	.2byte ITEM_MAWILITE
	.2byte ITEM_AGGRONITE
	.2byte ITEM_MEDICHAMITE
	.2byte ITEM_MANECTITE
	.2byte ITEM_SHARPEDONITE
	.2byte ITEM_CAMERUPTITE
	.2byte ITEM_ALTARIANITE
	.2byte ITEM_BANETTITE
	.2byte ITEM_ABSOLITE
	.2byte ITEM_GLALITITE
	.2byte ITEM_SALAMENCITE
	.2byte ITEM_METAGROSSITE
	.2byte ITEM_LATIASITE
	.2byte ITEM_LATIOSITE
	.2byte ITEM_LOPUNNITE
	.2byte ITEM_GARCHOMPITE
	.2byte ITEM_LUCARIONITE
	.2byte ITEM_ABOMASITE
	.2byte ITEM_GALLADITE
	.2byte ITEM_AUDINITE
	.2byte ITEM_DIANCITE
	.2byte ITEM_RED_ORB_PRIMAL
	.2byte ITEM_BLUE_ORB_PRIMAL
	.2byte ITEM_NONE
	release
	end
