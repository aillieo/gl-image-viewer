#ifndef MESH_H
#define MESH_H



#include "GL/glew.h"
#include "assimp/Importer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Utils/GLMethod.h"
#include "../Utils/Shader.h"

using std::vector;
using std::string;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};


struct Texture {
    unsigned int id;
    string type;
    aiString path;
};


class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

	void setupInstanceattribute(GLuint index, GLuint instanceAmount, GLsizeiptr size, const void* data, GLuint divisor);

    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        
        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }
    
    // render the mesh
    void Draw(Shader shader);

	void drawAsinstanced(Shader* shader, int amount);
    
private:
    
    /*  Render data  */
	unsigned int VAO;
    unsigned int VBO, EBO;
    
    // initializes VAO VBO EBO
    void setupMesh();

};


#endif
