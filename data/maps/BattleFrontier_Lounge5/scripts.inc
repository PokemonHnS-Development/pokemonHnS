BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "¡Jeje!\n"
	.string "¡Sé qué piensan los POKéMON!\p"
	.string "¡Por favor!\n"
	.string "¿Puedo ver tus POKéMON?$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
	.string "¡Buu!\n"
	.string "¡Tacaño!$"

BattleFrontier_Lounge5_Text_NatureGirlHardy::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta luchar!\n"
	.string "¡Luchará aunque tenga muchos\l"
	.string "golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlLonely::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta ser furtivo!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlBrave::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta luchar!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlAdamant::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta luchar!\n"
	.string "¡Luchará aunque tenga muchos\l"
	.string "golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlNaughty::
	.string "Hmhm…\p"
	.string "¡Dice que se cuida a sí mismo!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlBold::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta ser furtivo!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta luchar!\n"
	.string "Luchará aunque tenga muchos\l"
	.string "golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlRelaxed::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta ser astuto!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlImpish::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta luchar!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlLax::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta ser astuto!\n"
	.string "¡Dice que será astuto aunque\l"
	.string "tenga muchos golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlTimid::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta luchar!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡se volverá astuto!$"

BattleFrontier_Lounge5_Text_NatureGirlHasty::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta luchar!\n"
	.string "Luchará aunque tenga muchos\l"
	.string "golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlSerious::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta ser astuto!\n"
	.string "¡Dice que será astuto aunque\l"
	.string "tenga muchos golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlJolly::
	.string "Hmhm…\p"
	.string "¡Dice que le gusta ser astuto!\n"
	.string "Pero si recibe muchos golpes,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlModest::
	.string "Hmhm…\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "¡Dice que se preocupa aunque\l"
	.string "tenga muchos rasguños!$"

BattleFrontier_Lounge5_Text_NatureGirlMild::
	.string "Hmhm…\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "¡Pero si recibe muchos golpes,\l"
	.string "se volverá astuto!$"

BattleFrontier_Lounge5_Text_NatureGirlBashful::
	.string "Hmhm…\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "¡Dice que se preocupa aunque\l"
	.string "tenga muchos rasguños!$"

BattleFrontier_Lounge5_Text_NatureGirlRash::
	.string "Hmhm…\p"
	.string "¡Este dice que es muy astuto!\n"
	.string "¡Dice que le gusta ser astuto\l"
	.string "aunque tenga muchos rasguños!$"

BattleFrontier_Lounge5_Text_NatureGirlCalm::
	.string "Hmhm…\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "¡Dice que se preocupa aunque\l"
	.string "tenga muchos rasguños!$"

BattleFrontier_Lounge5_Text_NatureGirlGentle::
	.string "Hmhm…\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "¡Pero si recibe muchos golpes,\l"
	.string "contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlSassy::
	.string "Hmhm…\p"
	.string "¡Este dice que ama luchar!\n"
	.string "¡Pero si recibe muchos golpes,\l"
	.string "se volverá astuto!$"

BattleFrontier_Lounge5_Text_NatureGirlCareful::
	.string "Hmhm…\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "¡Pero si recibe muchos golpes,\l"
	.string "se volverá astuto!$"

BattleFrontier_Lounge5_Text_NatureGirlEgg::
	.string "¡Qué tontería! ¡El HUEVO duerme!\n"
	.string "¡No puedo hablar con él!$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
	.string "¡Qué encanto!\n"
	.string "¡Esa niña dice que puede\l"
	.string "entender a los POKéMON!$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
	.string "Siento que la niña está diciendo\n"
	.string "algo muy profundo.$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
	.string "¡Sé algo!\p"
	.string "¡Esa niña juega mucho en la\n"
	.string "casa roja!$"

