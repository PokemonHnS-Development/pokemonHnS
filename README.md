![HnS Logo](HnS_Logo.png)

# Pokemon Heart & Soul
Heart & Soul is a faithful retelling of the story of the Johto Region on the GBA built using Modern Emerald as a base, meaning there are many quality of life features included. This demake/remake contains the story of Crystal, but also contains many features from HGSS. This project aims to be the definitive Johto experience on the GBA, but also to serve as a framework for future developers who would like to add more customization such as randomization and nuzlocking.

![HnS Collage](HnS_Logo.png) <- placeholder for collage

## About the game: 
### Features
- Generation 1-3 Pokemon plus their later gen evolutions (excluding Regis and Jirachi)
- Full Johto story and Kanto postgame
- Overworld background Pokemon serve to enhance the vibe and show you the notable encounters on each route
- Day/Night System with variable encounters
- Apricons replaced with berries, Kurt will use them to make pokeballs
- Timekeeping does not track days of the week, Everything is progression based
- Two Safari Zones
- HMs do not need to be taught to a Pokemon in order for it to be used
- Customizable shiny rate
- Following pokemon
- AutoRun/FastSurf are toggleable
- Quick run from wild battles using button combination
- Ball prompts for quick catching 
- ... and much more!

## Download
### Download the .zip containing patch files in the [**Releases**](https://github.com/PokemonHnS-Development/pokemonHnS/releases) Section.

**The .zip file contains 8 Files:**
- A patch file for HnS, to be patched to Emerald.
- High Profile Trainer Doc
- Item Locations Doc
- Encounter Doc
- Evolution Methods Doc
- Completion Doc
- Breeding Methods Doc
- ReadME file

