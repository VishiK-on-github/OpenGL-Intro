Notes:

Steps involved in rendering 2D object are as follows:

1. vertex shading - takes vertex data and plots it
2. shape assembly - joins the vertexes using primitives (triangle or line)
3. geometry shader - add vertex and create new primitives
4. rasterization - shapes to pixels
5. fragment shader - add color to pixel (depends on  color lighting)
6. test and blending - color for pixel in case of overlapping objects and blending of transparent objects

What are shaders ?

- Functions which run on the GPU. Takes an input give an output. 
- In our case its a shader is openGLs shader language called GLSL

Standard 3D matrices:

1. model matrix: transforms from local coords (a particular objects coords) to world coords
2. view matrix: from world coords to how a camera sees it
3. projection matrix: view coords to clip coords (find more info)

projected to screen coordinates automatically

GLM helps us make these matrices