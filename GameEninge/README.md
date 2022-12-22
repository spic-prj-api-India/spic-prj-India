# spic-prj-api
Engine API for the SPiC minor's project.
Originally made by project India.

# Features:

**Scenes:** 
You can create and edit game or application content in scenes. A scene is a type of asset that contains all or part of a game or /application. For instance, you could build a simple game using just one scene, while a more complex game might require multiple scenes, each with its own set of characters, environments, obstacles, decorations, and UI elements. There is no limit to the number of scenes you can create in the engine.

**Tilemaps:** 
A scene can contain a 2D environment known as a tilemap. Tilemaps are created using a program called Tiled and serve as the backdrop for a scene. In addition to visual elements, a tilemap can also include a collision layer, which defines which areas of the map are accessible to characters and objects and which are not. By creating and arranging multiple tilemaps and objects within a scene, you can build complex and interactive worlds for your game or application.

**Saving and loading scenes:** 
Scenes can be saved and loaded. When you save a scene, the engine creates a local file that stores the properties of all the objects within the scene. This can be useful in cases where you want to preserve the state of a game or application, such as the location of the player character and enemies, so that you can continue playing from the same point later on. Scene saves allow you to create checkpoints or save points within your game or applicatione, giving players the option to pick up where they left off or to try different approaches to a challenge. Additionally, scene saves can be used to create multiple levels or environments within a larger game or applicatione, allowing players to progress through a series of challenges.

**Camera:** 
A scene usually contains one camera. The camera is an object that represents the player's perspective within the game. The camera's transform, or position and orientation in 2D space, determines what the camera sees. The camera’s transform’s position (X and Y) defines the viewpoint. When these parameters are set up, the camera can display the current view to the screen. As the camera's GameObject moves, the displayed view moves accordingly. By adjusting the camera's transform and component settings, you can control the view of the player within your game.

**GameObjects:** 
A GameObject is a class that represents any object that can exist within a scene. GameObjects serve as the building blocks for creating and organising content in a project, and they can contain functional components that determine how the object looks and behaves. GameObjects are flexible and can be customised in various ways using scripting. The GameObject class provides a range of methods that allow you to work with them in your code, such as finding, connecting, and communicating between GameObjects, adding or removing components, and setting values related to their status within the scene. By using GameObjects and components, you can create and manipulate a wide range of interactive and dynamic objects and behaviours in your project. 

**Components:** 
Components are the building blocks of functionality for GameObjects. They are attached to GameObjects and contain properties that define the behaviour of the object. You can attach multiple components to a single GameObject, giving you the ability to create complex and customised behaviours. However, every GameObject must have at least one Transform component, which determines the object's position, rotation, and scale in 3D2D space. The Transform component is a fundamental part of every GameObject and is essential for positioning and orienting objects within a scene. By using a combination of different components, you can create a wide range of functionalities and behaviours for your GameObject.

**UI Objects:** 
UIObjects can be used to create UI elements, such as buttons. When creating a UIObject, you can choose to include text and a sprite to customise its appearance. You can also set the width and height of the button to control its size. UIObjects, such as buttons, are useful for creating things like menus and heads-up displays (HUDs). By using UIObjects, you can create interactive and visually appealing interfaces for your projects.

**AudioSource:** 
The Audio Source component is a functional component that can be attached to a GameObject. It allows you to play an audio clip, or sound file, within the scene. With the Audio Source component, you can control the volume of the audio, specify whether it should loop or play through once, and determine if it should start playing automatically when the scene loads. You can also assign a specific audio clip to the Audio Source component. The Audio Source component is a useful tool for adding sound effects and music to your project. It can be used to create a wide range of audio experiences, such as character dialogue, environmental ambiance, and UI feedback. To use the Audio Source component, you will need to specify an audio clip and configure the desired volume, looping, and play on awake settings.

**Scripting (BehaviourScript):** 
Scripting is a key component of creating your game. It allows you to add interactivity and dynamic behaviour to your GameObjects and scenes. BehaviourScripts can be used to respond to player input, trigger events in the gameplay, create graphical effects, control the physical behaviour of objects, and implement custom AI systems for characters. Scripting is an essential tool for creating engaging and interactive experiences in your projects. With scripting, you can bring your ideas to life and create unique and immersive gameplay elements. To use scripting, you will need to create BehaviourScripts and attach them to your GameObjects as components. 

**Collider:** 
You can use colliders to handle collisions between GameObjects. Colliders are functional components that are attached to GameObjects and define the shape of the object for the purpose of physical collisions. Colliders are invisible, and you can use different types of colliders, such as the Box Collider and Circle Collider, depending on the shape of your GameObject. Colliders are an essential tool for creating realistic and immersive gameplay. They allow you to define the physical boundaries of your objects and control how they interact with other objects in the scene. You can use colliders to create obstacles, trigger events, and detect collisions between objects. To use colliders, you will need to attach the appropriate collider component to your GameObject and configure its shape and size to match the object. With colliders, you can add depth and realism to your projects.

