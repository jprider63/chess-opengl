Build
=====

Running `make` should build and run the executable `chess`. You may need to modify the Makefile's LIBFLAGS option to find OpenGL and GLUT. This implementation was tested on Mac OS X 10.7.5.

About
=====

This is the frontend for a chess game. You can move the camera by left clicking and dragging. Zoom in and out with 'i' and 'o'. The skybox is made of multiple textures, one for each side of the cube. You can right click to select a pawn and the right click another place to move it. All of this moving is animated with a shrink in and out effect. Shadows are especially crisp by setting the stencil op to GL_ZERO.

References
==========

Besides the given materials, I used the following tutorials:
- http://www.firstobject.com/getmillicount-milliseconds-portable-c++.htm
- http://www.nullterminator.net/gltexture.html
