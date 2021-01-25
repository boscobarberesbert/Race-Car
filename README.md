# Race Car | B.A.T. Studios

Link to the repository: [B.A.T. Studios' Race Car in GitHub](https://github.com/boscobarberesbert/Race-Car)

Link to the latest release: [Race Car newest release](https://github.com/boscobarberesbert/Race-Car/releases/tag/v1.0)

## Description

Race Car game developed by 3 students at CITM-UPC, in Barcelona. It has been developed with Bullet for the physics, and OpenGL and SDL as the render tools.

![Screenshot 1](https://user-images.githubusercontent.com/59050279/105526191-5a2a0680-5ce2-11eb-9c55-cc886603bef4.jpg)
![Screenshot 2](https://user-images.githubusercontent.com/59050279/105526199-5c8c6080-5ce2-11eb-8817-930e0d79831f.jpg)
![Screenshot 3](https://user-images.githubusercontent.com/59050279/105526211-5f875100-5ce2-11eb-96bc-59429891a7d3.jpg)
![Screenshot 4](https://user-images.githubusercontent.com/59050279/105526224-62824180-5ce2-11eb-8776-d5609cb699c2.jpg)
![Screenshot 5](https://user-images.githubusercontent.com/59050279/105526231-64e49b80-5ce2-11eb-8f5c-fa9720520a1b.jpg)

## Key Features

 - Scenario and ground, with platforms and traps.
 - The world has gravity.
 - Car moves with player input.
 - Camera follows the movement of the car.
 - Constraints for some elements in the level.
 - Countdown using timer as the game condition (when completing a lap or running out of time).
 - A simple HUD with the timer and an indicator showing the current part of the level.

## Goal of the Game

The game is about completing a full lap of the circuit dodging the different obstacles, reaching the platforms and achieving the different checkpoints in order before the countdown reaches zero. The checkpoints allow the player to recover from the last fall and save some of the time. 

- The red balls return the player to the last achieved checkpoint and the yellow ones just hit the player. 
- When the time runs out, the entire game is restarted (returns to the start) and the player loses all the achieved checkpoints.
 
## Controls

### Player movement

|Key|Action|
|---|------|
|W|Accelerate Forward|
|A|Turn Left (Rotate in mid-air)|
|S|Accelerate Backward|
|D|Turn Right (Rotate in mid-air)|
|🡳|Hand Brake|
|🡰|Rotate Left (Torque)|
|🡲|Rotate Right (Torque)|
|ESC|Quit Game|

### DEBUG Keys

|Key|Action|
|---|------|
|F1|Physics Debug View|
|F2|Framerate Debug Window Title|
|F3|Reset Checkpoint|
|F4|Reset Level|

## Developers

 - Alejandro Ávila [Omicrxn](https://github.com/Omicrxn) - Developer & Designer
 - Bosco Barber [boscobarberesbert](https://github.com/boscobarberesbert) - Developer & Designer
 - Yeray Tarifa [yeraytm](https://github.com/yeraytm) - Developer & Designer

## License

This project is licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
