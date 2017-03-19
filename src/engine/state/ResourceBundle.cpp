//
// Created by Timothy Blumberg on 31/12/16.
//

#include "ResourceBundle.h"

int ResourceBundle::getQuantity(Resource key)
{
    return resources[key];
}

void ResourceBundle::addResource(Resource key, int quantity)
{
    resources[key] += quantity;
}

std::unordered_map<int, unsigned int> ResourceBundle::getResources() const
{
    return resources;
}

ResourceBundle &ResourceBundle::operator+(const ResourceBundle &other)
{
    for(std::pair<const int, unsigned int> r: other.resources)
    {
        this->resources[r.first] += r.second;
    }

    return *this;
}

ResourceBundle &ResourceBundle::operator-(const ResourceBundle &other)
{
    for (std::pair<const int, unsigned int> r: other.resources)
    {
        this->resources[r.first] -= r.second;
    }

    return *this;
}

/*
 * Transfers resources from other to this. Other should be zeroed out after using this.
 */
ResourceBundle &ResourceBundle::operator >>(const ResourceBundle &other)
{
    for(const auto r: other.resources)
    {
        resources[r.first] += r.second;
        other.getResources()[r.first] = 0;
    }

    return *this;
}

ResourceBundle &ResourceBundle::operator+=(const ResourceBundle &other)
{
    return *this + other;
}

void ResourceBundle::printContents()
{
    std::cout << "mymap contains:";

    for (auto it = resources.begin(); it != resources.end(); ++it)
    {
        std::cout << " " << it->first << ":" << it->second << std::endl;
    }
}
