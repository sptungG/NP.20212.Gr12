## Exercise 1. Toxic chemicals

*Create a `Makefile` to make an executable file with the name **exercise1***

**Description:**
One of the most important problems while dealing with fire or emergency knows the chemical types.
Therefore, vehicles carrying toxic chemicals or factories need to display warning signs.
These signs show the HAZCHEM code with 2-3 characters providing necessary information to deal with fire or use suitable fire extinguishers.
A HAZCHEM code describes materials/tools needed to handle chemicals and protective clothes for the work.
Additionally, these codes provide corresponding chemical to neutralize or extinguish toxic chemicals.

Each HAZCHEM contains 2-3 characters.
The first character is a number ranged from 1-4 indicating chemical form,

![first](https://user-images.githubusercontent.com/61298021/163710663-cbcbdfa6-4d69-45a8-8251-453c473bf0a7.png)

The second character indicates chemical characteristics, protective clothes and whether the chemicals need to be contained.
Second character could be P, R, S, T, W, X, Y or Z.
Character S, T, Y or Z could have the color of white or black.
The following table indicates character and reference to necessary information

![Second](https://user-images.githubusercontent.com/61298021/163710637-3816e875-6204-4a42-85c2-ff09b6ec19ac.png)

* Interactive:
  * V – can be violently reactive
* Protective :
  * Full – full protective clothing must be worn
  * BA – breathing apparatus, protective gloves for fire only
* Containment:
  * Dilute – the dangerous goods may be washed down to a drain with a large quantity of water
  * Contain – a need to avoid spillages from entering drains or water courses.

The third character in a HAZCHEM code (if had) indicates whether evacuation is needed

![image](https://user-images.githubusercontent.com/61298021/163710745-70b3ad02-5ca7-48f7-91f3-f67d3a209b87.png)

Emergency actions need to be done according to HAZCHEM codes.

**Requirements:**
Write a problem asking users to input a HAZCHEM code and show emergency actions to the screen. If a user input one of S, T, Y, or Z character, that user need to give the color of the code.

*Note:* The program needs to check the validity of the input HAZCHEM. The following lines are an example of running that program

```sh
Enter HAZCHEM code: 3SE
Is the S reverse coloured? yes
***Emergency action advice***
Material: foam
Reactivity: can be violently reactive
Protection: breathing apparatus, protective gloves for fire only
Containment: may be diluted and washed down the drain
Evacuation: consider evacuation
*****************************
```