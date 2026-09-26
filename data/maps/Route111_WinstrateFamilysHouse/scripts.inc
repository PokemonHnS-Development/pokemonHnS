.set LOCALID_VIVI, 1
.set LOCALID_VICTOR, 2
.set LOCALID_VICTORIA, 3
.set LOCALID_VICKY, 4

Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "Eres el primer ENTRENADOR que veo\n"
	.string "usar POKéMON con tal maestría.\p"
	.string "Pero debo decirte que mi hijo es\n"
	.string "más fuerte que tú.\p"
	.string "Incluso aceptó el desafío de la\n"
	.string "LIGA POKéMON, que lo sepas.$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "Usamos esta CINTA FUERZA para\n"
	.string "fortalecer mejor a los POKéMON\l"
	.string "en el entrenamiento.\p"
	.string "Como nos venciste a todos,\n"
	.string "no sé si la necesites, pero\l"
	.string "queremos darte nuestra CINTA FUERZA.$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "En las batallas POKéMON,\n"
	.string "solemos ser muy apasionados.$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "Mamá es más fuerte que Papá.\p"
	.string "Yo soy más fuerte que Mamá.\p"
	.string "¡Y la abuela es más fuerte que yo!\p"
	.string "Pero mi hermano mayor es aún más\n"
	.string "fuerte que la abuela.$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "No hay duda de que eres fuerte.\p"
	.string "Pero si lucharas con mi nieto,\n"
	.string "llorarías de frustración.\p"
	.string "Es más fuerte que cualquier\n"
	.string "ENTRENADOR que conocemos.\p"
	.string "Ya debe estar desafiando al\n"
	.string "CAMPEÓN de la LIGA POKéMON.\p"
	.string "¡Conociéndolo, ya podría ser el\n"
	.string "CAMPEÓN!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "Mi nieto ya debe estar desafiando al\n"
	.string "CAMPEÓN de la LIGA POKéMON.\p"
	.string "¡Conociéndolo, ya podría ser el\n"
	.string "CAMPEÓN!$"

