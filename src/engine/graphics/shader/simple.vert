#version 330

layout(location = 0) in vec3 vertex_position_model_space;
layout(location = 1) in vec4 v_color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;

uniform mat4 M;
uniform mat4 VP;

out vec4 VColor; // Outs are CamelCase, while ins are like: 'v_color'
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;


void main() {
    gl_Position = VP * M * vec4(vertex_position_model_space, 1.0f);
    FragPos = vec3(M *     vec4(vertex_position_model_space, 1.0f));

    // Pass-through traits
    VColor = v_color;
    TexCoord = tex_coord;
    Normal = normal;
}