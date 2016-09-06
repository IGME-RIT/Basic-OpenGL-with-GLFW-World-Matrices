/*
Title: World Matrices
File Name: Main.cpp
Copyright � 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include "../../header/shape.h"

Shape* square;

// Scale, Rotation and Translation constants for our shape.
float s = .5f;
float r = .5f;
glm::vec2 t = glm::vec2(.3, .4);

// These are the matrices that perform the operations using the above values.
glm::mat3 scale;
glm::mat3 rotation;
glm::mat3 translation;

// A World Matrix performs all of the above operations at once!
glm::mat3 worldMatrix;

// Window resize callback
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char **argv)
{
	// Initializes the GLFW library
	glfwInit();

	// Initialize window
	GLFWwindow* window = glfwCreateWindow(800, 600, "World Matrix Transformations", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	//set resize callback
	glfwSetFramebufferSizeCallback(window, resizeCallback);

	// Initializes the glew library
	glewInit();


	// Indices for square (-1, -1)[2] to (1, 1)[1]
	// [0]------[1]
	//	|		 |
	//	|		 |
	//	|		 |
	// [2]------[3]

	// This tutorial assumes you already know how to use std::vector.
	// The GL Math library adds math vectors (vec2-4) that we can use to store or vertices.
	std::vector<glm::vec2> vertices;

	// std::vectors are a convenient form of storage.
	// They automatically resize, and are self contained, so they are easy to pass around.
	// The best part: the underlying storage is actually just an array.
	// Almost anything that you can do with an array, can also be done with a vector!

	vertices.push_back(glm::vec2(-1, 1));
	vertices.push_back(glm::vec2(1, 1));
	vertices.push_back(glm::vec2(-1, -1));
	vertices.push_back(glm::vec2(1, -1));

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(1);


	// Here we create a square using our new Shape class.
	// (You should probably take a look at shape.h, and shape.cpp to see what's happening.)
	square = new Shape(vertices, indices);


	// Set Render mode.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);




	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 0.0);

		// A scale matrix simply multiplies the x and y components by the scale.
		// (It's also possible to scale in only one direction, but it's usually not a good idea)
		// Written out the math looks like this:
		// newX = oldX * s;
		// newY = oldY * s;
		// newZ = oldZ * 1; this should always be 1
		scale = glm::mat3(
			s, 0, 0,
			0, s, 0,
			0, 0, 1
		);

		// Rotation matrices use trig to scale the x and y of an object around the origin.
		// Written out:
		// newX = cos(r) * oldX + sin(r) * oldY;
		// newY = cos(r) * oldY - sin(r) * oldX;
		// newZ = oldZ * 1;
		rotation = glm::mat3(
			cos(r), sin(r), 0,
			-sin(r), cos(r), 0,
			0, 0, 1
		);
		// If you've ever done math with 2d rotation matrices on paper, you may be confused, because
		// It looks like the transpose of what it should be. This is because glm stores them in "Column Major" order.
		// This DOES NOT affect the math in any way, only the order that they are stored in memory.



		// Here we are using a cool trick to translate our vertices.
		// The last column (yes it's a column) has our offset in it.
		// It ends up looking like this:
		// newX = oldX * 1 + t.x;
		// newY = oldY * 1 + t.y;
		// newZ = oldZ * 1;
		translation = glm::mat3(
			1, 0, 0,
			0, 1, 0,
			t.x, t.y, 1
		);


		// Once we have all 3 matrices, we can multiply them together.
		// This combines them all 3 operations into a world matrix, that we can use to translate each vertex.
		// If you've done matrix multiplication before, you know that the order here matters:
		// Matrix operations happen from right to left, so we scale first, rotate second, and translate last.
		///Try changing the order of these to see what happens.
		worldMatrix = translation * rotation * scale;


		// Draw geometry using the world matrix.
		// This can be done multiple times with different matrices.
		square->Draw(worldMatrix);
		square->Draw(scale);


		// Swap the backbuffer to the front.
		glfwSwapBuffers(window);

		// Poll input and window events.
		glfwPollEvents();

	}

	// Free memory from shape object
	delete square;

	// Free GLFW memory.
	glfwTerminate();


	// End of Program.
	return 0;
}
