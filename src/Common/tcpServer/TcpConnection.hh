#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

class TcpConnection:
  public boost::enable_shared_from_this<TcpConnection>
{

public:
  typedef boost::shared_ptr<TcpConnection> ConnectionPtr;
 
  static ConnectionPtr create(boost::asio::io_service& io) {
    return ConnectionPtr(new TcpConnection(io));
  }

  boost::shared_ptr<boost::asio::ip::tcp::socket> getSocket();
  void start();
  

private:
  TcpConnection(boost::asio::io_service &io);
  void prv_handleRead(const boost::system::error_code&, size_t);
  void prv_handleWrite(const boost::system::error_code&, size_t);


  // Member Variables
  boost::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
  enum { maxSize = 1024 };
  char m_data[maxSize];
  std::string m_message;
};
