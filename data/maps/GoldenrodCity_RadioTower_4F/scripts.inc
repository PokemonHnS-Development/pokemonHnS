GoldenrodCity_RadioTower_4F_MapScripts::
	.byte 0

GoldenrodCity_RadioTower_4F4_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_Studio2Sign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_ProductionSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_Grunt28::
	trainerbattle_single TRAINER_GRUNT_28 GoldenrodCity_RadioTower_4F4_Text_GruntF4Seen, GoldenrodCity_RadioTower_4F4_Text_GruntF4Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_GruntF4After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower4_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_9 GoldenrodCity_RadioTower_4F4_Text_GruntM10Seen, GoldenrodCity_RadioTower_4F4_Text_GruntM10Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_GruntM10After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower4_EventScript_Proton::
	trainerbattle_single TRAINER_PROTON_2 GoldenrodCity_RadioTower_4F4_Text_Proton_Seen, GoldenrodCity_RadioTower_4F4_Text_Proton_Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_Proton_After, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_4F4_EventScript_Fisher::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_4F4_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Scientist::
	trainerbattle_single TRAINER_RICH GoldenrodCity_RadioTower_4F4_Text_ScientistRichSeen, GoldenrodCity_RadioTower_4F4_Text_ScientistRichBeaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_ScientistRichAfter, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_4F4_EventScript_Mary::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_unset FLAG_GOT_MARY_BRIGHT_POWDER, GoldenrodCity_RadioTower_4F4_EventScript_Mary3
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Mary2::
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMary, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Mary3::
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryCleared, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_BRIGHT_POWDER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryPinkBow, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_GOT_MARY_BRIGHT_POWDER
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_4F4_Text_Meowth, MSGBOX_DEFAULT
	waitmoncry
	release
	end


GoldenrodCity_RadioTower_4F4_Text_Proton_Seen:
	.string "PROTON: ¡Espera un segundo!\p"
	.string "¿No eres tú quien se interpuso\n"
	.string "en el POZO SLOWPOKE?\p"
	.string "Ya veo... Haces todo esto\n"
	.string "para hacerme enfadar.\l"
	.string "¡Ten cuidado!\p"
	.string "Pero ya que lo deseas, ¡te mostraré\n"
	.string "la furia de un EJECUTIVO del\l"
	.string "TEAM ROCKET!$"

GoldenrodCity_RadioTower_4F4_Text_Proton_Beaten:
	.string "Uff...$"

GoldenrodCity_RadioTower_4F4_Text_Proton_After:
	.string "PROTON: Puede que hayas ganado\n"
	.string "esta vez... Pero solo lograste\p"
	.string "que la furia del TEAM ROCKET crezca.$"

GoldenrodCity_RadioTower_4F4_Text_Fisher:
	.string "Escuché la radio mientras estaba\n"
	.string "en las RUINAS.\p"
	.string "Oí una transmisión extraña allí.$"

GoldenrodCity_RadioTower_4F4_Text_DJMary:
	.string "MARY: ¿Por qué? ¿Por qué tengo que\n"
	.string "sufrir esto?\p"
	.string "¡MEOWTH, ayúdame!$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryCleared:
	.string "MARY: ¡Oh! ¡Eres mi pequeño salvador!\p"
	.string "¿Aceptas esto como agradecimiento?$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryPinkBow:
	.string "MARY: Es bueno para esquivar los\n"
	.string "ataques del enemigo.$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter:
	.string "MARY: ¡Sintonízame en el programa\n"
	.string "POKéMON TALK del PROF.OAK!$"

GoldenrodCity_RadioTower_4F4_Text_Meowth:
	.string "MEOWTH: Meowth…$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10Seen:
	.string "¿Planeas rescatar al DIRECTOR?\p"
	.string "¡No será posible porque voy a\n"
	.string "derrotarte!$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10Beaten:
	.string "¡No! ¡Increíble!$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10After:
	.string "¡No lo creo! ¡Me derrotaron!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2Seen:
	.string "¡Alto! ¡Soy la fortaleza del\n"
	.string "TEAM ROCKET!\p"
	.string "¡No darás ni un paso más!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2Beaten:
	.string "¡La fortaleza cayó!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2After:
	.string "Te ganaste mi respeto, así que\n"
	.string "toma un consejo.\p"
	.string "No es tarde. Aún puedes dar\n"
	.string "media vuelta.$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4Seen:
	.string "¿No creo que los POKéMON sean lindos?\p"
	.string "Creeré que los míos son lindos--\p"
	.string "¡después de que venzan a los tuyos!$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4Beaten:
	.string "¡Oh, no! ¡Son tan inútiles!$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4After:
	.string "¡Amo mi belleza!\p"
	.string "¿A quién le importan los POKéMON?$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichSeen:
	.string "Excelente.\p"
	.string "Esta RADIO TOWER cumplirá nuestro\n"
	.string "gran diseño.$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichBeaten:
	.string "Hmmm...\p"
	.string "Todo gran plan tiene sus fallas.$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichAfter:
	.string "¿De verdad crees que puedes detener\n"
	.string "al TEAM ROCKET?$"

GoldenrodCity_RadioTower_4F4_Text_ProductionSign:
	.string "PRODUCCIÓN 4F$"

GoldenrodCity_RadioTower_4F4_Text_Studio2Sign:
	.string "ESTUDIO 4F 2$"
