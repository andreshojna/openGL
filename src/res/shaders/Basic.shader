#shader vertex
// #version 330 core                    // not supported in HP Probook 4530s
#version 130                            // use this instead

// layout(location = 0) in vec4 position; // not supported in version 1.30
attribute vec4 position;                // use this instead
attribute vec2 texCoor;
out vec2 v_Texcoor;

void main() {
  gl_Position = position;
  v_Texcoor = texCoor;
};


#shader fragment
// #version 330 core                    // not supported in HP Probook 4530s
#version 130                            // use this instead
// layout(location = 0) out vec4 color;

in vec2 v_Texcoor;

uniform vec4 u_Color;  // if starts with u_ is a uniform variable
uniform sampler2D u_Texture;

void main() {
  // color = vec4(1.0, 0.0, 0.0, 1.0);      // not supported in version 1.30
  vec4 texcoor = texture(u_Texture, v_Texcoor);
  gl_FragColor = texcoor;
  // gl_FragColor = u_Color;  // using uniform
};