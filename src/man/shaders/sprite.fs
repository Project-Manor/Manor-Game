#version 330

in vec2 fragTexCoord;

uniform sampler2D texture0;
out vec4 finalColor;

uniform int animLength;
uniform int animFrame;
uniform int flip;

void main() {
    if (animLength > 0) {
        float xCoord = fragTexCoord.x / animLength + (float(animFrame) / animLength);
        if (flip > 0) {
            xCoord = (1.0 / animLength) - fragTexCoord.x / animLength + (float(animFrame) / animLength);
        }
        vec4 texel = texture(
                texture0,
                vec2(
                    xCoord,
                    fragTexCoord.y
                ));
        if (texel.a == 0.0) {
            discard;
        }
        finalColor = texel;
    }
    else {
        finalColor = vec4(1.0, 0, 1.0, 1.0);
    }
}
