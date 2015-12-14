# DeltaEngine

A 2D/3D Game Engine written in C++! (in development)

## Download
To download just click "Download as a zip". To use it you can rebuild the game engine or you can use the DeltaEngine.lib and DeltaEngine.dll files inside "bin/Debug".

Keep in mind that you also will need all the header files. You don't need the .cpp files if you don't want to recompile it.

Also, the version inside "bin/Debug" is obviously the debug version, it means that the library will output messages for errors into the console window. The release version doesn't output anything at all, even if there is an error, so you can close the console window using `FreeConsole()`

## Projects inside the solution
The Visual Studio solution contains two projects:
+ **DeltaEngine**: Contains all the files needed to build the game engine.
+ **Game**: This project is just for testing. It only contains a file, `main.cpp`. I recommend taking a look to it, as it will help you start developing your own game.

## Quick Start
### Creating a window
To create a window you will have to import the library file. Just add this line to the top:
```cpp
#include "window.h"
```

Then, create an instance of the class `Window`. This class is inside the namespace `DeltaEngine::Graphics`, so you will need to call `DeltaEngine::Graphics::Window`:
```cpp
#include <string>
#include "window.h"

int main(int argc, char* argv[])
{
  int height = 960;
  int width = 540;
  DeltaEngine::Graphics::Window myWindow(std::string("Window title"), height, width);
  
  return 0;
}
```

You need the `#include <string>` statement because the window title is an `std::string`.

### Initializing the library
You have to call `DeltaEngine::init(int argc, char* argv[])` after you create your window, but **before** you call any OpenGL function.

The library itself doesn't need any initialization, but GLEW does, so I created this little inline function to initialize OpenGL.

To call this function, you have to include `DeltaEngine.h` and GLEW (normally `glew.h`).

All the GLEW files I use are inside "dependencies/include/GLEW" for the header files, and "dependencies/lib/GLEW" for the static library version. If you want to use those files, remember to add the `GLEW_STATIC` define for the project. To do this, go to your project properties -> click on "C/C++" -> Select the "Preprocessor" page -> Add `GLEW_STATIC` to the preprocessor definitions.

### Keyboard and mouse input
To install keyboard, you just need to call the `installKeyboard()` method of your window, for example:
```cpp
#include <string>
#include "window.h"

int main(int argc, char* argv[])
{
  int height = 960;
  int width = 540;
  DeltaEngine::Graphics::Window myWindow(std::string("Window title"), height, width);
  
  myWindow.installKeyboard();
  // Now the keyboard is installed, you can read keys
  
  return 0;
}
```

Same with the mouse, but instead of calling `installKeyboard()` call `installMouse()`.

To read the state of a key, just call `isKeyPressed(int key)`. This will return true if the key is pressed, false otherwise.

To get the position of the mouse use the function `win.getMousePosition(int& x, int& y)`. This function takes two arguments by reference, and does not return anything, just sets the value of the X coordinate and Y coordinate in `x` and `y`. Here's an example:

```cpp
#include <string>
#include <iostream>

#include "window.h"

int main(int argc, char* argv[])
{
  int height = 960;
  int width = 540;
  DeltaEngine::Graphics::Window myWindow(std::string("Window title"), height, width);
  
  myWindow.installMouse();
  // Now the mouse is installed, we can read the mouse position and scroll
  
  float mouseX;
  float mouseY;
  
  myWindow.getMousePosition(mouseX, mouseY);
  
  std::cout << "Mouse position: X=" << mouseX << " Y=" << mouseY << std::endln;
  
  return 0;
}
```

### Creating a basic game loop
Because we want our game to be running until the player closes the window, we need a loop

The method `closed()` of the class `Window` allows us to know the state of the window, so we can create our `while` loop using it.

Inside the loop we will check for input, check for errors... and also update our window. This is easily done by calling `update()`:

```cpp
#include <string>
#include "window.h"

int main(int argc, char* argv[])
{
  int height = 960;
  int width = 540;
  DeltaEngine::Graphics::Window myWindow(std::string("Window title"), height, width);
  
  while(myWindow.closed == false)
  {
    // Check for input, such as keyboard, mouse... 
    
    // Update our window so it doesn't freeze
    myWindow.update();
  }
  
  return 0;
}
```
