@ VAR_LAST_TALKED would have made all these direct references unnecessary
.set LOCALID_SMART_MC, 4
.set LOCALID_SMART_JUDGE, 5
.set LOCALID_SMART_CONTESTANT_1, 6
.set LOCALID_SMART_CONTESTANT_2, 7
.set LOCALID_SMART_CONTESTANT_3, 8
.set LOCALID_SMART_CONTESTANT_4, 9
.set LOCALID_SMART_AUDIENCE_4, 11
.set LOCALID_SMART_AUDIENCE_2, 12
.set LOCALID_BEAUTY_MC, 13
.set LOCALID_BEAUTY_JUDGE, 14
.set LOCALID_BEAUTY_CONTESTANT_1, 15
.set LOCALID_BEAUTY_CONTESTANT_2, 16
.set LOCALID_BEAUTY_CONTESTANT_3, 17
.set LOCALID_BEAUTY_CONTESTANT_4, 18
.set LOCALID_BEAUTY_AUDIENCE_1, 19
.set LOCALID_BEAUTY_AUDIENCE_3, 20
.set LOCALID_BEAUTY_AUDIENCE_2, 21
.set LOCALID_SMART_AUDIENCE_3, 22
.set LOCALID_CUTE_MC, 23
.set LOCALID_CUTE_JUDGE, 24
.set LOCALID_CUTE_CONTESTANT_1, 25
.set LOCALID_CUTE_CONTESTANT_2, 26
.set LOCALID_CUTE_CONTESTANT_3, 27
.set LOCALID_CUTE_CONTESTANT_4, 28
.set LOCALID_CUTE_AUDIENCE_1, 29
.set LOCALID_CUTE_AUDIENCE_3, 30
.set LOCALID_CUTE_AUDIENCE_2, 31

LilycoveCity_ContestHall_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest:
	.string "Este POKéMON ganó el CONCURSO\n"
	.string "DE BELLEZA antes.\p"
	.string "¡Y adivina qué! Hoy logré que\n"
	.string "ganara el de INTELIGENCIA!\p"
	.string "Mis dotes me asustan hasta a mí…$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests:
	.string "He entrado a varios CONCURSOS,\n"
	.string "así que veo cómo funcionan.\p"
	.string "En un CONCURSO de GENIALIDAD,\n"
	.string "los movimientos geniales valen.\p"
	.string "Pero los inteligentes o lindos\n"
	.string "no funcionan tan bien, por ejemplo.$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks:
	.string "El joven que ganó hace rato tenía\n"
	.string "muchos {POKEBLOCK}S distintos.\p"
	.string "¿Podrías ganar tú si tuvieras\n"
	.string "tantas cosas así?$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous:
	.string "¡Vaya, este lugar es enorme!\p"
	.string "La tensión en el aire... No es\n"
	.string "como un CONTEST rural.$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal:
	.string "MC: Bien, POKéMON inteligentes y sus\n"
	.string "ENTRENADORES, ¿están listos?\p"
	.string "¡Den su mejor espectáculo!\n"
	.string "¡A cautivar!$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest:
	.string "JUEZ: ¿Disfrutas este CONCURSO?\p"
	.string "Vuelve con tres amigos y\n"
	.string "¡todos podrán entrar al CONCURSO!$"

LilycoveCity_ContestHall_Text_EnteredWrongContest:
	.string "Ayayayay…\n"
	.string "Entré al CONTEST equivocado.\p"
	.string "Metí a este POKéMON rudo en el\n"
	.string "CONTEST de INTELIGENCIA…\p"
	.string "¡Vamos, impresiona con un\n"
	.string "ROCK SMASH inteligente!$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart:
	.string "Pasé muchos años y toda mi\n"
	.string "sabiduría criando a este POKéMON\l"
	.string "para que sea inteligente.\p"
	.string "No será vencido fácilmente por el\n"
	.string "POKéMON de un novato.\p"
	.string "Querida esposa, ¿estás viendo esto?$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext:
	.string "¡Ahí está!\p"
	.string "Si mi POKéMON hace un movimiento\n"
	.string "astuto, ¡el público se emocionará!$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife:
	.string "¡Oh, no!\p"
	.string "¡El ABSORBÉCULA de mi ZUBAT es tan\n"
	.string "lindo que no dejé de usarlo!\p"
	.string "¡Pero esta gente no lo aprecia\n"
	.string "en absoluto!$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa:
	.string "¡Kiyaaah! ¡Eres hermoso, abuelo!$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves:
	.string "Aunque los ENTRENADORES usen el\n"
	.string "mismo POKéMON, usan distintos\l"
	.string "movimientos para atraer.\p"
	.string "Es como cuando la gente tiene\n"
	.string "estilos de combate diferentes.$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers:
	.string "Creo que los POKéMON se ven más\n"
	.string "listos que sus ENTRENADORES. Mucho.$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests:
	.string "Al final, sigo amando los CONCURSOS\n"
	.string "DE INTELIGENCIA.\p"
	.string "Ese color verde intelectual...\n"
	.string "Es tan... tan... genial.$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest:
	.string "MC: ¿También entrarás al CONCURSO\n"
	.string "DE BELLEZA? ¡Buena suerte!$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty:
	.string "JUEZ: ¡Cada POKéMON aquí es un\n"
	.string "modelo de belleza pura!\p"
	.string "¡Casi olvido darles su puntaje!$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty:
	.string "Un POKéMON tan hermoso...\n"
	.string "No hay otro igual.\p"
	.string "Todos quedarán cautivados por\n"
	.string "mi belleza.$"

