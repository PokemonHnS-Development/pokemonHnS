EventScript_MomGiftCall_Item::
	lockall
	pokenavcall Mom_Text_GiftCall_Item
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

EventScript_MomGiftCall_Berry::
	lockall
	pokenavcall Mom_Text_GiftCall_Berry
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

EventScript_MomGiftCall_Decoration::
	lockall
	pokenavcall Mom_Text_GiftCall_Decoration
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

Mom_Text_GiftCall_Item:
	.string "MOM: Hi, sweetie!\p"
	.string "I bought something nice\n"
	.string "for you with your savings!\p"
	.string "I sent it to your PC.\n"
	.string "Take care!$"

Mom_Text_GiftCall_Berry:
	.string "MOM: Hi, sweetie!\p"
	.string "I found some nice BERRIES\n"
	.string "at the store for you!\p"
	.string "I sent them to your PC.\n"
	.string "Take care!$"

Mom_Text_GiftCall_Decoration:
	.string "MOM: Hi, sweetie!\p"
	.string "I bought a cute POKê DOLL\n"
	.string "for your room!\p"
	.string "Check your DECORATIONS when you\n"
	.string "come home. Take care!$"
