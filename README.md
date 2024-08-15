# What's this?
#### This code adds professor birch's briefcase and enables us to create emerald style starter selection in pokemon fire red
## This code is created by Shiny Quagsire and it uses a very old template.
# How to compile?
If you had already compiled pokeemerald then you can compile it easily as we need to run a .sh file to compile.
#### Tools used : Devkitarm (idk others used here)
#### Put a rom named ALP.gba in the repository and run command : bash compile.sh
The code will compile to the ALP.gba rom , now you can call it easily using callasm 0x790001
#### To change where to insert it edit offset=790000 in compile.sh to your offset, remember you need to callasm the offset to which you're changing then.
# Changing pokemon shown in bag:
In main.c at line 24 , this part is given: 
#define starterUno 	1
#define starterDos 	4
#define starterTres	7
starteruno is the first ball pokemon and so on, I've set them for bulbasaur, charmander and squirtle. Change these numbers 1,4,7 for Pokemon's id in pokedex.
Here 1 is id for bulbasaur as you can see, if i change it to 2, an ivysaur will be shown in briefcase
# A screenshow
<image src="test_1723638189944.png"> </image>


- [Video Example](https://media.discordapp.net/attachments/1082555840281714789/1273245907881820171/Screenrecorder-2024-08-14-17-09-24-235.mp4?ex=66bf3ba8&is=66bdea28&hm=76de2d1264776fdf6e9b3e43a8099b1fc624dcf0e367fc7b18844ee12d0e2770&)
