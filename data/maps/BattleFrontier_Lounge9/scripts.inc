BattleFrontier_Lounge9_MapScripts::
	.byte 0

BattleFrontier_Lounge9_Heal::
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, SSTidalRooms_EventScript_Bed_PokecenterChallenge
	msgbox BattleFrontier_Lounge9_Heal_TEXT, MSGBOX_NPC
	waitmessage
	fadescreen 0x1
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	fadescreen 0x0
	msgbox BattleFrontier_Lounge9_Heal_TEXT2, MSGBOX_NPC
	waitmessage
	release
	end

BattleFrontier_Lounge9_Heal_TEXT:
	.string "¡Hola! ¡Bienvenido al DOJO!\n"
	.string "Curaré a tus POKéMON.$"

BattleFrontier_Lounge9_Heal_TEXT2:
	.string "¡Esperamos verte pronto!$"

BattleFrontier_Lounge9_EV_No:
	msgbox BattleFrontier_Lounge9_EV_No_TEXT, MSGBOX_DEFAULT
	waitmessage
	release
	end

@EV Gym

BattleFrontier_Lounge9_EV_HP::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge9_EV_HP_TEXT, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_HP_Yes
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_No
	end

BattleFrontier_Lounge9_EV_HP_Yes::
	msgbox BattleFrontier_Lounge9_EV_HP_TEXT2, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_WAILORD, 1, ITEM_NONE
	dowildbattle
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_NO_SHINY
	release
	end
	
BattleFrontier_Lounge9_EV_ATK::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge9_EV_ATK_TEXT, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_ATK_Yes
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_No
	end

BattleFrontier_Lounge9_EV_ATK_Yes::
	msgbox BattleFrontier_Lounge9_EV_ATK_TEXT2, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_GALLADE, 1, ITEM_NONE
	dowildbattle
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_NO_SHINY
	release
	end

BattleFrontier_Lounge9_EV_SATK::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge9_EV_SATK_TEXT, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_SATK_Yes
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_No
	end

BattleFrontier_Lounge9_EV_SATK_Yes::
	msgbox BattleFrontier_Lounge9_EV_SATK_TEXT2, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_GARDEVOIR, 1, ITEM_NONE
	dowildbattle
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_NO_SHINY
	release
	end

BattleFrontier_Lounge9_EV_DEF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge9_EV_DEF_TEXT, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_DEF_Yes
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_No
	end

BattleFrontier_Lounge9_EV_DEF_Yes::
	msgbox BattleFrontier_Lounge9_EV_DEF_TEXT2, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_AGGRON, 1, ITEM_NONE
	dowildbattle
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_NO_SHINY
	release
	end

BattleFrontier_Lounge9_EV_SDEF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge9_EV_SDEF_TEXT, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_SDEF_Yes
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_No
	end

BattleFrontier_Lounge9_EV_SDEF_Yes::
	msgbox BattleFrontier_Lounge9_EV_SDEF_TEXT2, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_LUDICOLO, 1, ITEM_NONE
	dowildbattle
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_NO_SHINY
	release
	end

BattleFrontier_Lounge9_EV_SPD::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge9_EV_SPD_TEXT, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_SPD_Yes
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_No
	end

BattleFrontier_Lounge9_EV_SPD_Yes::
	msgbox BattleFrontier_Lounge9_EV_SPD_TEXT2, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_SCEPTILE, 1, ITEM_NONE
	dowildbattle
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_NO_SHINY
	release
	end

BattleFrontier_Lounge9_EV_HP_TEXT:
	.string "¡Hola, amigo! Puedo entrenar los\n"
	.string "PS de tus POKéMON.\p"
	.string "¿Estás listo?$"

BattleFrontier_Lounge9_EV_HP_TEXT2:
	.string "¡Ve, WAILORD!$"

BattleFrontier_Lounge9_EV_ATK_TEXT:
	.string "¡OSHA! Puedo entrenar el ATAQUE\n"
	.string "de tus POKéMON.\p"
	.string "¿Estás listo?$"

