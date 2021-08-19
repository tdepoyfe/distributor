//
//  distributor.cpp
//

#include "distributor.hpp"

namespace distributor {

distributor::distributor(const std::string& up_address, const std::string& up_port,
        const std::string& down_address, const std::string& down_port)
    : io_context_(1),
      up_socket_(io_context_),
      acceptor_(io_context_)
{
    // Connect to the address upstream.
    boost::asio::ip::tcp::resolver resolver(io_context_);
    auto endpoints = resolver.resolve(up_address, up_port);
    boost::asio::connect(up_socket_, endpoints);

    do_receive();

    // Connect to the port downstream and start accepting new connections.
    endpoints = resolver.resolve(down_address, down_port);
    boost::asio::ip::tcp::endpoint endpoint = *endpoints.begin();
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    do_accept();
}

void distributor::run()
{
    io_context_.run();
}

void distributor::do_accept()
{
    acceptor_.async_accept(
            [this](const boost::system::error_code& error, 
                boost::asio::ip::tcp::socket connection)
            {
                if (!error)
                {
                   down_sockets_.push_back(std::move(connection)); 
                }

                do_accept();
            }
    );
}

void distributor::do_receive()
{
    buffer_ = buffer(8192);
    up_socket_.async_receive(buffer_.to_buffer(),
        [this](const boost::system::error_code& error,
            std::size_t bytes_transferred)
        {
            if (!error)
            {
                do_write();
            }

            do_receive();
        }
    );
}

void distributor::do_write()
{
    for (auto& socket : down_sockets_)
    {
        buffer buffer(buffer_);
        boost::asio::async_write(socket, buffer.to_buffer(),
            [this, buffer](const boost::system::error_code& error,
                std::size_t bytes_transferred)
            {
            }
        );
    }
};

} // namespace distributor
