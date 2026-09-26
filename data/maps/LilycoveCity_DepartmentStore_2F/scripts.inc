LilycoveCity_DepartmentStore_2F_MapScripts::
	.byte 0

LilycoveCity_DepartmentStore_2F_EventScript_Cook::
	msgbox LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_PokefanF::
	msgbox LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_Sailor::
	msgbox LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

@	.align 2
@LilycoveCity_DepartmentStore_2F_Pokemart1:
@	.2byte ITEM_POKE_BALL
@	.2byte ITEM_GREAT_BALL
@	.2byte ITEM_ULTRA_BALL
@	.2byte ITEM_ESCAPE_ROPE
@	.2byte ITEM_FULL_HEAL
@	.2byte ITEM_ANTIDOTE
@	.2byte ITEM_PARALYZE_HEAL
@	.2byte ITEM_BURN_HEAL
@	.2byte ITEM_ICE_HEAL
@	.2byte ITEM_AWAKENING
@	.2byte ITEM_FLUFFY_TAIL
@	.2byte ITEM_NONE
@	release
@	end

LilycoveCity_DepartmentStore_2F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart2:
	.2byte ITEM_MAX_POTION
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_WAVE_MAIL
	.2byte ITEM_MECH_MAIL
	.2byte ITEM_ORANGE_MAIL
    .2byte ITEM_HARBOR_MAIL
    .2byte ITEM_GLITTER_MAIL
    .2byte ITEM_WOOD_MAIL
    .2byte ITEM_BEAD_MAIL
    .2byte ITEM_SHADOW_MAIL
    .2byte ITEM_TROPIC_MAIL
    .2byte ITEM_DREAM_MAIL
    .2byte ITEM_FAB_MAIL
    .2byte ITEM_RETRO_MAIL
	.2byte ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly:
	.string "Aprende a usar los objetos bien.\n"
	.string "Es algo básico, de verdad.$"

LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband:
	.string "Mi esposo me espera en casa.\n"
	.string "¿Qué sería un buen regalo para él?$"

LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems:
	.string "Pronto partiré en un viaje largo.\n"
	.string "Debo comprar varios objetos.$"

