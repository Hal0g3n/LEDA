meeting notes 4/8/22
next meeting: 7/9/22

primarily 2d games

core engine systems (examples):
- graphics (opengl)
- collision system
	- binary collision
	- line segment
	- bounding box
	- consider difference between dynamic/static also (need to separate in functions)
- physics system
- input
	- game input (keyboard/mouse, controller, etc.)
	- data & serialization (file i/o): very important! loading game objects from a file (abstracts the creation of game objects from the code implementation)
- level manager
	- see which level is being played, decides which level to load
- audio system: fmod library
- transformation system: build matrices from data
- assets manager - handles the loading and freeing of all assets for the current level (determining which assets belong to which)

systems usually inherit from a parent abstract class (ISystem)
the Core class (core engine) contains a vector of systems
order of systems in the vector matters -- this determines which one is processed first (so input goes first and graphics probably last)

the engine needs tools (helper libraries) 
e.g. math library, frame rate, file i/o to read json, image loader (png) for textures 

game object class -- very important: decide organization of how to store game objects

in real game engines, instead of using cpp for level files, you store the game data in json files - the serialization
the json stores all the init properties (e.g. starting position)
the game engine loads in the json (in the load stage, the data used for the load and init stages) 

for a game, have assets folder:
- textures
- audio files
- levels
- logic (scripts) -- requires knowledge of how to map the scripting lang to the c++

game engine architecture: traditionally they use inheritance based but no one does it anymore lol
now people use component-based or ecs architecture
inheritance: every object extends a parent game object class
component based: objects contain vector of components that store data; the systems then use the corresponding components to do their jobs
	examples of components: rigid body (contains mass, velocity, physics things), display (contains mesh, textures, etc), transformation (contains position, scale, angle)'
	the parent component class has functions to load and save themselves 

what library to use? 
- e.g. glfw, sdl
- from scratch is cooler though


by next meeting:
- file structure (visual studio structure)
- basic systems - input and graphics (try and get some visual output)
- tools: math and frame rate? 
- 

