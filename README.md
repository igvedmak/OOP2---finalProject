# OOP2---finalProject
Remake of the original "Captain Claw" game using SFML

![Alt text](https://media.giphy.com/media/xcmVlEpoBxKYU/giphy.gif "Logo")
***
## **General**

In this project we made the classic game "Captain Claw" using wide verity of tools that we learned this year: Inheritance, polymorphism, RTTI, State design, singleton, mapping, exceptions and of course the graphic library SFML. We've been practicing game design while using complex classes.
In the game you are the one and only Captain Claw. A pirate cat whose goal (like any other pirate) is to achieve fortune and glory. You'll have to fight enemies who seek the same goal while trying not to die.  

***
## **Design**

Because of the game complexity and the fact it has many classes we will explain more generally.

![Alt text](https://image.ibb.co/bS7kuT/1.jpg "Object UML")


**Object** – The base class for every object that can be drawn in our game. Hold properties like position and sprite. Has some basic functions for objects like 'get' and 'set' for position, sprite and etc.

**StaticObject** – Inherits from 'Object'. Base class for every static object in the game.

**DynamicObject** - Inherits from 'Object'. Base class for every dynamic object.

**Player** – Inherits from 'DynamicObject'. Represents the player class

**Enemy** - Inherits from 'DynamicObject'. Represents the enemies' class. Has 2 types of enemies, smart and dumb.

**Shots** - Inherits from 'DynamicObject'. Represents the shoot able objects in the game such as TNT, bullets etc.

**Obstacle** – Inherits from 'StaticObject'. Represents every obstacle the player might meet in the game such as spikes, breakable tiles etc

**Tile** - Inherits from 'StaticObject'. This it the class for the tiles on the map (walls, walking tiles etc.)

**Pickup**- Inherits from 'StaticObject'. Represents every object the player might pickup. Such as health potions, coins etc.

![Alt text](https://image.ibb.co/mTBZoo/2.jpg "Menu UML")

**MenuButton**- This class and those who inherit from it are the buttons for the menu.

![Alt text](https://image.ibb.co/kx9b18/3.jpg "GameState UML")

**GameState** – This class and those who inherit from it are the states the game might be in. Such as pause, end.

![Alt text](https://image.ibb.co/fxzLTo/4.jpg "Commands UML")

**Command** - this class and those who inherit from it are the commands the player may use. Such as walking left or right, shooting, attacking and jumping.

![Alt text](https://image.ibb.co/kE778o/5.jpg "Other UML")

**Board** – Responsible to manage the board and load the levels

**Camera** - Manages how the camera focuses on the player

**Constants** – hold all the const values in the game

**Entity** – Manages the player characters entity

**GameClock** – Manages the game clock

**GameManager** – manages the game. The "glue" for all the other classes

***
## **Data Structures and Role**

**STL DUST**- Static and dynamic objects had their own vector of 'shared_ptr'. Stack that holds and manages the game states of 'unique_ptr' type. Many 'multimaps' to hold in an organized way the files with labels so we could find them easily. Furthermore, the collision map is being used in the 'CollisionMnager' to quickly grab the right function for the current collision.

***
## **Algorithms Worth Mentioning**

We made a 'Pixel Perfect' collision in the game. Instead of the regular SFML style collision which only uses the bounding rectangle of the texture to check for collision, our game takes every texture, Process the image so it makes a mask of bits of the actual pixels in the sprite and checks the collision by the pixel.
The jumping mechanism of the game works by a simple physic formula which calculates the distance and height of the character should go depending on the mass of the character and how long the jump key was pressed.

***
## **Known Bugs**
In some places, the player character can get stuck. This caused by the 'pixel perfect' collision.
