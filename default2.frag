#version 460 core
out vec4 FragColor;  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool textureExists;

void main()
{
    if (textureExists == true) {

        //FragColor = texture(ourTexture, TexCoord);
        FragColor = vec4(ourColor, 1.0);
    }
    else{
        FragColor = vec4(ourColor, 1.0);

    }


}