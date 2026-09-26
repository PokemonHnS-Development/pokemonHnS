LavenderTown_RadioStation_MapScripts::
	.byte 0

LavenderTown_RadioStation_EventScript_Officer::
	msgbox LavenderTown_RadioStation_Text_Officer, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Receptionist::
	msgbox LavenderTown_RadioStation_Text_Receptionist, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_SuperNerd::
	msgbox LavenderTown_RadioStation_Text_SuperNerd1, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Director::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_RADIO_GOT, LavenderTown_RadioStation_EventScript_DirectorGotRadio
	goto_if_set FLAG_RETURNED_MACHINE_PART, LavenderTown_RadioStation_EventScript_DirectorReturnedMachinePart
	msgbox LavenderTown_RadioStation_Text_Gentleman, MSGBOX_NPC
	end
LavenderTown_RadioStation_EventScript_DirectorReturnedMachinePart::
	msgbox LavenderTown_RadioStation_Text_Gentleman_ReturnedMachinePart, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox LavendertownRadioStation_Text_Upgraded_Radio, MSGBOX_DEFAULT
	waitfanfare
	msgbox LavenderTown_RadioStation_Text_Gentleman_GotExpnCard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_KANTO_RADIO_GOT
	release
	end
LavenderTown_RadioStation_EventScript_DirectorGotRadio::	
	msgbox LavenderTown_RadioStation_Text_Gentleman_GotExpnCard, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Host::
	goto_if_set FLAG_KANTO_RADIO_GOT, LavenderTown_RadioStation_EventScript_Host2
	msgbox LavenderTown_RadioStation_Text_SuperNerd2, MSGBOX_NPC
	end
LavenderTown_RadioStation_EventScript_Host2::
	msgbox LavenderTown_RadioStation_Text_SuperNerd2_GotExpnCard, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Directory::
	msgbox LavenderTown_RadioStation_Text_Directory, MSGBOX_SIGN
	end
LavenderTown_RadioStation_EventScript_Sign::
	msgbox LavenderTown_RadioStation_Text_PokeFluteSign, MSGBOX_SIGN
	end
LavenderTown_RadioStation_EventScript_Library::
	msgbox LavenderTown_RadioStation_Text_ReferenceLibrary, MSGBOX_SIGN
	end

LavenderTown_RadioStation_Text_Receptionist:
	.string "¡Bienvenido! Siéntete libre de mirar\n"
	.string "por todo este piso.$"

LavenderTown_RadioStation_Text_Officer:
	.string "Lo siento, solo puedes recorrer la\n"
	.string "planta baja.\p"
	.string "Desde que la RADIO TOWER de JOHTO\n"
	.string "fue tomada por una banda criminal,\l"
	.string "tuvimos que reforzar nuestra\l"
	.string "seguridad.$"

LavenderTown_RadioStation_Text_SuperNerd1:
	.string "Mucha gente trabaja duro aquí\n"
	.string "en la RADIO TOWER.\p"
	.string "Deben estar dando lo mejor de sí\n"
	.string "para dar buenos shows.$"

LavenderTown_RadioStation_Text_Gentleman:
	.string "¡Oh, no, no, no!\p"
	.string "Estamos fuera del aire desde que\n"
	.string "la CENTRAL ELÉCTRICA cerró.\p"
	.string "Todo mi esfuerzo por abrir esta\n"
	.string "estación sería inútil si no puedo\l"
	.string "transmitir.\p"
	.string "¡Estaré arruinado!$"

LavenderTown_RadioStation_Text_Gentleman_ReturnedMachinePart:
	.string "¡Ah! ¿Tú eres {PLAYER}, quien\n"
	.string "arregló la CENTRAL ELÉCTRICA?\p"
	.string "Gracias a ti, no perdí mi\n"
	.string "empleo.\p"
	.string "¡Te digo que me has salvado\n"
	.string "la vida!\p"
	.string "Toma esto como agradecimiento.$"

LavendertownRadioStation_Text_Upgraded_Radio:
	.string "{PLAYER} obtuvo la\n"
	.string "MEJORA DE RADIO!$"

LavenderTown_RadioStation_Text_Gentleman_GotExpnCard:
	.string "Con eso puedes sintonizar los\n"
	.string "programas de radio aquí en KANTO.\p"
	.string "¡Gahahahaha!$"

LavenderTown_RadioStation_Text_SuperNerd2:
	.string "¡Hola!\p"
	.string "¡Soy el súper DIRECTOR MUSICAL!\p"
	.string "¿Eh? Tu RADIO no sintoniza mis\n" @POKéGEAR
	.string "programas. ¡Qué mala suerte!\p"
	.string "Si consigues una EXPN CARD,\n"
	.string "podrás sintonizar. ¡Mejor busca\l"
	.string "una!$"

LavenderTown_RadioStation_Text_SuperNerd2_GotExpnCard:
	.string "¡Hola!\p"
	.string "¡Soy el súper DIRECTOR MUSICAL!\p"
	.string "Hago las hermosas melodías\n"
	.string "que salen al aire.\p"
	.string "No seas aburrido. ¡Sintoniza\n"
	.string "mi música!$"

LavenderTown_RadioStation_Text_Directory:
	.string "1F RECEPCIÓN 2F VENTAS\p"
	.string "3F PERSONAL 4F PRODUCCIÓN\p"
	.string "5F OFICINA DEL DIRECTOR$"

LavenderTown_RadioStation_Text_PokeFluteSign:
	.string "Anima a tu POKéMON con los\n"
	.string "sonidos de la POKé FLUTE en\l"
	.string "el CANAL 20$"

LavenderTown_RadioStation_Text_ReferenceLibrary:
	.string "¡Vaya! Un estante lleno de CDs\n"
	.string "y videos de POKéMON.\p"
	.string "Esta debe ser la biblioteca\n"
	.string "de referencia.$"

