# Traffic
Traffic 2D race in cocos2d-xv3.11

TO DO:

  <b>NEXT:</b>
  <b>To detect collisions - use box2d Engine (getBoundingBox method works incorrectly with rotated sprites</b>

Physics:
  - Collision detection system
  - Overtaking logic (Point of overtaking, bot overtaking when user_car nearby algorithm, 1.5*WIDTH_LINE change to 1.7-2)
  - Overtaking to one line bots (BUG)
  - Distance passed calculating
  - <i>Speed settings for cars, delta speed enable</i>
  
Graphics:
  - Animation fix police car
  - Road black stripe fix
  - Position of buttons
  - Stop and change line signals
  - Sounds (crash, emergency)
  - Android bar
  - Multi-resolution
  - Multitouch for gas and brakes
  
Game Logic:
  - <i>Number of cars of current type, their positioning (trucks left, police right)</i>
  - <i>Do not add cars when 10-15 added (don't wanna have traffic jams)</i>
  - <i>Initial car position on third line</i>
  
Design:
  - Layers (Main menu -> Choose game mode-> Game Layers (with scores) -> Game over layer
  - Game mode : coins for a minute
  - Game mode : two dimensional motion
  - Game mode : emergency mission (distance for some time -> to save live:))
  - Nitro
  - <i>Faster Game</i>

