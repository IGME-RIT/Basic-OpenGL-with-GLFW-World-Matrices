Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the World Matrix Tutorial!
Prerequesites: Draw two triangles

Scaling, Rotating, and Translating,
allow us to manipulate the state of any object.
In this tutorial, we show the basics of how to use each
type of transformation, they all involve what is called
the "World matrix", or some call it the "Model matrix".

A world matrix is a 4x4 matrix, that can be created 
with the data type glm::mat4. We do not need to 
write 4x4 matrices by hand though. the math library 
glm gives us functions that help us.

glm::translate makes a translation matrix,
glm::rotate makes a rotation matrix,
glm::scale makes a scale matrix
Multiplying these together will combine the 
effects.

glm::translate takes a vec3, for movement
on the x, y, and z axis

glm::scale takes a vec3, for scaling
on the x, y, and z axis

glm::rotate takes a float and a vec3, the float
is the angle in radians of rotation, and the vec3
is for rotation on the x, y, and z axis, but this
vec3 is not like translate or scale vec3.

If you want to rotate 180 degrees on the y axis, your
radians would be 3.14159, and your vec3 would be (0, 1, 0),
because we want to rotate on Y, but not X or Z. Each member
of this vec3 should be 0 or 1, not a decimal, not more than 1

This matrix will be inside our "triangle" entity

After we make the matrix, we need to give the matrix to the
vertex shader, so that we can transform each vertex
	glUniformMatrix4fv(2, 1, GL_FALSE, &triangle.worldMatrix[0][0]);
	
The '2' is the uniform location (more on this later)
The '1' tells us that we are passing one matrix
	
We use the glUniformMatrix4fv function, because the type of data 
we are passing is a matrix, with four vectors, that are made of floats,
that's why we have "matrix", "4f" and "v"

A uniform is a buffer of memory that is given to a shader, that 
does not change with each instance of the shader. Every time the 
Vertex Shader runs, it processes a different vertex, but has the same
uniform matrix.

In the shader, we allow the GPU to know that there is a matrix
at location '2', as mentioned a few lines earlier
	layout (location=2) uniform mat4 worldMatrix;
	
Finally, we apply the world matrix to each vertex
	gl_Position  = worldMatrix * vec4(position,1);
	
And we're done