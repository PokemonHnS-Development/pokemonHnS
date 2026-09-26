.set LOCALID_GOLDENROD_ROCKET_SCOUT, 11

GoldenrodCity_MapScripts::
	.byte 0

GoldenrodCity_EventScript_Trigger:: @flagheap
	call_if_unset FLAG_SHOWN_ELM_TOGEPI, GoldenrodCity_Elm_Togepi_Call
	setflag FLAG_VISITED_GOLDENROD_CITY
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	setflag FLAG_HIDE_GOLDENROD_BILL
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	setflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	
	clearflag FLAG_HIDE_GOLDENROD_BEAUTY
	clearflag FLAG_HIDE_GOLDENROD_ROCKET_SCOUT
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	clearflag FLAG_GOT_RETURN
	clearflag FLAG_GOT_FRUSTRATION
	clearflag FLAG_RECEIVED_BIKE
	clearflag FLAG_RECEIVED_SQUIRTBOTTLE
	clearflag FLAG_GOT_EEVEE
	clearflag FLAG_SYS_PC_BILL
	clearflag FLAG_RETURNED_MACHINE_PART
	clearflag FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
	clearflag FLAG_GOLDENROD_MACHOKE_1
	clearflag FLAG_GOLDENROD_MACHOKE_2
	clearflag FLAG_GOLDENROD_MACHOKE_3
	clearflag FLAG_COMPLETED_SWITCHES
	clearflag FLAG_ENABLE_RADIO
	clearflag FLAG_KANTO_RADIO_GOT
	clearflag FLAG_GOLDENROD_NPC_TRADE_COMPLETED
	clearflag FLAG_GOT_SKILL_SWAP
	clearflag FLAG_HIDE_RADIOTOWER_GATE
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	clearflag FLAG_GOT_MARY_BRIGHT_POWDER
	clearflag FLAG_GOT_QUICK_CLAW
	clearflag FLAG_GOT_MAGNET

	setvar VAR_BUG_CONTEST_STATE, 0
	setvar VAR_KENYA, 0
	setvar VAR_LUGIA_OR_HOOH, 0
	setvar VAR_TRAIN, 0
	setvar VAR_ELEVATOR, 0
	setvar VAR_GOLDENROD_CITY_STATE, 1
	release
	end

GoldenrodCity_Trigger_Music::
	goto_if_lt VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_Trigger_MusicNotYet
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 11, GoldenrodCity_Trigger_MusicNotYet
	playbgm MUS_HG_ROCKET_TAKEOVER, TRUE
	setvar VAR_TEMP_0, 1 
	end

GoldenrodCity_Trigger_MusicNotYet::
	setvar VAR_TEMP_0, 1
	end

GoldenrodCity_Elm_Togepi_Call::
	lock
	pokenavcall GoldenrodCity_Text_ElmCall
	waitmessage
	delay 30
	release
	return

GoldenrodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Youngster::
	msgbox GoldenrodCity_Text_Youngster1, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Youngster2::
	msgbox GoldenrodCity_Text_Youngster2, MSGBOX_NPC
	end

GoldenrodCity_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_GOLDENROD_ROCKET_SCOUT, GoldenrodCity_EventScript_CooltrainerFCleared
	msgbox GoldenrodCity_Text_CooltrainerF1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_CooltrainerFCleared::
	msgbox GoldenrodCity_Text_CooltrainerF1_Cleared, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_NameRaterSign::
	msgbox GoldenrodCity_Text_NameRaterSign, MSGBOX_SIGN
	end

GoldenrodCity_EventScript_RocketScout::
	lock
	msgbox GoldenrodCity_Text_RocketScout1, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROCKET_SCOUT, Common_Movement_ExclamationMark
	delay 20
	faceplayer
	msgbox GoldenrodCity_Text_RocketScout2, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROCKET_SCOUT, DIR_NORTH
	release
	end

