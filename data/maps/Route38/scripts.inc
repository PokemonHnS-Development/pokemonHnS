Route38_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route38_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route38_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route38_EventScript_Toby::
	trainerbattle_single TRAINER_TOBY, Route38_Text_BirdKeeperTobySeen, Route38_Text_BirdKeeperTobyBeaten
	msgbox Route38_Text_BirdKeeperTobyAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Chad::
	trainerbattle_single TRAINER_CHAD, Route38_Text_SchoolboyChad1Seen, Route38_Text_SchoolboyChad1Beaten
	msgbox Route38_Text_SchoolboyChadAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Dana::
	trainerbattle_single TRAINER_DANA, Route38_Text_LassDana1Seen, Route38_Text_LassDana1Beaten
	msgbox Route38_Text_LassDanaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE, Route38_Text_BeautyValerieSeen, Route38_Text_BeautyValerieBeaten
	msgbox Route38_Text_BeautyValerieAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Harry::
	trainerbattle_single TRAINER_HARRY, Route38_Text_SailorHarrySeen, Route38_Text_SailorHarryBeaten
	msgbox Route38_Text_SailorHarryAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, Route38_Text_BeautyOliviaSeen, Route38_Text_BeautyOliviaBeaten
	msgbox Route38_Text_BeautyOliviaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Sign1::
	lock
	msgbox Route38_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Sign2::
	lock
	msgbox Route38_Text_WaterSign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Item_LaxIncense::
	finditem ITEM_LAX_INCENSE
	end

Route38_Text_BirdKeeperTobySeen:
	.string "¡Vuela alto en el cielo,\n"
	.string "mi querido POKéMON ave!$"

Route38_Text_BirdKeeperTobyBeaten:
	.string "Siento que solo quiero\n"
	.string "salir volando ahora.$"

Route38_Text_BirdKeeperTobyAfter:
	.string "Entrenaré en CIUDAD ORQUIDEA\n"
	.string "para enseñar a VOLAR a mi POKéMON.$"

Route38_Text_SchoolboyChad1Seen:
	.string "Déjame intentar algo\n"
	.string "que aprendí hoy.$"

Route38_Text_SchoolboyChad1Beaten:
	.string "Supongo que no estudié\n"
	.string "lo suficiente.$"

Route38_Text_SchoolboyChadAfter:
	.string "Tengo tantos exámenes que\n"
	.string "no tengo mucho tiempo\l"
	.string "para los POKéMON.\p"
	.string "Así que cuando juego,\n"
	.string "me concentro al máximo.$"

Route38_Text_LassDana1Seen:
	.string "Pareces ser bueno con los\n"
	.string "POKéMON.\p"
	.string "Si es así, ¿podrías\n"
	.string "darme algunos consejos?$"

Route38_Text_LassDana1Beaten:
	.string "Ya veo. Así que puedes\n"
	.string "luchar de esa manera.$"

Route38_Text_LassDanaAfter:
	.string "¡Sé algo bueno!\p"
	.string "La leche de GRANJA MOOMOO\n"
	.string "es famosa por su sabor.$"

Route38_Text_BeautyValerieSeen:
	.string "¡Hola! ¡Qué lindo eres\n"
	.string "como entrenador!\p"
	.string "¿Puedo ver tus POKéMON?$"

Route38_Text_BeautyValerieBeaten:
	.string "¡Me alegra haber podido\n"
	.string "ver tus POKéMON!$"

Route38_Text_BeautyValerieAfter:
	.string "Cuando veo POKéMON, parece\n"
	.string "que se calman mis nervios.$"

Route38_Text_SailorHarrySeen:
	.string "He estado en el extranjero,\n"
	.string "¡así que conozco todo tipo\l"
	.string "de POKéMON!$"

Route38_Text_SailorHarryBeaten:
	.string "¡Tu habilidad es de clase mundial!$"

Route38_Text_SailorHarryAfter:
	.string "Gente de todo el mundo vive\n"
	.string "felizmente junto a sus\l"
	.string "POKéMON.$"

Route38_Text_BeautyOliviaSeen:
	.string "¿No crees que mis POKéMON\n"
	.string "y yo somos hermosos?$"

Route38_Text_BeautyOliviaBeaten:
	.string "Bebemos LECHE MU-MU todos\n"
	.string "los días.$"

Route38_Text_BeautyOliviaAfter:
	.string "La LECHE MU-MU es buena para\n"
	.string "la salud y belleza,\p"
	.string "pero solo venden una\n"
	.string "botella a la vez.$"

Route38_Text_Sign:
	.string "RUTA 38\p"
	.string "CIUDAD OLIVO - CIUDAD IRIS$"

Route38_Text_TrainerTips:
	.string "CONSEJOS\p"
	.string "Si un POKéMON intenta\n"
	.string "evolucionar, puedes pararlo.\p"
	.string "Pulsa el botón B durante la\n"
	.string "evolución para cancelarla.\p"
	.string "Eso asusta al POKéMON\n"
	.string "y detiene su evolución.$"


Route38_Text_WaterSign:
	.string "PROHIBIDO NADAR O PESCAR.\n"
	.string "AGUA SOLO PARA EL RIEGO.\p"
	.string "-CONSEJO DE CIUDAD IRIS$"
