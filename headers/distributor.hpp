//
// distributor.hpp
//

#ifndef DISTRIBUTOR_HPP
#define DISTRIBUTOR_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "buffer.hpp"

namespace distributor {

/// Establish connection upstream, listen for connections,
/// and pass information downstream.
class distributor
{
public:
    /// Constructor.
    distributor(const std::string& up_address, const std::string& up_port,
            const std::string& down_address, const std::string& down_port);

    /// Run the service.
    void run();
private:
    /// Start asynchronously accepting connections.
    void do_accept();

    /// Start asynchronously receiving for data from upstream.
    void do_receive();

    /// Start asynchronously writing on all downstream sockets.
    void do_write();

    /// The io_context for the whole service.
    boost::asio::io_context io_context_;
    
    /// The socket for the upstream connection.
    boost::asio::ip::tcp::socket up_socket_;

    /// The acceptor for downstream connections.
    boost::asio::ip::tcp::acceptor acceptor_;

    /// The vector to manage the connections downstream.
    std::vector<boost::asio::ip::tcp::socket> down_sockets_;

    /// The pointer to the current buffer to receive connections.
    buffer buffer_;
};

} // namespace distributor

#endif // DISTRIBUTOR_HPP
