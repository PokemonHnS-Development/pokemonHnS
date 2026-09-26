RuinsOfAlph_Outside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Outside_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

RuinsOfAlph_Outside_OnTransition: 
	callnative SetTimeBasedEncounters
	end	

RuinsOfAlph_Outside_EventScript_Quagsire::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_QUAGSIRE, CRY_MODE_NORMAL
	msgbox RuinsOfAlph_Outside_Text_Quagsire, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RuinsOfAlph_Outside_Text_Quagsire:
	.string "QUAGSIRE: Quag Quag$"

RuinsOfAlph_Outside_EventScript_Stan::
	trainerbattle_single TRAINER_STAN, RuinsOfAlph_Outside_Text_SuperNerdStan_Seen, RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten
	msgbox RuinsOfAlph_Outside_Text_SuperNerdStan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Nathan::
	trainerbattle_single TRAINER_NATHAN, RuinsOfAlph_Outside_Text_PsychicNathan_Seen, RuinsOfAlph_Outside_Text_PsychicNathan_Beaten
	msgbox RuinsOfAlph_Outside_Text_PsychicNathan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Youngster1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Youngster2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign1::
	lock
	msgbox RuinsOfAlph_Outside_Text_MainSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign2::
	lock
	msgbox RuinsOfAlph_Outside_Text_ResearchSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign3::
	lock
	msgbox RuinsOfAlph_Outside_Text_MysteryChamberSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_Text_Scientist:
	.string "¿Hm? Es una POKéDEX, ¿verdad?\n"
	.string "¿Puedo verla?\p"
	.string "Hay muchísimos tipos de\n"
	.string "POKéMON.\p"
	.string "¿Hm? ¿Qué es esto?\p"
	.string "¿Qué POKéMON es este?\p"
	.string "Se parece a los extraños\n"
	.string "escritos en los muros de las\p"
	.string "RUINAS.\p"
	.string "Si esos dibujos son realmente\n"
	.string "POKéMON, debería haber muchos\n"
	.string "más.\p"
	.string "¡Ya sé! Dejame mejorar tu\n"
	.string "POKéDEX. Sígueme.$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Seen:
	.string "¿Qué quieres? Estoy estudiando--\n"
	.string "¡no me molestes!$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten:
	.string "Lo siento...\n"
	.string "Me frustra que no tengamos\p"
	.string "una comprensión real...$"

RuinsOfAlph_Outside_Text_SuperNerdStan_After:
	.string "Las RUINAS son de hace unos 1500\n"
	.string "años.\p"
	.string "Nadie sabe quién las construyó.\p"
	.string "Tampoco se sabe si las estatuas\n"
	.string "POKéMON tienen algún sentido.\p"
	.string "Todo es un gran misterio...$"

RuinsOfAlph_Outside_Text_PsychicNathan_Seen:
	.string "Hmmm... Este es un lugar extraño.$"

RuinsOfAlph_Outside_Text_PsychicNathan_Beaten:
	.string "…$"

RuinsOfAlph_Outside_Text_PsychicNathan_After:
	.string "Me gusta pensar aquí.$"

RuinsOfAlph_Outside_Text_MysteryChamberSign:
	.string "SALA DEL PANEL DE PIEDRA MÍSTICA$"

RuinsOfAlph_Outside_Text_MainSign:
	.string "RUINAS ALFA\n"
	.string "BIENVENIDOS VISITANTES$"

RuinsOfAlph_Outside_Text_ResearchSign:
	.string "CENTRO INVESTIGACIÓN RUINAS ALFA\p"
	.string "LA AUTORIDAD SOBRE LAS\n"
	.string "RUINAS ALFA$"

RuinsOfAlph_Outside_Text_Fisher1:
	.string "Explorando las RUINAS, notamos\n"
	.string "una presencia extraña.\p"
	.string "Nos asustamos y huimos.\n"
	.string "Tú también ten cuidado.$"

RuinsOfAlph_Outside_Text_Fisher2:
	.string "¡Las RUINAS ocultan un gran secreto!\p"
	.string "...Creo...$"

RuinsOfAlph_Outside_Text_Youngster1:
	.string "Hay muchos tipos de UNOWN, así que\n"
	.string "los usamos para códigos secretos.$"

RuinsOfAlph_Outside_Text_Youngster2:
	.string "A... D... E... L... A... Hmm...\p"
	.string "¿Qué?\p"
	.string "¡Estoy descifrando el mensaje!$"
