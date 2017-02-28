#version 330

layout(location = 0) in vec3 vertex_position_model_space;
layout(location = 1) in vec4 v_color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;

uniform mat4 MVP;

out vec4 VColor; // Outs are CamelCase, while ins are like: 'v_color'
out vec2 TexCoord;


void main() {
    gl_Position = MVP * vec4(vertex_position_model_space, 1.0);
    VColor = v_color;
    TexCoord = tex_coord;
}