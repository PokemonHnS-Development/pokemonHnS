RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_VIOLET_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_GARBAGEVAR, 1
	addvar VAR_GARBAGEVAR, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_GARBAGEVAR, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	goto_if_set FLAG_FINITE_TMS, RustboroCity_Gym_EventScript_GiveRockTombFinite
	msgbox RustboroCity_Gym_Text_ExplainRockTombInfinite, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GiveRockTombFinite::
	msgbox RustboroCity_Gym_Text_ExplainRockTomb MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
	.string "¡Hola! ¿Cómo va todo?\p"
	.string "¡Escucha, amigo!\n"
	.string "¿Quieres ser el CAMPEÓN?\p"
	.string "No soy ENTRENADOR, pero puedo\n"
	.string "darte consejos para ganar.\p"
	.string "¡Trato hecho! ¡Iremos juntos por el\n"
	.string "CAMPEONATO POKéMON!\p"
	.string "Tu labor como ENTRENADOR es ganar\n"
	.string "MEDALLAS de GIMNASIO, ¿verdad?\p"
	.string "¡Pero los LÍDERES no son fáciles!\p"
	.string "¡Ahí es donde entro yo!\n"
	.string "¡Te daré consejos de experto!\p"
	.string "ROXANNE, la LÍDER, usa\n"
	.string "POKéMON tipo ROCA.\p"
	.string "El tipo ROCA es resistente, pero\n"
	.string "no aguanta ataques de AGUA y\l"
	.string "tipo PLANTA.\p"
	.string "Vuelve a verme si logras vencer\n"
	.string "al LÍDER del GIMNASIO.\p"
	.string "¡Bien, ve a por ello!$"

RustboroCity_Gym_Text_GymGuidePostVictory:
	.string "¡Guau! ¡Qué victoria tan increíble!\n"
	.string "¡Mi apoyo debió funcionar!\p"
	.string "¡Genial!\n"
	.string "Mira tu TRAINER CARD.\p"
	.string "La STONE BADGE que ganaste debe\n"
	.string "estar registrada ahí.\p"
	.string "En otras palabras...\p"
	.string "¡Subiste el primer escalón hacia\n"
	.string "el CHAMPIONSHIP!\p"
	.string "¡Debe sentirse increíble!$"

RustboroCity_Gym_Text_JoshIntro:
	.string "¡No subestimes a los GYM TRAINERS!\n"
	.string "¡Te mostraré por qué somos mejores!$"

RustboroCity_Gym_Text_JoshDefeat:
	.string "Fuiste demasiado bueno para mí...$"

RustboroCity_Gym_Text_JoshPostBattle:
	.string "¡No has visto el terrorífico poder\n"
	.string "del tipo ROCK!$"

RustboroCity_Gym_Text_TommyIntro:
	.string "¡Si no puedes vencerme, no tendrás\n"
	.string "oportunidad contra ROXANNE!$"

RustboroCity_Gym_Text_TommyDefeat:
	.string "¡Vaya! ¡Tienes mucho potencial!$"

RustboroCity_Gym_Text_TommyPostBattle:
	.string "ROXANNE es varias veces más\n"
	.string "fuerte que yo.\p"
	.string "¡Más vale que estés alerta!$"

RustboroCity_Gym_Text_MarcIntro:
	.string "Estamos en medio del pueblo,\n"
	.string "¿pero qué importa?\p"
	.string "¡Mis ROCK POKéMON necesitan espacio\n"
	.string "para arrasar!$"

RustboroCity_Gym_Text_MarcDefeat:
	.string "¡Vaya, vaya!\n"
	.string "¡Nuestro retador es muy impulsivo!$"

RustboroCity_Gym_Text_MarcPostBattle:
	.string "Debo admitirlo con nuestra LEADER.\p"
	.string "Fue inteligente elegir el tipo\n"
	.string "ROCK siendo tan joven.$"

RustboroCity_Gym_Text_RoxanneIntro:
	.string "Hola, soy ROXANNE, la LEADER del\n"
	.string "GIMNASIO de RUSTBORO.\p"
	.string "Soy LEADER para aplicar lo que\n"
	.string "aprendí en la ESCUELA de\l"
	.string "ENTRENADORES POKéMON.\p"
	.string "¿Me mostrarías cómo luchas\n"
	.string "y con qué POKéMON?$"