BattleFrontier_Lounge9_EV_ATK_TEXT2:
	.string "¡Ve, GALLADE!$"

BattleFrontier_Lounge9_EV_SATK_TEXT:
	.string "¡Bonjour! Puedo entrenar el ATAQUE\n"
	.string "ESPECIAL de tus POKéMON.\p"
	.string "¿Listo?$"

BattleFrontier_Lounge9_EV_SATK_TEXT2:
	.string "¡Ve, GARDEVOIR!$"
	
BattleFrontier_Lounge9_EV_DEF_TEXT:
	.string "¡Hola! Puedo entrenar la\n"
	.string "DEFENSA de tu POKéMON.\p"
	.string "¿Estás listo?$"

BattleFrontier_Lounge9_EV_DEF_TEXT2:
	.string "¡Ve, AGGRON!$"

BattleFrontier_Lounge9_EV_SDEF_TEXT:
	.string "¡Bonjour, entrenador! Puedo entrenar\n"
	.string "la DEF. ESP. de tu POKéMON.\p"
	.string "¿Estás listo?$"

BattleFrontier_Lounge9_EV_SDEF_TEXT2:
	.string "¡Ve, LUDICOLO!$"

BattleFrontier_Lounge9_EV_SPD_TEXT:
	.string "Hmph... Puedo entrenar la\n"
	.string "VELOCIDAD de tu POKéMON.\p"
	.string "¿Estás listo?$"

BattleFrontier_Lounge9_EV_SPD_TEXT2:
	.string "¡Ve, SCEPTILE!$"

BattleFrontier_Lounge9_EV_No_TEXT:
	.string "¿No? Está bien.$"

@Columns text

BattleFrontier_Lounge9_EV_Column::
	msgbox BattleFrontier_Lounge9_EV_Column_Text, MSGBOX_SIGN
	end

BattleFrontier_Lounge9_EV_Column_Text:
    .string "¡Bienvenido al DOJO DE ENTRENAMIENTO!\p"
    .string "Aquí hallarás entrenamientos para\n"
    .string "mejorar las ESTADÍSTICAS POKéMON.\p"
    .string "RESETEO DE EV:\n"
    .string "EV-MAN puede resetear los EV de un\l"
    .string "POKéMON a cero. Está a la derecha.\p"
    .string "ENTRENAMIENTO EV:\n"
    .string "Seis entrenadores se enfocan en cada\l"
    .string "ESTADÍSTICA: DEF - ATK - HP - VEL -\l"
    .string "ATK.ESP - DEF.ESP.\p"
    .string "TIP: ¡La MACHO BRACE multiplica los\n"
    .string "EV ganados por 5!\p"
    .string "Al ser el CAMPEÓN DE HOENN,\n"
    .string "desbloquearás lo siguiente:\p"
    .string "ENTRENAMIENTO IV Y PODER OCULTO:\n"
    .string "IV-MAN maximiza los IV de POKéMON.\l"
    .string "También ajusta IV para cambiar el\l"
    .string "tipo de PODER OCULTO.\p"
    .string "ENTRENAMIENTO DE EXP.:\n"
    .string "La ENFERMERA DE EXP. abajo a la\l"
    .string "izquierda entrena a tu equipo.\p"
    .string "CAMBIO DE HABILIDAD:\n"
    .string "El EXPERTO EN HABILIDADES arriba a la\l"
    .string "izquierda cambia las habilidades\l"
    .string "naturales de un POKéMON.$"

@EV RESET

BattleFrontier_Lounge9_EV_SetZero::
	lockall
	faceplayer
	goto_if_unset FLAG_EV_MAN_FIRSTIME, BattleFrontier_Lounge9_EV_SetZeroIntro
	msgbox BattleFrontier_Lounge9_EV_SetZeroTextNoIntro, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroMoney
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroNo
	end

