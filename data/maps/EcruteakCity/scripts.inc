.set LOCALID_ECRUTEAK_GRAMPS, 4
.set LOCALID_ECRUTEK_SILVER, 33

EcruteakCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

EcruteakCity_OnTransition::
	callnative SetTimeBasedEncounters
	end

EcruteakCity_Test_Lugia::
	setvar VAR_LUGIA_OR_HOOH, 1
	end
EcruteakCity_Test_League::
	setvar VAR_COMPLETED_HO_OH, 4
	setvar VAR_COMPLETED_LUGIA, 4
	end


EcruteakCity_EventScript_Trigger::
	@flagheap
	clearflag FLAG_RELEASED_BEASTS
	clearflag FLAG_AMPHAROS_HEALED
	clearflag FLAG_HIDE_ECRUTEAK_BILL
	clearflag FLAG_DEFEATED_HO_OH
	clearflag FLAG_CAUGHT_HO_OH
	clearflag FLAG_DEFEATED_LUGIA
	clearflag FLAG_CAUGHT_LUGIA
	clearflag FLAG_HIDE_ECRUTEAK_ROCKET
	clearflag FLAG_HIDE_BURNED_TOWER_NPCS  
	clearflag FLAG_HIDE_BURNED_TOWER_BEASTS
	clearflag FLAG_HIDE_BURNED_TOWER_B1F_EUSINE
	clearflag FLAG_HIDE_ECRUTEAK_CITY_SAGE
	clearflag FLAG_CAUGHT_ENTEI
	clearflag FLAG_CAUGHT_RAIKOU
	clearflag FLAG_GOT_TM_SNATCH
	clearflag FLAG_HIDE_ROUTE42_SUICUNE
	clearflag FLAG_GOT_TYROGUE
	clearflag FLAG_BEAT_KIYO
	clearflag FLAG_ENABLE_BAOBA_MATCH_CALL
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag FLAG_HIDE_TINTOWER_GUARD
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	clearflag FLAG_HIDE_LUGIA
	clearflag FLAG_HIDE_HO_OH

	setflag FLAG_VISITED_ECRUTEAK_CITY
	setflag FLAG_HIDE_ROUTE42_EUSINE

	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	setflag FLAG_HIDE_ROUTE39_SHADOW
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setvar VAR_COMPLETED_HO_OH, 0
	setvar VAR_COMPLETED_LUGIA, 0
	setvar VAR_ECRUTEAK_CITY_THEATER, 0 
	setvar VAR_ECRUTEAK_CITY_STATE, 1
	end

EcruteakCity_Trigger_Silver::
	lockall
	opendoor 39, 40
	waitdooranim
	delay 10
	clearflag FLAG_HIDE_ECRUTEAK_SILVER
	addobject LOCALID_ECRUTEK_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	playse SE_BANG
	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver1
	applymovement OBJ_EVENT_ID_PLAYER, EcruteakCity_Movement_Silver1
	message EcruteakCity_Text_Silver1
	
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_ECRUTEK_SILVER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	closedoor 39, 40
	waitdooranim
	msgbox EcruteakCity_Text_Silver2, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ECRUTEK_SILVER, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_ECRUTEK_SILVER, DIR_SOUTH
	msgbox EcruteakCity_Text_Silver3, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver2
	waitmovement LOCALID_ECRUTEK_SILVER


	setflag FLAG_HIDE_ECRUTEAK_SILVER
	removeobject LOCALID_ECRUTEK_SILVER
	fadedefaultbgm

	setvar VAR_ECRUTEAK_CITY_THEATER, 5
	releaseall
	end

EcruteakCity_Movement_Silver1:
	delay_16
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

EcruteakCity_Movement_Silver2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

EcruteakCity_Text_Silver1:
	.string "¡BUM!!$"

EcruteakCity_Text_Silver2:
	.string "{RIVAL}: ¿Cómo...? ¿Cómo es\n"
	.string "posible? ¿Cómo puedo perder contra\l"
	.string "unas KIMONO GIRLS...?$"

EcruteakCity_Text_Silver3:
	.string "{RIVAL}: Me estabas viendo,\n"
	.string "{PLAYER}...\p"
	.string "¡Sí, así es!\p"
	.string "No creí que vencer a cinco\n"
	.string "KIMONO GIRLS fuera tan difícil...\p"
	.string "Me dieron una paliza...\p"
	.string "...\p"
	.string "Seguro viniste por la misma\n"
	.string "razón, ¿verdad?\p"
	.string "¡No te creas mucho solo por\n"
	.string "vencer al TEAM ROCKET!\p"
	.string "Estas KIMONO GIRLS son\n"
	.string "increíblemente fuertes.\p"
	.string "Mira si puedes vencerlas.\p"
	.string "Pero no volveré, no quiero\n"
	.string "verte ganar.$"

EcruteakCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps1, MSGBOX_DEFAULT
	closemessage
	release
	end
		
