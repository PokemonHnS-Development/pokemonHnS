SootopolisCity_House6_MapScripts::
	.byte 0

SootopolisCity_House6_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WAILMER_DOLL, SootopolisCity_House6_EventScript_ReceivedWailmerDoll
	msgbox SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll, MSGBOX_YESNO
	call_if_eq VAR_RESULT, NO, SootopolisCity_House6_EventScript_DeclineWailmerDoll
	msgbox SootopolisCity_House6_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	givedecoration DECOR_WAILMER_DOLL
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_House6_EventScript_NoRoomForWailmerDoll
	setflag FLAG_RECEIVED_WAILMER_DOLL
	release
	end

SootopolisCity_House6_EventScript_DeclineWailmerDoll::
	msgbox SootopolisCity_House6_Text_DontWantThisDoll, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_ReceivedWailmerDoll::
	msgbox SootopolisCity_House6_Text_LovePlushDolls, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_NoRoomForWailmerDoll::
	bufferdecorationname STR_VAR_2, DECOR_WAILMER_DOLL
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	msgbox SootopolisCity_House6_Text_IllHoldItForYou, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll:
	.string "¡Hola! Eres nuestro primer cliente\n"
	.string "en mucho tiempo.\p"
	.string "Me alegraste el día, así que te\n"
	.string "daré un gran MUÑECO WAILMER.$"

SootopolisCity_House6_Text_TakeGoodCareOfIt:
	.string "¡Cuídalo mucho!$"

SootopolisCity_House6_Text_IllHoldItForYou:
	.string "¿Lo quieres, pero no ahora?\n"
	.string "Está bien, yo lo guardaré por ti.$"

SootopolisCity_House6_Text_DontWantThisDoll:
	.string "¿Estás seguro?\n"
	.string "¿No quieres este MUÑECO?$"

SootopolisCity_House6_Text_LovePlushDolls:
	.string "¡Amo los MUÑECOS de peluche!$"

