# TODO's

## functional 

[x] bullet rendering second screen
[x] delete serialized objects on new game
[x] end boss (need special attack)
[ ] write specification of game
[ ] boss should guard item
[x] make sure enemies are on their place
[x] respawn enemies if new game
[x] pick up items (health, ammo)
[x] play sound on pickup
[x] serialize room (to reload correct map)
[x] improve enemy AI
[x] place multiple enemies on map
[x] fix serialization
[ ] save game at new room
[ ] add another backround sound for last room
[x] avoid player running off screen

## cosmetics

[ ] bounding box of player
[ ] increase font size in menu
[ ] make menu keyboard-usable
[x] different screen/sound for successful/unsuccessful game over
[ ] coharent use of logger/log levels
[ ] dead enemies should be visible longer
[ ] make player immune a short time after he lost some life
[ ] limit hit-rate of player

## non-functional

[x] refactor manager accessing (renderer, soundmanager, collisionmanager) -> use similar approach as in Raygun
[x] refactor folder structure (external libs)
[ ] refactor naming of members, getters, setters
[x] add soundmanager to game

## before hand-in

[ ] rename root folder
[ ] change build type to release
[ ] check for memory leaks with valgrind
[ ] check build with Werror and Wall
[ ] set default settings
[ ] activate sound



## Goals

- (2) two consecutive areas, each:
    - with its own tone (architecture, sprites, music, enemies etc)
    - with a handful of rooms each
    - a boss guarding an item / ability
  
- (2) basic movement
    - running left / right
    - jumping
    - interacting with game entities (doors, chests etc)
  
- (1) save / load with dedicated save points (rooms)

- (1) main combat
    - melee and/or ranged
    - hitting enemies
    - getting hit by enemies
  - 
- (2) enemies
    - attack the player character as it gets in range
    - variants with melee attacks
    - variants with ranged attacks
    - bosses are capable of using different attacks

- (1) menus
    - main menu
        - new game
        - load game
        - exit
    - pause menu
        - shows player stats
        - inventory management
        - continue
        - go to main menu
    - game over
        - player dies
        - player defeats final boss


## Proposed shortcuts


- no advanced movement mechanics
- no map
- less rooms (maybe 5-6 in total)
