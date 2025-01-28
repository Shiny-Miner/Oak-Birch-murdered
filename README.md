### Sasta advertisement mere server ka; for any queries join : https://discord.com/invite/axNX3rhR9K
# What's this?
#### This code adds professor birch's briefcase and enables us to create RSE (Ruby/Sapphire/Emerald) style starter selection in pokemon fire red.
## This code is created by Shiny Quagsire and it uses a very old template.
# How to compile?
Open the repo in powershell window using cd for shift + right click of mouse and selecting open powershell window here. 
#### Tools used : Devkitarm (idk others used here)
#### Put a rom named ALP.gba in the repository and run command : bash compile.sh using powershell
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



https://github.com/user-attachments/assets/f5a4ae95-6860-4e41-8fab-3cc87249ca9a



