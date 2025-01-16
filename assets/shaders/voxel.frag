#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture; // optional, if using a texture

void main()
{
    // Sample from the texture
    FragColor = texture(uTexture, TexCoord);
    
    // Or if you don’t have a texture, you can just use a color:
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
