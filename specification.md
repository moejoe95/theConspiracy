# Specification

The project follows loosely the specification given [here](https://git.uibk.ac.at/c7031162/703807-advanced-cxx/blob/master/assignment2/metroidvania_specification.md). However, the given specification is designed for teams of three people, therefore some shortcuts are taken. Below is an adjusted list of goals.

## Description

Aim of this project is a simple 2D metroidvania-like game. It takes place in an post-apocalyptic world. The character makes progress by moving to the right and defeating enemies through his way. In the final room a boss-enemy, capable of a special attack, waits. 


The game launches in the main menu. The menu includes 3 options: *continue*, *new game*, and *exit*. While inside the game, the player can get to the main menu by pressing `ESC` or `Q`. Note that the menu is only usable with the mouse.

At the beginning of each room the state of the game is saved. If the save point is passed, a message is displayed at the top right corner. If the state was saved, the player can escape the game and continue with the previous state by pressing *continue* in the main menu. The previous saved state is discarded once a new game is started.

The player moves around with the keys `wasd`, and is able to fire his gun with `space`. Once a enemy gets hit, it starts to fire back. The time between its attack is randomized. If it is capable of more than one attack (only the boss), the action selection is also done randomly. Enemies do also harm when they are in direct contact to the player.

Not only enemies can do demage, also special objects in the environment: the lava floor and spikes. Additionally there are two special objects that can be picked up from the environment: health and ammo boxes to refill the life and ammo score.

Inside the game a very simple HUD menu in the top left corner displays life and ammo stats.

After the game is launched background music plays. The same music continues during playing. The background music changes to something more dramatic when the final room is entered. Special sound effects are used on: firing up a gun, picking up health/ammo boxes, dying, and wining.

The game ends if either: the player dies, or the player is able to beat the final boss and move to the end of the last room.


## Goals

The proposed shortcuts for the goals defined in the specification are: no advanced movement mechanics, no maps, and less rooms. Other goals are adjusted and re-weighted as follows:

- (2) 3 consecutive rooms with:
    - each with its own design
    - 2-3 enemies per room
    - boss enemy in the final room
  
- (2) basic movement
    - running left / right
    - jumping
    
- (1) interactions with environment
    - collecting game entities (health/ammo boxes)
    - static obstacles that cause demage (lava, spikes)
  
- (1) dedicated save points
    - state is saved at the beginning of each room (except first room)
    - latest state is loaded if 'continue' is pressed in menu

- (1) main combat
    - range based attack (gun shooting)
    - hitting enemies
    - getting hit by enemies
  
- (1) enemies
    - attack the player character as it gets in range
    - range based attacks
    - direct contact causes demage

- (1) boss
    - capable of special attack (throw granade)

- (1) sound effects
    - default background sound
    - special background sound for final room (more dramatic)
    - suitable sounds for: picking up health/ammo packages, shooting
    - sound for game over (fail and win)

- (1) menus
    - main menu
        - new game
        - load game
        - exit
    - game over
        - player dies
        - player defeats final boss

- (0) HUD
    - give status information on screen (life, ammo)
