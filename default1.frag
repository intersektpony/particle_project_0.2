#version 460 core

out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)
in vec2 texCoord;
uniform sampler2D ourTexture;
uniform bool textureExists;
void main()
{
    if (textureExists == true) {

        FragColor = texture(ourTexture, texCoord);
//        FragColor = vertexColor;
//        FragColor = vec4(1.0,0.0,0.0,1.0);
    }
    else{
        FragColor = vertexColor;
    }
} 