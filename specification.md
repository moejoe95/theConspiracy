# Specification

The project follows loosely the specification given [here](https://git.uibk.ac.at/c7031162/703807-advanced-cxx/blob/master/assignment2/metroidvania_specification.md). However, the given specification is designed for teams of three people, therefore some shortcuts are taken. Below is an adjusted list of goals.

## Description

...

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
