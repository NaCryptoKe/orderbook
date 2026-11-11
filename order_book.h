#pragma once

#include <cstdint>
#include <list>
#include <unordered_map>
#include <vector>

enum class Side : std::uint8_t { Bid, Ask };

struct Order {
    std::uint64_t   id;
    std::int64_t    price;      // in cents, $100.02 means 10002 cents.
    std::uint32_t   shares;
    Side            side;
};

// Queue for the bid and ask
using Level = std::list<Order>;

class OrderBook {
    std::vector<Level> levels_;                 // the queue storage

    // Hashmaps using price as int, and position in the vector
    std::unordered_map<std::int64_t, std::size_t> bid_level_;
    std::unordered_map<std::int64_t, std::size_t> ask_level_;

    std::unordered_map<std::uint64_t, Level::iterator> by_id_;

    std::vector<std::int64_t> bid_prices_;
    std::vector<std::int64_t> ask_prices_;

public:
    void add(const Order& o);
    bool cancel(std::uint64_t);
};
