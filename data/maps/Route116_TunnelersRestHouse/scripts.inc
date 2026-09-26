Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
	.string "Ese TÚNEL RUSTURF...\p"
	.string "Al inicio, tuvimos un gran equipo\n"
	.string "perforando la roca con maquinaria.\l"
	.string "Pero tuvimos que parar.\p"
	.string "Resulta que causaríamos un efecto\n"
	.string "negativo en los POKéMON salvajes\l"
	.string "de la zona.\p"
	.string "Así que no nos queda más que\n"
	.string "estar aquí sin hacer nada.$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
	.string "Hay un hombre cavando hacia\n"
	.string "VERDANTURF él solo.\l"
	.string "Está desesperado por pasar.\p"
	.string "Dice que si cava poco a poco\n"
	.string "sin máquinas, no molestará a los\l"
	.string "POKéMON ni dañará el medio\l"
	.string "ambiente natural.\p"
	.string "Me pregunto si ya lo logró.$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
	.string "Para ir a VERDANTURF sin usar\n"
	.string "este TÚNEL, tendrías que cruzar el\l"
	.string "mar a DEWFORD, ir a SLATEPORT\l"
	.string "y luego pasar por MAUVILLE.$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
	.string "¿Te enteraste? ¡El TÚNEL a\n"
	.string "VERDANTURF ya está terminado!\p"
	.string "A veces, si deseas algo con fuerza,\n"
	.string "los sueños se hacen realidad.$"

