.set LOCALID_TWIN, 2

VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_OLIVINE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_LickyEvo::
	msgbox VerdanturfTown_LickyEvo_Text, MSGBOX_NPC
	end

VerdanturfTown_LickyEvo_Text:
	.string "LICKITUNG evoluciona rodando.\n"
	.string "¡Intenta hacer eso!$"

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "Mi papá me lo contó.\p"
	.string "Dice que este túnel está lleno de\n"
	.string "POKéMON tímidos.\p"
	.string "Se asustan con ruidos fuertes y\n"
	.string "arman un gran alboroto.\p"
	.string "Por eso detuvieron el gran proyecto\n"
	.string "del túnel.\p"
	.string "Pero hay un hombre. ¡Intenta cavar\n"
	.string "el túnel él solo!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "Hubo un hombre que cavó un túnel por\n"
	.string "la mujer que amaba.\p"
	.string "No lo entiendo bien, ¡pero bueno!$"

VerdanturfTown_Text_AirCleanHere:
	.string "Por cómo sopla el viento, la ceniza\n"
	.string "volcánica nunca llega hacia acá.\p"
	.string "El aire es limpio y delicioso.\n"
	.string "Vivir aquí haría milagros incluso en\l"
	.string "gente débil y enferma.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "Mi POKéMON y yo llevamos una racha\n"
	.string "de victorias increíble.\p"
	.string "Así que decidí debutar con mi\n"
	.string "BATTLE TENT en este pueblo.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "¿Viste la cueva junto al\n"
	.string "POKéMON MART?\p"
	.string "Hay un tipo ahí intentando\n"
	.string "romper rocas para salir\l"
	.string "por el otro lado.\p"
	.string "Sería genial poder pasar...\n"
	.string "Sería fácil ir a RUSTBORO.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "La cueva junto al POKéMON MART\n"
	.string "ya es un túnel hacia el otro lado.\p"
	.string "Es genial, ahora es fácil comprar\n"
	.string "productos DEVON en RUSTBORO.$"

VerdanturfTown_Text_TownSign:
	.string "PUEBLO VERDANTURF\p"
	.string "“Tierras altas azotadas por el viento\n"
	.string "con dulce aroma a hierba.”$"

VerdanturfTown_Text_WandasHouse:
	.string "CASA DE WANDA$"

VerdanturfTown_Text_BattleTentSign:
	.string "TIENDA DE BATALLA VERDANTURF\n"
	.string "¡Mira estas batallas!$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "TÚNEL RUSTURF\n"
	.string "Une RUSTBORO y VERDANTURF\p"
	.string "El proyecto del túnel ha sido\n"
	.string "cancelado.$"

