#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;

void main(){
    //RGBA color (orange)
    //FragColor = vec4(1.0,0.5,0.2,1.0); 
    FragColor = texture(texture1, TexCoord);
}   