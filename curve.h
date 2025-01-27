#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class Curve {
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    // Constructor
    Curve(GLfloat ctrlpoints[], int numCtrlPoints, int segments = 50, int slices = 50)
        : ctrlpoints(ctrlpoints), numCtrlPoints(numCtrlPoints), segments(segments), slices(slices) {
        // Set default color to blue
        ambient = glm::vec3(0.0f, 0.0f, 1.0f);
        diffuse = glm::vec3(0.0f, 0.0f, 1.0f);
        specular = glm::vec3(0.5f, 0.5f, 1.0f);
        shininess = 32.0f;

        generateVertices();
        generateIndices();
        setupBuffers();
    }

    // Destructor
    ~Curve() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void drawCurve(Shader& shader, glm::mat4 model) const {
        shader.use();
        shader.setMat4("model", model);
        shader.setVec3("material.ambient", this -> ambient);
        shader.setVec3("material.diffuse", this -> diffuse);
        shader.setVec3("material.specular", this -> specular);
        shader.setFloat("material.shininess", this -> shininess);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    GLfloat* ctrlpoints;
    int numCtrlPoints;
    int segments;
    int slices;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;

    void generateVertices() {
        for (int i = 0; i <= segments; ++i) {
            float t = static_cast<float>(i) / segments;
            float x = 0.0f, y = 0.0f;

            for (int j = 0; j < numCtrlPoints; ++j) {
                float binomialCoeff = nCr(numCtrlPoints - 1, j);
                float oneMinusTPow = pow(1 - t, numCtrlPoints - 1 - j);
                float tPow = pow(t, j);
                float coef = binomialCoeff * oneMinusTPow * tPow;

                x += coef * ctrlpoints[j * 3];
                y += coef * ctrlpoints[j * 3 + 1];
            }

            for (int k = 0; k <= slices; ++k) {
                float theta = k * (2.0f * 3.1415926 / slices);
                float z = x * sin(theta);
                float nx = cos(theta);
                float ny = 0.0f;
                float nz = sin(theta);

                vertices.push_back(x * cos(theta));
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(nx);
                vertices.push_back(ny);
                vertices.push_back(nz);
            }
        }
    }

    void generateIndices() {
        for (int i = 0; i < segments; ++i) {
            for (int j = 0; j < slices; ++j) {
                int p1 = i * (slices + 1) + j;
                int p2 = p1 + slices + 1;

                indices.push_back(p1);
                indices.push_back(p2);
                indices.push_back(p1 + 1);

                indices.push_back(p1 + 1);
                indices.push_back(p2);
                indices.push_back(p2 + 1);
            }
        }
    }

    void setupBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

        // Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        glBindVertexArray(0);
    }

    long long nCr(int n, int r) {
        if (r > n / 2)
            r = n - r; // because C(n, r) == C(n, n - r)
        long long ans = 1;
        int i;

        for (i = 1; i <= r; i++) {
            ans *= n - r + i;
            ans /= i;
        }

        return ans;
    }
};

#endif /* CURVE_H */

