//
// buffer.hpp
//

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <memory>
#include <vector>
#include <boost/asio.hpp>

namespace distributor {

/// A reference-counted mutable buffer. The caller is responsible for only
/// writing from one thread.
class buffer {
public:
    /// Construct with the given size.
    explicit buffer(std::size_t size = 0)
        : data_(std::make_shared<std::vector<char>>(size))
    {
    }

    /// Create a mutable buffer to the data.
    boost::asio::mutable_buffer to_buffer()
    { 
        return boost::asio::buffer(*data_);
    }
private:
    std::shared_ptr<std::vector<char>> data_;
};

} // namespace distributor

#endif // BUFFER_HPP
