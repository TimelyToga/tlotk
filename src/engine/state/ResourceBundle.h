//
// Created by Timothy Blumberg on 31/12/16.
//

#ifndef OPENGL_TEST1_RESOURCEBUNDLE_H
#define OPENGL_TEST1_RESOURCEBUNDLE_H

#include "Resource.h"
#include <unordered_map>
#include <iostream>

class ResourceBundle
{
    public:
        ResourceBundle();
        ~ResourceBundle();

        int getQuantity(Resource key);
        void addResource(Resource key, int quantity);
        std::unordered_map<int, unsigned int> getResources() const;

        ResourceBundle& operator +(const ResourceBundle &other);
        ResourceBundle& operator -(const ResourceBundle &other);
        ResourceBundle& operator +=(const ResourceBundle &other);
        ResourceBundle& operator >>(const ResourceBundle &other);

        void printContents();

    private:
        std::unordered_map<int, unsigned int> resources;


};


#endif //OPENGL_TEST1_RESOURCEBUNDLE_H