BattleFrontier_Lounge9_EV_SetZeroIntro::
	setflag FLAG_EV_MAN_FIRSTIME
	msgbox BattleFrontier_Lounge9_EV_SetZeroText, MSGBOX_NPC
	waitmessage
	end

BattleFrontier_Lounge9_EV_SetZeroMoney::
	msgbox BattleFrontier_Lounge9_EV_SetZeroMoneyText, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroCheckMoney
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroNo
	end

BattleFrontier_Lounge9_EV_SetZeroCheckMoney::
	checkmoney 20000, 0
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroYes
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroNoMoney
	end

BattleFrontier_Lounge9_EV_SetZeroYes::
	msgbox BattleFrontier_Lounge9_EV_SetZeroText2, MSGBOX_DEFAULT
	waitmessage
	closemessage
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge BattleFrontier_Lounge9_EV_SetZeroNo
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroEgg
	goto BattleFrontier_Lounge9_EV_SetZeroSure
	end

BattleFrontier_Lounge9_EV_SetZeroNo::
	msgbox BattleFrontier_Lounge9_EV_SetZeroTextNo, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_EV_SetZeroNoMoney::
	msgbox BattleFrontier_Lounge9_EV_SetZeroTextNoMoney, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_EV_SetZeroEgg::
	msgbox BattleFrontier_Lounge9_EV_SetZeroTextEgg, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_EV_SetZeroSure::
	faceplayer
	msgbox BattleFrontier_Lounge9_EV_SetZeroTextSure, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroProceed
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroNo
	end

BattleFrontier_Lounge9_EV_SetZeroProceed::
	faceplayer
	fadescreen 0x1
	delay 30
	removemoney 20000, 0
	fadescreen 0x0
	setvar VAR_0x8000, 0
	setvar VAR_0x8001, 0
	setvar VAR_0x8002, 0
	setvar VAR_0x8003, 0
	setvar VAR_0x8005, 0
	setvar VAR_0x8006, 0
	special SetHpEvs
	special SetAtkEvs
	special SetDefEvs
	special SetSpdEvs
	special SetSpAtkEvs
	special SetSpDefEvs
	msgbox BattleFrontier_Lounge9_EV_SetZeroText3, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_EV_SetZeroText:
    .string "Hola, entrenador. Soy EVAN,\n"
    .string "aunque me llaman comúnmente\n"
    .string "EV-MAN.\p"
    .string "Soy el dueño de este lugar,\n"
    .string "donde entreno junto a mi\n"
    .string "hermano, IVAN.\p"
    .string "Si quieres resetear los EVs de un\n"
    .string "POKéMON, habla conmigo.$"

BattleFrontier_Lounge9_EV_SetZeroTextNoIntro:
    .string "EV-MAN: Bienvenido de nuevo.\n"
    .string "¿Quieres que resetee los VALORES\l"
    .string "DE ESFUERZO de tu POKéMON?$"

BattleFrontier_Lounge9_EV_SetZeroText2:
	.string "¿Qué EVs de POKéMON debo resetear\n"
	.string "a cero?$"

BattleFrontier_Lounge9_EV_SetZeroText3:
    .string "¡Uff! Fue duro, ¡pero lo logré!\n"
    .string "¡Sus EVs han vuelto a cero!$"

BattleFrontier_Lounge9_EV_SetZeroTextEgg:
	.string "Lo siento, eso no funcionará.$"

BattleFrontier_Lounge9_EV_SetZeroTextNo:
	.string "¡Vuelve cuando lo necesites!$"

BattleFrontier_Lounge9_EV_SetZeroMoneyText:
    .string "Este proceso es muy difícil.\n"
    .string "Costará 20,000¥.\l"
    .string "¿Quieres continuar?$"

BattleFrontier_Lounge9_EV_SetZeroTextNoMoney:
    .string "No tienes suficiente dinero.\p"
    .string "Vuelve cuando tengas.$"

