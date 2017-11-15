#version 330 core


layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_uv;

// Values that stay constant for the whole mesh.
uniform mat4 light_mvp;
uniform mat4 projection; // Projected view
uniform mat4 view;
// layout(location = 12) in mat4 model_view; // Camera view
uniform mat4 model_view;
uniform vec3 camera_position;

out vec3 to_shade_vertex;
out vec3 normal_input;
out vec3 vector_to_camera;
out vec2 uv;
out vec4 shadow_coord;
out vec4 onscreen_vertex;

void main(){

    // compute true position of actual vertex and pass it to fragment shader
    to_shade_vertex = (model_view * vec4(vertex, 1)).xyz;
    normal_input = mat3(transpose(inverse(model_view))) * vertex_normal;

    vector_to_camera = camera_position - to_shade_vertex;
    // vector_to_camera = to_shade_vertex - camera_position;
    vector_to_camera = normalize(vector_to_camera);

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  projection * view * model_view * vec4(vertex, 1);
    shadow_coord = light_mvp * model_view * vec4(vertex, 1);

    uv = vertex_uv;
}
