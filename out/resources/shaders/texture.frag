in vec2 coordTexture;

uniform sampler2D tex;

out vec4 out_Color;

void main()
{
    out_Color = texture(tex, coordTexture);
}