BattleFrontier_Lounge9_EV_SetZeroTextSure:
    .string "¿Seguro que quieres reiniciar los\n"
    .string "EVs de este POKéMON?\p"
    .string "No podrás deshacer este proceso.$"

@IV setter to 31 (all of them) &&&& HIDDEN POWER Type selector

BattleFrontier_Lounge9_IV_Man::
	checkflag FLAG_IV_SETTER
	lockall
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, BattleFrontier_Lounge9_IV_ManNoChampion
	call_if_unset FLAG_IV_SETTER, BattleFrontier_Lounge9_IV_First_Time
	msgbox BattleFrontier_Lounge9_IV_Text1, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_IV_CheckMoney
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_IV_No
	end

BattleFrontier_Lounge9_IV_ManNoChampion::
	msgbox BattleFrontier_Lounge9_IV_TextNoChampion, MSGBOX_NPC
	releaseall
	end

BattleFrontier_Lounge9_IV_First_Time::
	msgbox BattleFrontier_Lounge9_IV_TextFirstTime, MSGBOX_NPC
	setflag FLAG_IV_SETTER
	releaseall
	end

BattleFrontier_Lounge9_IV_No::
	msgbox BattleFrontier_Lounge9_IV_Text_No, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_IV_NoLevel::
	msgbox BattleFrontier_Lounge9_IV_Text_NoLevel, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_IV_CheckMoney::
	checkmoney 100000, 0
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_Lounge9_IV_ChoosePkm
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroNoMoney
	end

BattleFrontier_Lounge9_IV_ChoosePkm::
	faceplayer
	closemessage
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge BattleFrontier_Lounge9_IV_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroEgg
	goto BattleFrontier_Lounge9_IV_CheckIfLvlMax
	end

BattleFrontier_Lounge9_IV_CheckIfLvlMax::
	faceplayer
	waitmessage
	checkpartymonlevel 100
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_Lounge9_IV_Continue_Question_CustomOrMax
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_Lounge9_IV_NoLevel
	releaseall
	end

BattleFrontier_Lounge9_IV_Continue_Question_CustomOrMax::
	faceplayer
	msgbox BattleFrontier_Lounge9_IV_Text_CustomizeIVs, MSGBOX_DEFAULT
	waitmessage
	dynmultichoice 20, 8, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, EventScript_IVSetter_Text_CustomizeIVs, EventScript_IVSetter_Text_SetMax
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge9_IV_CustomizeIVs_SelectType
	case 1, BattleFrontier_Lounge9_IV_SetMax
	case MULTI_B_PRESSED, BattleFrontier_Lounge9_IV_No
	closemessage
	release
	end

EventScript_IVSetter_Text_CustomizeIVs:
	.string "PERSONALIZAR$"

EventScript_IVSetter_Text_SetMax:
	.string "PONER AL MÁX.$"

