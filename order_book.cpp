#include "order_book.h"
#include <iterator> // For std::prev

void OrderBook::add(const Order& o) {
    /*
     * First we check if it is a bid or an ask:
     *
     *      If it is a bid (same goes on for ask, just instead of bid make it ask):
     *          we go through bid_level_ to check if the price of o's exist.
     *
     *          If it exists:
     *              we take the bid_level_ value, then use it to push_back to the list at that position.
     *              we then use that position's memory as a value to the order's id and insert into by_id_
     *
     *          If it doesn't exist:
     *              we make a new entry to bid_prices_ using the o's price
     *              (when inserting, we check in what position it should be inserted then insert using vec.insert())
     *              we insert into levels_ a new list that holds the new order
     *              we use the last levels_ index as an id
     *              that id will be used for bid_level_ as a value, and the o's price as a key.
     *              we then add into by_id_ how we did in the existing case.
     *          
    */

    auto& level_map     = (o.side == Side::Bid) ? bid_level_ : ask_level_;
    auto& prices        = (o.side == Side::Bid) ? bid_prices_ : ask_prices_; 

    std::size_t slot;
    auto it = level_map.find(o.price);

    if (it != level_map.end()) {
        // price already has a level: reuse its slot
        slot = it->second;
    } else { 
        // new price: make an empty list at the end of levels_
        levels_.emplace_back();
        slot = levels_.size() - 1;
        level_map.emplace(o.price, slot);

        // keep prices sorted: bids ascending, asks descending (best at the back)
        std::size_t i = 0;
        if (o.side == Side::Bid) {
            while (i < prices.size() && prices[i] < o.price) ++i;
        } else {
            while (i < prices.size() && prices[i] > o.price) ++i;
        }

        prices.insert(prices.begin() + i, o.price);
    }

    // shared by both paths
    levels_[slot].push_back(o);
    by_id_.emplace(o.id, std::prev(levels_[slot].end()));
}

bool OrderBook::cancel(std::uint64_t id) {
    return false;
}
