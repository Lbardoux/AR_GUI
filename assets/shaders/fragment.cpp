#version 330 core

in vec3 o_position;
in vec3 o_normal;
in vec2 o_uv;
out vec4 color;

uniform sampler2D u_texture;

void main(){
    vec3 ambient = texture(u_texture, o_uv).rgb * 0.5f;
    vec3 light_dir = vec3(10.0f, -100.0f, 10.0f);
    vec3 n = normalize(o_normal);
    vec3 l = normalize(light_dir);
    float cos_theta = clamp(dot(n, l), 0.0, 1.0);
    vec3 diffuse = vec3(1.0f, 1.0f, 1.0f) * cos_theta;
    vec3 e = normalize(vec3(0.f, 0.f, 0.f) - o_position);
    vec3 h = normalize(l + e);
    vec3 specular = vec3(1.0f, 1.0f, 1.0f) * pow(max(0.0, dot(h, n)), 30.0);
    vec3 withlight = ambient + diffuse;
    color = vec4(withlight, 255);
}
