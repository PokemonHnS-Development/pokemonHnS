SaffronCity_CopyCatsHouse_1F_MapScripts::
	.byte 0

SaffronCity_CopyCatsHouse_1F_EventScript_Mom::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_CopyCatsHouse_1F_EventScript_MomAfter
	msgbox CopycatsHouse1F_Text_PokefanF, MSGBOX_NPC
	end

SaffronCity_CopyCatsHouse_1F_EventScript_MomAfter::
	msgbox CopycatsHouse1F_Text_PokefanF_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_CopyCatsHouse_1F_EventScript_Dad::
	msgbox CopycatsHouse1F_Text_PokefanM, MSGBOX_NPC
	end

SaffronCity_CopyCatsHouse_1F_EventScript_Blissey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BLISSEY, CRY_MODE_NORMAL
	msgbox CopycatsHouse1F_Text_Blissey, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CopycatsHouse1F_Text_PokefanM:
	.string "A mi hija le gusta imitar.\p"
	.string "Por eso aquí todos la llaman\n"
	.string "la IMITADORA.$"

CopycatsHouse1F_Text_PokefanF:
	.string "Mi hija es muy egocéntrica...\p"
	.string "Solo tiene unos pocos amigos.$"

CopycatsHouse1F_Text_PokefanF_ReturnedPart:
	.string "Perdió hace poco la POKé DOLL\n"
	.string "que un chico le dio hace tres\l"
	.string "años.\p"
	.string "Desde entonces, es aún mejor\n"
	.string "imitando...$"

CopycatsHouse1F_Text_Blissey:
	.string "BLISSEY: ¡Bliisii!$"
