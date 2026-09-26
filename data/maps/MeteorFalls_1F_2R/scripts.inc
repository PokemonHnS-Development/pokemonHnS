MeteorFalls_1F_2R_MapScripts::
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas::
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas::
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  @ John speaks for both during register
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro:
	.string "Aquí es donde los usuarios de\n"
	.string "DRAGON entrenamos.\p"
	.string "Hasta el CAMPEÓN nos visita.\n"
	.string "¿Ves ahora lo especial que es?$"

MeteorFalls_1F_2R_Text_NicolasDefeat:
	.string "¡Urgh!\n"
	.string "¡No esperaba que fueras tan fuerte!$"

MeteorFalls_1F_2R_Text_NicolasPostBattle:
	.string "El camino sigue siendo largo y duro.\p"
	.string "¿Cuándo seremos los mejores\n"
	.string "mi POKéMON y yo?$"

MeteorFalls_1F_2R_Text_NicolasRegister:
	.string "Quiero saber más sobre tu poder.\n"
	.string "Déjame registrarte en mi POKéNAV.$"

MeteorFalls_1F_2R_Text_NicolasRematchIntro:
	.string "Desde que nos vimos, entrenamos\n"
	.string "para ser los número uno.\p"
	.string "¡Ayúdanos a ver cuánto más\n"
	.string "fuertes nos hemos vuelto!$"

MeteorFalls_1F_2R_Text_NicolasRematchDefeat:
	.string "¡Urgh!\n"
	.string "¡No esperaba que fueras tan fuerte!$"

MeteorFalls_1F_2R_Text_NicolasPostRematch:
	.string "Se nota que no has dejado de\n"
	.string "entrenar a tus POKéMON.\p"
	.string "Si sigues siendo fuerte, ¡yo\n"
	.string "también podré serlo!$"

MeteorFalls_1F_2R_Text_JohnIntro:
	.string "JOHN: Siempre batallamos con\n"
	.string "POKéMON juntos, en pareja.\l"
	.string "Confiamos plenamente en nosotros.$"

MeteorFalls_1F_2R_Text_JohnDefeat:
	.string "JOHN: Vaya, vaya.\n"
	.string "Hemos perdido, querida esposa.$"

MeteorFalls_1F_2R_Text_JohnPostBattle:
	.string "JOHN: Llevamos casados\n"
	.string "cincuenta años.\p"
	.string "Pensándolo bien, aún no he vencido\n"
	.string "a mi esposa en batalla.$"

MeteorFalls_1F_2R_Text_JohnNotEnoughMons:
	.string "JOHN: ¡Vaya, qué joven ENTRENADOR!\p"
	.string "¿Lucharás con nosotros? Si es así,\n"
	.string "vuelve con más POKéMON.$"

MeteorFalls_1F_2R_Text_JohnRegister:
	.string "JOHN: Joven ENTRENADOR, si surge la\n"
	.string "oportunidad, ¿lucharás con nosotros?$"

MeteorFalls_1F_2R_Text_JayIntro:
	.string "JAY: Llevamos casados\n"
	.string "cincuenta años.\p"
	.string "El vínculo que tenemos como pareja\n"
	.string "jamás podrá romperse.$"

MeteorFalls_1F_2R_Text_JayDefeat:
	.string "JAY: Oh, cielo.\n"
	.string "Hemos perdido, querido esposo.$"

MeteorFalls_1F_2R_Text_JayPostBattle:
	.string "JAY: Cincuenta años de casados…\p"
	.string "Si discutíamos, lo resolvíamos\n"
	.string "con una batalla POKéMON…$"

MeteorFalls_1F_2R_Text_JayNotEnoughMons:
	.string "JAY: Vaya, ¿no eres un joven\n"
	.string "ENTRENADOR?\p"
	.string "Si quieres luchar con nosotros, debes\n"
	.string "volver con más POKéMON.$"

MeteorFalls_1F_2R_Text_JohnRematchIntro:
	.string "JOHN: Siempre luchamos con POKéMON\n"
	.string "juntos como pareja.\l"
	.string "Confiamos en nosotros mismos.$"

MeteorFalls_1F_2R_Text_JohnRematchDefeat:
	.string "JOHN: Vaya, vaya.\n"
	.string "Hemos perdido, querida esposa.$"

MeteorFalls_1F_2R_Text_JohnPostRematch:
	.string "JOHN: Casados por cincuenta años...\p"
	.string "Pensándolo bien, mi esposa y yo\n"
	.string "luchamos día tras día...$"

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons:
	.string "JOHN: ¡Vaya, qué joven ENTRENADOR!\p"
	.string "¿Lucharás con nosotros? Si es así,\n"
	.string "vuelve con más POKéMON.$"

MeteorFalls_1F_2R_Text_JayRematchIntro:
	.string "JAY: Llevamos casados\n"
	.string "cincuenta años.\p"
	.string "Nos apoyamos todo este tiempo.\n"
	.string "Así nos hicimos fuertes.$"

MeteorFalls_1F_2R_Text_JayRematchDefeat:
	.string "JAY: Oh, cielos.\n"
	.string "Hemos perdido, querido esposo.$"

MeteorFalls_1F_2R_Text_JayPostRematch:
	.string "JAY: Cincuenta años de matrimonio...\n"
	.string "Pasaron muchas cosas.\p"
	.string "Espero que sigamos creando\n"
	.string "recuerdos felices juntos.$"

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons:
	.string "JAY: Vaya, ¿no eres un joven\n"
	.string "ENTRENADOR?\p"
	.string "Si quieres luchar con nosotros,\n"
	.string "vuelve con más POKéMON.$"

