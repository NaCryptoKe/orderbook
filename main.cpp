#include "order_book.h"
#include <iostream>

int main()
{
    Order o1{1, 10002, 10, Side::Bid};

    OrderBook ob;
    ob.add(o1);

    return 0;
}
