UnionCave_B1F_MapScripts::
	.byte 0

UnionCave_B1F_EventScript_HikerPhillip::
	trainerbattle_single TRAINER_PHILLIP, UnionCave_B1F_Text_HikerPhillipSeen, UnionCave_B1F_Text_HikerPhillipBeaten
	msgbox UnionCave_B1F_Text_HikerPhillipAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_HikerLeonard::
	trainerbattle_single TRAINER_LEONARD, UnionCave_B1F_Text_HikerLeonardSeen, UnionCave_B1F_Text_HikerLeonardBeaten
	msgbox UnionCave_B1F_Text_HikerLeonardAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacAndrew::
	trainerbattle_single TRAINER_ANDREW, UnionCave_B1F_Text_PokemaniacAndrewSeen, UnionCave_B1F_Text_PokemaniacAndrewBeaten
	msgbox UnionCave_B1F_Text_PokemaniacAndrewAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacCalvin::
	trainerbattle_single TRAINER_CALVIN, UnionCave_B1F_Text_PokemaniacCalvinSeen, UnionCave_B1F_Text_PokemaniacCalvinBeaten
	msgbox UnionCave_B1F_Text_PokemaniacCalvinAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_Item_SecretPower::
	finditem ITEM_TM_SECRET_POWER
	end

UnionCave_B1F_EventScript_Item_Xdefend::
	finditem ITEM_X_DEFEND
	end

UnionCave_B1F_Text_HikerPhillipSeen:
	.string "Ha pasado tiempo desde que vi\n"
	.string "a otra persona.\p"
	.string "No seas tímido. ¡Luchamos!$"

UnionCave_B1F_Text_HikerPhillipBeaten:
	.string "Uurggh…$"

UnionCave_B1F_Text_HikerPhillipAfter:
	.string "Llevo mucho tiempo perdido…\p"
	.string "No me importa, ¡pero tengo\n"
	.string "muchísima hambre!$"

UnionCave_B1F_Text_HikerLeonardSeen:
	.string "¡No lo puedo creer! ¡Una visita!$"

UnionCave_B1F_Text_HikerLeonardBeaten:
	.string "¡Jajaja! ¡Eres muy valiente!$"

UnionCave_B1F_Text_HikerLeonardAfter:
	.string "Vivo aquí abajo.\p"
	.string "Tú también puedes, si quieres.\p"
	.string "Hay espacio de sobra, ya ves.$"

UnionCave_B1F_Text_PokemaniacAndrewSeen:
	.string "¿Quién está ahí?\p"
	.string "¡Déjanos en paz a mí y a mi POKéMON!$"

UnionCave_B1F_Text_PokemaniacAndrewBeaten:
	.string "¡Vete… Vete de aquí!$"

UnionCave_B1F_Text_PokemaniacAndrewAfter:
	.string "Solo mi POKéMON y yo. ¡Estoy\n"
	.string "loco de alegría!$"

UnionCave_B1F_Text_PokemaniacCalvinSeen:
	.string "Vine hasta aquí para hacer mi\n"
	.string "estudio de POKéMON.\p"
	.string "¡Demostraré mis hallazgos en una\n"
	.string "batalla real!$"

UnionCave_B1F_Text_PokemaniacCalvinBeaten:
	.string "¡Tú demostraste conmigo!$"

UnionCave_B1F_Text_PokemaniacCalvinAfter:
	.string "Debo compilar y anunciar los\n"
	.string "resultados del estudio.\p"
	.string "¡Podría ser famoso como el\n"
	.string "PROF.ELM!$"
