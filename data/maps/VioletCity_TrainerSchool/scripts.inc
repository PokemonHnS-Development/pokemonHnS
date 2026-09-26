VioletCity_TrainerSchool_MapScripts::
	.byte 0

VioletCity_TrainerSchool_EventScript_Earl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_EarlIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy1::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy2::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Girl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Twin::
	msgbox VioletCity_TrainerSchool_Text_Twin, MSGBOX_NPC
	end

VioletCity_TrainerSchool_EventScript_BlackBoard::
	lock
	msgbox VioletCity_TrainerSchool_Text_Blackboard, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_Text_Twin:
	.string "No soy un niño de GBA, ¡pero amo\n"
	.string "jugar juegos de POKéMON!\p"
	.string "En los viejos, debías luchar contra\n"
	.string "muchos POKéMON salvajes para\l"
	.string "ganar EXP.\p"
	.string "Pero en los nuevos, el EXP. SHARE\n"
	.string "hace que suban de nivel muy rápido.\p"
	.string "Aquí, el EXP. SHARE está\n"
	.string "balanceado para que tus POKéMON\l"
	.string "estén al nivel justo. O un poco\l"
	.string "más, según cuántas veces luches.\p"
	.string "Si quieres la experiencia de la\n"
	.string "GEN 1-4, apaga el EXP. SHARE.\l"
	.string "Si quieres algo moderno,\l"
	.string "activa el EXP. SHARE.\p"
	.string "¡Tú eliges cómo jugar!$"

VioletCity_TrainerSchool_Text_EarlIntro:
	.string "¡EARL, soy!\p"
	.string "¡Maravillosos son los POKéMON!\p"
	.string "¡Te enseñaré a ser un mejor\n"
	.string "ENTRENADOR!$"

VioletCity_TrainerSchool_Text_Teacher:
	.string "Ciertos POKéMON empiezan débiles\n"
	.string "y requieren más EXP para ser\l"
	.string "fuertes que otros.\p"
	.string "Por ejemplo, LARVITAR es débil\n"
	.string "pero llegará a ser un poderoso\l"
	.string "TYRANITAR, a costa de\l"
	.string "mucha EXP.\p"
	.string "Solo los ENTRENADORES más\n"
	.string "dedicados deberían intentar\l"
	.string "criar a tal POKéMON.$"

VioletCity_TrainerSchool_Text_TeachHowToWin:
	.string "¡Bien! ¡Te enseñaré!\p"
	.string "¡En batalla, el POKéMON arriba\n"
	.string "en la lista sale primero!\p"
	.string "¡Cambiar el orden puede hacer\n"
	.string "la batalla más fácil!\p"
	.string "¿Quieres oír más de mí?$"

VioletCity_TrainerSchool_Text_TeachMore:
	.string "Entonces, ¿quieres saber cómo\n"
	.string "criar bien a tus POKéMON?$"

VioletCity_TrainerSchool_Text_TeachRaiseWell:
	.string "¡Bien! ¡Te enseñaré!\p"
	.string "Si un POKéMON sale en batalla\n"
	.string "aunque sea brevemente, gana\p"
	.string "puntos de EXP.\n"
	.string "Pon al POKéMON débil arriba\p"
	.string "¡Cámbialo rápido en batalla!\n"
	.string "¡Así, el POKéMON débil se\p"
	.string "volverá fuerte!$"

VioletCity_TrainerSchool_Text_NoMoreToTeach:
	.string "¡Oh! ¡Qué alumno tan listo!\n"
	.string "¡Ya no tengo nada más que enseñar!\p"
	.string "Si quieres más, ¡habla con los\n"
	.string "estudiantes!$"

VioletCity_TrainerSchool_Text_Youngster1:
	.string "POKéMON que antes solo\n"
	.string "evolucionaban por cambio, ahora\p"
	.string "pueden hacerlo por nivel.\n"
	.string "MACHOKE y GRAVELER evolucionan\p"
	.string "al NIV 38, mientras KADABRA y\n"
	.string "HAUNTER lo hacen al NIV 42.\p"
	.string "Objetos como el METAL COAT\n"
	.string "también hacen evolucionar a\p"
	.string "ciertos POKéMON al subir de\n"
	.string "nivel mientras lo llevan.$"

VioletCity_TrainerSchool_Text_GameboyKid1:
	.string "¡Verás POKéMON notables en el\n"
	.string "mapa según el área!\p"
	.string "¡Revisa las rutas de DÍA y\n"
	.string "de NOCHE!$"

VioletCity_TrainerSchool_Text_GameboyKid2:
	.string "Las BAYAS de JOHTO sirven para\n"
	.string "curar y crear BALLS.\p"
	.string "Las BAYAS de KANTO sirven para\n"
	.string "bajar stats de un POKéMON.\p"
	.string "El DOJO de KANTO ayuda a mejorar\n"
	.string "los stats individuales.$"

VioletCity_TrainerSchool_Text_Youngster2:
	.string "Tus rivales ahora usan equipos\n"
	.string "con mejor cobertura de tipos,\l"
	.string "así que el viaje será mucho\l"
	.string "más difícil de ahora en adelante.$"

VioletCity_TrainerSchool_Text_Blackboard:
	.string "La pizarra describe los\n"
	.string "movimientos MO de POKéMON.\p"
	.string "Los MO, al desbloquearse, no\n"
	.string "necesitan aprenderse para usarse.$"

VioletCity_TrainerSchool_Text_Notebook:
	.string "Es el cuaderno de este chico…\p"
	.string "Atrapa POKéMON con POKé BALLS.\p"
	.string "Puedes llevar hasta seis contigo.\p"
	.string "¿Sigo leyendo?$"

VioletCity_TrainerSchool_Text_Notebook1:
	.string "Antes de lanzar una POKé BALL,\n"
	.string "debilita primero al objetivo.\p"
	.string "Un POKéMON envenenado o quemado\n"
	.string "es más fácil de atrapar.\p"
	.string "¿Sigo leyendo?$"

VioletCity_TrainerSchool_Text_Notebook2:
	.string "Algunos movimientos confunden.\p"
	.string "La confusión puede hacer que un\n"
	.string "POKéMON se ataque a sí mismo.\p"
	.string "Huir de la batalla quita la\n"
	.string "confusión.\p"
	.string "¿Sigo leyendo?$"

VioletCity_TrainerSchool_Text_Notebook3:
	.string "Quienes atrapan y usan\n"
	.string "POKéMON en batalla son\n"
	.string "ENTRENADORES.\p"
	.string "Ellos visitan los GIMNASIOS y\n"
	.string "derrotan a otros\n"
	.string "ENTRENADORES.\p"
	.string "¡La siguiente página está vacía!\p"
	.string "Niño: Je, je, je…\p"
	.string "No escribí nada más…$"

VioletCity_TrainerSchool_Text_StickerMachine:
	.string "¡Esta supermáquina imprime datos\n"
	.string "en calcomanías!$"
