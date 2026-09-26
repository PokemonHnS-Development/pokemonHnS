CeruleanCity_House3_MapScripts::
	.byte 0

CeruleanCity_House3_EventScript_Granny::
	msgbox CeruleanHouse_Text_Granny, MSGBOX_NPC
	end
CeruleanCity_House3_EventScript_Gramps::
	msgbox CeruleanHouse_Text_Gramps, MSGBOX_NPC
	end

CeruleanCity_House3_EventScript_Kangaskhan::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_NORMAL
	msgbox CeruleanHouse_Text_Kangaskhan, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CeruleanCity_House3_EventScript_Zubat::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZUBAT, CRY_MODE_NORMAL
	msgbox CeruleanHouse_Text_Zubat, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CeruleanHouse_Text_Granny:
	.string "Mi esposo vive feliz con\n"
	.string "POKéMON que obtuvo por cambios.$"

CeruleanHouse_Text_Gramps:
	.string "Ah... estoy tan feliz...$"

CeruleanHouse_Text_Kangaskhan:
	.string "KANGASKHAN: Garu garuu.$"

CeruleanHouse_Text_Zubat:
	.string "ZUBAT: Zuba zubaa.$"