BattleFrontier_Lounge9_IV_SetMax::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31
	setvar VAR_0x8008, 31
	setvar VAR_0x8009, 31
	setvar VAR_0x800A, 31
	setvar VAR_0x800B, 31
	setvar VAR_UNUSED_0x8014, 31
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpdIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_IV_CustomizeIVs_SelectType:
	msgbox BattleFrontier_Lounge9_IV_Text_CustomizeIVs_SetType, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, EventScript_IVSetter_Type_Fighting, EventScript_IVSetter_Type_Flying, EventScript_IVSetter_Type_Poison, EventScript_IVSetter_Type_Ground, EventScript_IVSetter_Type_Rock, EventScript_IVSetter_Type_Bug, EventScript_IVSetter_Type_Ghost, EventScript_IVSetter_Type_Steel, EventScript_IVSetter_Type_Fairy, EventScript_IVSetter_Type_Fire, EventScript_IVSetter_Type_Water, EventScript_IVSetter_Type_Grass, EventScript_IVSetter_Type_Electric, EventScript_IVSetter_Type_Psychic, EventScript_IVSetter_Type_Ice, EventScript_IVSetter_Type_Dragon, EventScript_IVSetter_Type_Dark 
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Fighting
	case 1, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Flying
	case 2, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Poison
	case 3, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Ground
	case 4, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Rock
	case 5, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Bug
	case 6, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Ghost
	case 7, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Steel
	case 8, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Fairy
	case 9, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Fire
	case 10, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Water
	case 11, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Grass
	case 12, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Electric
	case 13, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Psychic
	case 14, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Ice
	case 15, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Dragon
	case 16, BattleFrontier_Lounge9_MultichoiceIVs_SetType_Dark
	closemessage
	release
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Fighting::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Flying::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Poison::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Ground::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Rock::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Bug::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Ghost::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Steel::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 30 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Fairy::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 30 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Fire::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 30 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Water::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Grass::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 30 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Electric::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 30 @HP
	setvar VAR_0x8008, 30 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Psychic::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 30 @HP
	setvar VAR_0x8008, 30 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 30 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Ice::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 30 @HP
	setvar VAR_0x8008, 30 @ATK
	setvar VAR_0x8009, 30 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Dragon::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 30 @HP
	setvar VAR_0x8008, 30 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_MultichoiceIVs_SetType_Dark::
	faceplayer
	fadescreen 0x1
	delay 100
	removemoney 100000, 0
	fadescreen 0x0
	faceplayer
	setvar VAR_0x8007, 31 @HP
	setvar VAR_0x8008, 31 @ATK
	setvar VAR_0x8009, 31 @DEF
	setvar VAR_0x800B, 31 @SP. ATK
	setvar VAR_UNUSED_0x8014, 31 @SP. DEF
	setvar VAR_0x800A, 31 @SPD
	special SetHpIvs
	special SetAtkIvs
	special SetDefIvs
	special SetSpAtkIvs
	special SetSpDefIvs
	special SetSpdIvs
	msgbox BattleFrontier_Lounge9_IV_Finish, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_IV_TextNoChampion:
	.string "¿Mmm? ¿Qué?\p"
	.string "Oh, eres entrenador, pero no\n"
	.string "de los fuertes…\p"
	.string "Intenta vencer a la LIGA POKéMON y\n"
	.string "vuelve otra vez.\p"
	.string "Te mostraré la rutina de\n"
	.string "entrenamiento más fuerte de la región!$"

BattleFrontier_Lounge9_IV_Text_CustomizeIVs:
	.string "¿Quieres poner los IVs en un valor\n"
	.string "específico para tener distintos\l"
	.string "tipos de PODER OCULTO?\p"
	.string "¿O pongo todos los IVs en 31?$"

BattleFrontier_Lounge9_IV_Text_CustomizeIVs_SetType:
	.string "¿Qué tipo de PODER OCULTO\n"
	.string "estás buscando?$"

EventScript_IVSetter_Type_Fighting:
	.string "TIPO LUCHA$"

EventScript_IVSetter_Type_Flying:
	.string "TIPO VOLADOR$"

EventScript_IVSetter_Type_Poison:
	.string "TIPO VENENO$"

EventScript_IVSetter_Type_Ground:
	.string "TIPO TIERRA$"

EventScript_IVSetter_Type_Rock:
	.string "TIPO ROCA$"

EventScript_IVSetter_Type_Bug:
	.string "TIPO BICHOS$"

EventScript_IVSetter_Type_Ghost:
	.string "TIPO FANTASMA$"

EventScript_IVSetter_Type_Steel:
	.string "TIPO ACERO$"

EventScript_IVSetter_Type_Fairy:
	.string "TIPO HADA$"

EventScript_IVSetter_Type_Fire:
	.string "TIPO FUEGO$"

EventScript_IVSetter_Type_Water:
	.string "TIPO AGUA$"

EventScript_IVSetter_Type_Grass:
	.string "TIPO PLANTA$"

