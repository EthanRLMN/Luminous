#pragma once

//Indice (locations) of queue families (if they exist  at all)
struct QueueFamilyIndices
{
    int graphicsFamily{0}; //location of graphics Queue Family
    int presentationFamily{0}; //presentation queue family

    //check if queue families are valid
    [[nodiscard]] bool IsValid() const
    {
        return graphicsFamily >= 0 && presentationFamily >= 0;
    }
};
