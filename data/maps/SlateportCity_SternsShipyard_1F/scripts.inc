.set LOCALID_DOCK, 1

SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_GARBAGEFLAG
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
	.string "Umm... Si esto va aquí, y aquello\n"
	.string "va por allá...\p"
	.string "¿Entonces dónde va esta cosa?\n"
	.string "¿Y qué pasa con ese aparatito?\p"
	.string "¡Aaargh! ¡No entiendo nada\n"
	.string "de esto!$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
	.string " ¿Hm?\n"
	.string "Hola, soy DOCK.\p"
	.string "El CAPT. STERN me encargó\n"
	.string "diseñar un ferry.\p"
	.string "¡Oh! Eso de ahí...\n"
	.string "¿Son PRODUCTOS DEVON?\p"
	.string "Pero, hmm...\n"
	.string "Esto no servirá...\p"
	.string "El CAPT. STERN se fue a algún lado.\n"
	.string "Dijo que tenía trabajo que hacer.\p"
	.string "¿Podrías buscar al CAPT. STERN\n"
	.string "y entregárselo?$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
	.string "DOCK: ¿A dónde habrá ido el\n"
	.string "CAPT. STERN?\p"
	.string "¿Podrías buscar al CAPT. STERN y\n"
	.string "entregarle ese paquete?$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
	.string "DOCK: Construir barcos es un arte.\p"
	.string "Hay cosas que no se resuelven\n"
	.string "solo con cálculos.\p"
	.string "Me vendría bien el consejo de un\n"
	.string "veterano que conozca el mar…$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
	.string "DOCK: ¡Hola! El SR. BRINEY se unió\n"
	.string "para ayudarnos.\p"
	.string "Gracias al viejo marinero, el\n"
	.string "ferry va tomando forma.$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
	.string "DOCK: ¡El ferry ya está listo!\p"
	.string "¡El nuevo S.S. TIDAL es una maravilla\n"
	.string "tecnológica!\p"
	.string "Pero siento que podemos crear\n"
	.string "algo aún mejor.\p"
	.string "Ya sabes, la tecnología nunca\n"
	.string "deja de avanzar.$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "MR. BRINEY: ¡Ah, {PLAYER}{KUN}!\n"
	.string "¡Ha pasado mucho tiempo!\p"
	.string "¡Desde que te vi, este viejo lobo\n"
	.string "de mar se siente animado!\p"
	.string "Así que decidí ayudar a DOCK a\n"
	.string "hacer un ferry.\p"
	.string "Después de todo, un ferry podría\n"
	.string "llevar a mucha gente.\p"
	.string "Pero sabes, ese DOCK es realmente\n"
	.string "alguien especial.\p"
	.string "Con su don tecnológico y mi\n"
	.string "experiencia, seguro que\l"
	.string "haremos un gran barco, ¡sí!$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "Las estaciones, el clima, dónde\n"
	.string "está la luna en el cielo...\p"
	.string "Eso y otras condiciones hacen\n"
	.string "que el mar cambie su expresión.\p"
	.string "¡Así es!\n"
	.string "¡El mar es como un ser vivo!$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "Me mareo muy fácil en el mar.\n"
	.string "Así que ayudo aquí en su lugar.$"

