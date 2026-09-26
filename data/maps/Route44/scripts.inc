Route44_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route44_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route44_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route44_EventScript_Wilton::
	trainerbattle_single TRAINER_WILTON Route44_Text_FisherWilton1Seen, Route44_Text_FisherWilton1Beaten
	msgbox Route44_Text_FisherWiltonHugePoliwag, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR Route44_Text_FisherEdgarSeen, Route44_Text_FisherEdgarBeaten
	msgbox Route44_Text_FisherEdgarAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Vance::
	trainerbattle_single TRAINER_VANCE Route44_Text_BirdKeeperVance1Seen, Route44_Text_BirdKeeperVance1Beaten
	msgbox Route44_Text_BirdKeeperVanceBirds, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Phil::
	trainerbattle_single TRAINER_PHIL Route44_Text_PsychicPhilSeen, Route44_Text_PsychicPhilBeaten
	msgbox Route44_Text_PsychicPhilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Zach::
	trainerbattle_single TRAINER_ZACH Route44_Text_PokemaniacZachSeen, Route44_Text_PokemaniacZachBeaten
	msgbox Route44_Text_PokemaniacZachAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN Route44_Text_CooltrainermAllenSeen, Route44_Text_CooltrainermAllenBeaten
	msgbox Route44_Text_CooltrainermAllenAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Cybil::
	trainerbattle_single TRAINER_CYBIL Route44_Text_CooltrainerfCybilSeen, Route44_Text_CooltrainerfCybilBeaten
	msgbox Route44_Text_CooltrainerfCybilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Sign1::
	msgbox Route44_Text_Sign1, MSGBOX_SIGN
	end

Route44_EventScript_Sign2::
	msgbox Route44_Text_Sign2, MSGBOX_SIGN
	end

Route44_EventScript_Item_MaxRepel::
	finditem ITEM_MAX_REPEL
	end

Route44_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route44_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route44_Text_FisherWilton1Seen:
    .string "¡Aack!\p"
    .string "¡Hice perder a un POLIWAG!\n"
    .string "¿Qué piensas hacer al respecto?$"

Route44_Text_FisherWilton1Beaten:
    .string "Olvídalo nomás.$"

Route44_Text_FisherWiltonHugePoliwag:
    .string "Ese POLIWAG que escapó...\n"
    .string "era enorme.\p"
    .string "¡Juro que debía medir\n"
    .string "unos 5 metros!$"

Route44_Text_FisherEdgarSeen:
    .string "Pesco hasta que no pueda más.\p"
    .string "Lucho hasta que caigo.\p"
    .string "Así es mi relación con mis\n"
    .string "POKéMON.$"

Route44_Text_FisherEdgarBeaten:
    .string "Hmmmm... Esto no está bien.$"

Route44_Text_FisherEdgarAfter:
    .string "Son 100 victorias y 101 derrotas.\p"
    .string "No lucharé por un tiempo.$"

Route44_Text_BirdKeeperVance1Seen:
    .string "¿Sabes algo sobre los POKéMON\n"
    .string "aves legendarios?$"

Route44_Text_BirdKeeperVance1Beaten:
    .string "¡Uff! Eres muy bueno.$"

Route44_Text_BirdKeeperVanceBirds:
    .string "ARTICUNO, ZAPDOS y MOLTRES son\n"
    .string "los tres POKéMON aves legendarios.\p"
    .string "Aunque oí que existen otras aves\n"
    .string "legendarias.$"

Route44_Text_PsychicPhilSeen:
    .string "¡Voy a ganar, seguro!$"

Route44_Text_PsychicPhilBeaten:
    .string "Arrgh... Qué derrota tan impactante...$"

Route44_Text_PsychicPhilAfter:
    .string "Es importante tener convicción\n"
    .string "de tu lado.$"

Route44_Text_PokemaniacZachSeen:
    .string "¡Haré lo que sea por atrapar\n"
    .string "POKéMON raros!$"

Route44_Text_PokemaniacZachBeaten:
    .string "Oooh, tus POKéMON son muy\n"
    .string "atractivos.$"

Route44_Text_PokemaniacZachAfter:
    .string "Si un POKéMON tiene colores\n"
    .string "inusuales, vale mucho más.\p"
    .string "¿Qué? ¿Dices que no es cierto?$"

Route44_Text_CooltrainermAllenSeen:
    .string "Veo que eres un buen entrenador\n"
    .string "solo con mirarte.\p"
    .string "Soy bueno con los POKéMON, y veo\n"
    .string "que tú también lo eres.$"

Route44_Text_CooltrainermAllenBeaten:
    .string "¡Tch! He perdido por completo.$"

Route44_Text_CooltrainermAllenAfter:
    .string "Vaya. Tienes muchas MEDALLAS.\p"
    .string "No es raro que seas tan fuerte.\p"
    .string "¿MORTY del GIMNASIO de IRIS\n"
    .string "seguirá entrenando?\p"
    .string "Realmente me dio una paliza.$"

Route44_Text_CooltrainerfCybilSeen:
    .string "Te ves fuerte.\p"
    .string "Los buenos ENTRENADORES buscan\n"
    .string "rivales fuertes por instinto.$"

Route44_Text_CooltrainerfCybilBeaten:
    .string "¡No! Esto no servirá de nada.$"

Route44_Text_CooltrainerfCybilAfter:
    .string "Mejoramos luchando en\n"
    .string "muchas batallas.\p"
    .string "Luché mucho para ser lo que soy\n"
    .string "hoy: un miembro de la élite.$"

Route44_Text_Sign1:
    .string "RUTA 44\n"
    .string "CAMINO HIELO ADELANTE$"

Route44_Text_Sign2:
    .string "RUTA 44\p"
    .string "PUEBLO CAOBA - CIUDAD ENDRINO$"