EventScript_IVSetter_Type_Electric:
	.string "TIPO ELÉCTRICO$"

EventScript_IVSetter_Type_Psychic:
	.string "TIPO PSÍQUICO$"

EventScript_IVSetter_Type_Ice:
	.string "TIPO HIELO$"

EventScript_IVSetter_Type_Dragon:
	.string "TIPO DRAGÓN$"

EventScript_IVSetter_Type_Dark:
	.string "TIPO SINIESTRO$"

BattleFrontier_Lounge9_IV_Text_SetMaxQuestion:
	.string "Pondré todos los IV al máximo\n"
	.string "valor, que es 31. ¿Continúo?$"

BattleFrontier_Lounge9_IV_TextFirstTime:
    .string "¡Hola! ¡Eres tú! ¡Qué bueno es\n"
    .string "verte por aquí!\p"
    .string "Espera... ¿No me conoces?\p"
    .string ". . .\p"
    .string ". . .\p"
    .string "¡Ah, claro! ¡Te vi en la TV hace\n"
    .string "poco tiempo!\p"
    .string "Soy IVAN, ¡pero puedes llamarme\n"
    .string "IV-MAN!\p"
    .string "Sí, soy el hermano de EV-MAN.\n"
    .string "No es ninguna sorpresa.\p"
    .string "Y tú...\p"
    .string "¡Eres {PLAYER}, quien ganó la\n"
    .string "LIGA POKéMON hace poco!\p"
    .string "Tu última batalla fue increíble.\n"
    .string "Aprendí tanto viéndote que me\n"
    .string "uní a tu CLUB DE FANS!\p"
    .string "Después, decidí hacerme más\n"
    .string "fuerte y creé la rutina de\n"
    .string "entrenamiento definitiva.\p"
    .string "¡Para POKéMON, por supuesto!\n"
    .string "Si quieres, podemos entrenar para\n"
    .string "maximizar el potencial de tus POKéMON.\p"
    .string "Pero... para aguantar esto, un\n"
    .string "POKéMON debe estar preparado.\p"
    .string "Solo quienes alcanzaron el\n"
    .string "NIVEL MÁXIMO pueden resistirlo.\p"
    .string "¿Quieres intentarlo?\p"
    .string "Es un proceso duro y largo,\n"
    .string "así que necesito 100,000¥ para todo.\p"
    .string "¡Dime cuando estés listo!$"

BattleFrontier_Lounge9_IV_Text1:
	.string "IV-MAN: ¡Hola! ¿Vienes por la rutina\n"
	.string "definitiva de HOENN?\p"
	.string "Cuesta 100,000¥, ¡pero vale la pena!\n"
	.string "¿Empezamos?$"

BattleFrontier_Lounge9_IV_Text_No:
	.string "Oh... Bueno, nos vemos luego.$"

BattleFrontier_Lounge9_IV_Text_NoLevel:
	.string "Creo que tu POKéMON no ha llegado\n"
	.string "a su NIVEL máximo...$"

BattleFrontier_Lounge9_IV_Finish:
	.string "Uff... Estoy agotado...\n"
	.string "¿Y tu POKéMON?\p"
	.string "Deberías descansar antes de irte.\p"
	.string "¡Bueno, nos vemos pronto!$"

@Chansey training

BattleFrontier_Lounge9_Nurse::
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, BattleFrontier_Lounge9_NurseChampion
	msgbox BattleFrontier_Lounge9_NurseRepeat2, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_Lounge9_Chansey1End
	case YES, BattleFrontier_Lounge9_NurseBattle
	case MULTI_B_PRESSED, BattleFrontier_Lounge9_Chansey1End

BattleFrontier_Lounge9_NurseBattle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JOEY, 0, BattleFrontier_Lounge9_NurseIntro, BattleFrontier_Lounge9_NurseDefeat, BattleFrontier_Lounge9_ChanseyBattleAgain
	end

BattleFrontier_Lounge9_Chansey1End::
	closemessage
	end

