#version 330

in vec4 VColor;
in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D tex;

void main() {
    // vec4 texColor = texture(tex, TexCoord);

    fragColor = vec4(VColor.rgb, 1.0);

    // if(texColor == vec4(0, 0, 0, 1)) {
    //     fragColor = vec4(VColor.rgb, 1.0);
    // } else {
    //    fragColor = vec4(VColor.rgb, 1.0) * (texture(tex, TexCoord));
    //}
}