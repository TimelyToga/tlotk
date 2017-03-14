#version 330

layout(location = 0) in vec3 vertex_position_model_space;
layout(location = 1) in vec4 v_color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;

uniform mat4 M;
uniform mat4 VP;
uniform float t;

out vec4 VColor; // Outs are CamelCase, while ins are like: 'v_color'
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

#define PI 3.14159265358979323846


float rand(vec2 c){
    return fract(sin(dot(c.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float noise(vec2 p, float freq ){
    float unit = 10.f;
    vec2 ij = floor(p/unit);
    vec2 xy = mod(p,unit)/unit;
    //xy = 3.*xy*xy-2.*xy*xy*xy;
    xy = .5*(1.-cos(PI*xy));
    float a = rand((ij+vec2(0.,0.)));
    float b = rand((ij+vec2(1.,0.)));
    float c = rand((ij+vec2(0.,1.)));
    float d = rand((ij+vec2(1.,1.)));
    float x1 = mix(a, b, xy.x);
    float x2 = mix(c, d, xy.x);
    return mix(x1, x2, xy.y);
}

float pNoise(vec2 p, int res){
    float persistance = .9;
    float n = 0.;
    float normK = 0.;
    float f = 4.;
    float amp = 0.5;
    int iCount = 0;
    for (int i = 0; i<50; i++){
        n+=amp*noise(p, f);
        f*=2.;
        normK+=amp;
        amp*=persistance;
        if (iCount == res) break;
        iCount++;
    }
    float nf = n/normK;
    return nf*nf*nf*nf;
}

void main() {
    // vec2 nVec = vec2(vertex_position_model_space.x + t, vertex_position_model_space.y + t);
    float zcoord = 0; // pNoise(nVec, 1);
    gl_Position = VP * M * vec4(vertex_position_model_space.x,
                                vertex_position_model_space.y + zcoord,
                                vertex_position_model_space.z, 1.0f);
    FragPos = vec3(M *     vec4(vertex_position_model_space, 1.0f));

    // Pass-through traits
    VColor = v_color;
    TexCoord = tex_coord;
    Normal = normal;
}
