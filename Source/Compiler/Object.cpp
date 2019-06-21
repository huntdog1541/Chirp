#include "Object.h"

#include <iostream>

namespace Obj
{
	Object FindByName(std::string name,std::vector<Object> objects)
	{
		bool hasFound = false;

		for (auto& obj : objects)
		{
			if (hasFound)
			{
				break;
			}
			
			if (obj.Name == name)
			{
				hasFound = true;
				return obj;
			}
		}

		if (!hasFound)
		{
			Object undef; // Undefined object
			undef.Name = "undefined";
			undef.Size = 1;
			return undef;
		}
	}
	Object FindById(std::string id, std::vector<Object> objects)
	{
		bool hasFound = false;
		
		for (auto& obj : objects)
		{
			if (hasFound)
			{
				break;
			}

			if (obj.Id == id) // I forgot that works
			{
				hasFound = true;
				return obj;
			}
		}

		if (!hasFound)
		{
			Object undef; // Undefined object
			undef.Name = "undefined";
			undef.Size = 1;
			return undef;
		}
	}
}