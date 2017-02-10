#version 330 core

#ifdef VERTEX_SHADER

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 vertexUV;
out vec3 o_position;
out vec3 o_normal;
out vec2 o_uv;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 N;

void main(){
    gl_Position = MVP * vec4(position, 1.0);
    o_position = (MV * vec4(position, 1.0)).xyz;
    o_normal = (N * vec4(normal, 0.0)).xyz;
    o_uv = vertexUV;
}

#endif
#ifdef FRAGMENT_SHADER

in vec3 o_position;
in vec3 o_normal;
in vec2 o_uv;
out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
    vec3 ambient = texture(myTextureSampler, o_uv).rgb * 0.5f;

    vec3 light_dir = vec3(10.0f, -100.0f, 10.0f);

    vec3 n = normalize(o_normal);
    vec3 l = normalize(light_dir);
    float cos_theta = clamp(dot(n, l), 0.0, 1.0);
    vec3 diffuse = vec3(1.0f, 1.0f, 1.0f) * cos_theta;

    vec3 e = normalize(vec3(0.f, 0.f, 0.f) - o_position);
    vec3 h = normalize(l + e);
    vec3 specular = vec3(1.0f, 1.0f, 1.0f) * pow(max(0.0, dot(h, n)), 30.0);
    color = ambient + diffuse;
    //color = ambient + diffuse + specular;
}

#endif
