.set LOCALID_STAIR_GUARD, 2

RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
	.string "Hola, bienvenido a la\n"
	.string "CORPORACIÓN DEVON.\p"
	.string "Hacemos objetos y medicinas que\n"
	.string "mejoran tu vida.$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
	.string "Un investigador fue robado\n"
	.string "estúpidamente de un paquete vital.$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
	.string "¡Esas ZAPATILLAS DE CORRER!\n"
	.string "¡Son de nuestros productos!\p"
	.string "Me alegra ver a alguien usando\n"
	.string "algo que nosotros hicimos.$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
	.string "Ese paquete robado...\p"
	.string "Es importante, pero no es algo\n"
	.string "que cualquiera pueda usar.\p"
	.string "Creo que el ladrón no debió ser\n"
	.string "muy inteligente.$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
	.string "Parece que recuperaron los\n"
	.string "PRODUCTOS DEVON robados.$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
	.string "Lo siento, solo el personal\n"
	.string "autorizado puede entrar aquí.$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
	.string "Es más que estúpido.\n"
	.string "¿Cómo pudieron robarnos?$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
	.string "¡Hola!\n"
	.string "¡Siempre eres bienvenido aquí!$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
	.string "Muestras de rocas y metal están\n"
	.string "en la vitrina.\p"
	.string "Hay un panel con un texto\n"
	.string "escrito…\p"
	.string "“DEVON CORPORATION empezó como\n"
	.string "productora de piedras de cantera.\p"
	.string "“La empresa también producía hierro\n"
	.string "de limaduras de arena.\p"
	.string "“Desde ese humilde inicio con\n"
	.string "materias primas, DEVON creció.\p"
	.string "“DEVON ahora fabrica una amplia\n"
	.string "gama de productos industriales.”$"

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
	.string "Prototipos y pruebas llenan\n"
	.string "la vitrina de cristal.\p"
	.string "Hay un panel con una descripción…\p"
	.string "“Además de productos industriales,\n"
	.string "DEVON vende artículos y fármacos\l"
	.string "para mejorar la calidad de vida.\p"
	.string "“Recientemente, DEVON vende\n"
	.string "útiles para ENTRENADORES POKéMON,\l"
	.string "como POKé BALLS y POKéNAV.”$"