BattleFrontier_Lounge9_ChanseyBattleAgain::
	faceplayer
	msgbox BattleFrontier_Lounge9_NurseRepeat, MSGBOX_AUTOCLOSE
	clearflag 0x85B
	end

BattleFrontier_Lounge9_NurseChampion:
	faceplayer
	msgbox BattleFrontier_Lounge9_NurseChampionText, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge9_NurseChampionText:
	.string "¡Soy la ENFERMERA DE EXP!\n"
	.string "Lamentablemente, no puedo luchar\l"
	.string "si no eres el CAMPEÓN.$"

BattleFrontier_Lounge9_NurseIntro:
	.string "¡Vamos, BLISSEY!$"

BattleFrontier_Lounge9_NurseDefeat:
	.string "Oh no… ¡BLISSEY, usa HUEVO SALUDABLE!$"

BattleFrontier_Lounge9_NurseRepeat:
	.string "¡Si quieres, podemos luchar otra vez!$"

BattleFrontier_Lounge9_NurseRepeat2:
	.string "¿Listo para una batalla?$"

@Ability swapper

BattleFrontier_Lounge9_Ability_Man::
	lockall
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, BattleFrontier_Lounge9_Ability_ManNoChampion
	msgbox BattleFrontier_Lounge9_Ability_Text1, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_Lounge9_Ability_CheckMoney
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge9_Ability_No
	end

BattleFrontier_Lounge9_Ability_ManNoChampion::
	msgbox BattleFrontier_Lounge9_Ability_Text_NoChampion, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_Ability_No:
	msgbox BattleFrontier_Lounge9_Ability_Text_No, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_Ability_CheckMoney:
	checkmoney 25000, 0
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_Lounge9_Ability_Continue
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_Lounge9_EV_SetZeroNoMoney
	end

BattleFrontier_Lounge9_Ability_Continue:
	closemessage
	special ChoosePartyMon
	waitstate
	special SwitchMonAbility
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_Lounge9_Ability_Finish
	compare VAR_RESULT, FALSE
	goto_if_eq BattleFrontier_Lounge9_Ability_Cant
	end

BattleFrontier_Lounge9_Ability_Cant:
	msgbox BattleFrontier_Lounge9_Ability_Text_Cant, MSGBOX_DEFAULT
	waitmessage
	releaseall
	end

BattleFrontier_Lounge9_Ability_Finish:
	fadescreen 0x1
	delay 100
	fadescreen 0x0
	faceplayer
	waitse
	playse SE_EXP_MAX
	msgbox BattleFrontier_Lounge9_Ability_Finish_Text, MSGBOX_DEFAULT
	removemoney 25000, 0
	closemessage
	releaseall
	end

BattleFrontier_Lounge9_Ability_Finish_Text:
	.string "¡Eso es! ¡De nada!$"

BattleFrontier_Lounge9_Ability_Text1:
	.string "¡Bienvenido! ¡Soy el EXPERTO EN\p"
	.string "HABILIDADES! Puedo cambiar la\n"
	.string "habilidad de un POKéMON por 25.000¥.\p"
	.string "¿Quieres que cambie la habilidad\n"
	.string "de algún POKéMON?$"

BattleFrontier_Lounge9_Ability_Text_No:
	.string "Claro. Estaré aquí si me necesitas.$"

BattleFrontier_Lounge9_Ability_Text_Cant:
	.string "No puedo hacer eso. ¡Este POKéMON\n"
	.string "no tiene una segunda HABILIDAD!$"

BattleFrontier_Lounge9_Ability_Text_NoChampion:
	.string "¡Bienvenido! ¡Soy el EXPERTO EN\p"
	.string "HABILIDADES! Puedo cambiar las\n"
	.string "habilidades de los POKéMON.\p"
	.string "Lamentablemente, me duele la espalda\n"
	.string "y hoy no puedo trabajar.\p"
	.string "¡Vuelve más tarde!$"

