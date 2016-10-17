# Traffic
Traffic 2D race in cocos2d-xv3.11

TO DO:

Physics:
  - Collision detection system
  - Overtaking logic (Point of overtaking, bot overtaking when user_car nearby algorithm, 1.5*WIDTH_LINE change to 1.7-2)
  - Overtaking to one line bots (BUG)
  
Graphics:
  - Animation fix police car
  - Road black stripe fix
  - Position of buttons
  - Stop and change line signals
  - Sounds (crash, emergency)
  
Game Logic:
  - Number of cars of current type, their positioning (trucks left, police right)
  - Do not add cars when 10-15 added (don't wanna have traffic jams)
  - Initial car position on third line
  
Design:
  - Layers (Main menu -> Choose game mode-> Game Layers (with scores) -> Game over layer
  - Game mode : coins for a minute
  - Game mode : one linear motion
  - Game mode : emergency mission (distance for some time -> to save live:))
  - Nitro
  - Faster Game
