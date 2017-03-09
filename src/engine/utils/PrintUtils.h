//
// Created by Timothy Blumberg on 09/03/17.
//

#ifndef TLOTK_PRINTUTILS_H
#define TLOTK_PRINTUTILS_H

#include <glm/vec3.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>

namespace utils
{
    static void print(glm::vec3 v)
    {
        std::cout << " (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
    }

    static void print(glm::mat4 m)
    {
        for(int x = 0; x < 4; x++)
        {
            if(x == 0)
            {
                std::cout << " [ ";
            } else
            {
                std::cout << "   ";
            }
            for(int y = 0; y < 4; y++)
            {
                std::cout << m[y][x] << ", ";
            }

            std::cout << std::endl;
        }
    }

}

#endif //TLOTK_PRINTUTILS_H
