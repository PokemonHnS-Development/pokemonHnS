GoldenrodCity_BikeShop_MapScripts::
	.byte 0

GoldenrodCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived
	msgbox GoldenrodCity_BikeShop_Text_ClerkIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed
	msgbox GoldenrodCity_BikeShop_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed::
	msgbox GoldenrodCity_BikeShop_Text_ClerkAgreed, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	setflag FLAG_RECEIVED_BIKE
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived::
	msgbox GoldenrodCity_BikeShop_Text_Mainshop, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk2::
	lock
	faceplayer
	msgbox GoldenrodCity_BikeShop_Text_Clerk2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Bike::
	lock
	msgbox GoldenrodCity_BikeShop_Text_Bicycle, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Clerk2:
	.string "Usar la BIKE es tan simple como\n"
	.string "presionar un botón si la\l"
	.string "REGISTRAS desde la MOCHILA.\p"
	.string "Si quieres ir más rápido,\n"
	.string "¡primero debes detenerte!\p"
	.string "Parece un consejo extraño,\n"
	.string "pero solo puedes cambiar\l"
	.string "marchas con la BIKE parado.\p"
	.string "Presiona R al detenerte y\n"
	.string "la próxima vez que pedalees,\l"
	.string "¡irás a mayor velocidad!$"

GoldenrodCity_BikeShop_Text_ClerkIntro:
    .string "…suspiro… Me mudé aquí, pero no\n"
    .string "puedo vender mis BICYCLES. ¿Por qué?\p"
    .string "¿Podrías usar una BICYCLE y\n"
    .string "hacer publicidad por mí?$"

GoldenrodCity_BikeShop_Text_ClerkAgreed:
    .string "¿En serio? ¡Genial!\p"
    .string "Dame tu nombre y teléfono,\n"
    .string "y te prestaré una BICYCLE.$"

GoldenrodCity_BikeShop_Text_BorrowedBicycle:
    .string "{PLAYER} pidió una BICYCLE prestada.$"

GoldenrodCity_BikeShop_Text_Mainshop:
	.string "El negocio ha sido difícil\n"
	.string "desde que nos mudamos de KANTO.\l"
	.string "¡Agradecemos tu ayuda!\p"
	.string "¿Puedes presumir nuestra\n"
	.string "tecnología de cambio de marchas?\p"
	.string "Solo presiona R cuando estés\n"
	.string "detenido con tu BIKE.\p"
	.string "¡Cuidado! ¡Luego irás más rápido!$"

GoldenrodCity_BikeShop_Text_Refused:
    .string "…suspiro… Oh, la bondad de\n"
    .string "la gente…$"

GoldenrodCity_BikeShop_Text_JustReleasedCompact:
    .string "¡Recién salidas!\p"
    .string "¡BICYCLES compactas de primera!$"

GoldenrodCity_BikeShop_Text_Bicycle:
    .string "¡Es una BICYCLE nueva y brillante!$"
