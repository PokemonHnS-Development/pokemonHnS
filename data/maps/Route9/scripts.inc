Route9_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route9_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route9_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route9_EventScript_Dean::
	trainerbattle_single TRAINER_DEAN Route9_Text_CamperDeanSeen, Route9_Text_CamperDeanBeaten
	msgbox Route9_Text_CamperDeanAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Heidi::
	trainerbattle_single TRAINER_HEIDI Route9_Text_PicnickerHeidiSeen, Route9_Text_PicnickerHeidiBeaten
	msgbox Route9_Text_PicnickerHeidiAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Edna::
	trainerbattle_single TRAINER_EDNA Route9_Text_PicnickerEdnaSeen, Route9_Text_PicnickerEdnaBeaten
	msgbox Route9_Text_PicnickerEdnaAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sid::
	trainerbattle_single TRAINER_SID Route9_Text_CamperSidSeen, Route9_Text_CamperSidBeaten
	msgbox Route9_Text_CamperSidAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Tim::
	trainerbattle_single TRAINER_TIM Route9_Text_HikerTimSeen, Route9_Text_HikerTimBeaten
	msgbox Route9_Text_HikerTimAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sidney::
	trainerbattle_single TRAINER_SIDNEY Route9_Text_HikerSidneySeen, Route9_Text_HikerSidneyBeaten
	msgbox Route9_Text_HikerSidneyAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sign::
	msgbox Route9_Text_Sign, MSGBOX_SIGN
	end

Route9_Text_CamperDeanSeen:
	.string "Vine a explorar el TÚNEL ROCA.$"

Route9_Text_CamperDeanBeaten:
	.string "¡Vaya! Es peligroso, amigo.$"

Route9_Text_CamperDeanAfter:
	.string "Mis POKéMON se hirieron antes de\n"
	.string "entrar al TÚNEL ROCA.\p"
	.string "Mejor los llevo a un CENTRO POKéMON\n"
	.string "de inmediato.$"

Route9_Text_PicnickerHeidiSeen:
	.string "¿Has ido alguna vez de picnic?\p"
	.string "¡Son muy divertidos!$"

Route9_Text_PicnickerHeidiBeaten:
	.string "¡Ohhhh!$"

Route9_Text_PicnickerHeidiAfter:
	.string "Horneamos dulces y los compartimos\n"
	.string "con todos.\p"
	.string "¡Están deliciosos!$"

Route9_Text_CamperSidSeen:
	.string "¡Oye, tú! ¡No tires basura!$"

Route9_Text_CamperSidBeaten:
	.string "Solo estaba señalando que...$"

Route9_Text_CamperSidAfter:
	.string "Perdón. No estabas tirando basura.\n"
	.string "Fue mi error.$"

Route9_Text_PicnickerEdnaSeen:
	.string "La gente no debería dejar basura\n"
	.string "tirada.$"

Route9_Text_PicnickerEdnaBeaten:
	.string "Oh... perdí...$"

Route9_Text_PicnickerEdnaAfter:
	.string "Ahorrar energía es importante,\n"
	.string "pero el ambiente es aún más\l"
	.string "vital.$"

Route9_Text_HikerTimSeen:
	.string "Ella vendrá por el MT.SILVER\n"
	.string "cuando regrese...\p"
	.string "MT.SILVER está en JOHTO, ¿no?$"

Route9_Text_HikerTimBeaten:
	.string "Estaba muy ocupado cantando...$"

Route9_Text_HikerTimAfter:
	.string "Las batallas requieren concentración.$"

Route9_Text_HikerSidneySeen:
	.string "Te diré un secreto.\p"
	.string "¡Pero primero, luchamos!$"

Route9_Text_HikerSidneyBeaten:
	.string "¡Rayos! Perdí eso…$"

Route9_Text_HikerSidneyAfter:
	.string "La CENTRAL ELÉCTRICA está tras un\n"
	.string "río pequeño.$"

Route9_Text_Sign:
	.string "RUTA 9\p"
	.string "CIUDAD CERULEAN - TÚNEL ROCA$"
