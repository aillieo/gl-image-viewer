#include "Mesh.h"

void Mesh::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    
    glBindVertexArray(0);
}


void Mesh::Draw(Shader shader)
{
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::stringstream ss;
        string number;
        string name = textures[i].type;
        if(name == "texture_diffuse")
            ss << diffuseNr++; // transfer unsigned int to stream
        else if(name == "texture_specular")
            ss << specularNr++; // transfer unsigned int to stream
        else if(name == "texture_normal")
            ss << normalNr++; // transfer unsigned int to stream
        else if(name == "texture_height")
            ss << heightNr++; // transfer unsigned int to stream
        number = ss.str();
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}


void Mesh::setupInstanceattribute(GLuint index, GLuint instanceAmount, GLsizeiptr size, const void* data, GLuint divisor)
{
	// Vertex Buffer Object
	GLuint buffer;
	glBindVertexArray(VAO);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, instanceAmount * size, data, GL_STATIC_DRAW);

	if(size == sizeof(glm::mat4))
	{
		// Vertex Attributes
		GLsizei vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(index);

		glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
		glEnableVertexAttribArray(index);
		glVertexAttribDivisor(index, divisor);
		glVertexAttribPointer(++index, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(vec4Size));
		glEnableVertexAttribArray(index);
		glVertexAttribDivisor(index, divisor);
		glVertexAttribPointer(++index, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2 * vec4Size));
		glEnableVertexAttribArray(index);
		glVertexAttribDivisor(index, divisor);
		glVertexAttribPointer(++index, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3 * vec4Size));
		glEnableVertexAttribArray(index);
		glVertexAttribDivisor(index, divisor);

	}
	else
	{
		// todo
		std::cout<<"not implemented !!!"<<std::endl;
		assert(false);
	}

	glBindVertexArray(0);

}


void Mesh::drawAsinstanced(Shader* shader, int amount)
{
	// bind appropriate textures
	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr   = 1;
	unsigned int heightNr   = 1;
	for(unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		string number;
		string name = textures[i].type;
		if(name == "texture_diffuse")
			ss << diffuseNr++; // transfer unsigned int to stream
		else if(name == "texture_specular")
			ss << specularNr++; // transfer unsigned int to stream
		else if(name == "texture_normal")
			ss << normalNr++; // transfer unsigned int to stream
		else if(name == "texture_height")
			ss << heightNr++; // transfer unsigned int to stream
		number = ss.str();
		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glDrawElementsInstanced(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0, amount);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}