**RigidBody:** 
The Rigidbody component is a component that you can use to apply physics-based movement and position control to your GameObjects. With the Rigidbody component, you can use simulated physics forces and torque to move a GameObject and let the physics system calculate the results, rather than manually adjusting the Transform properties of the object. The Rigidbody component allows you to define the mass, velocity, gravity scale, and body type of an object, as well as use the "AddForce" method to apply additional forces to the object. You can use the Rigidbody component to detect and respond to collisions and other physical interactions with other objects in the scene. To use the Rigidbody component, you will need to attach it to your GameObject and configure its physical properties.

**AI (ForceDriven GameObjects):** 
"ForceDriven" GameObjects are objects that are influenced by simulated physics forces. These types of GameObjects can have various AI behaviours, such as obstacle avoidance, separation from other objects, cohesion, alignment, wall avoidance, fleeing, seeking, and going after a target. You can use these behaviours to create dynamic and interactive gameplay experiences. For example, you could use the obstacle avoidance behaviour to make a character avoid obstacles in its path, or the separation behaviour to make characters spread out from each other. You could also use the cohesion behaviour to make characters move towards each other, or the alignment behaviour to make characters move in the same direction. By using these behaviours, you can create complex and realistic AI behaviours for your GameObjects.

**Input:** 
Input is a crucial aspect of creating interactive and engaging games. It allows users to control your application using a keyboard and/or mouse. You can use input to program in-app elements, such as the graphic user interface (GUI) or a user avatar, to respond to user actions in various ways. By using input, you can create dynamic and responsive experiences for your players. For example, you could use input to allow a player to navigate through a menu or control a character in a game. To use input, you will need to write script code that detects and responds to user actions.

**Gameplay speed (TimeScale):** 
"TimeScale" is a property that determines the scale at which time passes within your application. You can use TimeScale to create slow motion effects or speed up your application. When TimeScale is set to 1.0, time passes at the same rate as real-time. When TimeScale is set to 0.5, time passes at half the normal speed, or 2x slower than real-time. If you set TimeScale to zero, your application will appear to be paused. Negative values for TimeScale are ignored. In the other direction you can set timescale to max 2.0. Any values higher than that are ignored. You can use TimeScale to create a wide range of time-based effects in your projects, such as slow motion, fast-forward, and pause. To use TimeScale, you will need to access it in your script code and set it to the desired value. 

**Saving Settings:** 
You can use the ability to save game settings to store player preferences and customise their gameplay experience. You can save settings such as background music, player type, and difficulty level in a local save file. These settings can be restored at any time during the game, allowing players to customise their experience and pick up where they left off. By using the save game settings feature, you can create a more personalised gameplay experience for your players.

**FPS Counter**
The engine includes by default the ability to show and hide the fps counter. By default it is bound to tab but it is completly possible to change it to another key by changing the relevant settting in the settings namespace.

**Advanced Features:** 
	- **Networking (Multiplayer):** The engine includes built-in support for multiplayer gameplay, allowing you to create multiplayer experiences that can be played across multiple devices. With multiplayer support, you can synchronise GameObjects and events happening in-game across all connected devices. With multiplayer support, you can create a wide range of multiplayer experiences, such as cooperative or competitive games, real-time multiplayer simulations, and social multiplayer experiences.

	- **Extensions:** The engine includes support for custom extensions for physics and networking, allowing you to tailor the physics and multiplayer functionality of your project to fit your specific needs. This can be particularly useful if you need to implement custom physics or networking systems that are not provided out-of-the-box by the engine. Note that only one physics extension can be implemented at a time.

If you are developing an game with this engine everything contained in the namespace internal is not for you.

# Installation
The game engine is a static library, so this library must be statically linked to your project. Furthermore it is not out of the box compatible with CMake. Instead, it uses a Visual studio solution file.

Run these lines in powershell (width admin rights) to install the libraries used by the game engine (using the package manager VCPKG):
```
$path = "C:\dev\vcpkg"
Set-Location $path
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg integrate install
.\vcpkg\vcpkg install sdl2:x64-windows sdl2-image:x64-windows sdl2-mixer:x64-windows sdl2-ttf:x64-windows
.\vcpkg\vcpkg install boost:x64-windows 
.\vcpkg\vcpkg install boost-asio:x64-windows
.\vcpkg\vcpkg install tinyxml:x64-windows
.\vcpkg\vcpkg install box2d:x64-windows
```

Follow these steps to install/use the game engine:
Place the game engine folder in a logical place in your project, for example in a folder “external”.
Link the static game library with your game. If you do not know how to do this you can follow the guide [here](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-170).
Now you can start coding. This website always has the latest information about the engine. 

# Copyright (c) 2022 Avans Hogeschool, 's-Hertogenbosch. 
