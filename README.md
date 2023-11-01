# SimpleShooterAI

This is the documentation for this project.

Everything related to the character (setting up components, attacking and moving) is done in C++, and the AI ​​is done in Blueprints

WeaponComponent has an InitAnimations method that is called on BeginPlay

![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/03f7e23d-c609-458c-b009-6d503dbc250a)


In this function we receive the AnimNotify UReloadFinishedAnimNotify and subscribe to it. This is necessary so that after the reload animation ends the player can shoot and reload again.
This approach saves us from a lot of bugs, and also allows us to add new functionality


AnimNotify, which must be set to AnimMonatge, otherwise the ReloadAnimInProgress variable will always be true

![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/cb406178-5ccc-4241-b4d8-62b24acd17dc)


In the GetPlayerViewPoint method we check whether the character is controlled by the AI. If yes, then we get the "eyes" of the actor. Due to animations, we won't be able to trace directly from muzzle, but we can still play the FX by getting a muzzle socket

![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/476978e3-a627-4232-8a68-31f35c765858)


The behavior tree contains various tasks

![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/bc3a72a0-6da7-4630-8040-22fe4627011a)


![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/1678d8ad-c9d8-4886-bafd-b75921924848)


Due to its complexity, of greatest interest to us is EQG_CreateCoverPoints, which is called in EQS_CreateCoverPoints


In this Blueprint, we make a trace around the player character, and focusing on the points we hit, we set the AI ​​value to NextLocation. AI will run to the point that is closest to it
We can reduce the number of traces for better performance, or use standard EQS depending on the game design

![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/d52b9de4-5b55-4d2a-8e3b-7eec40dcb376)
![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/06d63742-2d2e-4984-a628-0936090bad20)


BTD_IsAmmoEmpty simply checks to see if the AI ​​has any bullets left. If not, then he looks for a place to hide, after which he reloads (by default in C++ code, if you shoot when there are no bullets, reloading automatically occurs)

![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/cdda7004-f2f5-4d1d-97ad-2b9d156d9e6f)
![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/d6c747ca-3b4f-4245-ae0a-1c9563409a66)
![image](https://github.com/InexhaustibleSnake/SimpleShooterAI/assets/93211950/3b72e6e5-9667-47ad-8e6d-8a653d21c871)


