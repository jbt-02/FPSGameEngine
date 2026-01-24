#version 330 core

//Input var from vertex buffer (location = 0)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord; //Texture coordinate

out vec2 TexCoord; //Output to frag shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}