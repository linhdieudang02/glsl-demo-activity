#version 330

// Fragment shader

// These get passed in from the vertex shader and are interpolated (varying) properties
// change for each pixel across the triangle:
in vec3 interpSurfNormal;

// This is an out variable for the final color we want to render this fragment.
out vec4 fragColor;

//TODO: Add sampler and an input variable for the interpolated texture coordinate


in vec2 interpTexCoord;


void main() {

    //TODO: Sample from the texture rather than specifying a color
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);

}
