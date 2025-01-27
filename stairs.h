#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "staircube.h"
#include "cylinder.h"

void stair(Shader& lightingShader, Cylinder& cylinder, Staircube& cube1)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // Initialize to identity matrix
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    // Midpoints of stairs; left-side staircases
    float j = 0.0;
    float k = 0.0;
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, .5 + j, -9.5 - k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, .5, .5));
        model = translateMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 10.5 + j, -9.5 - k));
        model = translateMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);

        j += .5;
        k += .5;
    }

    // Midpoints of stairs; right-side staircases
    j = 0.0;
    k = 0.0;
    float rotateAngle_Y = 180.0;
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 5.5 + j, -13.5 + k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, .5, .5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 15.5 + j, -13.5 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);

        j += .5;
        k += .5;
    }

    // Stair railings for right stairs
    j = 0.0;
    k = 0.0;
    for (int i = 0; i < 10; i++) {
        // Ground floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 6.5 + j, -13.75 + k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.15, 6.5 + j, -13.75 + k));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        // Second floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 16.5 + j, -13.75 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.15, 16.5 + j, -13.75 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        j += .5;
        k += .5;
    }

    // Stair railings for left stairs
    j = 0.0;
    k = 0.0;
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.35, 1.5 + j, -9.25 - k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.35, 11.5 + j, -9.25 - k));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        j += .5;
        k += .5;
    }

    // Stair floor railings
    float m = 0.0, n = 0.0;
    for (int i = 0; i < 1; i++) {
        m = 0.0;
        for (int j = 0; j < 16; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.65, 11.0 + n, -17.0 + m));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
            model = translateMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);
            m += .5;
        }
        n += 10;
    }

    // Stair mid-floor railings
    m = 0.0; n = 0.0;
    for (int i = 0; i < 2; i++) {
        m = 0.0;
        for (int j = 0; j < 6; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 6.0 + n, -16.75 + m));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
            model = translateMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.6 + m, 6.0 + n, -16.75));
            model = translateMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);

            if (i < 2) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.6 + m, 11.0 + n, -17.25));
                model = translateMatrix * scaleMatrix;
                cylinder.drawCylinderWithTexture(lightingShader, model);
            }
            m += .5;
        }
        n += 10;
    }

    // Stair lomba railing
    m = 0.0;
    float rotateAngle_X = -45.0;
    float rotateAngle_Z = 90.0;

    for (int i = 0; i < 2; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.35, 4.25 + m, -11.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 3.5, .05));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 9.25 + m, -11.5));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X * -1), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.15, 9.25 + m, -11.5));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X * -1), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 6.5 + m, -15.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 1.5, .05));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.25, 6.5 + m, -16.75));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateZMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        if (i < 1) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.25, 11.5 + m, -17.25));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = translateMatrix * rotateZMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.65, 11.5 + m, -13.35));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 4, .05));
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(1.0f, 0.0f, 0.0f));
            model = translateMatrix * rotateXMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);
        }

        m += 10;
    }
}
