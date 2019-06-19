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
}