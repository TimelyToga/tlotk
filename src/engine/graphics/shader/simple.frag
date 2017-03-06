#version 330

in vec3 FragPos;
in vec4 VColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 fragColor;

//uniform float t;
//uniform sampler2D tex;
uniform vec3 viewPos;
uniform vec3 lightPos;

void main() {
    // vec4 texColor = texture(tex, TexCoord);
    vec3 lightColor = vec3(1, 1, 1);
    float specularStrength = 0.5f;

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Normalize direction vectors
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Calculate diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // A+D+S lighting
    vec3 result = (ambient + diffuse + specular) * VColor.rgb;
    fragColor = vec4(result, 1.0f);

    // if(texColor == vec4(0, 0, 0, 1)) {
    //     fragColor = vec4(VColor.rgb, 1.0);
    // } else {
    //    fragColor = vec4(VColor.rgb, 1.0) * (texture(tex, TexCoord));
    //}
}