GoldenrodCity_EventScript_Rocket1::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket2::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket3::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket4::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket5::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket5, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket6::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket6, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Woman::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_DAY_POKEMON, GoldenrodCity_EventScript_Hiker2
	msgbox GoldenrodCity_Text_HikerDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker2::
	msgbox GoldenrodCity_Text_HikerNight, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Snubbull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SNUBBULL, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_Snubbull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_Mime::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MR_MIME, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_MrMime, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_SignUnderground::
	lock
	msgbox GoldenrodCity_Text_UndergroundSouthSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignDept::
	lock
	msgbox GoldenrodCity_Text_DeptStoreSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignBike::
	lock
	msgbox GoldenrodCity_Text_BikeShopSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignTrain::
	lock
	msgbox GoldenrodCity_Text_StationSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignGym::
	lock
	msgbox GoldenrodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignFlower::
	lock
	msgbox GoldenrodCity_Text_FlowerShopSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignRadio::
	lock
	msgbox GoldenrodCity_Text_RadioTowerSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignGameCorner::
	lock
	msgbox GoldenrodCity_Text_GameCornerSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_Beauty::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Beauty:
	.string "¡Es el GIMNASIO de CIUDAD TRIGAL!\p"
	.string "La líder WHITNEY no está aquí\n"
	.string "ahora. Tal vez esté en la\l"
	.string "TORRE RADIO.$"

GoldenrodCity_Text_Woman:
	.string "Entrenaba en el GIMNASIO de WHITNEY,\n"
	.string "pero sus llantos me daban\l"
	.string "dolor de cabeza.$"

GoldenrodCity_Text_HikerDay:
	.string "Entré al GAME CORNER de día\n"
	.string "y al salir era de noche... ¡¿Cuánto\l"
	.string "tiempo estuve ahí?!$"

GoldenrodCity_Text_HikerNight:
	.string "Entré al GAME CORNER de noche\n"
	.string "y al salir era de día... ¡¿Cuánto\l"
	.string "tiempo estuve ahí?!$"

GoldenrodCity_Text_Snubbull:
	.string "SNUBBULL: ¡SNUUUBUUUULL!$"

GoldenrodCity_Text_MrMime:
	.string "............................$"

GoldenrodCity_Text_ElmCall:
	.string "PROF.ELM: ¡Hola, {PLAYER}?\n"
	.string "¿Ya nació ese HUEVO?\p"
	.string "Cuando nazca, ¡no olvides\n"
	.string "traerlo al lab! ¡Necesito\l"
	.string "verlo!$"

GoldenrodCity_Text_PokefanM:
	.string "Hicieron la nueva TORRE RADIO\n"
	.string "para reemplazar la vieja y ruin.$"

GoldenrodCity_Text_Youngster1:
	.string "Sé que hay una nueva TIENDA DE BIKES,\n"
	.string "pero no la encuentro por ningún lado.$"

GoldenrodCity_Text_CooltrainerF1:
	.string "Ese hombre de negro ¿está vestido\n"
	.string "como el TEAM ROCKET?\p"
	.string "¡Qué tonto!$"

GoldenrodCity_Text_CooltrainerF1_Cleared:
	.string "¿Ese hombre de negro era del\n"
	.string "TEAM ROCKET? ¡No lo puedo creer!$"

GoldenrodCity_Text_CooltrainerF2:
	.string "La TORRE RADIO de CIUDAD TRIGAL\n"
	.string "es un gran monumento.\p"
	.string "Tienen una campaña ahora.\p"
	.string "Te darán una RADIO nueva si\n"
	.string "pasas su cuestionario.$"

GoldenrodCity_Text_CooltrainerF2_GotCard:
	.string "¡Oh, tu POKéGEAR ya funciona\n"
	.string "como una radio!$"

GoldenrodCity_Text_Youngster2:
	.string "Je-je-je-je…\p"
	.string "Me regañaron por jugar en el\n"
	.string "sótano del CENTRO COMERCIAL.$"

GoldenrodCity_Text_Lass:
	.string "El hombre de ahí califica los\n"
	.string "apodos de tus POKéMON.\p"
	.string "¡Incluso puede cambiarlos!$"

GoldenrodCity_Text_Gramps:
	.string "¡Uff! Este pueblo es tan grande\n"
	.string "que no encuentro nada.$"

