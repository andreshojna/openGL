#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_Texture;
layout(location = 3) in float a_TexIndex;

out vec4 v_Color;
out vec2 v_TexCoor;
out float v_TexIndex;

uniform mat4 u_MVP;

void main() {
  v_Color = a_Color;
  v_TexCoor = a_Texture;
  v_TexIndex = a_TexIndex;
  gl_Position = u_MVP * a_Position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoor;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main() {
  int index = int(v_TexIndex);
  switch(index) {
    case 0:
      o_Color = texture(u_Textures[0], v_TexCoor);
      break;
    case 1:
      o_Color = texture(u_Textures[1], v_TexCoor);
      break;
  }
};