# Editor


Multiuse editor software
*   Drag & drop images
*   Cut images
*   Draw lines and bezier curves



### Requirements
Software was developed and tested on Debian 9 (SMP Debian 4.9.130-2)
* [Qt5] - graphics and rendering, version 5.7.1 was used
* [qmake] - Makefile creation
* [g++] - Compiler, version 6.3.0 was used
* [Doxygen] -Inline documentation,  version 1.8.14 was used



### Installation

Installing requirements:

```sh
$ sudo apt-get install build-essential cmake
$ sudo apt-get install qtbase5-dev libqt5x11extras5-dev qttools5-dev qttools5-dev-tools libgcrypt20-dev zlib1g-dev libxi-dev libxtst-dev
$ sudo apt-get install doxygen
```

### Using Editor
Compile using included Makefile (in the main folder):
```sh
$ make
```
Run the program (in the main folder):
```sh
$ ./Editor
```
Using Editor should be mostly staight-forward: just follow promts on window.

| Special Controls    |  Description |
|---------------------|--------------|
| Mouse Middle click  |  Center view |
| Mouse Wheel     | Zoom view in /out|

### Missing Features
* Support for CTRL-Z and other shortcuts
* Other than .png and .jpg saving
* Wider range of editor tools
    *   e.g. free form paint
