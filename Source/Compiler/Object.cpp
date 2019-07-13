#include "Object.h"

#include <iostream>

namespace Obj
{
	int FindByName (std::string name,std::vector<Object> objects)
	{
		bool hasFound = false;

		int pos = 0;

		for (auto& obj : objects)
		{
			if (obj.Name == name)
			{
				return pos;
			}
			pos++;
		}

        return -1;
	}
	int FindById(std::string id, std::vector<Object> objects)
	{
		bool hasFound = false;
		int pos = 0;

		for (auto& obj : objects)
		{
			if (obj.Id == id)
			{
				return pos;
			}
			pos++;
		}
        return -1;
	}
}
