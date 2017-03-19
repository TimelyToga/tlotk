//
// Created by Timothy Blumberg on 18/03/17.
//

#ifndef TLOTK_VECTORUTILS_H
#define TLOTK_VECTORUTILS_H

namespace utils
{
    static glm::vec3 calculateNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
    {
        /*
         *  PSEUDO-CODE FROM (https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal):
         *  Set Vector U to (Triangle.p2 minus Triangle.p1)
         *  Set Vector V to (Triangle.p3 minus Triangle.p1)
         *
         *  Set Normal.x to (multiply U.y by V.z) minus (multiply U.z by V.y)
         *  Set Normal.y to (multiply U.z by V.x) minus (multiply U.x by V.z)
         *  Set Normal.z to (multiply U.x by V.y) minus (multiply U.y by V.x)
         */
        glm::vec3 u = p2 - p1;
        glm::vec3 v = p3 - p1; // maybe this is fine?

        glm::vec3 n;

        n.x = (u.y * v.z) - (u.z * v.y);
        n.y = (u.z * v.x) - (u.x * v.z);
        n.z = (u.x * v.y) - (u.y * v.x);

        return n;
    }
}

#endif //TLOTK_VECTORUTILS_H
