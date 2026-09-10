#version 330 core

/*----------------------------------------------------------------------------*/

layout (location = 0) in vec3 position;

/*----------------------------------------------------------------------------*/

uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

/*----------------------------------------------------------------------------*/

out vec3 i_texture_coordinates;

/*----------------------------------------------------------------------------*/

void main() {
    i_texture_coordinates = position;
    gl_Position = u_projection_matrix * u_view_matrix * vec4(position, 1.0);
}

/*----------------------------------------------------------------------------*/