RustboroCity_Gym_Text_RoxanneDefeat:
	.string "Así que...\n"
	.string "perdí...\p"
	.string "Parece que aún me queda mucho\n"
	.string "por aprender...\p"
	.string "Entiendo.\p"
	.string "Las reglas de la LIGA POKéMON dicen\n"
	.string "que los ENTRENADORES reciben esto\l"
	.string "al vencer a un LEADER.\p"
	.string "Toma la MEDALLA ROCA oficial de la\n"
	.string "LIGA POKéMON.$"

RustboroCity_Gym_Text_ReceivedStoneBadge:
	.string "{PLAYER} recibió la MEDALLA ROCA\n"
	.string "de ROXANNE.$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
	.string "La MEDALLA ROCA sube el ATTACK\n"
	.string "de tus POKéMON.\p"
	.string "También permite usar la MO la\n"
	.string "MO CORTE fuera de combate.\p"
	.string "Lleva esto contigo también.$"

RustboroCity_Gym_Text_ExplainRockTomb:
	.string "Esa MO. TM39,\n"
	.string "contiene Tumba Rocas.\p"
	.string "Causa daño al lanzar rocas\n"
	.string "y también baja la VELOCIDAD.\p"
	.string "Si usas una MO, enseña el movimiento\n"
	.string "al POKéMON al instante.$"
	.string "Recuerda que una MO se usa una vez,\n"
	.string "así que piénsalo bien.$"

RustboroCity_Gym_Text_ExplainRockTombInfinite:
	.string "Esa MO QUÉ TÉCNICA, MT39,\n"
	.string "contiene Tumba Rocas.\p"
	.string "Causa daño al lanzar rocas y\n"
	.string "también baja la VELOCIDAD.\p"
	.string "Si usas una MT, le enseña el\n"
	.string "movimiento a un POKéMON.$"
	.string "Puedes usar una MT las veces que\n"
	.string "quieras, ¡así que disfrútala!$"

RustboroCity_Gym_Text_RoxannePostBattle:
	.string "Como eres tan fuerte, deberías\n"
	.string "retar a otros LÍDERES de GIMNASIO.\p"
	.string "Luchando contra muchos ENTRENADORES,\n"
	.string "aprenderás muchas cosas.$"

RustboroCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE CIUDAD FUNDA$"

RustboroCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE CIUDAD FUNDA\p"
	.string "ENTRENADORES DE ROXANNE:\n"
	.string "{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall:
	.string "… … … … … …\n"
	.string "… … … … … ¡Bip!\p"
	.string "ROXANNE: Hola, ¿{PLAYER}?\n"
	.string "Soy ROXANNE de CIUDAD FUNDA.\p"
	.string "BRAWLY me dijo que estás\n"
	.string "subiendo de rango entre los\l"
	.string "ENTRENADORES muy rápido.\p"
	.string "Bueno, prefiero no pensar que\n"
	.string "no podré vencerte.\p"
	.string "Prometo mejorar mi GIMNASIO\n"
	.string "para que nos retes otra vez.\p"
	.string "¡Espero que lo aguardes con\n"
	.string "tantas ganas como yo!\p"
	.string "… … … … … …\n"
	.string "… … … … … ¡Click!$"

RustboroCity_Gym_Text_RegisteredRoxanne:
	.string "LÍDER de GIMNASIO ROXANNE\n"
	.string "registrada en el POKéNAV.$"

RustboroCity_Gym_Text_RoxannePreRematch:
	.string "ROXANNE: Me alegra verte de nuevo.\n"
	.string "Soy ROXANNE, la LÍDER aquí.\p"
	.string "Seguro que ambos hemos tenido\n"
	.string "muchas batallas desde entonces.\p"
	.string "Quiero ver cuánto hemos\n"
	.string "mejorado. ¡Luchemos!$"

RustboroCity_Gym_Text_RoxanneRematchDefeat:
	.string "Grr…\n"
	.string "He perdido otra vez…$"

RustboroCity_Gym_Text_RoxannePostRematch:
	.string "ROXANNE: Aún tengo mucho que aprender\n"
	.string "sobre las batallas POKéMON.\p"
	.string "¡Saber eso hace que me encante aún\n"
	.string "más combatir!$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
	.string "ROXANNE: Me alegra verte de nuevo.\n"
	.string "Soy ROXANNE, la LÍDER del GIMNASIO.\p"
	.string "Seguro que ambos tuvimos muchas\n"
	.string "batallas desde que nos vimos.\p"
	.string "Quiero ver cuánto hemos mejorado\n"
	.string "desde entonces...\p"
	.string "Oh, no...\n"
	.string "¿Solo traes un POKéMON contigo?\p"
	.string "Vuelve con al menos un POKéMON\n"
	.string "más.$"
