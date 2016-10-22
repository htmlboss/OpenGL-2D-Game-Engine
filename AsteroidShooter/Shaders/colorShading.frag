#version 440

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D spriteTexture;

void main() {

	vec4 textureColor = texture(spriteTexture, fragmentUV);
	color = textureColor * fragmentColor;
}