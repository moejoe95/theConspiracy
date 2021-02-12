# TODO's

[x] bullet rendering second screen
[x] delete serialized objects on new game
[ ] end boss
[ ] write specification of game
[x] respawn enemies if new game
[x] pick up items (health, ammo)
[x] play sound on pickup
[ ] serialize room (to reload correct map)
[ ] improve enemy AI
[ ] place multiple enemies on map

[ ] refactor manager acessing (renderer, soundmanager, collisionmanager), maybe service locator pattern
[ ] refactor folder structure (external libs)
[ ] refactor naming of members, getters, setters
[ ] rename root folder
[ ] change build type to release
[ ] check for memory leaks with valgrind
[ ] check build with Werror and Wall


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
