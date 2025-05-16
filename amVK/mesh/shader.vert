#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;

layout (location = 0) out vec4 outColor;

void main() 
{
	outColor = inColor;
	gl_Position = vec4(inPos.x, -inPos.y, 0.0, 1.0);    // Flip y-coords. This Ties with RasterizationSCI.CULLING / FrontFaceDirection
        // You won't see anything on the scree
}