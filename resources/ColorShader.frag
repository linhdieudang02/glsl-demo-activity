#version 330

// Fragment shader

// These get passed in from the vertex shader and are interpolated (varying) properties
// change for each pixel across the triangle:
in vec3 interpSurfNormal;
uniform vec4 colorSampler;
// This is an out variable for the final color we want to render this fragment.
out vec4 fragColor;

//TODO: Add sampler and an input variable for the interpolated texture coordinate



void main() {

    //TODO: Sample from the texture rather than specifying a color
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    colorSampler = vec4(1.0, 1.0, 0.0, 0.0)

}
