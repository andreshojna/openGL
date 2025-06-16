#shader vertex
#version 330 core                    // not supported in HP Probook 4530s

layout(location = 0) in vec4 position; // not supported in version 1.30
layout(location = 1) in vec2 texCoor; // not supported in version 1.30

// #version 130                            // use this instead
// attribute vec4 position;                // use this instead
// attribute vec2 texCoor;

out vec2 v_Texcoor;

uniform mat4 u_MVP; // Model view projection matrix

void main() {
  gl_Position = u_MVP * position;
  v_Texcoor = texCoor;
};

#shader fragment
#version 330 core                    // not supported in HP Probook 4530s
layout(location = 0) out vec4 color;

// #version 130                            // use this instead

in vec2 v_Texcoor;

uniform vec4 u_Color;  // if starts with u_ is a uniform variable
// uniform sampler2D u_Texture;

void main() {
  // color = vec4(1.0, 0.0, 0.0, 1.0);      // not supported in version 1.30
  // vec4 texcoor = texture(u_Texture, v_Texcoor);
  // gl_FragColor = texcoor;     // using texture
  gl_FragColor = u_Color;  // using uniform
};