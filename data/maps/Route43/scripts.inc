Route43_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route43_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route43_MapScript_OnTransition::
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route43_EventScript_Ben::
	trainerbattle_single TRAINER_BEN Route43_Text_PokemaniacBenSeen, Route43_Text_PokemaniacBenBeaten
	msgbox Route43_Text_PokemaniacBenAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Brent::
	trainerbattle_single TRAINER_BRENT Route43_Text_PokemaniacBrentSeen, Route43_Text_PokemaniacBrentBeaten
	msgbox Route43_Text_PokemaniacBrentAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Ron::
	trainerbattle_single TRAINER_RON Route43_Text_PokemaniacRonSeen, Route43_Text_PokemaniacRonBeaten
	msgbox Route43_Text_PokemaniacRonAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Marvin::
	trainerbattle_single TRAINER_MARVIN Route43_Text_FisherMarvinSeen, Route43_Text_FisherMarvinBeaten
	msgbox Route43_Text_FisherMarvinAfter, MSGBOX_AUTOCLOSE
	end
	
Route43_EventScript_Spencer::
	trainerbattle_single TRAINER_SPENCER Route43_Text_CamperSpencerSeen, Route43_Text_CamperSpencerBeaten
	msgbox Route43_Text_CamperSpencerAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY Route43_Text_PicnickerTiffanySeen, Route43_Text_PicnickerTiffanyBeaten
	msgbox Route43_Text_PicnickerTiffanyWantsPicnic, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Sign1::
	msgbox Route43_Sign2, MSGBOX_SIGN
	end

Route43_EventScript_Sign2::
	msgbox Route43_TrainerTips, MSGBOX_SIGN
	end

Route43_EventScript_Item_Max_Ether::
	finditem ITEM_MAX_ETHER
	end

Route43_Text_PokemaniacBenSeen:
    .string "¡Amo a los POKéMON!\p"
    .string "¡Por eso empecé y por eso\n"
    .string "seguiré atrapando POKéMON!$"

Route43_Text_PokemaniacBenBeaten:
    .string "¿Cómo pudiste hacerme esto?$"

Route43_Text_PokemaniacBenAfter:
    .string "¿Qué más me gusta aparte de los\n"
    .string "POKéMON?\p"
    .string "MARY en la radio. ¡Apuesto a que\n"
    .string "es linda!$"

Route43_Text_PokemaniacBrentSeen:
    .string "¡Oye! ¿Tienes algún POKéMON\n"
    .string "poco común?$"

Route43_Text_PokemaniacBrentBeaten:
    .string "¡Oh, mis pobres POKéMON! ¡Cariños!$"

Route43_Text_PokemaniacBrentAfter:
    .string "Sería feliz solo con tener un\n"
    .string "solo POKéMON raro.$"

Route43_Text_PokemaniacRonSeen:
    .string "¿Puedes creerlo?\p"
    .string "¡Un tal {RIVAL} se burló de mis\n"
    .string "POKéMON!\p"
    .string "¡Rayos! ¡Mis POKéMON son geniales!$"

Route43_Text_PokemaniacRonBeaten:
    .string "¡Mi NIDOKING lo hizo muy bien!$"

Route43_Text_PokemaniacRonAfter:
    .string "Está bien que a la gente le gusten\n"
    .string "distintos tipos de POKéMON.\p"
    .string "No se trata solo de tener al\n"
    .string "más poderoso.$"

Route43_Text_FisherMarvinSeen:
    .string "Estoy en una mala racha.\p"
    .string "Quizás es el equipo que uso.\p"
    .string "¡Luchemos para cambiar el ritmo!$"

Route43_Text_FisherMarvinBeaten:
    .string "Perdí, pero me siento mejor así.$"

Route43_Text_FisherMarvinAfter:
    .string "La LURE BALL de KURT es la mejor\n"
    .string "para capturar POKéMON pescados.\p"
    .string "Es mucho más efectiva que una\n"
    .string "ULTRA BALL.$"

Route43_Text_CamperSpencerSeen:
    .string "Puedo hacer mucho con mis\n"
    .string "POKéMON, ¡es superdivertido!$"

Route43_Text_CamperSpencerBeaten:
    .string "Perder no es nada divertido…$"

Route43_Text_CamperSpencerAfter:
    .string "¿Qué pasa en el LAGO DE la FURIA?\p"
    .string "Planeábamos acampar allí.$"

Route43_Text_PicnickerTiffanySeen:
    .string "¿Vas al LAGO DE la FURIA también?\p"
    .string "¡Juguemos un ratito!$"

Route43_Text_PicnickerTiffanyBeaten:
    .string "¡Jugué demasiado!$"

Route43_Text_PicnickerTiffanyWantsPicnic:
    .string "Hago un picnic con POKéMON.\p"
    .string "¿No quieres unirte?$"

Route43_Sign1:
    .string "RUTA 43\p"
    .string "LAGO DE la FURIA - PUEBLO CAOBA$"

Route43_Sign2:
    .string "RUTA 43\p"
    .string "LAGO de la FURIA - PUEBLO CAOBA$"

Route43_TrainerTips:
    .string "CONSEJOS\p"
    .string "Todo POKéMON tiene pros y contras\n"
    .string "según sus tipos.\p"
    .string "Si sus tipos difieren, un POKéMON de\n"
    .string "nivel alto puede perder la batalla.\p"
    .string "Aprende qué tipos son fuertes y\n"
    .string "débiles ante el tipo de tu POKéMON.$"