LilycoveCity_ContestHall_Text_OverdidGrooming:
	.string "¡Waaaah!\p"
	.string "Aseé a mi POKéMON con cuidado\n"
	.string "para este CONCURSO...\p"
	.string "Pero me pasé...\n"
	.string "¡Su pelaje quedó todo erizado!\p"
	.string "¿Qué debo hacer?$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam:
	.string "Este RAYO AURORA es tan brillante\n"
	.string "que el JUEZ no podrá verlo.\p"
	.string "Eh, espera un segundo...\n"
	.string "¡Entonces no servirá de nada!$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe:
	.string "Este POKéMON se parece a mí\n"
	.string "cuando era joven.\p"
	.string "Al decir eso, mi esposo escupió\n"
	.string "el café que estaba bebiendo.\p"
	.string "¿Dije algo gracioso?$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy:
	.string "Sabes, si gano un CONCURSO de\n"
	.string "BELLEZA, claro que me hace\l"
	.string "feliz. Más de lo normal, al menos.$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon:
	.string "¡Wahahahah!\p"
	.string "¡Mira todos esos POKéMON\n"
	.string "tan hermosos!\l"
	.string "¡Amo este tipo de brillo!$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone:
	.string "No siempre se gana solo con\n"
	.string "belleza.\p"
	.string "Debes asear a tu POKéMON para que\n"
	.string "brille como el mío.$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest:
	.string "MC: ¡Oh, hola!\n"
	.string "¡Estamos en medio de un CONCURSO!\p"
	.string "Regístrate en el mostrador y\n"
	.string "luego vuelve, ¿está bien?$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals:
	.string "JUEZ: ¡Qué apelaciones tan\n"
	.string "encantadoras y lindas!\p"
	.string "¡Cielos! ¡Qué apelación de\n"
	.string "DEPORTE ACUÁTICO tan adorable!$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted:
	.string "Oh, no... Mi dulce AZURILL se\n"
	.string "distrajo con otro POKéMON.$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest:
	.string "Mi POKéMON nunca ganó una batalla,\n"
	.string "¡pero en un CONCURSO, cuidado!$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel:
	.string "El PETAL DANCE de mi POKéMON es\n"
	.string "una maravilla de elegancia.\p"
	.string "No dejaré que nadie interrumpa\n"
	.string "su actuación.$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter:
	.string "Todos los POKéMON son muy lindos.\p"
	.string "Pero si mi POKéMON hiciera\n"
	.string "una apelación linda...\p"
	.string "¡Seguro sería mucho más linda\n"
	.string "que las demás!$"

LilycoveCity_ContestHall_Text_MyChildIsInContest:
	.string "Mi hijo está en este CONCURSO.$"

LilycoveCity_ContestHall_Text_ComeOnDear:
	.string "¡Vamos, cariño! ¡Tú puedes!\n"
	.string "¡Tu POKéMON es el mejor!$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest:
	.string "Creo que esa chica de allá es\n"
	.string "la más linda de todas.\p"
	.string "¿Qué? ¿Juzgan a los POKéMON\n"
	.string "por su apariencia?$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn:
	.string "¡Oh, ver tantos POKéMON lindos,\n"
	.string "me dan ganas de tener los míos!\p"
	.string "¡Iré a capturar algunos!$"

LilycoveCity_ContestHall_Text_BeautyContestStage:
	.string "ESCENARIO DE BELLEZA\n"
	.string "¡DÉJATE ATRAER POR POKéMON BELLOS!$"

LilycoveCity_ContestHall_Text_CuteContestStage:
	.string "ESCENARIO DE TERNURA\n"
	.string "¡DÉJATE ENCANTAR POR POKéMON LINDOS!$"

LilycoveCity_ContestHall_Text_SmartContestStage:
	.string "ESCENARIO DE INTELIGENCIA\n"
	.string "¡MIRA ESTOS POKéMON INTELIGENTES!$"

