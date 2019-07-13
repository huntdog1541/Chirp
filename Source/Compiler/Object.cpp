#include "Object.h"

#include <algorithm>
namespace Obj
{
	int FindByName (const std::string& name, const std::vector<Object>& objects)
	{
        const auto it = std::find_if(objects.begin(), objects.end(),[&](const Object& obj){ return obj.Name == name; });
        if(objects.end() == it){ return -1; }
        
        return std::distance(objects.begin(), it);
	}

	int FindById(const std::string& id, const std::vector<Object>& objects)
	{
        const auto it = std::find_if(objects.begin(), objects.end(),[&](const Object& obj){ return obj.Id == id; });
        if(objects.end() == it){ return -1; }
        
        return std::distance(objects.begin(), it);
	}
}
