#version 330

in vec3 FragPos;
in vec4 VColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 fragColor;

//uniform sampler2D tex;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDir;

void main() {
    // vec4 texColor = texture(tex, TexCoord);
//    vec3 lightColor = vec3(0.65, 1, 1);
    float specularStrength = 0.1f;

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

    // Attenuation
    float distance    = length(lightPos - FragPos);
    float lconstant   = 1.0f;
    float llinear     = 0.0014;
    float lquad       = 0.000007;
    float attenuation = 1.0f / (lconstant + llinear * distance + lquad * (distance * distance));

    diffuse  *= attenuation;
    specular *= attenuation;

    // A+D+S lighting
    vec3 result = (ambient + diffuse + specular) * VColor.rgb;
    fragColor = vec4(result, 1.0f);

    // if(texColor == vec4(0, 0, 0, 1)) {
    //     fragColor = vec4(VColor.rgb, 1.0);
    // } else {
    //    fragColor = vec4(VColor.rgb, 1.0) * (texture(tex, TexCoord));
    //}
}