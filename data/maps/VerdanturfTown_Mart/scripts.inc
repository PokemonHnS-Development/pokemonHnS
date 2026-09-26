VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_Mart_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_NEST_BALL
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_POKE_DOLL
	.2byte ITEM_NONE
	release
	end

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "Para cualquier combate POKéMON, X\n"
	.string "SPECIAL es crucial.\p"
	.string "Sube el poder de algunos movimientos\n"
	.string "solo por una batalla.$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "No venden guías de estrategia para\n"
	.string "la CARPA DE COMBATE...\p"
	.string "Parece que al final uno debe confiar\n"
	.string "en su propio ingenio...$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "La NEST BALL funciona mejor con\n"
	.string "POKéMON debilitados.\p"
	.string "VERDANTURF es el único lugar donde\n"
	.string "puedes comprarla.$"

