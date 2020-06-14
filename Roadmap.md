# Roadmap for developing pkmnboy:

### Project:
- Define assets folders - DONE

- Define Tilemap files specs - DONE
* Background tiles
* Sprite tiles - DONE

- UI Menu tiles (are we using fonts? or do we want to bitmapped font?)
* Define UI Menu manager
* Implement UI Menu

### Visuals:
- Create basic sprites to have as a minimun executable game.
* create a room DONE
* create a character DONE
* create some objects to collide with DONE 
Nice to have
* Create a "world" outside the room, in order to handle change from indoor to outdoor. - DONE

### Game Engine Features
- Player movement - DONE
- Collision detection: Wall - DONE
- Camera - DONE
- Collision detection: Objects - DONE

- Map change - DONE

- Menu

- Dialogue
* Create the window/panel/box (SDL Rect) Entity - Done
Create a specific asset with a GUI component that will draw a DialogBox
There will be a specific texture file for any type of GUI element (DialogBox, Menu, etc)
* Being able to show and hide the box
* Read some Text (text Manager / add fonts)
* Dialogue in map: talk to another character, interact with an object

- Layers Definition (abstractions)
* i.e. create Background layer that supports 4 colors, read a specific tile file 
- Define Characters behaviours:
* Statuses: Idle, Walk, etc - DONE 
(SpriteComponent is in charge of that)
- Define how .map files works
An the moment, it has 2 "matrix"
* the first one contains int with 2 digits, that matches a (x,y) coordinate for the
background tile file (so it will look for position x,y and get the tile according to the size)
* the second one defines the collision for the given map




------------------

Preventive collision - Kind of done

* current:
- player gets the last "valid" position
- Collision is detected
- player tries to move in toward the wall
- destPosition now is an unreachable state
BUG - END

Posible workoaround
- player reachs the last valid position
- Collision is detected
b) Game knows it's last valid position, flagging to avoid movement towards that direction
(Block that direction)
- Player tries to move again in the same direction
a) TransformComponent checks if new destPosition is a valid position.

------------------

Known bugs/issues:

- Moonwalk: I think this is caused by the KEY event managing not only the movement transform action, but also coupling the Sprite animation
to the key event, instead of the movement action itself. This means, that a possible solution could be to move all the Animation changes
to the Transform Component, so when the "fixed movement" takes places, we play the Animation (that will long until the movement is done, not
until you stop pressing a movement key)  

