GoldenrodCity_DepartmentStore_4F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore4_EventScript_Cooltrainer::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FCooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_GBAKid::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FGameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_4FCooltrainerM:
    .string "Hola. Amo los POKéMON fuertes.\p"
    .string "Les doy PROTEÍNA para subir\n"
    .string "su ATAQUE.$"

GoldenrodDeptStore_Text_4FBugCatcher:
    .string "El HIERRO aumenta la\n"
    .string "DEFENSA de tu POKéMON.$"

GoldenrodDeptStore_Text_4FGameboyKid:
    .string "Había rumores de que algunos\n"
    .string "POKéMON evolucionan solo al\l"
    .string "ser intercambiados por cable\l"
    .string "link.\p"
    .string "Pfft...\p"
    .string "Qué desinformación.\p"
    .string "Conozco algunos de esos\n"
    .string "POKéMON:\l"
    .string "MACHOKE, KADABRA, HAUNTER y,\l"
    .string "este, GRAVELER,\l"
    .string "pero todos evolucionan al\l"
    .string "subir de nivel.$"

GoldenrodDeptStore_Text_4FDirectory:
    .string "¡Potenciemos tu POKéMON!\p"
    .string "CAJA MEDICINAS 4F$"
