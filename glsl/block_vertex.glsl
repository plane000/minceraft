#version 330 core

// Vertex attributes.

layout (location = 0) in vec3 vertex_position;

layout (location = 1) in vec3 vertex_texture;

layout (location = 2) in float vertex_lighting;

// Input matrices.

uniform mat4 matrix_projection;

uniform mat4 matrix_view;

uniform mat4 matrix_model;

// Output to the fragment shader.

out vec3 frag_texture;

out float frag_lighting;

out float frag_distance;

// Shader code.

void main()
{
	// Multiply the vertex position by the projection, view, and model 
	// matrices to find the final position.

	gl_Position = matrix_projection * matrix_view * matrix_model * vec4(vertex_position, 1.0f);

	// Pass the texture vertex attribute and the lighting vertex attribute to 
	// the fragment shader.

	frag_texture = vertex_texture;

	frag_lighting = vertex_lighting;

	// Pass the distance to the origin squared to the fragment shader, so that
	// it is simple to calculate fog density.

	frag_distance = 
	(
		gl_Position.x * gl_Position.x + 
		gl_Position.y * gl_Position.y + 
		gl_Position.z * gl_Position.z + 
		gl_Position.w * gl_Position.w
	);
}