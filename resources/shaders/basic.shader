#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texPos;
layout(location = 2) in float texInd;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec3 blockOffset = vec3(0.0, 0.0, 0.0);

out vec2 v_TexCoord;

void main() {
   gl_Position = projection * view * model* vec4((position + blockOffset), 1.0);
   v_TexCoord = vec2(texPos.x, 1.0 - (texPos.y + texInd) / NUM_TEXTURES);
};

#shader fragment
#version 330 core

in vec2 v_TexCoord;
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

void main() {
   vec4 texColor = texture(u_Texture, v_TexCoord);
   color = texColor;
};