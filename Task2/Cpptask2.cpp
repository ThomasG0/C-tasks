#include <ctime>
#include <vector>
#include <assert.h>
#include <algorithm>
// ....

struct TItem
{
    int value;
    time_t timestamp;
    TItem(int v):
        value(v),
        timestamp(std::time(0))
    {}
    //...
};

using Items = std::vector<TItem>;

template<int... args>
Items MakeItemsSimple()
{
    std::vector<TItem> example = {args...};
    return example;
}

auto MakePredicate(Items items)
{
    return [items](const int check) -> bool
            {
                return std::find_if(items.begin(), items.end(),
                                        [check](const TItem elem) -> bool
                                            {
                                                return (elem.value == check);
                                            }
                                    ) != items.end();
            };
}

int main()
{
Items items = MakeItemsSimple<0, 1, 4, 5, 6>();
Items newItems = MakeItemsSimple<7, 15, 1>();
auto isFound = MakePredicate(items);
auto isFoundNew = MakePredicate(newItems);
assert(isFound(6) == true);
assert(isFound(7) == false);
assert(isFoundNew(8) == false);
assert(isFoundNew(6) == false);

    return 0;
}
