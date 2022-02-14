#include "StructUtils.h"
#include <set>

//template <typename Titem>
bool ExtractFromSet(char const& item, std::multiset<char>& container)
{
    std::multiset<char>::iterator ItemPosition = container.find(item);

    // El elemento no está en el conjunto
    if (ItemPosition == container.end())
        return false;

    // Borro el elemento del conjunto
    container.erase(ItemPosition);

    return true;
}
