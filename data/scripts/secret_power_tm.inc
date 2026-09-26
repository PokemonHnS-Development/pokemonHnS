Route111_Text_MakingRoomUseTMToMakeYourOwn:
	.string "¿Qué es eso?\n"
	.string "¿Qué estoy haciendo?\p"
	.string "Pienso crear mi propia habitación\n"
	.string "aquí usando un movimiento POKéMON.\p"
	.string "¡Ya sé! Te daré esta MT.\n"
	.string "¿La usarás para crear tu cuarto?$"

Route111_Text_ExplainSecretPower:
	.string "Busca un árbol grande que parezca que\n"
	.string "tenga algunas lianas.\p"
	.string "Usa PODER SECRETO frente al árbol.\n"
	.string "Unas lianas se soltarán y bajarán\l"
	.string "para que puedas subir al árbol.\p"
	.string "Hallarás mucho espacio para poner\n"
	.string "tus cosas favoritas.\p"
	.string "Será tu propia habitación secreta...\n"
	.string "¡UNA BASE SECRETA!\p"
	.string "Tú también deberías hacer una.\p"
	.string "Además, no siempre tienes que hacer\n"
	.string "tu BASE SECRETA en un árbol.\p"
	.string "Usa PODER SECRETO en paredes rocosas\n"
	.string "que tengan pequeñas hendiduras.\p"
	.string "Buscaré otros lugares también.\n"
	.string "¡Bueno, adiós!$"

Route111_Text_DontWantThis:
	.string "Oh, ¿no quieres esto?\n"
	.string "Si cambias de opinión, dime, ¿sí?$"

Route111_Text_DontHaveAnyRoom:
	.string "Oh, no tienes espacio para esto.\p"
	.string "Yo lo guardaré, vuelve por él\n"
	.string "en otro momento, ¿está bien?$"

Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower::
	giveitem ITEM_TM_SECRET_POWER
	goto_if_eq VAR_RESULT, FALSE, Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_GARBAGEFLAG
	call_if_eq VAR_FACING, DIR_WEST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_EAST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_NORTH, Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower::
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
