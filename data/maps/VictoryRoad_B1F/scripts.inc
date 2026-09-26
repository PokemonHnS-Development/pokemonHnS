VictoryRoad_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_TRANSITION, SetTimeEncounters
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_PRYCE_1, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
	.string "Pensar que estoy más cerca de la\n"
	.string "LIGA POKéMON...\p"
	.string "Me dan nervios...$"

VictoryRoad_B1F_Text_SamuelDefeat:
	.string "No pude hacer nada...$"

VictoryRoad_B1F_Text_SamuelPostBattle:
	.string "La LIGA POKéMON se alejó de nuevo...\n"
	.string "Qué decepción...$"

VictoryRoad_B1F_Text_ShannonIntro:
	.string "Para ganar en la LIGA POKéMON,\n"
	.string "necesitas la confianza de tus\l"
	.string "POKéMON.$"

VictoryRoad_B1F_Text_ShannonDefeat:
	.string "Su relación se basa en una\n"
	.string "confianza sólida.$"

VictoryRoad_B1F_Text_ShannonPostBattle:
	.string "Al estar siempre juntos, la confianza\n"
	.string "crece entre POKéMON y ENTRENADORES.$"

VictoryRoad_B1F_Text_MichelleIntro:
	.string "Esta no es la meta. Es solo un lugar\n"
	.string "camino a la LIGA POKéMON.$"

VictoryRoad_B1F_Text_MichelleDefeat:
	.string "¡Así se hace!$"

VictoryRoad_B1F_Text_MichellePostBattle:
	.string "¡Te irá bien, seguro!\n"
	.string "¡Tus POKéMON están ansiosos!$"

VictoryRoad_B1F_Text_MitchellIntro:
	.string "¡Mis POKéMON son cósmicamente\n"
	.string "impresionantes!$"

VictoryRoad_B1F_Text_MitchellDefeat:
	.string "Nunca había conocido a alguien así.$"

VictoryRoad_B1F_Text_MitchellPostBattle:
	.string "Aun sin luchar, siento un poder\n"
	.string "increíble emanando de ti\l"
	.string "y de tus POKéMON.$"

VictoryRoad_B1F_Text_HalleIntro:
	.string "¡Vale, no te pongas así!\n"
	.string "¡Relájate, vamos con calma!$"

VictoryRoad_B1F_Text_HalleDefeat:
	.string "¡Vaya!\n"
	.string "¡Maravilloso!$"

VictoryRoad_B1F_Text_HallePostBattle:
	.string "Sí, esta es la VIA VICTORIA.\p"
	.string "Pero no es tan distinta al\n"
	.string "camino que has seguido.\p"
	.string "¡Disfruta el resto del\n"
	.string "trayecto!$"

