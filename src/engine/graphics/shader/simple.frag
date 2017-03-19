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
uniform vec3 spotDir;
uniform float lightCutoffAngle; // cutoff angle

void main() {
    // Normalize direction vectors
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Spotlight calculations
    float theta = dot(lightDir, normalize(-spotDir));
    float specularStrength = 0.1f;

    // Ambient light
    float ambientStrength = 0.2;
    vec3 ambientLight = ambientStrength * lightColor;

    if(theta > lightCutoffAngle)
    {
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
        float llinear     = 0.007;
        float lquad       = 0.0002;
        float attenuation = 1.0f / (lconstant + llinear * distance + lquad * (distance * distance));

        diffuse  *= attenuation;
        specular *= attenuation;

        // Soft spotlight edges
        float lightOuterCutoffAngle = 0.2555;
        float epsilon   =  - lightOuterCutoffAngle - lightCutoffAngle;
        float intensity = clamp((lightOuterCutoffAngle - theta) / epsilon, 0.0, 1.0);

        diffuse  *= intensity;
        specular *= intensity;

        // A+D+S lighting
        vec3 result = (ambientLight + diffuse + specular) * VColor.rgb;
        fragColor = vec4(result, 1.0f);
    }
    else
    {
        // No lighting not in cone
        fragColor = vec4(ambientLight * VColor.rgb, 1.0f);
    }
}