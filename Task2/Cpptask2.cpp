#include <ctime>
#include <vector>
#include <assert.h>
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
	return [items](int check) -> bool {
				bool f = false;
				for(int i = 0; i < items.size(); ++i)
					if (items[i].value == check) {
						f = true;
						break;
					}
				return f;
			};
}

int main(void)
{
Items items = MakeItemsSimple<1, 1, 4, 5, 6>();
Items newItems = MakeItemsSimple();
auto isFound = MakePredicate(items);
auto isFoundNew = MakePredicate(newItems);
assert(isFound(6) == true);
assert(isFound(7) == false);
assert(isFoundNew(8) == false);
assert(isFoundNew(6) == false);

	return 0;
}
