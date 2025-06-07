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

