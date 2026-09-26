.set LOCALID_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER, 2
.set LOCALID_SSAQUA_CAPTAINS_ROOM_CAPTAIN, 1

SSAqua_CaptainsRoom_MapScripts::
	.byte 0

SSAqua_CaptainsRoom_EventScript_Captain::
	goto_if_eq VAR_TEMP_0, 1, SSAqua_CaptainsRoom_EventScrip_CaptainAfter
	msgbox SSAqua_CaptainsRoom_Text_CaptainExhausting, MSGBOX_NPC
	setvar VAR_TEMP_0, 1
SSAqua_CaptainsRoom_EventScrip_CaptainAfter::
	msgbox SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike, MSGBOX_DEFAULT
	closemessage
	end

SSAqua_CaptainsRoom_EventScript_Granddaughter::
	lock
	applymovement LOCALID_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER, SSAqua_CaptainsRoom_Movement_Jump
	waitmovement 0
	msgbox SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe, MSGBOX_DEFAULT
	turnobject LOCALID_SSAQUA_CAPTAINS_ROOM_CAPTAIN, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SSAQUA_CAPTAINS_ROOM_CAPTAIN, Common_Movement_QuestionMark
	waitmovement 0
	delay 60
	faceplayer
	msgbox SSAqua_CaptainsRoom_Text_GranddaughterHasToFindGrandpa, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER
	setvar VAR_SSAQUA_STATE, 4
	clearflag FLAG_HIDE_SSAQUA_ROOM_SSE_GRANDDAUGHTER
	warp MAP_SSAQUA_ROOM_SSE, 0
	release
	end

SSAqua_CaptainsRoom_Movement_Jump:
	jump_in_place_right
	jump_in_place_right
	jump_in_place_right
	step_end

SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe:
	.string "CAPTAIN, ¡juega conmigo, por favor!\p"
	.string "¡Estoy aburrida! ¡Quiero jugar más!$"

SSAqua_CaptainsRoom_Text_GranddaughterHasToFindGrandpa:
	.string "¡Hola! ¿Jugarías conmigo?\p"
	.string "…¡Oh!\p"
	.string "¿El abuelo está preocupado?\p"
	.string "¡Tengo que irme!\p"
	.string "¡Debo buscar al abuelo!$"

SSAqua_CaptainsRoom_Text_CaptainExhausting:
	.string "¡Uff! Gracias por acompañarme.\p"
	.string "Mantener a esa niña entretenida\n"
	.string "fue agotador.$"

SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike:
	.string "¿Qué te parece el viaje en S.S.AQUA?\p"
	.string "Prácticamente se desliza sobre\n"
	.string "las olas.$"

