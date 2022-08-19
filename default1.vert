#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
//layout (location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec4 vertexColor;
// Outputs the texture coordinates to the fragment shader
// out vec2 texCoord;

// Controls the scale of the vertices
//uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}