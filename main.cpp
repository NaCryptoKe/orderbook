#include "order_book.h"
#include <iostream>

int main()
{
    Order o1{7521, 1025, 200, Side::Bid};
    Order o2{7522, 1025, 50, Side::Bid};
    Order o3{7523, 1030, 100, Side::Bid};

    OrderBook ob;
    ob.add(o1);
    ob.add(o2);
    ob.add(o3);

    return 0;
}
