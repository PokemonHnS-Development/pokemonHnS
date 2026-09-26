FuchsiaCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_EventScript_CityEnter
	.byte 0

FuchsiaCity_OnFrame::
	map_script_2 VAR_FUCHSIA_CITY_STATE, 0,  FuchsiaCity_EventScript_BaobaCall
	.2byte 0

FuchsiaCity_EventScript_CityEnter::
	setflag FLAG_VISITED_FUCHSIA_CITY
	end

FuchsiaCity_EventScript_BaobaCall::
	pokenavcall FuchsiaCity_Text_Baoba
	waitmessage
	delay 30
	setvar VAR_BAOBA_QUEST_STATE, 1
	setvar VAR_FUCHSIA_CITY_STATE, 1
	end

FuchsiaCity_Text_Baoba:
	.string "GUARDIA BAOBA: {PLAYER}!\p"
	.string "Soy el GUARDIA BAOBA.\p"
	.string "¡Ha pasado algo terrible!\n"
	.string "¡Mi antigua SAFARI ZONE en\l"
	.string "CIUDAD FUCHSIA fue comprada!\p"
	.string "¡Y al parecer tiene nuevos\n"
	.string "POKéMON exóticos!\p"
	.string "¡Daña mi negocio!\p"
	.string "{PLAYER}, ve a la nueva SAFARI ZONE\n"
	.string "y atrapa un POKéMON para mí.\l"
	.string "Debo saber sobre esos POKéMON\l"
	.string "exóticos.\p"
	.string "¡{PLAYER}, mi negocio depende\n"
	.string "de ti!$"

FuchsiaCity_EventScript_Dratini::
	lock
	showmonpic SPECIES_DRATINI, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kangaskhan::
	lock
	showmonpic SPECIES_KANGASKHAN, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Cubone::
	lock
	showmonpic SPECIES_CUBONE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Omanyte::
	lock
	showmonpic SPECIES_OMANYTE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kabuto::
	lock
	showmonpic SPECIES_KABUTO, 10, 3
	delay 60
	hidemonpic
	release
	end

FuchsiaCity_EventScript_Youngster::
	msgbox FuchsiaCity_Text_Youngster, MSGBOX_NPC
	end

FuchsiaCity_EventScript_PokefanM::
	msgbox FuchsiaCity_Text_PokefanM, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Teacher::
	msgbox FuchsiaCity_Text_Teacher, MSGBOX_NPC
	end

FuchsiaCity_EventScript_CitySign::
	msgbox FuchsiaCity_Text_Sign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_GymSign::
	msgbox FuchsiaCity_Text_GymSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariZone::
	msgbox FuchsiaCity_Text_SafariZone, MSGBOX_NPC
	end

FuchsiaCity_Text_Youngster:
	.string "Uno del ELITE FOUR fue alguna vez\n"
	.string "el LÍDER del GIMNASIO de FUCHSIA.$"

FuchsiaCity_Text_PokefanM:
	.string "La hija de KOGA lo sucedió como\n"
	.string "LÍDER del GIMNASIO al unirse él\l"
	.string "al ELITE FOUR.$"

FuchsiaCity_Text_Teacher:
	.string "La SAFARI ZONE tiene nueva\n"
	.string "administración.\p"
	.string "¡Y tiene muchos POKéMON nuevos!$"

FuchsiaCity_Text_Sign:
	.string "CIUDAD FUCHSIA\p"
	.string "¡Mira! ¡Es Rosa Pasión!$"

FuchsiaCity_Text_GymSign:
	.string "GIMNASIO POKéMON CIUDAD FUCHSIA\n"
	.string "LÍDER: JANINE\p"
	.string "La Maestra Ninja Venenosa$"

FuchsiaCity_Text_SafariZoneOfficeSign:
	.string "Hay un aviso aquí...\p"
	.string "La OFICINA SAFARI ZONE estará\n"
	.string "cerrada hasta nuevo aviso.$"

FuchsiaCity_Text_SafariZone:
	.string "SAFARI ZONE\n"
	.string "AHORA PROPIEDAD DE\l"
	.string "DEVON CORP.$"

FuchsiaCity_Text_SafariZoneClosedSign:
	.string "El GUARDIA viaja al extranjero.\p"
	.string "Por eso, la ZONA SAFARI está\n"
	.string "cerrada.$"

FuchsiaCity_Text_NoLitteringSign:
	.string "No tires basura.\p"
	.string "Lleva tus desechos contigo.$"

