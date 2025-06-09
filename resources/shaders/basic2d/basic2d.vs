#version 300 es
precision mediump float;

in vec3 vertexPosition;
in vec4 vertexColor;

uniform mat4 matrix;

out vec4 fragColor;

void main()
{
  gl_Position = matrix* vec4(vertexPosition, 1.0); // No flip!
  fragColor = vertexColor;
}