GoldenrodCity_Text_RocketScout1:
	.string "Así que esta es la RADIO TOWER…$"

GoldenrodCity_Text_RocketScout2:
	.string "¿Qué quieres, plaga?\n"
	.string "¡Lárgate ya!$"

GoldenrodCity_Text_Rocket1:
	.string "¡No estorbes!\n"
	.string "¡Fuera de aquí, niño!$"

GoldenrodCity_Text_Rocket2:
	.string "Tomar la TORRE RADIO…\p"
	.string "¿Qué? ¡No es asunto tuyo!$"

GoldenrodCity_Text_Rocket3:
	.string "¿POKéMON? Solo son herramientas\n"
	.string "¡para ganar dinero!$"

GoldenrodCity_Text_Rocket4:
	.string "Nuestro sueño se hará realidad…\p"
	.string "Fue una lucha larga y dura…$"

GoldenrodCity_Text_Rocket5:
	.string "¡Oye, mocoso! No perteneces aquí\n"
	.string "¡Lárgate de una vez!$"

GoldenrodCity_Text_Rocket6:
	.string "¡Ven y prueba el terror del\n"
	.string "TEAM ROCKET!$"

GoldenrodCity_Text_StationSign:
	.string "ESTACIÓN DE CIUDAD TRIGAL$"

GoldenrodCity_Text_RadioTowerSign:
	.string "TORRE RADIO DE CIUDAD TRIGAL$"

GoldenrodCity_Text_DeptStoreSign:
	.string "¡Toda clase de artículos POKéMON!\p"
	.string "ALMACENES DE CIUDAD TRIGAL$"

GoldenrodCity_Text_GymSign:
	.string "GIMNASIO POKéMON DE CIUDAD TRIGAL\n"
	.string "LÍDER: WHITNEY\p"
	.string "¡La chica increíblemente linda!$"

GoldenrodCity_Text_CitySign:
	.string "CIUDAD TRIGAL\p"
	.string "Ciudad festiva de encanto opulento$"

GoldenrodCity_Text_BikeShopSign:
	.string "¡El mundo es una ciclovía!\n"
	.string "TIENDA DE BICICLETAS$"

GoldenrodCity_Text_GameCornerSign:
	.string "¡Tu lugar de juegos!\p"
	.string "CASINO DE CIUDAD TRIGAL$"

GoldenrodCity_Text_NameRaterSign:
	.string "CALIFICADOR DE NOMBRES\p"
	.string "Califica los apodos de tus POKéMON$"

GoldenrodCity_Text_UndergroundNorthSign:
	.string "ENTRADA AL SUBTERRÁNEO$"

GoldenrodCity_Text_UndergroundSouthSign:
	.string "ENTRADA SUBTERRÁNEA$"


GoldenrodCity_Text_FlowerShopSign:
	.string "FLORERÍA BLOOMING BEAUTIFUL$"

GoldenrodCity_Text_MoveTutorAsk:
	.string "¡Puedo enseñar a tu POKéMON\n"
	.string "movimientos increíbles!\p"
	.string "¿Quieres aprender uno?$"

GoldenrodCity_Text_MoveTutorCost:
	.string "Te costará 1000 monedas.\n"
	.string "¿Está bien?$"

GoldenrodCity_Text_MoveTutorDecline:
	.string "Ay… ¡Pero estos ataques son geniales!$"

GoldenrodCity_Text_MoveTutorWhich:
	.string "¡Jajaja! ¡No te arrepentirás!\p"
	.string "¿Qué movimiento enseño?$"

GoldenrodCity_Text_MoveTutorNoCash:
	.string "Qué mal. Tendré que ir a casa\n"
	.string "por más dinero...$"

GoldenrodCity_Text_MoveTutorUnderstand:
	.string "Si entiendes este movimiento,\n"
	.string "ya eres un gran entrenador.$"

GoldenrodCity_Text_MoveTutorFarewell:
	.string "¡Jajaja! ¡Adiós, niño!$"

GoldenrodCity_Text_MoveTutorBut:
	.string "P-pero...$"

GoldenrodCity_Text_MoveTutorNotEnoughCoins:
	.string "...No tienes suficientes monedas...$"
