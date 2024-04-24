# Setting up PlantsVszombies Game with SFML in Visual Studio

To set up the PlantsVszombies game project with SFML in Visual Studio, follow these instructions:

## Prerequisites
- Clone the repository into your local machine's D drive.

## Configuration Steps
1. Open the project in Visual Studio.
2. Navigate to `Project > PlantsVszombies Properties` in the navigation bar.

### Debug Configuration
3. Ensure that the configuration is set to `x64` and the mode is `Debug`.
4. In the `Configuration Properties`, open `Debugging`.
5. In the `Environment` option, add the following path:
    ```plaintext
    PATH=D:\project\SFML-2.5.1\bin
    ```
6. Apply the changes but do not click "OK" yet.
7. Go to `C/C++` option and in `Additional Include Directories`, add the following path:
    ```plaintext
    D:\project\SFML-2.5.1\include
    ```
8. Go to `Linker` option, and in `General`, add the following path in `Additional Library Directories`:
    ```plaintext
    D:\project\SFML-2.5.1\lib
    ```
9. Go to `Input` option, and in `Additional Dependencies`, add the following:
    ```plaintext
    sfml-graphics-d.lib
    sfml-window-d.lib
    sfml-audio-d.lib
    sfml-network-d.lib
    sfml-system-d.lib
    ```

### Release Configuration
10. Switch to `Release` configuration.
11. Repeat steps 4-8 for the `Release` configuration.
12. Go to `Input` option, and in `Additional Dependencies`, add the following:
    ```plaintext
    sfml-graphics.lib
    sfml-window.lib
    sfml-audio.lib
    sfml-network.lib
    sfml-system.lib
    ```

13. Click "OK" and close the properties window.

You have now successfully configured the PlantsVszombies game project with SFML in Visual Studio.
