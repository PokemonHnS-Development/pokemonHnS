# Reference for Music & SFX Usage for Pokémon Crystal

# Pokémon Crystal Sound Listing & Usage
This list will be the file names as they are in [PokeCrystal](https://github.com/pret/pokecrystal) project, the file names will match their names in PokeCrystal except for the "gbs_" prefix. I'm not going to list out the **battle_moves_sfx** or **pokemon_cries_sfx** cause I see less of a need as they're slightly more self contained. If you wanna see how they're mapped in Crystal I would recommend checking out PokeCrystal's mapping, My mapping will match for the Pokémon and moves that existed in Crystal.

Note: `nothing.asm` is not ported I don't want to check it.

## Unique to Crystal SFX (Unique to GSC) [`gbs/crystal_sfx/`]

**Sfx_4NoteDitty**
- Played in the mobile battle system (Japan-only) when a mobile battle concludes. Plays the jingle on the "battle ended" screen in `mobile/mobile_40.asm`.

**Sfx_DittoBounce**
- Played in the Game Freak logo splash screen each time Ditto bounces as it falls down toward the ground in `engine/movie/splash.asm`.

**Sfx_DittoPopUp**
- Played in the Game Freak logo splash screen when Ditto's sprite pops up after finishing its bounce animation in `engine/movie/splash.asm`.

**Sfx_DittoTransform**
- Played in the Game Freak logo splash screen when Ditto begins transforming into the "f" letter of the Game Freak logo in `engine/movie/splash.asm`.

**Sfx_GameFreakPresents**
- Played in the Game Freak logo splash screen when the "GAME FREAK presents" text is drawn on screen in `engine/movie/splash.asm`.

**Sfx_GlassTing**
- Played in Elm's Lab when Professor Elm's PC receives an email from Mr. Pokémon in `maps/ElmsLab.asm`.

**Sfx_GlassTing2**
- Played during the mobile trade animation when the trade sparkle/ping completes and the received Pokémon appears in `mobile/mobile_42.asm`.

**Sfx_IntroPichu**
- Played in the Crystal intro (IntroScene10) when Pichu appears in the outdoor pan scene in `engine/movie/intro.asm`.
- Reused in the same scene when Wooper appears in `engine/movie/intro.asm`.

**Sfx_IntroSuicune1**
- Defined in audio data but never explicitly called in any game script or engine code. Unused.

**Sfx_IntroSuicune2**
- Played in the Crystal intro (IntroScene8) when Suicune finishes its run across the outdoor scene in `engine/movie/intro.asm`.

**Sfx_IntroSuicune3**
- Played in the Crystal intro (IntroScene8) when Suicune begins running across the outdoor scene in `engine/movie/intro.asm`.

**Sfx_IntroSuicune4**
- Played in the Crystal intro (IntroScene13+) when Suicune jumps in `engine/movie/intro.asm`.

**Sfx_IntroUnown1**
- Played in the Crystal intro (IntroScene2) when the first Unown appears in `engine/movie/intro.asm`.
- Played again in IntroScene6 for a second Unown appearance and in the Unown spiral sound sequence in `engine/movie/intro.asm`.

**Sfx_IntroUnown2**
- Played in the Crystal intro (IntroScene6) for certain Unown appearances and multiple times throughout the Unown spiral sound sequence in `engine/movie/intro.asm`.

**Sfx_IntroUnown3**
- Played in the Crystal intro for the first and fifth Unown in the spiral animation sound table in `engine/movie/intro.asm`.

**Sfx_IntroWhoosh**
- Played in the Crystal intro during the final logo fade/whoosh effect near the end of the intro sequence in `engine/movie/intro.asm`.

**Sfx_Tingle**
- Played in Pokecenter 2F when Kris changes her appearance when entering the Cable Club in `maps/Pokecenter2F.asm`.
- Played when Kris changes her appearance when exiting the Cable Club in `maps/Pokecenter2F.asm`.
- Played when Kris changes her appearance when entering the Link Battle room in `maps/Pokecenter2F.asm`.
- Played when Kris changes her appearance when exiting the Link Battle room in `maps/Pokecenter2F.asm`.
- Played when Kris changes her appearance when entering the Time Capsule in `maps/Pokecenter2F.asm`.

**Sfx_Twinkle**
- Played in the mobile adapter system (Japan-only) when the Mobile Card Folder opens in `mobile/mobile_22_2.asm`.
- Played during a related mobile menu exit in `mobile/mobile_22.asm`.

**Sfx_TwoPcBeeps**
- Played in the mobile battle system (Japan-only) when the countdown timer is displayed before a mobile battle concludes in `mobile/mobile_40.asm`.

## Music [`gbs/music/`]
Note: These match the file names in PokeCrystal.
**aftertherivalfight**
- Plays during the scripted encounter after defeating the Rival at Cherrygrove City in `maps/CherrygroveCity.asm`.
- Plays during the scripted encounter after defeating the Rival at Azalea Town in `maps/AzaleaTown.asm`.
- Plays during the scripted encounter after defeating the Rival at Burned Tower in `maps/BurnedTower1F.asm`.
- Plays during the scripted encounter after defeating the Rival at Mt. Moon in `maps/MountMoon.asm`.
- Plays during the scripted encounter after defeating the Rival at Goldenrod Underground in `maps/GoldenrodUndergroundSwitchRoomEntrances.asm`.
- Plays during the scripted encounter after defeating the Rival at Victory Road in `maps/VictoryRoad.asm`.
- Plays during the scripted encounter after defeating the Rival at Indigo Plateau Pokémon Center in `maps/IndigoPlateauPokecenter1F.asm`.

**azaleatown**
- Map music for Azalea Town, the Charcoal Kiln, Azalea Mart, and Kurt's House in `data/maps/maps.asm`.
- Map music for Blackthorn City, its Mart, Dragon Speech House, Emys House, and the Move Deleter's House in `data/maps/maps.asm`.
- Map music for the Day Care on Route 34 in `data/maps/maps.asm`.
- Map music for the Heal House on Route 26, the Day-of-Week Siblings' House, and the Sandstorm House on Route 27 in `data/maps/maps.asm`.
- Map music for the Steel Wing House on Route 28 in `data/maps/maps.asm`.

**battletowerlobby** *(new to Crystal)*
- Map music for Battle Tower 1F in `data/maps/maps.asm`.

**battletowertheme** *(new to Crystal)*
- Map music for the Battle Tower Battle Room in `data/maps/maps.asm`.
- Map music for the Battle Tower Hallway in `data/maps/maps.asm`.
- Map music for the Battle Tower Outside area in `data/maps/maps.asm`.

**bicycle**
- Plays as overriding map music whenever the player is riding the Bicycle in `engine/events/overworld.asm` and `home/audio.asm`.
- Plays as the Pokégear Radio bike channel in `data/radio/channel_music.asm`.

**buenaspassword** *(new to Crystal)*
- Plays when talking to Buena at the Radio Tower and entering her password show in `maps/RadioTower2F.asm`.
- Plays as the Pokégear Radio Buena's Password channel in `data/radio/channel_music.asm`.

**bugcatchingcontest**
- Map music for the National Park during the Bug-Catching Contest in `data/maps/maps.asm`.
- A related ranking variant (`MUSIC_BUG_CATCHING_CONTEST_RANKING`) plays at the Route 35 and Route 36 National Park Gates when the contest timer is active in `home/audio.asm`.

**burnedtower**
- Map music for Burned Tower 1F in `data/maps/maps.asm`.
- Map music for Burned Tower B1F in `data/maps/maps.asm`.

**celadoncity**
- Map music for Celadon City, its Dept Store (floors 1–6 and elevator), Mansion (1F–3F, roof, roof house), Game Corner Prize Room, Café, and Pokécenter 2F (beta) in `data/maps/maps.asm`.
- Map music for Fuchsia City, its Mart, Safari Zone Main Office, Safari Zone Warden's Home, Bill's Older Sister's House, and Pokécenter 2F (beta) in `data/maps/maps.asm`.
- Map music for the Fuchsia Speech House on Route 16 in `data/maps/maps.asm`.

**championbattle**
- Plays when battling Champion Lance in `engine/battle/start_battle.asm`.
- Plays when battling Red at Mt. Silver in `engine/battle/start_battle.asm`.
- Plays when battling a late-game Rival (at or after the Indigo Plateau) in `engine/battle/start_battle.asm`.

**cherrygrovecity**
- Map music for Cherrygrove City, its Mart, Gym Speech House, Guide Gent's House, and Evolution Speech House in `data/maps/maps.asm`.
- Map music for the Route 30 Berry House and Mr. Pokémon's House on Route 30 in `data/maps/maps.asm`.
- Map music for Mahogany Town and the Red Gyarados Speech House in `data/maps/maps.asm`.
- Map music for the Trade Center, Colosseum, Time Capsule, Mobile Trade Room, and Mobile Battle Room (link/multiplayer rooms) in `data/maps/maps.asm`.
- Also plays as a fallback for maps incorrectly assigned the Mahogany Mart music value due to a known design flaw in `home/map.asm`.

**clair** *(new to Crystal)*
- Plays during the scripted cutscene in Dragon's Den B1F when Clair awards the player TM24 Dragonbreath in `maps/DragonsDenB1F.asm`.
- Plays during the scripted cutscene in the Dragon Shrine when Clair appears after the player passes the Elder's test in `maps/DragonShrine.asm`.

**contestresults**
- Plays at the Route 35 and Route 36 National Park Gates when the Bug-Catching Contest timer is active (i.e. the ranking/results state) in `home/audio.asm`.

**credits**
- Plays when the end credits sequence begins after entering the Hall of Fame in `engine/movie/credits.asm`.

**crystalopening** *(new to Crystal)*
- Plays during the Crystal intro sequence (IntroScene13) when Suicune appears running in the outdoor scene in `engine/movie/intro.asm`.

**dancinghall**
- Map music for the Dance Theater in Ecruteak City in `data/maps/maps.asm`.

**darkcave**
- Map music for Dark Cave (Violet City entrance and Blackthorn City entrance) in `data/maps/maps.asm`.
- Map music for Slowpoke Well B1F and B2F in `data/maps/maps.asm`.
- Map music for Ice Path 1F, B1F, B2F (Mahogany side), B2F (Blackthorn side), and B3F in `data/maps/maps.asm`.

**dragonsden**
- Map music for Dragon's Den 1F, B1F, and the Dragon Shrine in `data/maps/maps.asm`.

**ecruteakcity**
- Map music for Ecruteak City, the Tin Tower Entrance, Wise Trio's Room, Lugia Speech House, Mart, Dance Theater, and Itemfinder House in `data/maps/maps.asm`.
- Map music for Cianwood City, Mania's House, Cianwood Pharmacy, Photo Studio, Lugia Speech House, and the Poké Seer's House in `data/maps/maps.asm`.
- Map music for the Route 39 Barn and Farmhouse in `data/maps/maps.asm`.

**elmslab**
- Map music for Elm's Lab in New Bark Town in `data/maps/maps.asm`.

**evolution**
- Plays when a Pokémon evolves via the evolution animation sequence in `engine/movie/evolution_animation.asm`.
- Plays during the trade animation sequence when viewing the received Pokémon in `engine/movie/trade_animation.asm`.
- Plays during the egg hatch sequence in `engine/pokemon/breeding.asm`.

**gamecorner**
- Map music for Goldenrod Game Corner and Celadon Game Corner in `data/maps/maps.asm`.
- Plays when the slot machine game starts in `engine/games/slot_machine.asm`.
- Plays when the card flip game starts in `engine/games/card_flip.asm`.
- Plays as a Pokégear Radio channel in `data/radio/channel_music.asm`.

**goldenrodcity**
- Map music for Goldenrod City and its Dept Store (1F–6F, elevator, roof), Bike Shop, Happiness Rater, Bill's Family's House, Magnet Train Station, Flower Shop, PP Speech House, Name Rater, Game Corner, and Dept Store B1F in `data/maps/maps.asm`.
- Map music for the Radio Tower (1F–5F), with the `RADIO_TOWER_MUSIC` flag set so the radio overrides it based on the active channel in `data/maps/maps.asm`.
- Map music for the Route 35 and Route 36 National Park Gates in `data/maps/maps.asm`.

**goldsilveropening**
- Defined in audio data (`MUSIC_GS_OPENING`, `$52`) but never referenced anywhere in engine code, maps, or scripts. Unused in Crystal.

**goldsilveropening2**
- Defined in audio data (`MUSIC_GS_OPENING_2`, `$53`) but never referenced anywhere in engine code, maps, or scripts. Unused in Crystal.

**gym**
- Map music for all 17 gyms: Violet, Azalea, Goldenrod, Ecruteak, Cianwood, Olivine, Mahogany, Blackthorn (1F & 2F), Viridian, Pewter, Cerulean, Vermilion, Celadon, Fuchsia, Saffron, and Seafoam Islands Gym in `data/maps/maps.asm`.

**gymleadervictory**
- Plays after winning a battle against a Gym Leader in `engine/battle/core.asm`.

**halloffame**
- Plays during the Hall of Fame recording sequence after defeating Lance and becoming Champion in `engine/events/halloffame.asm`.

**healpokemon**
- Plays during the Pokémon Center heal machine animation in `engine/events/heal_machine_anim.asm`.
- Plays as a scripted music override at Mr. Pokémon's House on Route 30 in `maps/MrPokemonsHouse.asm`.
- Plays as a scripted music override at the Route 26 Heal House in `maps/Route26HealHouse.asm`.
- Plays as a scripted music override at the Route 39 Barn in `maps/Route39Barn.asm`.
- Plays as a scripted music override at the top of Olivine Lighthouse 6F in `maps/OlivineLighthouse6F.asm`.
- Plays as a scripted music override at Jasmine's location on the Fast Ship in `maps/FastShipCabins_SW_SSW_NW.asm`.
- Plays as a scripted music override at two points in the Goldenrod Underground in `maps/GoldenrodUnderground.asm`.
- Plays as a scripted music override at Blue's House in `maps/BluesHouse.asm`.
- Plays as a scripted music override in the Battle Tower Battle Room after a battle in `maps/BattleTowerBattleRoom.asm`.
- Plays as a scripted music override in the Mobile Battle Room after a battle in `maps/MobileBattleRoom.asm`.

**indigoplateau**
- Map music for the Indigo Plateau Pokémon Center and all four Elite Four rooms (Will, Koga, Bruno, Karen) and Lance's Room in `data/maps/maps.asm`.
- Map music for Route 23 and the Victory Road Gate in `data/maps/maps.asm`.
- Map music for Route 28, Silver Cave Outside in `data/maps/maps.asm`.

**johtogymbattle**
- Plays during battles against Johto Gym Leaders (Falkner, Bugsy, Whitney, Morty, Chuck, Jasmine, Pryce, Clair) and Elite Four members (Will, Bruno, Karen, Koga), determined in `engine/battle/start_battle.asm`.

**johtotrainerbattle**
- Plays during battles against regular trainers (non-gym leader, non-Rocket) encountered while in the Johto region, determined by `RegionCheck` in `engine/battle/start_battle.asm`.
- Explicitly played during the scripted Youngster Joey tutorial battle on Route 30 in `maps/Route30.asm`.

**johtowildbattle**
- Plays during wild Pokémon encounters in Johto during the morning or daytime, determined by `RegionCheck` and `wTimeOfDay` in `engine/battle/start_battle.asm`.

**johtowildbattlenight**
- Plays during wild Pokémon encounters in Johto at night, determined by `wTimeOfDay` check in `engine/battle/start_battle.asm`.

**kantogymbattle**
- Plays during battles against Kanto Gym Leaders (Brock, Misty, Lt. Surge, Erika, Janine, Sabrina, Blaine, Blue), determined by `IsKantoGymLeader` in `engine/battle/start_battle.asm`.

**kantotrainerbattle**
- Plays during battles against regular trainers (non-gym leader) encountered while in the Kanto region, determined by `RegionCheck` in `engine/battle/start_battle.asm`.

**kantowildbattle**
- Plays during wild Pokémon encounters in Kanto, determined by `RegionCheck` in `engine/battle/start_battle.asm`.

**lakeofrage**
- Map music for Lake of Rage, Route 43, Route 43 Mahogany Gate, the Lake of Rage Hidden Power House, and the Lake of Rage Magikarp House in `data/maps/maps.asm`.
- Map music for Route 42, Route 42 Ecruteak Gate, and Route 44 in `data/maps/maps.asm`.

**lakeofragerocketradio**
- Plays as the Rocket Radio broadcast on all Johto radio stations when Team Rocket is occupying the Radio Tower, replacing normal programming via `engine/pokegear/radio.asm`.

**lavendertown**
- Map music for Lavender Town, Mr. Fuji's House, the Lavender Speech House, the Lavender Name Rater, the Lavender Mart, the Soul House, and the Lavender Radio Tower 1F in `data/maps/maps.asm`.

**lighthouse**
- Map music for Olivine Lighthouse 1F through 5F in `data/maps/maps.asm`.
- Map music for Silver Cave Room 1, Room 2, Room 3, and Silver Cave Item Rooms in `data/maps/maps.asm`.

**lookbeauty**
- Trainer encounter music for Beauty, Cool Trainer F, Swimmer F, Pokéfan F, Skier, Teacher, Sabrina, and Clair, assigned in `data/trainers/encounter_music.asm`.

**lookhiker**
- Trainer encounter music for Hiker, Fisherman, Sailor, Guitarist, Biker, Firebreather, Black Belt, Boarder, Cool Trainer M, Gentleman, Swimmer M, Pokéfan M, Will, Koga, Karen, Lt. Cal, Red, Officer, and various others with no dedicated encounter theme, assigned in `data/trainers/encounter_music.asm`.

**lookkimonogirl**
- Trainer encounter music for Kimono Girl, assigned in `data/trainers/encounter_music.asm`.

**looklass**
- Trainer encounter music for Lass, Picnicker, Twins, Jasmine, Misty, Janine, and Whitney, assigned in `data/trainers/encounter_music.asm`.

**lookmysticalman** *(new to Crystal)*
- Played via scripted events for Eusine's encounters in Cianwood City in `maps/CianwoodCity.asm`.
- Played via scripted event for Eusine's encounter at Tin Tower 1F in `maps/TinTower1F.asm`.

**lookofficer**
- Trainer encounter music for Morty, Pryce, Chuck, Bruno, Lance (Champion), Lt. Surge, Erika, Blaine, Brock (in the Johto games), and various others, assigned in `data/trainers/encounter_music.asm`.

**lookpokemaniac**
- Trainer encounter music for Pokémaniac, Super Nerd, Burglar, and Juggler, assigned in `data/trainers/encounter_music.asm`.

**lookrival**
- Trainer encounter music for Rival (both Rival1 and Rival2 classes) and Blue, assigned in `data/trainers/encounter_music.asm`.
- Played via scripted events for Silver's appearances throughout the game, including Cherrygrove City, Azalea Town, Burned Tower 1F, Goldenrod Underground, Team Rocket Base B3F, Mt. Moon, Victory Road, Dragon's Den B1F, Indigo Plateau Pokécenter, Sprout Tower 3F, Olivine City, and others in their respective map files.

**lookrocket**
- Trainer encounter music for Team Rocket Grunt M, Grunt F, Executive M, Executive F, and Scientist, assigned in `data/trainers/encounter_music.asm`.

**looksage**
- Trainer encounter music for Sage and Medium, assigned in `data/trainers/encounter_music.asm`.

**lookyoungster**
- Trainer encounter music for Youngster, Schoolboy, Bug Catcher, Bird Keeper, Camper, Psychic, Falkner, Bugsy, and Brock, assigned in `data/trainers/encounter_music.asm`.

**magnettrain**
- Plays during the Magnet Train riding animation/cutscene, triggered in `engine/events/magnet_train.asm`.

**mainmenu**
- Plays on the main menu (New Game / Continue / Options screen) in `engine/menus/intro_menu.asm`.
- Plays on the save deletion screen in `engine/menus/delete_save.asm`.
- Plays on the RTC reset password screen in `engine/rtc/reset_password.asm`.
- Replaces Mobile Adapter Menu music when returning to the main menu from a mobile session in `mobile/mobile_menu.asm`.

**mobileadapter** *(new to Crystal)*
- Plays during the Mobile Adapter connection/communication sequence in `mobile/mobile_45_sprite_engine.asm`.

**mobileadaptermenu** *(new to Crystal)*

- Plays on the Mobile Adapter menu screen in `mobile/mobile_menu.asm` and `engine/menus/intro_menu.asm`.

**mobilecenter** *(new to Crystal)*
- Plays in the Mobile Center in `mobile/mobile_5f.asm`.

**mom**
- Played via scripted events when Mom stops the player at the start of the game in Player's House 1F in `maps/PlayersHouse1F.asm`.
- Played via scripted events when the teacher NPC stops the player at the start of the game in New Bark Town in `maps/NewBarkTown.asm`.

**mtmoon**
- Map music for Mt. Moon in `data/maps/maps.asm`.
- Map music for Diglett's Cave in `data/maps/maps.asm`.
- Map music for Rock Tunnel 1F and B1F in `data/maps/maps.asm`.
- Map music for the Underground Path in `data/maps/maps.asm`.

**mtmoonsquare**
- Map music for Mt. Moon Square in `data/maps/maps.asm`.

**nationalpark**
- Map music for National Park in `data/maps/maps.asm`.

**newbarktown**
- Map music for New Bark Town, Player's House 1F and 2F, Player's Neighbor's House, and Elm's House in `data/maps/maps.asm`.
- Map music for the Hall of Fame room in `data/maps/maps.asm`.
- Played via scripted events when the player is stopped at the beginning of the game in `maps/PlayersNeighborsHouse.asm` and `maps/PlayersHouse2F.asm`.

**pallettown**
- Map music for Pallet Town, Red's House 1F and 2F, and Blue's House in `data/maps/maps.asm`.

**pokeflutechannel**
- Plays as the Pokémon Flute radio channel (channel 8) in the Pokégear radio, tuned in via `engine/pokegear/radio.asm`.
- Used by `engine/events/specials.asm` as a background music check to determine if the player is near a sleeping Snorlax while the Poké Flute channel is active.

**pokemoncenter**
- Map music for every Pokémon Center in both Johto and Kanto, the Cable Club (Pokecenter 2F), and the Pokécom Center Admin Office in `data/maps/maps.asm`.
- Assigned to the Pokémon Center radio show (channel 1) via `data/radio/channel_music.asm`.

**pokemonchannel**
- Plays as the background music when the Pokémon Music radio show (Ben's or Fern's show, channel 2) is active in the Pokégear, triggered via `engine/pokegear/pokegear.asm`.

**pokemonlullaby**
- Plays as the background music on even-day broadcasts of the Pokémon Music radio show (Ben's or Fern's show), toggled by day of week in `engine/pokegear/radio.asm`.
- While active as map music, halves the wild Pokémon encounter rate, checked in `engine/overworld/wildmons.asm`.

**pokemonmarch**
- Plays as the background music on odd-day broadcasts of the Pokémon Music radio show (Ben's or Fern's show), toggled by day of week in `engine/pokegear/radio.asm`.
- While active as map music, doubles the wild Pokémon encounter rate, checked in `engine/overworld/wildmons.asm`.

**postcredits**
- Plays at the end of the credits sequence after fading out the credits music, triggered in `engine/movie/credits.asm`.

**printer**
- Plays during Game Boy Printer operation in `engine/printer/printer.asm`.

**profoak**
- Played via scripted event when Professor Oak visits Mr. Pokémon's House and gives the player the Pokédex in `maps/MrPokemonsHouse.asm`.

**profoakspokemontalk**
- Map music for Oak's Lab in Pallet Town in `data/maps/maps.asm`.
- Assigned to the Oak's Pokémon Talk radio show (channel 0) via `data/radio/channel_music.asm`.
- Played during the scripted intro radio broadcast in Player's Neighbor's House in `maps/PlayersNeighborsHouse.asm`.
- Played during the scripted intro sequence in Player's House 2F in `maps/PlayersHouse2F.asm`.

**rivalbattle**
- Plays during battles against Silver (Rival1 and Rival2 trainer classes) except at Indigo Plateau where Champion music plays instead, and also for Blue, determined in `engine/battle/start_battle.asm`.

**rocketbattle**
- Plays during battles against Team Rocket Grunt M and Grunt F, determined in `engine/battle/start_battle.asm`.

**rockethideout**
- Map music for Team Rocket Base B1F, B2F, and B3F (Mahogany Town) in `data/maps/maps.asm`.
- Plays as the map music for the Goldenrod Radio Tower floors while Team Rocket is occupying them, dynamically set via `home/map.asm`.

**rockettheme**
- Assigned to the Rocket Broadcast radio channel (channel 7) via `data/radio/channel_music.asm`.
- Plays for all Radio Tower maps while Team Rocket is occupying the Radio Tower, dynamically substituted via `home/map.asm`.

**route1**
- Map music for Route 1 in `data/maps/maps.asm`.

**route12**
- Map music for Route 12, Route 11, Route 13, Route 14, Route 15, and the Route 15 Fuchsia Gate in `data/maps/maps.asm`.

**route2**
- Map music for Route 2 and Route 2 Gate in `data/maps/maps.asm`.

**route26**
- Map music for Route 26 and Route 27 in `data/maps/maps.asm`.

**route29**
- Map music for Route 29 and the Route 29/Route 46 Gate in `data/maps/maps.asm`.

**route3**
- Map music for Route 3, Route 4, Route 5, Route 6, Route 7, Route 8, Route 9, Route 10 North, Route 10 South, Route 16, Route 17, Route 18, Route 19, Route 20, Route 21, Route 22, Route 24, Route 25, and their associated gates in `data/maps/maps.asm`.

**route30**
- Map music for Route 30, Route 31, Route 32, Route 33, the Route 31/Violet Gate, and the Route 32/Ruins of Alph Gate in `data/maps/maps.asm`.
- Plays during the link trade sequence (while waiting for the trade partner) in `engine/link/link.asm`.
- Plays during the link trade intro screen at startup in `engine/menus/intro_menu.asm`.

**route36**
- Map music for Route 35, Route 36, Route 37, Route 34, Route 40, Route 41, Route 45, Route 46, the Route 35/Goldenrod Gate, the Route 36/Ruins of Alph Gate, the Ilex Forest/Azalea Gate, the Route 34/Ilex Forest Gate, and the Route 40/Battle Tower Gate in `data/maps/maps.asm`.

**route37**
- Map music for Route 38, Route 39, and the Route 38/Ecruteak Gate in `data/maps/maps.asm`.

**ruinsofalphinterior**
- Map music for the Ruins of Alph Inner Chamber in `data/maps/maps.asm`.

**ruinsofalphradio**
- Assigned to the Unown Radio channel (channel 9) via `data/radio/channel_music.asm`.
- While active as map music, doubles the wild Pokémon encounter rate, checked in `engine/overworld/wildmons.asm`.

**showmearound**
- Played via scripted event when the Guide Gent walks the player around Cherrygrove City in `maps/CherrygroveCity.asm`.
- Played via scripted event when Earl walks the player to the Pokémon Academy in Violet City in `maps/VioletCity.asm`.
- Played via scripted event when the scientist leads the player to the Ruins of Alph Research Center in `maps/RuinsOfAlphOutside.asm`.
- Played via scripted event when the Goldenrod Pokécenter receptionist escorts the player to the Cable Club in `maps/GoldenrodPokecenter1F.asm`.

**sprouttower**
- Map music for Sprout Tower 1F, 2F, and 3F in `data/maps/maps.asm`.

**ssaqua**
- Map music for the S.S. Aqua 1F, all cabin rooms (NNW/NNE/NE, SW/SSW/NW, SE/SSE/Captain's Cabin), and B1F in `data/maps/maps.asm`.

**successfulcapture**
- Plays after successfully catching a Pokémon in battle, triggered in `engine/items/item_effects.asm`.

**suicunebattle** *(new to Crystal)*
- Plays during the battle against the roaming Suicune (`BATTLETYPE_SUICUNE`) and roaming legendary Pokémon (`BATTLETYPE_ROAMING`), determined in `engine/battle/start_battle.asm`.

**surf**
- Plays while the player is surfing (`PLAYER_SURF` or `PLAYER_SURF_PIKA`), dynamically replacing the map music via `home/audio.asm`.

**tintower**
- Map music for Tin Tower 1F through 9F and the Tin Tower Roof in `data/maps/maps.asm`.

**titlescreen**
- Plays on the title screen in `engine/menus/intro_menu.asm`.
- Assigned to the Pokémon Music radio show channel (channel 2) via `data/radio/channel_music.asm`.

**trainervictory**

- Plays after defeating a non-gym-leader trainer in battle, determined in `engine/battle/core.asm`.

**unioncave**
- Map music for Union Cave 1F, B1F, and B2F in `data/maps/maps.asm`.
- Map music for Ilex Forest in `data/maps/maps.asm`.
- Map music for Mt. Mortar 1F Outside, 1F Inside, 2F Inside, and B1F in `data/maps/maps.asm`.
- Map music for all Whirl Islands floors (NW, NE, SW, SE, Cave, B1F, B2F, and Lugia Chamber) in `data/maps/maps.asm`.
- Map music for Tohjo Falls in `data/maps/maps.asm`.
- Map music for Goldenrod Underground and Goldenrod Underground Switch Room Entrances and Warehouse in `data/maps/maps.asm`.
- Map music for all Ruins of Alph areas (Outside, puzzle chambers, item rooms, word rooms, and Research Center) in `data/maps/maps.asm`.

**vermilioncity**
- Map music for Vermilion City and all its interior buildings (Pokémon Fan Club, Mart, Fishing House, Magnet Train Speech House, Diglett's Cave Speech House, Port, and Port Passage) in `data/maps/maps.asm`.

**victoryroad**
- Map music for Victory Road in `data/maps/maps.asm`.

**violetcity**
- Map music for Violet City, Violet Mart, Earl's Pokémon Academy, and all Violet City houses in `data/maps/maps.asm`.
- Map music for Olivine City and all its interior buildings (houses, café, mart, port, port passage) in `data/maps/maps.asm`.
- Map music for Olivine Lighthouse 6F in `data/maps/maps.asm`.

**viridiancity**
- Map music for Viridian City, Pewter City, Cerulean City, Saffron City, and Cinnabar Island, along with all their interior buildings in `data/maps/maps.asm`.
- Map music for Trainer House 1F and B1F, Silph Co. 1F, Copycat's House, Fighting Dojo, Power Plant, Bill's House, Mt. Moon Gift Shop, and Route 12 Super Rod House in `data/maps/maps.asm`.
- Assigned to the Places & People radio show (channel 5) via `data/radio/channel_music.asm`.

**wildpokemonvictory**
- Plays after defeating a wild Pokémon in battle, determined in `engine/battle/core.asm`.


## Sound Effects [`gsc/sfx/`]
**Sfx_1stPlace**:
- Plays in `maps/RadioTower1F.asm` during the Lucky Channel Lucky Number Show when the player's card is a perfect match
- Plays in `engine/events/bug_contest/judging.asm` when the player places 1st in the Bug-Catching Contest
- Plays in `engine/games/unown_puzzle.asm` when the player successfully solves the Unown Puzzle

**Sfx_2Boops**:
- Plays in `engine/pokemon/stats_screen.asm` when viewing an Egg on the stats screen that is very close to hatching (fewer than 6 egg cycles remaining)

**Sfx_2ndPlace**:
- Plays in `maps/RadioTower1F.asm` during the Lucky Channel Lucky Number Show when the player's card is a partial match
- Plays in `engine/events/bug_contest/judging.asm` when the player places 2nd in the Bug-Catching Contest
- Plays in `engine/games/slot_machine.asm` when three 7s line up in the Slot Machine
- Plays in `engine/games/card_flip.asm` on any winning match in the Card Flip game

**Sfx_3rdPlace**:
- Plays in `maps/RadioTower1F.asm` during the Lucky Channel Lucky Number Show when the player's card is a weak match
- Plays in `engine/events/bug_contest/judging.asm` when the player places 3rd in the Bug-Catching Contest
- Plays in `engine/games/slot_machine.asm` when three Poké Balls line up in the Slot Machine

**Sfx_BallBounce**:
- Plays in `data/moves/animations.asm` (BattleAnim_ThrowPokeBall) when a thrown Poké Ball bounces on the ground

**Sfx_BallPoof**:
- Plays in `data/moves/animations.asm` during `BattleAnim_ThrowPokeBall` (ball opening on capture), `BattleAnim_SendOutMon` (Pokémon emerging from ball), and `BattleAnim_ReturnMon` (Pokémon returning to ball)
- Plays in `engine/movie/trade_animation.asm` during the trade Poké Ball animation
- Plays in `mobile/mobile_42.asm` during Mobile Battle Tower battle sequences

**Sfx_BallWobble**:
- Plays in `data/moves/animations.asm` (BattleAnim_ThrowPokeBall) when a Poké Ball wobbles after striking a Pokémon

**Sfx_Boat**:
- Plays in `maps/FastShip1F.asm` during the S.S. Aqua departure cutscene when the ship horn sounds and the boat rumbles before leaving port

**Sfx_BootPc**:
- Plays in `engine/events/pokecenter_pc.asm` when opening or closing a PC at a Pokémon Center
- Plays in `maps/RuinsOfAlphResearchCenter.asm` during the scientist cutscene when the Unown Pokédex computer is accessed
- Plays in `engine/events/heal_machine_anim.asm` as part of the Hall of Fame saving sequence, after the Game Freak logo flash

**Sfx_Bump**:
- Plays in `engine/overworld/player_movement.asm` when the player walks into an impassable tile or wall

**Sfx_Burn**:
- Plays in `data/moves/animations.asm` (BattleAnim_Brn) during the burn status infliction animation

**Sfx_Call**:
- Plays in `engine/phone/phone.asm` (Phone_StartRinging) when an incoming phone call begins ringing
- Plays in `engine/pokegear/pokegear.asm` when dialing out from the Pokégear phone
- Plays in `maps/PowerPlant.asm` during the scripted scene where the guard's phone rings at the Power Plant

**Sfx_Caughtmon**:
- Plays embedded in `data/text/common_3.asm` (Text_BallCaught) — the "Gotcha! X was caught!" message
- Plays embedded in `data/text/common_2.asm` (_BreedEggHatchText) when an Egg hatches
- Plays in `engine/pokemon/evolve.asm` when a Pokémon evolves
- Plays in `engine/events/sacred_ash.asm` when Sacred Ash revives all fainted Pokémon
- Plays in `maps/ElmsLab.asm` when receiving a starter Pokémon from Prof. Elm
- Plays in `maps/BillsFamilysHouse.asm` when receiving Eevee from Bill
- Plays in `maps/MountMortarB1F.asm` when receiving Tyrogue from Kiyo
- Plays in `maps/DragonShrine.asm` when receiving Dratini from the Dragon Master
- Plays in `data/events/pokedex_ratings.asm` for high Pokédex rating milestones (124 and 139 Pokémon seen)

**Sfx_ChangeDexMode**:
- Plays in `engine/pokedex/pokedex.asm` (Pokedex_DisplayChangingModesMessage) when the player switches the Pokédex sort mode (ABC / Type / Number)
- Plays in `data/moves/animations.asm` (BattleAnim_ThrowPokeBall) as the Poké Ball click sound when it snaps shut around a Pokémon during a catch attempt

**Sfx_ChooseAsCard**:
- Plays in `engine/games/card_flip.asm` (.CheckTheCard) when the player flips over a card in the Card Flip game

**Sfx_ChoosePcOption**:
- Plays in `engine/events/pokecenter_pc.asm` when navigating PC menu options, and when attempting to access the PC without any Pokémon in the party

**Sfx_Damage**:
- Plays in `engine/battle_anims/anim_commands.asm` (PlayHitSound) when a move deals normal effectiveness damage

**Sfx_DexFanfare_140169**:
- Plays in `data/events/pokedex_ratings.asm` for Pokédex rating milestones at 154 and 169 Pokémon seen

**Sfx_DexFanfare_170199**:
- Plays in `data/events/pokedex_ratings.asm` for Pokédex rating milestones at 184 and 199 Pokémon seen

**Sfx_DexFanfare_200229**:
- Plays in `data/events/pokedex_ratings.asm` for Pokédex rating milestones at 214 and 229 Pokémon seen

**Sfx_DexFanfare_2049**:
- Plays in `data/events/pokedex_ratings.asm` for Pokédex rating milestones at 34 and 49 Pokémon seen
- Plays in `maps/RadioTower1F.asm` during the Lucky Channel Lucky Number Show suspense pause before revealing results

**Sfx_DexFanfare_230Plus**:
- Plays in `data/events/pokedex_ratings.asm` for Pokédex rating milestones at 239, 248, and 255 (full) Pokémon seen
- Plays in `maps/CeladonMansion3F.asm` when the Game Freak game designer acknowledges a completed Pokédex

**Sfx_DexFanfare_5079**:
- Plays embedded in `data/text/common_1.asm` (_GrewToLevelText) — the level-up fanfare that plays after a Pokémon gains a level
- Plays in `data/events/pokedex_ratings.asm` for Pokédex rating milestones at 64 and 79 Pokémon seen

**Sfx_DexFanfare_80109**:
- Plays in `data/events/pokedex_ratings.asm` for Pokédex rating milestones at 94 and 109 Pokémon seen

**Sfx_DexFanfare_Lt20**:
- Plays in `data/events/pokedex_ratings.asm` for the earliest Pokédex rating milestones at 9 and 19 Pokémon seen

**Sfx_EggCrack**:
- Plays in `engine/pokemon/breeding.asm` (EggHatch_CrackShell) each time the Egg shell sprite cracks during the hatching animation

**Sfx_EggHatch**:
- Plays in `engine/pokemon/breeding.asm` (EggHatch_AnimationSequence) when a Pokémon fully hatches from its Egg

**Sfx_Elevator**:
- Plays in `maps/GoldenrodDeptStoreElevator.asm` and `maps/CeladonDeptStoreElevator.asm` when the department store elevator begins moving
- Plays in `maps/SproutTower3F.asm` when the swinging floor platform moves
- Plays in `maps/BattleTowerElevator.asm` when the Battle Tower elevator departs

**Sfx_ElevatorEnd**:
- Plays in `engine/events/std_scripts.asm` (ElevatorButtonScript) when the player presses an elevator button and the doors open upon arrival
- Plays in `maps/RadioTower1F.asm` after each correct answer in the Radio Card quiz
- Plays in `maps/FastShipCabins_SW_SSW_NW.asm` and `maps/FastShipCabins_SE_SSE_CaptainsCabin.asm` when the S.S. Aqua arrives at port and the cabin doors open
- Plays in `engine/events/bug_contest/contest.asm` when the Bug-Catching Contest bus arrives and departs

**Sfx_EnterDoor**:
- Plays in `engine/overworld/tile_events.asm` (GetWarpSFX) whenever the player steps onto a door tile warp
- Plays in numerous map scripts for scripted door-opening events (Elite Four chambers, Goldenrod Underground, Tin Tower, Dragon's Den, and others)

**Sfx_EscapeRope**:
- Plays in `engine/menus/intro_menu.asm` (ShrinkPlayer) during the intro sequence when the player sprite is scaled down
- Plays in `data/moves/animations.asm` (BattleAnim_Bide) as part of the Bide charge animation

**Sfx_EvolutionIntro**:
- No corresponding constant exists in the codebase; the evolution sequence uses the music track `MUSIC_EVOLUTION` (`audio/music/evolution.asm`) rather than an SFX

**Sfx_Evolved**:
- Plays in `engine/movie/evolution_animation.asm` (.PlayEvolvedSFX) when a Pokémon's silhouette snaps from the evolved form back to itself, marking the completion of the evolution transformation

**Sfx_ExitBuilding**:
- Plays in `engine/overworld/tile_events.asm` (GetWarpSFX) whenever the player steps onto a non-door, non-warppanel exit tile (building exits, cave exits, etc.)
- Plays in numerous map scripts for scripted exits (Pokémon Centers, ports, gyms, and others)

**Sfx_ExpBar**:
- Plays in `engine/battle/core.asm` (.PlayExpBarSound) repeatedly while the EXP bar fills up after a battle

**Sfx_Faint**:
- Plays in `engine/battle/core.asm` (FaintEnemyPokemon) when an enemy Pokémon faints
- Plays in `engine/battle/core.asm` (SpikesDamage) when a Pokémon faints from Spikes damage upon switching in
- Plays in `maps/MahoganyMart1F.asm` during Lance's scripted scene when he reveals the hidden staircase tapped by Team Rocket

**Sfx_Fanfare**:
- Registered in `home/text.asm` as the text-embeddable `TX_SOUND_FANFARE` sound command, though no text strings in the codebase currently use it directly

**Sfx_Fanfare2**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase

**Sfx_Fly**:
- Plays in `engine/events/field_moves.asm` (FlyFunction_FrameTimer) periodically during the Fly field move takeoff/landing animation
- Plays in `maps/KurtsHouse.asm` when Kurt rushes out of his house to confront Team Rocket in Azalea Town, and again during the GS Ball scripted scene

**Sfx_FullHeal**:
- Plays in `data/moves/animations.asm` (BattleAnim_Recover) during the Recover move animation
- Plays in `engine/items/item_effects.asm` (Play_SFX_FULL_HEAL) when using HP-restoring items (Potions, Full Heals, etc.), status-curing items (Antidote, Full Restore, etc.), and PP-restoring items (Ether, Elixir, etc.)
- Plays in `engine/items/pack.asm` (RegisterItem) when registering an item to the Select button
- Plays in `engine/battle/ai/items.asm` (AIUsedItemSound) when the trainer AI uses any item during battle
- Plays in `maps/TeamRocketBaseB2F.asm` when Lance heals the player's party in the Mahogany Rocket Base

**Sfx_GameFreakLogoGs**:
- Plays in `engine/events/heal_machine_anim.asm` (.HOF_PlaySFX) as part of the Hall of Fame saving sequence — the chime that accompanies the screen flash when the save completes

**Sfx_GetBadge**:
- Plays in all 16 Gym maps (`maps/VioletGym.asm`, `maps/AzaleaGym.asm`, `maps/GoldenrodGym.asm`, `maps/EcruteakGym.asm`, `maps/OlivineGym.asm`, `maps/CianwoodGym.asm`, `maps/MahoganyGym.asm`, `maps/DragonShrine.asm`, `maps/PewterGym.asm`, `maps/CeruleanGym.asm`, `maps/VermilionGym.asm`, `maps/CeladonGym.asm`, `maps/FuchsiaGym.asm`, `maps/SaffronGym.asm`, `maps/SeafoamGym.asm`, `maps/ViridianGym.asm`) when the player receives a Badge after defeating a Gym Leader

**Sfx_GetCoin**:
- Plays in `engine/games/slot_machine.asm` (SlotsAction_GiveEarnedCoins) during the coin payout animation after a winning spin in the Slot Machine

**Sfx_GetEgg**:
- Plays in `engine/events/std_scripts.asm` (ReceiveTogepiEggScript) when the player receives the Togepi Egg from Mr. Pokémon
- Plays in `engine/events/daycare.asm` when the player picks up the Egg from the Day-Care Man

**Sfx_GetTm**:
- Plays in `engine/overworld/scripting.asm` (Script_specialsound) when the player receives a TM or HM item

**Sfx_GetTrademon**:
- Plays in `engine/movie/trade_animation.asm` (TradeAnim_GetTrademonSFX) when the incoming trade Pokémon's Poké Ball arrives during a link trade
- Plays in `mobile/mobile_42.asm` during the Mobile trade animation

**Sfx_GiveTrademon**:
- Plays in `engine/movie/trade_animation.asm` (TradeAnim_GiveTrademonSFX) when the player's Pokémon's Poké Ball is sent away during a link trade
- Plays in `mobile/mobile_42.asm` during the Mobile trade animation

**Sfx_GotSafariBalls**:
- Plays in `maps/Route35NationalParkGate.asm` and `maps/Route36NationalParkGate.asm` when the player receives Park Balls upon entering the Bug-Catching Contest
- Plays in `engine/sprite_anims/functions.asm` (SpriteAnimFunc_TradePokeBall) during the Poké Ball animation in a trade sequence
- Plays in `engine/games/slot_machine.asm` (ReelAction_WaitSlowAdvanceReel3) as the reel slows on the third reel

**Sfx_GrassRustle**:
- Triggered by the `EMOTE_GRASS_RUSTLE` sprite animation in `engine/overworld/overworld.asm` when the player walks through tall grass, playing alongside the rustling grass sprite animation

**Sfx_GsIntroCharizardFireball**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase; likely a remnant from Gold/Silver's opening sequence which was replaced in Crystal

**Sfx_GsIntroPokemonAppears**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase; likely a remnant from Gold/Silver's opening sequence which was replaced in Crystal

**Sfx_HangUp**:
- Plays in `engine/phone/phone.asm` (HangUp_Beep) when a phone call ends and the player or caller hangs up

**Sfx_HitEndOfExpBar**:
- Plays in `engine/battle/core.asm` (AnimateExpBar) when the EXP bar reaches the right edge and the Pokémon gains a level

**Sfx_Item**:
- Plays embedded in `data/text/common_1.asm` (_ReceiveItemText) — the "Player received X!" text that triggers whenever a regular item is given
- Plays in `engine/overworld/scripting.asm` (Script_specialsound) when a non-TM/HM item is received via script
- Plays in `engine/events/std_scripts.asm` when receiving an item via the standard receive-item script
- Plays in numerous map scripts for specific item-give events (`maps/MrPokemonsHouse.asm`, `maps/DragonsDenB1F.asm`, `maps/LakeOfRage.asm`, `maps/CeladonCafe.asm`, `maps/BlackthornGym1F.asm`, `maps/RuinsOfAlphResearchCenter.asm`, and others)

**Sfx_JumpOverLedge**:
- Plays in `engine/overworld/player_movement.asm` when the player jumps over a one-way ledge
- Plays in `engine/games/slot_machine.asm` (Slots_AnimateChansey) during the Chansey bonus game reel animation

**Sfx_KeyItem**:
- Plays in `maps/GoldenrodBikeShop.asm` when receiving the Bicycle
- Plays in `maps/CianwoodPharmacy.asm` when receiving the SecretPotion
- Plays in `maps/ManiasHouse.asm` when receiving Shuckie from Mania
- Plays in `maps/MrPokemonsHouse.asm` when receiving the Mystery Egg / Pokémon Egg item
- Plays in `maps/DayCare.asm` when receiving the Phone Number from the Day-Care Man
- Plays in `maps/Route35GoldenrodGate.asm` when receiving the Squirtbottle
- Plays in `maps/PokemonFanClub.asm` when receiving an item from the Fan Club

**Sfx_LevelUp**:
- Plays in `mobile/mobile_40.asm` (Function102142) during the Mobile Stadium adapter feature when a new news card arrives
- Note: shares identical sound data with `Sfx_DexFanfare_5079`, which is used for the in-battle level-up fanfare via the text system

**Sfx_MasterBall**:
- Plays in `data/moves/animations.asm` (BattleAnim_ThrowPokeBall) during the Master Ball throw animation after the ball poof, accompanying the Master Ball's unique sparkle effect

**Sfx_Menu**:
- Plays in `engine/menus/start_menu.asm` (StartMenu) when the Start Menu is opened
- Plays in `data/moves/animations.asm` during the battle animations for: BattleAnim_InSandstorm, BattleAnim_StringShot, BattleAnim_PetalDance, BattleAnim_Smokescreen, BattleAnim_QuickAttack, BattleAnim_MachPunch, BattleAnim_Spikes, BattleAnim_Sandstorm, BattleAnim_Swagger, BattleAnim_RapidSpin, BattleAnim_VitalThrow, BattleAnim_Extremespeed, BattleAnim_BeatUp

**Sfx_Metronome**:
- Plays in `data/moves/animations.asm` during the battle animations for: BattleAnim_Metronome, BattleAnim_Softboiled, BattleAnim_Swift, BattleAnim_GigaDrain, BattleAnim_Present, BattleAnim_BeatUp

**Sfx_MoveDeleted**:
- Plays in `engine/events/move_deleter.asm` when the player confirms having a move deleted at the Move Deleter's house

**Sfx_MovePuzzlePiece**:
- Plays in `engine/games/unown_puzzle.asm` when picking up or placing a puzzle piece in the Ruins of Alph Unown Puzzles
- Plays in `data/moves/animations.asm` during the battle animations for: BattleAnim_Bonemerang, BattleAnim_Thrash, BattleAnim_Rage, BattleAnim_Outrage

**Sfx_NoSignal**:
- Plays in `engine/phone/phone.asm` (Phone_NoSignal) when a Pokégear phone call cannot connect due to no signal

**Sfx_NotVeryEffective**:
- Plays in `engine/battle_anims/anim_commands.asm` (PlayHitSound) when a move hits for not very effective damage, selected based on the type effectiveness value in `wTypeModifier`

**Sfx_PayDay**:
- Plays in `data/moves/animations.asm` (BattleAnim_PayDay) during the Pay Day move battle animation
- Plays in `engine/games/slot_machine.asm` when placing a bet and starting a round at the slot machine
- Plays in `engine/games/card_flip.asm` during the card flip game when coins are won

**Sfx_PlacePuzzlePieceDown**:
- Plays in `engine/events/field_moves.asm` during the Cut field move animation when used on applicable tile types
- Plays in `engine/sprite_anims/functions.asm` when a sprite finishes sliding horizontally to its destination during certain animations
- Plays in `engine/games/unown_puzzle.asm` when successfully placing a held puzzle piece into an empty tile in the Ruins of Alph Unown Puzzles
- Plays in `engine/games/slot_machine.asm` during slot reel animations

**Sfx_Poison**:
- Plays in `data/moves/animations.asm` (BattleAnim_Psn) during the Poison and Toxic move battle animations
- Plays in `engine/events/poisonstep.asm` (.PlayPoisonSFX) each time the player takes a step while poisoned in the overworld

**Sfx_PokeballsPlacedOnTable**:
- Plays in `engine/sprite_anims/functions.asm` during the trade animation when Poké Balls slide onto the trading table
- Plays in `engine/games/card_flip.asm` periodically during the card flip game's setup animation

**Sfx_Pokeflute**:
- Plays in `engine/items/item_effects.asm` when the Poké Flute item is used in the overworld to wake sleeping Pokémon

**Sfx_Potion**:
- Plays in `engine/items/item_effects.asm` (HealHP_SFX_GFX) when a Potion or any HP-restoring item heals a Pokémon
- Plays in `engine/movie/trade_animation.asm` during the trade tube link animation sequence

**Sfx_PushButton**:
- Plays in `mobile/mobile_40.asm` (Function1033af) when pressing a button in the Mobile System's interface

**Sfx_QuitSlots**:
- Plays in `engine/games/slot_machine.asm` when the player's slot machine session ends and the game returns to the overworld
- Plays in `engine/games/card_flip.asm` when the card flip game ends and the player exits

**Sfx_ReadText**:
- Defined in `audio/sfx_pointers.asm` but never directly referenced in code; shares identical sound data with `Sfx_ReadText2` as both labels point to the same channel definitions in `audio/sfx.asm`

**Sfx_RegisterPhoneNumber**:
- Plays in `maps/ElmsLab.asm` when receiving Professor Elm's phone number at the start of the game
- Plays in `maps/RadioTower2F.asm` when registering Buena's phone number at the Radio Tower
- Plays in `maps/BillsFamilysHouse.asm` when registering Bill's family's phone number
- Plays in `engine/events/std_scripts.asm` (RegisteredNumberMScript) as the generic script used whenever any trainer or NPC's number is successfully saved to the Pokégear

**Sfx_Run**:
- Plays in `engine/battle/core.asm` when the player successfully runs from a wild Pokémon battle
- Plays in `engine/battle/core.asm` when the player gets away safely (separate call via WaitPlaySFX)
- Note: a known bug causes this SFX not to play correctly when a wild Pokémon flees from battle (documented in `docs/bugs_and_glitches.md`)

**Sfx_Save**:
- Plays in `engine/menus/save.asm` when the game is saved via the start menu or during PC box operations
- Plays in `maps/BattleTowerBattleRoom.asm` when the Battle Tower performs a quicksave after completing a battle

**Sfx_SecondPartOfItemfinder**:
- Plays in `engine/events/itemfinder.asm` (.ItemfinderSound) repeatedly as part of the Itemfinder beep pattern when a hidden item is nearby
- Plays in `engine/events/heal_machine_anim.asm` (.LoadBallsOntoMachine) for each ball placed onto the Pokémon Center healing machine during the heal animation
- Plays in `maps/CeruleanCity.asm` at specific item-hiding locations reacting to the Itemfinder

**Sfx_ShutDownPc**:
- Plays in `engine/events/pokecenter_pc.asm` (PC_PlayShutdownSound) when the player logs out or exits the PC
- Note: also defined but unreferenced in `engine/phone/phone.asm` (HangUp_ShutDown), which is an unreferenced function

**Sfx_SlotMachineStart**:
- Plays in `engine/games/slot_machine.asm` when the reels begin spinning after the player presses the button to start a slot machine round
- Plays via the text system (`home/text.asm` TextSFX table, `TX_SOUND_SLOT_MACHINE_START`) for text-embedded triggers
- Plays in `engine/games/card_flip.asm` at the start of the card flip game

**Sfx_Squeak**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase

**Sfx_StopSlot**:
- Plays in `engine/games/slot_machine.asm` each time one of the three reels stops spinning when the player presses A during a slot machine round

**Sfx_Strength**:
- Plays in `engine/overworld/map_objects.asm` when a Strength boulder is successfully pushed by the player
- Plays in `engine/overworld/events.asm` and `engine/events/overworld.asm` during Strength boulder interactions
- Plays in `data/moves/animations.asm` during the battle animations for: BattleAnim_RockThrow, BattleAnim_RockSlide, BattleAnim_Strength, BattleAnim_SeismicToss, BattleAnim_SleepTalk, BattleAnim_Magnitude
- Plays in `maps/BrunosRoom.asm`, `maps/WillsRoom.asm`, `maps/KogasRoom.asm`, `maps/LancesRoom.asm`, `maps/KarensRoom.asm` — the Elite Four chamber door-opening sequences
- Plays in `maps/BlackthornGym2F.asm`, `maps/CianwoodGym.asm`, `maps/TinTower1F.asm`, `maps/IcePathB1F.asm` — puzzle/boulder interactions in those areas
- Plays in all four `maps/RuinsOfAlph*Chamber.asm` files during the sliding puzzle solutions

**Sfx_SuperEffective**:
- Plays in `engine/battle_anims/anim_commands.asm` (PlayHitSound) when a move hits for super effective damage, selected based on the type effectiveness value in `wTypeModifier`

**Sfx_SweetScent2**:
- Plays in `data/moves/animations.asm` (BattleAnim_SweetScent) as a secondary sound cue during the Sweet Scent battle animation

**Sfx_SwitchPockets**:
- Plays in `engine/items/pack.asm` when the player presses left or right to cycle between the Bag's item pockets (Items, Balls, KeyItems, TMs/HMs, PC)

**Sfx_SwitchPokemon**:
- Plays in `engine/pokemon/mon_menu.asm` when swapping two moves in the move reorder screen
- Plays in `engine/pokemon/learn.asm` when a Pokémon learns a new move by swapping it with an old one
- Plays in `engine/pokemon/switchpartymons.asm` when the player reorders Pokémon in the party menu
- Plays in `engine/sprite_anims/functions.asm` during the trade send animation
- Plays in `engine/items/pack.asm` when switching Pokémon order via the Bag
- Plays in `engine/events/pokecenter_pc.asm` during the PC Pokémon swap animation
- Plays in `maps/RuinsOfAlphResearchCenter.asm` as part of the scientist's PC sequence

**Sfx_Tally**:
- Plays in `maps/TeamRocketBaseB1F.asm` when the player activates the secret switch that shuts off the security cameras
- Plays in `maps/RuinsOfAlphResearchCenter.asm` as part of the scientist's PC item-reveal sequence

**Sfx_ThrowBall**:
- Plays in `data/moves/animations.asm` (BattleAnim_ThrowPokeBall) as the throwing sound at the start of every Poké Ball throw animation (all ball types)
- Plays in `engine/games/slot_machine.asm` during a slot reel animation
- Plays in `mobile/mobile_42.asm` during the Mobile Battle system's ball-throwing sequence

**Sfx_TitleScreenEntrance**:
- Plays in `engine/movie/title.asm` once when the title screen loads and Suicune's animation begins

**Sfx_TrainArrived**:
- Plays in `engine/events/magnet_train.asm` (.TrainArrived) when the Magnet Train pulls into the station

**Sfx_Transaction**:
- Plays in `engine/menus/options_menu.asm` when the player exits the Options menu, confirming their settings
- Plays in `engine/items/mart.asm` when completing a purchase at a Poké Mart
- Plays in `engine/pokemon/move_mon.asm` when moving a Pokémon to or from the PC
- Plays in `engine/events/itemfinder.asm` as part of the Itemfinder beep pair (alternates with `Sfx_SecondPartOfItemfinder`)
- Plays in `engine/events/std_scripts.asm` for generic item-trade or shop confirmation scripts
- Plays in `engine/events/buena.asm` when spending points at Buena's Password show
- Plays in `engine/events/mom.asm` when Mom withdraws or deposits money from savings
- Plays in `maps/GoldenrodGameCorner.asm`, `maps/CeladonGameCornerPrizeRoom.asm` when exchanging coins for prizes
- Plays in numerous other map scripts for shop and exchange interactions

**Sfx_Unknown60**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase

**Sfx_Unknown61**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase

**Sfx_Unknown63**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase

**Sfx_Unknown66**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase

**Sfx_WallOpen**:
- Defined in `audio/sfx_pointers.asm` but never referenced anywhere in the codebase; likely intended for the Ruins of Alph chamber wall-opening sequences, which instead use `SFX_STRENGTH`

**Sfx_WarpFrom**:
- Plays in `engine/events/overworld.asm` when the player uses Dig or Escape Rope to warp out of a dungeon
- Plays in `maps/BurnedTowerB1F.asm` when the three legendary beasts (Raikou, Entei, Suicune) break through and escape
- Plays in `maps/TinTower1F.asm`, `maps/Route42.asm`, `maps/Route36.asm`, `maps/CianwoodCity.asm` for specific warp/fade-out events

**Sfx_WarpTo**:
- Plays in `engine/overworld/tile_events.asm` (GetWarpSFX) for warp panel tiles (transport pads, teleporters)
- Plays in `data/moves/animations.asm` (BattleAnimSub_WarpAway) during the warp send-out battle animation
- Plays in `engine/events/overworld.asm` for scripted teleport arrivals
- Plays in `engine/events/sacred_ash.asm` when the Sacred Ash item effect triggers
- Plays in `maps/SproutTower3F.asm`, `maps/LakeOfRage.asm`, `maps/CinnabarIsland.asm`, `maps/IndigoPlateauPokecenter1F.asm` for specific warp-arrival events

**Sfx_Wrong**:
- Plays in `engine/battle/core.asm` when an invalid switch target is chosen during battle (e.g., already fainted or same Pokémon)
- Plays in `engine/pokemon/bills_pc.asm` for various invalid actions on the PC (full box, no Pokémon to withdraw, etc.)
- Plays in `engine/items/tmhm.asm` when a TM/HM cannot be taught to the selected Pokémon
- Plays in `engine/events/move_tutor.asm` when the Move Tutor cannot teach the move to the selected Pokémon
- Plays in `engine/games/unown_puzzle.asm` when trying to place a puzzle piece in an invalid position
- Plays in `engine/games/card_flip.asm` for an invalid card flip action
- Plays in `maps/RadioTower1F.asm` when a wrong answer is given during the Radio Tower quiz
- Plays in various `mobile/*.asm` files for invalid inputs in the Mobile System adapter menus

## Battle Moves SFX 
gbs_sfx_aeroblast.s
gbs_sfx_attract.s
gbs_sfx_batonpass.s
gbs_sfx_beatup.s
gbs_sfx_bellydrum.s
gbs_sfx_bind.s
gbs_sfx_bite.s
gbs_sfx_boneclub.s
gbs_sfx_bubblebeam.s
gbs_sfx_charge.s
gbs_sfx_cometpunch.s
gbs_sfx_curse.s
gbs_sfx_cut.s
gbs_sfx_doublekick.s
gbs_sfx_doubleslap.s
gbs_sfx_eggebomb.s
gbs_sfx_ember.s
gbs_sfx_encore.s
gbs_sfx_flash.s
gbs_sfx_foresight.s
gbs_sfx_gigadrain.s
gbs_sfx_headbutt.s
gbs_sfx_healbell.s
gbs_sfx_hornattack.s
gbs_sfx_hydropump.s
gbs_sfx_hyperbeam.s
gbs_sfx_jumpkick.s
gbs_sfx_karatechop.s
gbs_sfx_kinesis.s
gbs_sfx_kinesis2.s
gbs_sfx_leer.s
gbs_sfx_lick.s
gbs_sfx_meanlook.s
gbs_sfx_megakick.s
gbs_sfx_megapunch.s
gbs_sfx_milkdrink.s
gbs_sfx_mindreader.s
gbs_sfx_moonlight.s
gbs_sfx_morningsun.s
gbs_sfx_nightmare.s
gbs_sfx_outrage.s
gbs_sfx_peck.s
gbs_sfx_perishsong.s
gbs_sfx_poisonsting.s
gbs_sfx_pound.s
gbs_sfx_powder.s
gbs_sfx_present.s
gbs_sfx_protect.s
gbs_sfx_psybeam.s
gbs_sfx_psychic.s
gbs_sfx_rage.s
gbs_sfx_raindance.s
gbs_sfx_razorwind.s
gbs_sfx_return.s
gbs_sfx_sandstorm.s
gbs_sfx_scratch.s
gbs_sfx_screech.s
gbs_sfx_sharpen.s
gbs_sfx_shine.s
gbs_sfx_sing.s
gbs_sfx_sketch.s
gbs_sfx_sludgebomb.s
gbs_sfx_snore.s
gbs_sfx_spark.s
gbs_sfx_spiderweb.s
gbs_sfx_spite.s
gbs_sfx_stomp.s
gbs_sfx_submission.s
gbs_sfx_supersonic.s
gbs_sfx_surf.s
gbs_sfx_sweetkiss.s
gbs_sfx_sweetkiss2.s
gbs_sfx_sweetscent.s
gbs_sfx_swordsdance.s
gbs_sfx_tackle.s
gbs_sfx_tailwhip.s
gbs_sfx_thief.s
gbs_sfx_thief2.s
gbs_sfx_thunder.s
gbs_sfx_thundershock.s
gbs_sfx_toxic.s
gbs_sfx_unknown5f.s
gbs_sfx_vicegrip.s
gbs_sfx_vinewhip.s
gbs_sfx_watergun.s
gbs_sfx_whirlwind.s
gbs_sfx_wingattack.s
gbs_sfx_zapcannon.s


# Useful Links
HGSS Super Music Collection: https://archive.org/details/pkmn-hgss-soundtrack/Disc+1/14+-+Hurry+Along+2.flac
