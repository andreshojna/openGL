#shader vertex
// #version 330 core                    // not supported in HP Probook 4530s
#version 130                            // use this instead

// layout(location = 0) in vec4 position; // not supported in version 1.30
attribute vec4 position;                // use this instead

void main() {
  gl_Position = position;
};


#shader fragment
// #version 330 core                    // not supported in HP Probook 4530s
#version 130                            // use this instead
// layout(location = 0) out vec4 color;

uniform vec4 u_Color;  // if starts with u_ is a uniform variable

void main() {
  // color = vec4(1.0, 0.0, 0.0, 1.0);      // not supported in version 1.30
  gl_FragColor = u_Color;  // using uniform
};