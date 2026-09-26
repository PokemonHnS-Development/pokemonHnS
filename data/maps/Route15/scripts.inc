Route15_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route15_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route15_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route15_EventScript_Colette::
	trainerbattle_single TRAINER_COLETTE Route15_Text_TeacherColetteSeen, Route15_Text_TeacherColetteBeaten
	msgbox Route15_Text_TeacherColetteAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Hillary::
	trainerbattle_single TRAINER_HILLARY Route15_Text_TeacherHillarySeen, Route15_Text_TeacherHillaryBeaten
	msgbox Route15_Text_TeacherHillaryAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Kipp::
	trainerbattle_single TRAINER_KIPP Route15_Text_SchoolboyKippSeen, Route15_Text_SchoolboyKippBeaten
	msgbox Route15_Text_SchoolboyKippAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY Route15_Text_SchoolboyTommySeen, Route15_Text_SchoolboyTommyBeaten
	msgbox Route15_Text_SchoolboyTommyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Johnny::
	trainerbattle_single TRAINER_JOHNNY Route15_Text_SchoolboyJohnnySeen, Route15_Text_SchoolboyJohnnyBeaten
	msgbox Route15_Text_SchoolboyJohnnyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY Route15_Text_SchoolboyBillySeen, Route15_Text_SchoolboyBillyBeaten
	msgbox Route15_Text_SchoolboyBillyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Sign::
	msgbox Route15_Text_Sign, MSGBOX_SIGN
	end

Route15_EventScript_PPup::
	finditem ITEM_PP_UP
	end

Route15_Text_TeacherColetteSeen:
	.string "¿Olvidaste algo?$"

Route15_Text_TeacherColetteBeaten:
	.string "¡Kyaaah!$"

Route15_Text_TeacherColetteAfterBattle:
	.string "Antes de ser maestra, solía\n"
	.string "olvidar muchas cosas.$"

Route15_Text_TeacherHillarySeen:
	.string "En días soleados, creo que los\n"
	.string "niños prefieren jugar en el\l"
	.string "patio que estudiar en clase.$"

Route15_Text_TeacherHillaryBeaten:
	.string "No quería perder…$"

Route15_Text_TeacherHillaryAfterBattle:
	.string "Estudiar es importante, pero\n"
	.string "el ejercicio es igual de vital.$"

Route15_Text_SchoolboyKippSeen:
	.string "Espera. Debo llamar a mi mamá.$"

Route15_Text_SchoolboyKippBeaten:
	.string "¡Perdón, mamá! ¡Me vencieron!$"

Route15_Text_SchoolboyKippAfterBattle:
	.string "Mi mamá se preocupa mucho, tengo\n"
	.string "que llamarla a cada rato.$"

Route15_Text_SchoolboyTommySeen:
	.string "¡Luchemos! ¡No voy a perder!$"

Route15_Text_SchoolboyTommyBeaten:
	.string "¡Olvidé hacer mi tarea!$"

Route15_Text_SchoolboyTommyAfterBattle:
	.string "¡Sayonara! Lo acabo de aprender\n"
	.string "en mi clase de japonés.$"

Route15_Text_SchoolboyJohnnySeen:
	.string "Estamos de excursión a la TORRE\n"
	.string "RADIO LAVANDA por estudios.$"

Route15_Text_SchoolboyJohnnyBeaten:
	.string "¡Eres increíblemente fuerte!$"

Route15_Text_SchoolboyJohnnyAfterBattle:
	.string "Estoy cansado de caminar. Necesito\n"
	.string "tomarme un descanso.$"

Route15_Text_SchoolboyBillySeen:
	.string "¡Mi clase favorita es Gimnasio!$"

Route15_Text_SchoolboyBillyBeaten:
	.string "¡Oh, no! ¿Cómo pude perder?$"

Route15_Text_SchoolboyBillyAfterBattle:
	.string "¡Si los POKéMON fueran materia\n"
	.string "escolar, sería el mejor!$"

Route15_Text_Sign:
	.string "RUTA 15\p"
	.string "CIUDAD FUXIA - PUEBLO LAVANDA$"

