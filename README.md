# Vertex Objects

1. Vertex Buffer (VBO – Vertex Buffer Object)

    Purpose: Stores vertex data like positions, colors, normals, texture coordinates, etc.

    Usage: You upload your vertex data to the GPU using a VBO so that shaders can access it.

```
float vertices[] = {
    // x, y, z       // r, g, b
     0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f,-0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,-0.5f, 0.0f,  0.0f, 0.0f, 1.0f
};
```


2. Index Buffer (IBO or EBO – Element Buffer Object)

    Purpose: Stores indices that tell OpenGL how to reuse vertices from the VBO to construct primitives (triangles, lines, etc.).

    Benefit: Reduces duplication of vertex data, which improves performance and memory usage.

```
unsigned int indices[] = {
    0, 1, 2  // Use the first, second, and third vertex to make a triangle
};
```

3. Vertex Array Object (VAO – Not "VertexArrayBuffer")

    Purpose: Stores the state of vertex attribute configuration, i.e., how the VBO data is interpreted (layout) and which VBO and IBO are bound.

    Usage: You configure it once (e.g., which VBO is used, how data is laid out), then bind it when rendering.
SW
Think of it as a shortcut:

    You set up the VAO once with glVertexAttribPointer, etc.

    Then later, just bind the VAO to restore all that state at once.


| Object        | Stores                       | OpenGL Binding Target     | Purpose                    |
| ------------- | ---------------------------- | ------------------------- | -------------------------- |
| **VBO**       | Raw vertex data              | `GL_ARRAY_BUFFER`         | Supplies vertex attributes |
| **IBO / EBO** | Indices into vertex data     | `GL_ELEMENT_ARRAY_BUFFER` | Defines vertex reuse       |
| **VAO**       | VBO & attribute state config | `glBindVertexArray()`     | Bundles VBO/IBO state      |


# Blending

Blending: rendering something which is partially or fully transparent.
Determines how we combine our output color with what is already in our target buffer
The output color is the color that we put on our fragment shader (source)
The targe buffer is where the fragment shader is drawing
We need to:
  * Enable/Disable glEnable(GL_BLEND)
  * Set the blending function glBlendFunc(src, dest): multiply source and destination by src and dest. Default for src and dest is 1 and 0 (always copy the source and override the dest)
  * Set the blending equation glBlendEquation(mode) how to combine src and dest colors (default: add)
  * The equation is done for each color channel

### Default example:
```
glBlendFunc(GL_ONE, GL_ZERO);
glBlendEquation(GL_FUNC_ADD);
```

src: rs, gs, bs, as  
dest: rd, gd, bd, ad
```
r_res = rs * 1 + rd * 0 = rs
g_res = rs * 1 + rd * 0 = gs
b_res = rs * 1 + rd * 0 = bs
a_res = rs * 1 + rd * 0 = as
```

### Cherno Example
```
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glBlendEquation(GL_FUNC_ADD);
```

If the pixel is fully transparent:
```
a_src = 0; --> a_dest = 1 - 0 = 1;

r = ( r_src * 0) + ( r_dest * (1 - 0)) = r_dest
g = ( g_src * 0) + ( g_dest * (1 - 0)) = g_dest
b = ( b_src * 0) + ( b_dest * (1 - 0)) = b_dest
a = ( a_src * 0) + ( a_dest * (1 - 0)) = a_dest
```

And if it is fully opaque:
```
a_src = 1; --> a_dest = 1 - 1 = 0;

r = ( r_src * 1) + ( r_dest * (1 - 1)) = r_src
g = ( g_src * 1) + ( g_dest * (1 - 1)) = g_src
b = ( b_src * 1) + ( b_dest * (1 - 1)) = b_src
a = ( a_src * 1) + ( a_dest * (1 - 1)) = a_src
```

### Example 2

White pixel partially transparent: (1.0, 1.0, 1.0, 0.5)  
Destination buffer is opaque magenta: (1.0, 0.0, 1.0, 1.0)  

```
r = ( 1.0 * 0.5) + ( 1.0 * (1 - 0.5)) = 1.0
g = ( 1.0 * 0.5) + ( 0.0 * (1 - 0.5)) = 0.5
b = ( 1.0 * 0.5) + ( 1.0 * (1 - 0.5)) = 1.0
a = ( 0.5 * 0.5) + ( 1.0 * (1 - 0.5)) = 0.75
```

The result is a light magenta with alpha 0.75


# Model View Projection (MVP)
Each word is a matrix and all are multiplied between themselves (P\*V\*M).  

* Projection matrix:  
  Convert the space into normalized device coordinates.

* View matrix (i-matrix):  
  Is the view of the camera: position, rotation.

* Model matrix:  
  Simulate the model-matrix: translation (position), rotation, scale (TRS) of our model/object.

# Rendering a second object

To render a second object in a different position we can:
  * Create another vertex buffer with new position data
  * Pass to our shader another MVP matrix which transform the original position in a new one

We are going to do the MVP way because create a new vertex buffer is not performant: both objects will be the same and new each bind is slow.

# Batch Rendering

### 'Till now
* We make a draw call per square
* If we have 1000 squares --> 1000 draw calls = slow

To draw a square we need:
* Vertex Array
  * Vertex buffer: 4 vertices {0, 1, 2, 3}
  * Idex buffer: 6 indices: {{0, 1, 2}, {2, 3, 0}}

Then transform the first square to reposition, change color and make the second draw call

### With batch rendering

* Dynamic Vertex array (stream data in every frame)
  * Vertex buffer: 2 quads: 8 vertices
    * Color is in the vertex buffer
    * Position is in the vertex buffer
  *Index buffer: 2 quads: 12 indices