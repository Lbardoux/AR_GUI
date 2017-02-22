#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 vertexUV;
out vec3 o_position;
out vec3 o_normal;
out vec2 o_uv;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 N;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
    o_position = (MV * vec4(position, 1.0)).xyz;
    o_normal = (N * vec4(normal, 0.0)).xyz;
    o_uv = vertexUV;

    /*const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),
                                    vec4(-0.25, -0.25, 0.5, 1.0),
                                    vec4( 0.25, 0.25, 0.5, 1.0));
	gl_Position = vertices[gl_VertexID];*/
}
