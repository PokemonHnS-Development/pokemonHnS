SootopolisCity_Gym_B1F_MapScripts::
	.byte 0

SootopolisCity_Gym_B1F_EventScript_Andrea::
	trainerbattle_single TRAINER_BRIAN, SootopolisCity_Gym_B1F_Text_AndreaIntro, SootopolisCity_Gym_B1F_Text_AndreaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Crissy::
	trainerbattle_single TRAINER_HARRY, SootopolisCity_Gym_B1F_Text_CrissyIntro, SootopolisCity_Gym_B1F_Text_CrissyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Brianna::
	trainerbattle_single TRAINER_ELLEN, SootopolisCity_Gym_B1F_Text_BriannaIntro, SootopolisCity_Gym_B1F_Text_BriannaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Connie::
	trainerbattle_single TRAINER_CONNIE, SootopolisCity_Gym_B1F_Text_ConnieIntro, SootopolisCity_Gym_B1F_Text_ConnieDefeat
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET, SootopolisCity_Gym_B1F_Text_BridgetIntro, SootopolisCity_Gym_B1F_Text_BridgetDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, SootopolisCity_Gym_B1F_Text_OliviaIntro, SootopolisCity_Gym_B1F_Text_OliviaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY, SootopolisCity_Gym_B1F_Text_TiffanyIntro, SootopolisCity_Gym_B1F_Text_TiffanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_TiffanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bethany::
	trainerbattle_single TRAINER_BETHANY, SootopolisCity_Gym_B1F_Text_BethanyIntro, SootopolisCity_Gym_B1F_Text_BethanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Annika::
	trainerbattle_single TRAINER_CARRIE, SootopolisCity_Gym_B1F_Text_AnnikaIntro, SootopolisCity_Gym_B1F_Text_AnnikaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Daphne::
	trainerbattle_single TRAINER_JIMMY, SootopolisCity_Gym_B1F_Text_DaphneIntro, SootopolisCity_Gym_B1F_Text_DaphneDefeat
	msgbox SootopolisCity_Gym_B1F_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_Text_AndreaIntro:
	.string "¡Te mostraré las técnicas sublimes\n"
	.string "que aprendí del LÍDER JUAN!$"

SootopolisCity_Gym_B1F_Text_AndreaDefeat:
	.string "Por favor, perdóname, JUAN…$"

SootopolisCity_Gym_B1F_Text_AndreaPostBattle:
	.string "Mira qué pasa si rompes todas\n"
	.string "las baldosas del suelo.$"

SootopolisCity_Gym_B1F_Text_CrissyIntro:
	.string "Viniste hasta aquí, pero no\n"
	.string "verás a JUAN.\p"
	.string "¡No si pierdes contra mí!$"

SootopolisCity_Gym_B1F_Text_CrissyDefeat:
	.string "¡Eres fuerte!\n"
	.string "¡Me engañó tu apariencia tierna!$"

SootopolisCity_Gym_B1F_Text_CrissyPostBattle:
	.string "Quizás seas lo bastante bueno para\n"
	.string "que JUAN no te derrote de un golpe.$"

SootopolisCity_Gym_B1F_Text_DaphneIntro:
	.string "Ver a JUAN dirigiendo\n"
	.string "una batalla…\p"
	.string "¡Su belleza me impulsó a\n"
	.string "ser un ENTRENADOR!$"

SootopolisCity_Gym_B1F_Text_DaphneDefeat:
	.string "Luchaste con más belleza de la\n"
	.string "que yo pude reunir…$"

SootopolisCity_Gym_B1F_Text_DaphnePostBattle:
	.string "Tu gracia en batalla es\n"
	.string "fabulosa.\p"
	.string "Oh... Qué suerte tuve al encontrar\n"
	.string "a los POKéMON.$"

SootopolisCity_Gym_B1F_Text_ConnieIntro:
	.string "Debo enseñarte lo duras que\n"
	.string "pueden ser las batallas.$"

SootopolisCity_Gym_B1F_Text_ConnieDefeat:
	.string "Oh.\n"
	.string "Eres fuerte.$"

SootopolisCity_Gym_B1F_Text_ConniePostBattle:
	.string "Te diré algo útil.\p"
	.string "Para llegar a JUAN, debes pisar\n"
	.string "cada baldosa una sola vez.$"

SootopolisCity_Gym_B1F_Text_BridgetIntro:
	.string "El GIMNASIO de mayor nivel de la\n"
	.string "región de HOENN...\p"
	.string "Es el GIMNASIO de CIUDAD ARRECIFE.$"

SootopolisCity_Gym_B1F_Text_BridgetDefeat:
	.string "¡Qué nivel tan alto tienes!$"

SootopolisCity_Gym_B1F_Text_BridgetPostBattle:
	.string "Más que estar satisfecho en un\n"
	.string "GIMNASIO fuerte, creo que entrenar\l"
	.string "en otros sitios te hará más fuerte.\l"
	.string "Y sobre todo, parece más divertido.$"

SootopolisCity_Gym_B1F_Text_OliviaIntro:
	.string "Entreno mis POKéMON junto a\n"
	.string "JUAN.\p"
	.string "No creas que soy un debilucho.$"

SootopolisCity_Gym_B1F_Text_OliviaDefeat:
	.string "Me han vencido…$"

SootopolisCity_Gym_B1F_Text_OliviaPostBattle:
	.string "Creo que tienes potencial.\n"
	.string "¿Por qué no te quedas a entrenar?$"

SootopolisCity_Gym_B1F_Text_TiffanyIntro:
	.string "Un desliz suave sobre el hielo sin\n"
	.string "cruzar ninguna línea...\p"
	.string "¡Un ENTRENADOR con tal destreza\n"
	.string "sería elegantemente bello!$"

SootopolisCity_Gym_B1F_Text_TiffanyDefeat:
	.string "¡¿Perdona?!$"

SootopolisCity_Gym_B1F_Text_TiffanyPostBattle:
	.string "Es obvio, pero tu fuerza como\n"
	.string "ENTRENADOR no tiene nada que ver\l"
	.string "con tu edad.$"

SootopolisCity_Gym_B1F_Text_BethanyIntro:
	.string "Con mis POKéMON, el tiempo vuela\n"
	.string "antes de que digas: ¡Ups!$"

SootopolisCity_Gym_B1F_Text_BethanyDefeat:
	.string "¡Ups!$"

SootopolisCity_Gym_B1F_Text_BethanyPostBattle:
	.string "Quisiera olvidar las causas perdidas\n"
	.string "antes de decir un ¡Ups!$"

SootopolisCity_Gym_B1F_Text_AnnikaIntro:
	.string "Puedo luchar con POKéMON muy raros\n"
	.string "si quieres.$"

SootopolisCity_Gym_B1F_Text_AnnikaDefeat:
	.string "¡Vaya! ¿Miraste bien a mis\n"
	.string "POKéMON?$"

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle:
	.string "Vine a este GIMNASIO porque JUAN\n"
	.string "elogió a mis lindos POKéMON.\p"
	.string "Ojalá hubiera conocido a JUAN\n"
	.string "cuando era más joven…$"

SootopolisCity_Gym_B1F_Text_BriannaIntro:
	.string "Jeje…\n"
	.string "Tu mirada seria es encantadora.$"

SootopolisCity_Gym_B1F_Text_BriannaDefeat:
	.string "Vaya, vaya.\n"
	.string "Fui demasiado blanda contigo.$"

SootopolisCity_Gym_B1F_Text_BriannaPostBattle:
	.string "No pudiste tocar a JUAN,\n"
	.string "estoy segura. Jeje…$"

