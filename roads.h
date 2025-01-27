#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "cylinder.h"



void roads(Shader& lightingShader, Cube& cube_road, Cube& cube_footpath)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //Cube cube = Cube(diffMap_road, specMap_black, 52.0f, 0.0f, 0.0f, 50.0f, 1.0f);

    //roads
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, -0.5, 3.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(60, .5, 3));
    model = translateMatrix * scaleMatrix;
    cube_road.drawCubeWithTexture(lightingShader, model);
    

    
    //Cube cube1 = Cube(diffMap_footpath, specMap_black, 32.0f, 0.0f, 0.0f, 50.0f, 4.0f);
    
    //footpath
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-25, -0.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0, 1, 3));
    model = translateMatrix * scaleMatrix;
    cube_footpath.drawCubeWithTexture(lightingShader, model);
    
   
}


#pragma once
