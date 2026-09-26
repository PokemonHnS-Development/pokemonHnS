.set LOCALID_UNION_CAVE_LAPRAS, 6

UnionCave_B2F_MapScripts::
	.byte 0

UnionCave_B2F_EventScript_CooltrainerNick::
	trainerbattle_single TRAINER_NICK, UnionCave_B2F_Text_CooltrainermNickSeen, UnionCave_B2F_Text_CooltrainermNickBeaten
	msgbox UnionCave_B2F_Text_CooltrainermNickAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfGwen::
	trainerbattle_single TRAINER_GWEN, UnionCave_B2F_Text_CooltrainerfGwenSeen, UnionCave_B2F_Text_CooltrainerfGwenBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfGwenAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfEmma::
	trainerbattle_single TRAINER_EMMA, UnionCave_B2F_Text_CooltrainerfEmmaSeen, UnionCave_B2F_Text_CooltrainerfEmmaBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfEmmaAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_Lapras::
	lock
	faceplayer
	playmoncry SPECIES_LAPRAS, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_LAPRAS, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, UnionCave_B2F_EventScript_LaprasRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_UNION_CAVE_LAPRAS
	setflag FLAG_HIDE_UNION_CAVE_LAPRAS
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

UnionCave_B2F_EventScript_LaprasRan::
	release
	end


UnionCave_B2F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

UnionCave_B2F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

UnionCave_B2F_EventScript_Item_MaxRevive::
	finditem ITEM_MAX_REVIVE
	end

UnionCave_B2F_Text_CooltrainermNickSeen:
	.string "Hay dos tipos de personas.\p"
	.string "Las que tienen estilo y las que\n"
	.string "no.\p"
	.string "¿Tú qué tipo de persona eres?$"

UnionCave_B2F_Text_CooltrainermNickBeaten:
	.string "¡Tienes un estilo deslumbrante!$"

UnionCave_B2F_Text_CooltrainermNickAfter:
	.string "Tu estilo POKéMON es impactante y\n"
	.string "colorido, lo admito.\p"
	.string "¡Seguirás mejorando cada vez más!$"

UnionCave_B2F_Text_CooltrainerfGwenSeen:
	.string "Estoy entrenando. ¿Quieres jugar?$"

UnionCave_B2F_Text_CooltrainerfGwenBeaten:
	.string "¡Ay, no! Eres demasiado bueno.$"

UnionCave_B2F_Text_CooltrainerfGwenAfter:
	.string "Entrenaré solo hasta que\n"
	.string "me mejore.$"

UnionCave_B2F_Text_CooltrainerfEmmaSeen:
	.string "Si estuvieran los POKéMON que amo,\n"
	.string "iría a donde sea.\p"
	.string "Eso hace un entrenador real.$"

UnionCave_B2F_Text_CooltrainerfEmmaBeaten:
	.string "¡Prefiero acariciar a mis bebés!$"

UnionCave_B2F_Text_CooltrainerfEmmaAfter:
	.string "Solo una vez por semana, un POKéMON\n"
	.string "viene a la orilla del agua.\p"
	.string "Quería ver a ese POKéMON…$"