EcruteakCity_EventScript_Lass::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RELEASED_BEASTS, EcruteakCity_EventScript_Girl2
	msgbox EcruteakCity_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl2::
	msgbox EcruteakCity_Text_Lass2_ReleasedBeasts, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man::
	lock
	faceplayer
	goto_if_set FLAG_AMPHAROS_HEALED, EcruteakCity_EventScrip_Man2
	msgbox EcruteakCity_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man2::
	msgbox EcruteakCity_Text_Fisher_JasmineReturned, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageRight::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageTower::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps3, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageGym::
	lock
	faceplayer
	msgbox EcruteakCity_Text_SageGym, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_TheaterSign::
	lock
	msgbox EcruteakCity_Text_DanceTheaterSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_OfficeSign::
	lock
	msgbox EcruteakCity_Text_OfficeSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_BurnedSign::
	lock
	msgbox EcruteakCity_Text_BurnedTowerSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_CitySign::
	lock
	msgbox EcruteakCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_GymSign::
	lock
	msgbox EcruteakCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_Eevee::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Eevee, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Vulpix::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VULPIX, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Vulpix, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

EcruteakCity_Text_Eevee:
	.string "EEVEE: ¡Veee!$"

EcruteakCity_Text_Vulpix:
	.string "VULPIX: ¡Vullll Pix!$"


EcruteakCity_Text_UnusedMissingDaughter:
	.string "Oh, no. Oh, no…\p"
	.string "Mi hija ha desaparecido.\p"
	.string "No… No puede haber ido a la\n"
	.string "TORRE QUEMADA.\p"
	.string "Le dije que no se acercara…\p"
	.string "La gente desaparece allí…\p"
	.string "Oh, ¿qué debo hacer…?$"

EcruteakCity_Text_Gramps1:
	.string "CIUDAD IRIS tenía dos torres:\n"
	.string "una al este y otra al oeste.$"

EcruteakCity_Text_Gramps2:
	.string "Ah, niño. ¿Ya aprendiste a\n"
	.string "bailar como las KIMONO GIRLS?\p"
	.string "Si vas a su TEATRO DE DANZA,\n"
	.string "un viejo extraño te dará\l"
	.string "algo bueno, según oí.$"

EcruteakCity_Text_Lass1:
	.string "Iré a practicar al TEATRO DE\n"
	.string "BAILE. ¿Quieres venir?$"

EcruteakCity_Text_Lass2:
	.string "La torre que había aquí...\p"
	.string "Mi abuela decía que antes era\n"
	.string "mucho más alta.\p"
	.string "Dicen que ahora hay fantasmas.$"

EcruteakCity_Text_Lass2_ReleasedBeasts:
	.string "Tres POKéMON grandes huyeron en\n"
	.string "distintas direcciones. ¿Qué eran?$"

EcruteakCity_Text_Fisher:
	.string "Oí un rumor sobre el FARO de\n"
	.string "CIUDAD OLIVO.\p"
	.string "El POKéMON que sirve de guía\n"
	.string "enfermó. Parece que están\l"
	.string "en problemas.$"

EcruteakCity_Text_Fisher_JasmineReturned:
	.string "El POKéMON del FARO DE OLIVO\n"
	.string "ya se curó.\p"
	.string "Los barcos ya pueden navegar\n"
	.string "seguros de noche.$"

EcruteakCity_Text_Youngster:
	.string "Oigo que hay POKéMON furiosos en el\n"
	.string "LAGO DE la FURIA. Quiero verlo.$"

EcruteakCity_Text_Gramps3:
	.string "En el pasado remoto...\p"
	.string "Esta torre ardió en un fuego.\n"
	.string "Tres POKéMON murieron allí.\p"
	.string "Un POKéMON arcoíris bajó del\n"
	.string "cielo y los resucitó...\p"
	.string "Es una leyenda de los LÍDERES\n"
	.string "del GIMNASIO de CIUDAD IRIS.\p"
	.string "¿Yo?\p"
	.string "Fui entrenador hace mucho.\n"
	.string "¡Jo, jo, jo!$"

EcruteakCity_Text_SageGym:
	.string "El LÍDER MORTY no está ahora.\n"
	.string "Tal vez esté en la\l"
	.string "TORRE QUEMADA.$"

EcruteakCity_Text_Sign:
	.string "CIUDAD IRIS\n"
	.string "Ciudad Histórica\p"
	.string "Donde el pasado se une al presente$"

EcruteakCity_Text_TinTowerSign:
	.string "TORRE CAMPANA\p"
	.string "Dicen que un POKéMON legendario\n"
	.string "anida aquí.$"

EcruteakCity_Text_OfficeSign:
	.string "Estación de Barrera a TORRE CAMPANA\p"
	.string "Prohibido el paso a los indignos.$"

EcruteakCity_Text_GymSign:
	.string "GIMNASIO de CIUDAD IRIS\n"
	.string "LÍDER: MORTY\p"
	.string "El vidente místico del futuro$"

EcruteakCity_Text_DanceTheaterSign:
	.string "TEATRO DE DANZA DE CIUDAD IRIS$"

EcruteakCity_Text_BurnedTowerSign:
	.string "TORRE QUEMADA\p"
	.string "Fue destruida por un fuego\n"
	.string "misterioso.\p"
	.string "Aléjate, ya que es peligroso.$"
