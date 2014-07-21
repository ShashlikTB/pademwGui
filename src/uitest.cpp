#include <QApplication>
#include <iostream>
 
#include "form.h"





//Asynchronous printer function that prints a statement after some number of seconds
//Note: This uses absolute time for the count, so if you stop and restart the server you 
//may all of sudden get a bunch of statements 
class printer { 

public:
  printer(boost::asio::io_service &service, boost::posix_time::seconds s) : timer_(service, boost::posix_time::seconds(s)), count_(0) {
    timer_.async_wait(boost::bind(&printer::print, this)); 

  }

  ~printer() { 
    std::cout << "Final Count: " << count_ << std::endl; 
  }
  
  void print() {
      std::cout << "Fired! " << count_ << std::endl; 
      ++count_; 
      //When does the timer expire
      timer_.expires_at(timer_.expires_at()+boost::posix_time::seconds(1)); 
      //Add the timer to io_service, must be readded each time it fires 
      timer_.async_wait(boost::bind(&printer::print, this)); 
      
  }

private: 
  boost::asio::deadline_timer timer_; 
  int count_; 
}; 


 
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  //io_service provides its own event loop and has good documentation at 
  //http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference/io_service.html
  //Currently it's running in the main thread so I'm using polling to check for updates rather than run()
  //for the actual network server I may have it running in its own thread

  boost::asio::io_service mainThreadService; 

  io_server bs(mainThreadService); 

  MyForm form(0, bs); 


  form.show();
 
  
  printer printing(mainThreadService, boost::posix_time::seconds(1)); 
	      



  
  return app.exec();
}


