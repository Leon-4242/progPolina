#include "stack.h"

int main(void)
{
	list * lst = make_list();
	push_back(lst, 0);
	push_back(lst, 1);
	pop_back(lst);
	push_back(lst, 2);

	del_list(lst);
	return 0;
}