## Patching your ROM
Use [Rom Patcher JS](https://www.marcrobledo.com/RomPatcher.js/legacy/) to patch the files.
**You will need to provide your own **legally obtained** copy of Emerald.**
- Upload the Emerald.gba file to the "ROM file" section
- Upload the HnS patch file to the "Patch file" section
- Look for a green checkmark and hit apply patch. 
This will automatically download your new Heart & Soul.gba ROM for you to play!

## Recommended Emulators
- For PC/Mac: mGBA
- For Android: pizzaboy, Lemuroid, Retroarch w/ mGBA core.
- For IOS: Retroarch w/ mGBA core, Ignited.
- For Linux Handheld Devices: Retroarch w/ mGBA core.
  
## Support
For further assistance, join the [discord](link pending)!

## Credits
See the [pokecommunity](insert link) page for full credit information.


# For Developers

## Pokémon Modern Emerald 

This project is based on the decompilation of Pokémon Emerald, edited to be "Pokémon Modern Emerald".
You can get more information about Modern Emerald by resetes12 at [Pokecommunity](https://www.pokecommunity.com/showthread.php?t=494005) and at [Github](https://github.com/resetes12/pokeemerald).

## If you want to compile:

Please follow [Pret's guide on how to build the rom](https://github.com/pret/pokeemerald/blob/master/INSTALL.md) but using this branch instead of theirs. 
When you compile, use the modern compiler with "make modern". Compiling using the old compiler won't work.

## Modern Emerald Features: (not all present in Hns)

**Selectable options (at the start of the game):**

**Gamemode**
* Choose between a "Classic" or "Modern" preset, or customize it to your liking.
* Modern Spawns: You can now capture the 423 new Pokémon available. Only changes wild Pokémon, not trainers. Modern Spawns have also a Night encounter version for each route, making certain Pokémon night exclusive.
* Modern Typings: Some Pokémon have their types changed to buff them.
* Add Fairy Type: Adds Fairy Type to Pokémon that had it added in Generation 6.
* Better Stats: Some Pokémon have their stats changed to buff them.
* Extra Legendaries: Adds new legendaries that weren't available in vanilla Emerald.
* Legendary abilities: Buffs some legendaries giving them a better ability than "Pressure".
* Modern Movepool: Adds 15 new moves, and modifies all Pokémon movepool to add them.
* Nature mints: Adds nature mints to the game, available after the 4th gym.
* Synchronize: Choose if this ability works like in modern games or like in Gen 3.
* Sturdy: Choose if this ability works like in modern games or like in Gen 3.
* Reusable TMs: Choose between a faithful usage of TMs or a simplistic option that makes TMs infinite. All TMs can be bought in the Battlefrontier PokéMart only if you have Reusable TMs off, and makes Move Tutors one time only just like in the original (Move tutors are infinite if you enable Reusable TMs).
* Citrus berry: Choose if it works like Gen 3 or like Gen 4+.
* Survive Poison: If enabled, your Pokémon will survive poison damage with 1hp when outside of battle.
* Features
* RTC Type: Choose between using a real clock, or using a fake clock. Fake clock rate is 1h irl, 1 day ingame.
* Shiny Chance: 8192 (Emerald default) - 4096 (Gen VI+) - 2048 - 1024 - 512.
* Item Drops: Items held by wild Pokémon, when defeated, will be dropped and obtained by the player. Forget about catching it or using Thief!
* Pokémon Faint: Your Pokémon will stay in the FAINTED status, meaning that you can't use them again. CAREFUL as it could end your adventure if you lose all your Pokémon (Previously known as Perma Faint).
* Uncaped wondertrade.
* Easier Feebas: If enabled, Feebas have a 5% chance to appear around all Route 119.

**Randomizer: (not implemented in HnS)**
* Includes every option that any randomizer can have, and it's completely modular. 

**Nuzlocke: (not implemented in HnS)**
* Any option that any Nuzlocker would want to use. (not implemented in HnS)

**Difficulty:**
* Lock difficulty: locks the current select option that was selected during Birch's Speech and can't be changed ingame. Hard sets "Battle Style" to "Set" always. Beating the game disables the lock.
* Number of Party Members limit: From 1 to 5
* Level caps
* Exp. Multipliers
* Player items
* Trainer items
* Player IVs: Sets all IVs from wild Pokémon to 31, or if you choose "No (HP) , between 30 and 31 to allow for different Hidden Powers.
* Trainer IVs: If hard is selected together with "Player IVs", you'll completely remove IVs from the game.
* Player EVs
* Trainer EVs
* Play without Pokémon Centers

**Challenges:**
* PC doesn't heal
* Evolution limits
* One type only challenges
* Stat equalizers
* Mirror Mode
* Mirror Mode Thief

**Story related:**
* Gym rematches are easier to trigger. After 10 wild battles won, or 5 trainer battles won, there is a 50% chance of getting a rematch.
* The Elite Four can be rematched after battling with Steven, and they are double battles.
* After completing the Elite Four Rematch, a rematch with Steven will be available. You will get a unique, special prize.
* The Sealed Chambers puzzles have changed slightly. Learn braille and find out what changed!
* Also, there are 6 Regis. Try to discover where are the new 3!
* All the trainer rematches scale up a lot more than in the original game, and their parties have been changed.
* All the trainers in the Battle Frontier have new Pokémon in their teams and have been buffed or modified.
* All the gym leaders, Elite Four, the 2 champions, Wally, Magma / Aqua leaders, and Red and Leaf will appear during the Battle Frontier challenges.


**Pokémon related:**
* Following Pokémon (Optional, with a second option to enable or not Big Followers like Rayquaza).
* 40 new Pokémon species, mostly from Gen. IV and 3 from Gen 9 (Annihilape, Dudunsparce, Farigiraf).
* 1 new box space since 2.0.
* Night encounters. Certain species will have a higher rate during night and others will only be available during night (only with Modern Spawns).
* All the buffs from later generations are in (optional).
* Extra buffs for other Pokémon are in. Includes stats, abilities and/or typings. (Ex. Arbok is now POISON / DARK and Meganium is now GRASS / FAIRY). You can have a look at them in my personal document, on the "3. Pokémon changes" tab. (It's optional now)
* All the move buffs AND nerfs from later generations are in, with small changes to make them work in a 3rd gen game (optional).
* All Egg moves and tutor moves have been improved with data from later generations.
* New evolution methods.
* Pokémon inherit 5 IV's from their parents, no item needed.
* Everstone works on male or female Pokémon and guarantees nature.
* Gen. VIII Synchronize (optional).
* Kanto fossils are available in 3 different caves.
* Shuckle can make berry juice just like in Gen. II!! Yay?
* Nature Mints are available to buy in the Flower Shop after the 4th Gym (optional).
* Deoxys forms can be changed.
* Custom Shiny forms for some Pokémon.


**Battle related:**
* Modern Battle Frontier, Battle Tents and Trainer Hill. Your Pokémon will be limited to level 50 when playing in those battle facilities, even if your level is 100.
* 15 new moves from Gen IV to buff typings that didn't have a certain Physical / Special move. (Ex. Dark Pulse, as Dark type didn't have a Special Dark type move). (Now optional).
* Fairy type introduced.
* 3 New abilities for Regidrago, Regieleki and Arceus.
* Gen. VI EXP. SHARE and Gen III EXP. SHARE in the same game. "EXP. SHARE S" can be obtained at the Slateport Mart after obtaining the "EXP. SHARE" at Devon Corp.
* HM01 Cut is now Grass type, NightShade does 50 static damage, Hidden power is now 60 always, and shows the type in the summary screen and in battle, Charge now ups Sp. Def.
* EV Training available in Lilycove.
* IV Maximizer available in Lylicove, after beating the game. Needs a lvl.100 Pokémon.
* A nurse NPC is available after beating the game to farm EXP in Lilycove.
* Faster battle intros. Enable "Fast Intros" option in the options menu.
* Faster-paced battles. Enable "Fast Battles" option in the options menu.
* 3 beeps when low-health, then it stops.
* Press START while selecting a move to open a new Submenu with information about the selected move.
* Trainer class-based Pokéballs.
* Catching EXP.
* Macho Brace multiplies EV gain * 5.
* Gen. IV Sitrus Berry (optional).


**UI related:**
* New Pokédex! You can now see important information on the new "Stats" page. It's very, VERY useful and it's like having the game documentation in-game.
* Faster battle transitions ported from Fire Red.
* Hold L+R, then A when entering a Wild Battle to instantly run.
* You can now register 2 key items: Pressing (as usual) and holding SELECT!
* Swap Pokémon pressing SELECT.
* Colored Stats (red = good, blue = bad).
* Pressing L in the stats section of a Pokémon will bring the EVs, pressing R will bring the IVs, and pressing START will bring the default stats.
* HM moves don't need to be taught anymore. If you have a Pokémon that can use a certain HM, if you have the correct HM in the bag, and if you have the required badge, you will be able to perform an HM move.
* HM moves can be deleted since they are not that important anymore.
* TM had their price changed, especially if you are not using Infinite TMs.
* The bag now holds up to 90 items, and item capacity has been upgraded to x999.
* When the bag is full, items go to the PC.
* You can change the ball your Pokémon is in using a different ball from the bag.
* Reusable repel prompt.
* The time on the clock can be changed.
* Two pages with additional options in the options menu.
* Debug menu can be enabled by everybody so you can cheat or modify whatever you want. To enable it, just hold "SELECT" then press "START" inside the options menu and you'll hear a noise. Pressing "START" to open the menu from that moment will show a "DEBUG" option at the bottom. It can also be opened with "R" + "START". Be careful, using certain options can break your save so I'm not responsible for any misuse.


**Gameplay related:**
* Wonder-trade on the second floor of the Pokémon Center, available after the 5th badge (unless you are doing a randomizer, which makes it available from the start, or a challenge, which enables WT after beating the game). Can be uncapped now.
* 3 difficulty modes (EASY, NORMAL and HARD). Selected at the start of the game, can be changed anytime from the options menu.
    EASY mode: Makes the game quite a lot easier by scaling levels down, and obtaining more EXP (+20%).
    - Trainer Pokémon and Wild Pokémon scale down to 10 levels compared to the original game. More badges, less level.
    - There are no restrictions on the Battle Frontier.

    NORMAL mode: Vanilla.
    - No changes, except rematches and small things (also on EASY mode).

    HARD mode: Makes the game a bit more difficult by scaling levels up, and obtaining less EXP (-40%). This mode does not intent do be a "super difficult" hack-rom. It only tries to be a bit more difficult than vanilla.
    - Trainer Pokémon and Wild Pokémon scale up to 10 levels compared to the original game. More badges, more level.
    - Certain ace Pokémon have had their abilities or items changed to make everything a bit more difficult. This mode does not change anything else in trainer parties, or their strategies.
    - SET MODE is automatically selected and can't be disabled if you lock the difficulty.
    - There are more restrictions on the Battle Frontier.
    - The GEN VI Exp. Share will give less Exp. to the battling Pokémon.
    - Legendaries will have higher stats WHILE battling, to make it more challenging.
    - (OPTIONAL but recommended) Use in combination with scaling IV/EV trainers from the Challenge Menu at the start of the game for an interesting challenge. You can also lock the difficulty in the Challenges menu at the start of the game.
* Optional and recommended PHYSICAL / SPECIAL MOVE split from Gen. IV. Selected in the options menu, second page.
* New Challenge Menu at the start of the game.
* Bag capacity increased to 90,
* Day / Night System with Day / Night encounters. Now Daytime is from 6AM to 20PM. Night-time is from 20PM to 6AM. For (2 new) evolutions, Morning is from 6AM to 9AM. Also includes cool lighting at night!
* Run everywhere.
* Autorun (in the options menu).
* HM moves text and interaction is way faster.
* Link with Fire Red / Leaf Green available from the start.
* One-time tutors are infinite, but you have to pay now (only if Infinite TMs is on).
* Trainer HIll prizes are the berries that were not available in the GBA games.
* Match and Acro Bike are now one. Change between them by pressing "R".
* Chain fishing has been added.
* Easier fishing has been added to the options menu (FR/LG fishing).
* All tickets are available to buy, together with its events.
* Faster nurse Joy healing, and now with an even faster version in options.
* Daily money event with Meowth (post-game).
* You can check the Soot Sack to know how much ash you have.
* Interacting with berry trees is faster, berry trees that are in rainy routes don't need to be watered, and berry trees don't decay.
* Higher berry yield (6 max, 4 min).
* A new "Growth Mulch" item which makes berries instantly grow.
* New Self-trader to force trade evolutions (trading with another game still works).
* PokéMarts items change with every badge.
* AI improvements.
* Amulet coin works always, doesn't matter who has it.

**Map related:**
* Altering cave is now an Unown cave.
* A few new maps to introduce the new Regis and the legendary events.
* Mirage Island can be forced with a certain Pokémon in the party, apart from its unusual rate.