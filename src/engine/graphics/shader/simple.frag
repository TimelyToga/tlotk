#version 330

in vec3 FragPos;
in vec4 VColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 fragColor;

uniform float t;
uniform sampler2D tex;

void main() {
    // vec4 texColor = texture(tex, TexCoord);
    vec3 lightColor = vec3(1, 1, 1);

    // Calculate lightPos
    vec3 lightPos = vec3(30*cos(t)+50, 30*sin(t)+50, 20);

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Normalize direction vectors
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Calculate diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // A+D lighting
    vec3 result = (ambient + diffuse) * VColor.rgb;
    fragColor = vec4(result, 1.0f);

    // if(texColor == vec4(0, 0, 0, 1)) {
    //     fragColor = vec4(VColor.rgb, 1.0);
    // } else {
    //    fragColor = vec4(VColor.rgb, 1.0) * (texture(tex, TexCoord));
    //}
}