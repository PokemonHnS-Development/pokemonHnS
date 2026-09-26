.set LOCALID_CAPT_STERN, 1
.set LOCALID_ARCHIE, 2
.set LOCALID_GRUNT_1, 3
.set LOCALID_GRUNT_2, 4

SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_GRUNT_1
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_GRUNT_2
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_TODD, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_TOM, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_ARCHIE
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_GARBAGEFLAG
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_GOODS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	removeobject LOCALID_CAPT_STERN
	setflag FLAG_GARBAGEFLAG
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "¿Sí? Si buscas a STERN,\n"
	.string "ese soy yo.\p"
	.string "¡Ah! Deben ser las piezas que pedí\n"
	.string "al SR. STONE de DEVON.\p"
	.string "¡Gracias! ¡Genial!\n"
	.string "Ya podemos preparar la expedición.$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "Jejeje, ¡espera!\n"
	.string "¡Nos llevamos esas piezas!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "CAPT. STERN: ¿Qu-qué?\n"
	.string "¿Quiénes son ustedes?$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "¡Somos el TEAM AQUA!\p"
	.string "¡El JEFE quiere esas piezas!\n"
	.string "¡Cállate y entrégalas ya!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "¡Awaaaah!\n"
	.string "¡Un niño me venció!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "Cielos, qué desastre...\n"
	.string "El JEFE se pondrá furioso...$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "¡Hmph, debilucho llorón!\n"
	.string "¡Déjame encargarme yo!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "¡¿Qué?!\n"
	.string "¡Yo también perdí!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "¿Y ahora qué? Si no conseguimos las\n"
	.string "piezas, ¡estaremos mal!\p"
	.string "¡Grrr, no esperaba que un niño\n"
	.string "metiche se interpusiera!$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "Vine a ver por qué tardaban\n"
	.string "tanto en robar piezas, ¿y ustedes\l"
	.string "están frenados por un niño?$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "Somos el TEAM AQUA,\n"
	.string "¡y amamos el mar!\p"
	.string "Y yo soy el líder del TEAM AQUA,\n"
	.string "¡ARCHIE!\p"
	.string "¿Por qué interfieres con nosotros?\p"
	.string "…¡No! ¡No puede ser!\n"
	.string "¿No eres del TEAM MAGMA?\p"
	.string "Espera, eso no puede estar bien.\n"
	.string "No vistes para el papel.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "POKéMON, personas… Toda la vida\n"
	.string "depende del mar.\p"
	.string "Así que el TEAM AQUA se dedica a\n"
	.string "expandir el mar.\p"
	.string "¿No estás de acuerdo? Lo que hacemos\n"
	.string "es una obra magnífica.\p"
	.string "Ah, está bien…\n"
	.string "Eres muy joven para entender\l"
	.string "nuestro noble objetivo.\p"
	.string "Pero te advierto, ni consideres\n"
	.string "estorbar nuestros planes otra vez.\p"
	.string "¡Las consecuencias te costarán\n"
	.string "muy caro!\p"
	.string "¡Y no lo olvides!$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "CAP. STERN: Eres...\n"
	.string "Ah, ya veo, eres {PLAYER}{KUN}...\p"
	.string "¡En fin, fue una situación tensa!\n"
	.string "¡Gracias por salvarnos!\p"
	.string "Oh, sí, casi olvido que incluso\n"
	.string "trajiste las piezas de DEVON!$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "CAP. STERN: ¡Vaya!\n"
	.string "¡No hay tiempo que perder!\p"
	.string "Debemos partir pronto en nuestra\n"
	.string "expedición submarina.\p"
	.string "Gracias de nuevo, ¡pero ahora\n"
	.string "debo irme!\p"
	.string "Puedes pasear y revisar nuestras\n"
	.string "instalaciones mientras tanto.$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "Vi una maqueta de un barco aquí.\p"
	.string "Me recordó al BARCO ABANDONADO\n"
	.string "cerca de PUEBLO ARTEMISA…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "¡No te atrevas a correr dentro\n"
	.string "del MUSEO!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "¡Guau, el submarino es genial!\n"
	.string "¡Quiero dar un paseo!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "“MUESTRA DE AGUA 1”, dice la\n"
	.string "etiqueta.\p"
	.string "El mar está conectado, pero el\n"
	.string "agua varía según la región.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "“MUESTRA DE AGUA 2”, dice la\n"
	.string "etiqueta.\p"
	.string "¿La salinidad del mar también varía\n"
	.string "según la región?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "Una pelota de goma se expande y\n"
	.string "se encoge.\p"
	.string "“En el mar, el peso del agua misma\n"
	.string "ejerce presión.\p"
	.string "“En aguas bajas, la presión no es\n"
	.string "muy fuerte.\p"
	.string "“Pero en aguas muy profundas,\n"
	.string "la presión puede llegar a miles de\l"
	.string "toneladas en un área pequeña.”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "“MODELO DE LA REGIÓN de HOENN”\p"
	.string "Es un diorama en miniatura de la\n"
	.string "región de HOENN.\p"
	.string "¿Dónde está PUEBLO RAÍZ aquí?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "Es una muestra del flujo del mar.\p"
	.string "“Cerca del fondo marino, el agua\n"
	.string "fluye por factores como la\l"
	.string "temperatura y la salinidad.”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "Es una muestra del flujo marino.\p"
	.string "“Hacia la superficie, el agua fluye\n"
	.string "en corrientes impulsadas por viento.”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "“EL FERRY S.S. TIDAL\p"
	.string "“Réplica a escala del barco en\n"
	.string "construcción en el ASTILLERO STERN.”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "“SUBMARINO EXPLORADOR 1\p"
	.string "“Réplica del submarino de alto\n"
	.string "rendimiento para explorar el fondo.”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "“CÁPSULA SUMERGIBLE\p"
	.string "“Réplica de una cápsula compacta\n"
	.string "sin tripulación para el fondo.”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "“S.S. ANNE\p"
	.string "“Réplica del crucero de lujo que\n"
	.string "recorre todo el mundo.”$"

