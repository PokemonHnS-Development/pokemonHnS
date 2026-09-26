SSTidalRooms_MapScripts::
	.byte 0

SSTidalRooms_EventScript_SnatchGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_SNATCH, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SNATCH
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch::
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed::
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, SSTidalRooms_EventScript_Bed_PokecenterChallenge
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Bed_PokecenterChallenge::
	msgbox SSTidalRooms_Text_TakeRestOnBed_PokecenterChallenge, MSGBOX_DEFAULT
	closemessage
	end

SSTidalRooms_EventScript_Colton::
	trainerbattle_single TRAINER_GRUNT_26, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah::
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas::
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret::
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi::
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end
	
SSTidalRooms_Text_TakeRestOnBed_PokecenterChallenge:
	.string "Lo siento, estás jugando el\n"
	.string "desafío del POKéCENTER!$"

SSTidalRooms_Text_TakeRestOnBed:
	.string "Hay una cama...\n"
	.string "Voy a descansar.$"

SSTidalRooms_Text_ColtonIntro:
	.string "Suelo navegar a CIUDAD FONDOMARINO.\p"
	.string "Me gusta ir a los CONTESTS,\n"
	.string "ya sabes.$"

SSTidalRooms_Text_ColtonDefeat:
	.string "¡Fue un combate muy divertido!$"

SSTidalRooms_Text_ColtonPostBattle:
	.string "Me emociona pensar qué POKéMON\n"
	.string "veré en el próximo\l"
	.string "CONTEST. ¡Qué gran emoción!$"

SSTidalRooms_Text_MicahIntro:
	.string "¿Tus amigos son fuertes?$"

SSTidalRooms_Text_MicahDefeat:
	.string "Tus amigos son, en verdad, fuertes.$"

SSTidalRooms_Text_MicahPostBattle:
	.string "Los amigos no deben ser humanos.\n"
	.string "¡Los POKéMON son mis grandes amigos!$"

SSTidalRooms_Text_ThomasIntro:
	.string "Niño...\n"
	.string "¿Tocaste a la puerta?$"

SSTidalRooms_Text_ThomasDefeat:
	.string "Una derrota se acepta sin prisas\n"
	.string "ni pánico.$"

SSTidalRooms_Text_ThomasPostBattle:
	.string "No alterarse jamás es el código de\n"
	.string "conducta de un CABALLERO.$"

SSTidalRooms_Text_JedIntro:
	.string "JED: Me da algo de pena, pero...\n"
	.string "¡Verás nuestro poder del amor!$"

SSTidalRooms_Text_JedDefeat:
	.string "JED: Suspiro...$"

SSTidalRooms_Text_JedPostBattle:
	.string "JED: ¡Es la primera vez que nuestro\n"
	.string "amor no prevalece!\l"
	.string "¡Eres un gran ENTRENADOR!$"

SSTidalRooms_Text_JedNotEnoughMons:
	.string "JED: ¿Solo tienes un POKéMON?\n"
	.string "¿No te sientes muy solo?$"

SSTidalRooms_Text_LeaIntro:
	.string "LEA: Me siento algo tonta, pero...\n"
	.string "¡Verás nuestro poder del amor!$"

SSTidalRooms_Text_LeaDefeat:
	.string "LEA: ¡Oh, no!$"

SSTidalRooms_Text_LeaPostBattle:
	.string "LEA: ¡No lo puedo creer!\n"
	.string "Nuestro poder falló...\l"
	.string "¡Debes ser un gran ENTRENADOR!$"

SSTidalRooms_Text_LeaNotEnoughMons:
	.string "LEA: Quería luchar...\n"
	.string "Pero ni tienes dos POKéMON...$"

SSTidalRooms_Text_GarretIntro:
	.string "Ah, llegaste justo a tiempo.\p"
	.string "Estoy aburrida, ya ves.\n"
	.string "Puedes entretenerme.$"

SSTidalRooms_Text_GarretDefeat:
	.string "...Eso bastará.$"

SSTidalRooms_Text_GarretPostBattle:
	.string "Quizá le pida a mi padre que me\n"
	.string "compre un yate.\l"
	.string "¡Un yate para mí y mis POKéMON!$"

SSTidalRooms_Text_NaomiIntro:
	.string "Eres un ENTRENADOR adorable.\n"
	.string "¿Quieres tomar el té?\l"
	.string "¿O prefieres luchar?$"

SSTidalRooms_Text_NaomiDefeat:
	.string "Ya veo.\n"
	.string "Eres del tipo activo.$"

SSTidalRooms_Text_NaomiPostBattle:
	.string "Un crucero de lujo tiene su encanto,\n"
	.string "debo decirlo...\p"
	.string "Pero admito que recorrer HOENN en\n"
	.string "ferry también es atractivo.$"

SSTidalRooms_Text_NotSuspiciousTakeThis:
	.string "¡Eh... Hola! ¡No actúo raro!\n"
	.string "¡Toma esto! ¡Es gratis!\p"
	.string "Honestamente... ¡no se lo ROBÉ a\n"
	.string "nadie! ¡Jamás haría eso!\l"
	.string "¡Está limpio! ¡Puedes usarlo!$"

SSTidalRooms_Text_ExplainSnatch:
	.string "ROBAR quita los efectos positivos\n"
	.string "de ciertos movimientos antes de que\l"
	.string "un aliado o rival los use.$"

