#ifndef FORM_H
#define FORM_H

#include <QTimer>
#include "ui_form.h"

#include <functional> 
#include <boost/signals2/signal.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
 
//I based the qt and boost code off of an example I found at http://programmingexamples.net/wiki/Qt/Boost

//Io server isn't really necessary, I had some earlier compilation problems and so I wrapped boost's io_service in another object 
//So really this should probably go away 
class io_server { 
  
  boost::asio::io_service &service_; 
 public: 
  io_server(boost::asio::io_service &service) : service_(service) {}; 
  
  
  void stop() { 

    service_.stop(); 
    service_.reset(); 
  }

  void operator()() { 
    service_.reset(); 
    service_.poll(); 
  }
  

}; 

//Typical Object inheriting from QtWidget 
class MyForm : public QWidget, private Ui::Form
{
	Q_OBJECT
	std::shared_ptr<QTimer> timer_; 
	bool status_; 
	io_server &server_; 
	
 public:
	MyForm(QWidget *parent, io_server &server); 

	public Q_SLOTS:
	  void startButton_ServerRunner(); //Start timer_ 
	  void timeout_Poll(); //Poll the boost io service 


};
 
#endif

