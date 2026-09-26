Route45_MapScripts::
	.byte 0

Route45_EventScript_Erik::
	trainerbattle_single TRAINER_ERIK Route45_Text_HikerErikSeen, Route45_Text_HikerErikBeaten
	msgbox Route45_Text_HikerErikAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Michael::
	trainerbattle_single TRAINER_MICHAEL Route45_Text_HikerMichaelSeen, Route45_Text_HikerMichaelBeaten
	msgbox Route45_Text_HikerMichaelAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Parry::
	trainerbattle_single TRAINER_PARRY Route45_Text_HikerParrySeen, Route45_Text_HikerParryBeaten
	msgbox Route45_Text_HikerParryAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Timothy::
	trainerbattle_single TRAINER_TIMOTHY Route45_Text_HikerTimothySeen, Route45_Text_HikerTimothyBeaten
	msgbox Route45_Text_HikerTimothyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kenji::
	trainerbattle_single TRAINER_KENJI Route45_Text_BlackbeltKenjiSeen, Route45_Text_BlackbeltKenjiBeaten
	msgbox Route45_Text_BlackbeltKenjiAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Ryan::
	trainerbattle_single TRAINER_RYAN Route45_Text_CooltrainermRyanSeen, Route45_Text_CooltrainermRyanBeaten
	msgbox Route45_Text_CooltrainermRyanAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kelly::
	trainerbattle_single TRAINER_KELLY Route45_Text_CooltrainerfKellySeen, Route45_Text_CooltrainerfKellyBeaten
	msgbox Route45_Text_CooltrainerfKellyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Quentin::
	trainerbattle_single TRAINER_QUENTIN Route45_Text_CamperQuentinSeen, Route45_Text_CamperQuentinBeaten
	msgbox Route45_Text_CamperQuentinAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Sign::
	msgbox Route45_Text_Sign, MSGBOX_SIGN
	end

Route45_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route45_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end

Route45_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

Route45_EventScript_Item_Nugget::
	finditem ITEM_NUGGET
	end

Route45_Text_HikerErikSeen:
    .string "¡Prepárate para todo!\p"
    .string "¡Veré si tus POKéMON han\n"
    .string "sido bien entrenados!$"

Route45_Text_HikerErikBeaten:
    .string "¡Oh, perdí!$"

Route45_Text_HikerErikAfter:
    .string "Volveré a la SENDA HIELO de\n"
    .string "CIUDAD ENDRINO a entrenar más.$"

Route45_Text_HikerMichaelSeen:
    .string "¡Ey! ¡Tienes agallas! Pero\n"
    .string "¿sabes qué?\p"
    .string "¡En cuestión de agallas,\n"
    .string "yo soy el mejor!$"

Route45_Text_HikerMichaelBeaten:
    .string "¡Mis POKéMON no tuvieron agallas!$"

Route45_Text_HikerMichaelAfter:
    .string "¡Amo el VITUP! ¡Mmmm, rico!\p"
    .string "¡Me bebo las de mis POKéMON!\p"
    .string "¡No puedo evitarlo!$"

Route45_Text_HikerParrySeen:
    .string "¡Mis POKéMON están al máximo!$"

Route45_Text_HikerParryBeaten:
    .string "¡Jajaja! ¡Soy el gran perdedor!$"

Route45_Text_HikerParryAfter:
    .string "No soy bueno pensando,\n"
    .string "¿ves?\p"
    .string "¡Así que avanzo con poder!$"


Route45_Text_HikerTimothySeen:
    .string "¿Por qué subo montañas?\p"
    .string "Porque están ahí.\p"
    .string "¿Por qué entreno POKéMON?\p"
    .string "¡Porque están ahí!$"

Route45_Text_HikerTimothyBeaten:
    .string "¡Las derrotas... también están ahí!$"

Route45_Text_HikerTimothyAfter:
    .string "Lo mejor que me ha pasado\n"
    .string "fue descubrir los POKéMON.$"

Route45_Text_HikerParryGivesIron:
    .string "¡No hallo forma de ganar!\p"
    .string "¡Sigue así!\p"
    .string "Toma esto, es el regalo que\n"
    .string "no pudiste llevarte la\n"
    .string "última vez.$"

Route45_Text_BlackbeltKenjiSeen:
    .string "Entrenaba aquí solo.\p"
    .string "¡Mira los frutos de mi labor!$"

Route45_Text_BlackbeltKenjiBeaten:
    .string "¡Waaaargh!$"

Route45_Text_BlackbeltKenjiAfter:
    .string "Esto requiere medidas extremas.\p"
    .string "Iré a los montes a entrenar\n"
    .string "en soledad.$"

Route45_Text_BlackbeltKenjiMorning:
    .string "Entrenaré un poco más\n"
    .string "antes de ir a almorzar.$"

Route45_Text_BlackbeltKenjiNight:
    .string "Descansamos mucho al almuerzo, así\p"
    .string "¡que ya estamos listos para seguir!\p"
    .string "¡Vamos a entrenar otra vez!$"

Route45_Text_CooltrainermRyanSeen:
    .string "¿Qué opinas sobre el entrenamiento\n"
    .string "de POKéMON?$"

Route45_Text_CooltrainermRyanBeaten:
    .string "Te has ganado mi respeto.$"

Route45_Text_CooltrainermRyanAfter:
    .string "Veo que crías a tus POKéMON\n"
    .string "con cuidado.\p"
    .string "Ese vínculo te salvará en las\n"
    .string "situaciones difíciles.$"

Route45_Text_CooltrainerfKellySeen:
    .string "¿Cuál es tu estrategia de batalla?\p"
    .string "Es necio usar movimientos fuertes\n"
    .string "sin pensar.$"

Route45_Text_CooltrainerfKellyBeaten:
    .string "Está bien. Perdí.$"

Route45_Text_CooltrainerfKellyAfter:
    .string "No estoy a favor de los ataques\n"
    .string "demasiado fuertes.\p"
    .string "Quiero ganar, pero no quiero\n"
    .string "dañar a los POKéMON.$"

Route45_Text_CamperQuentinSeen:
    .string "¡Soy muy, muy fuerte!$"

Route45_Text_CamperQuentinBeaten:
    .string "Fui fuerte en COLINA ENTRENADOR…$"

Route45_Text_CamperQuentinAfter:
    .string "¿Fuiste a TRAINER HILL?\p"
    .string "Nunca pierdo allí, pero…$"

Route45_Text_Sign:
    .string "RUTA 45\n"
    .string "CAMINO DE MONTAÑA ADELANTE$"
