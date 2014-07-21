#include "form.h"

//I based the qt and boost code off of an example I found at http://programmingexamples.net/wiki/Qt/Boost


 
MyForm::MyForm(QWidget *parent, io_server &server)
  : QWidget(parent), server_(server)
{
  status_ = false; 
  setupUi(this);
  timer_ = std::make_shared<QTimer>(); 

  //Connecting the start button click with the local server runner function 
  connect( this->startButton, SIGNAL( clicked () ), this, SLOT(startButton_ServerRunner() ) ); 
  //Connecting the timer's timeout signal to our boost calling fn 
  connect( this->timer_.get(), SIGNAL( timeout() ), this, SLOT(timeout_Poll()) ); 
  
}
 

// If stopped start the server, otherwise stop the server (by stopping the QTimer)
void MyForm::startButton_ServerRunner() { 
  if (status_) { 
      std::cout << "Stopping server" << std::endl; 
      timer_->stop(); 
      status_ = false; 
      startButton->setText("Stopped"); 

  }
  else { 
    std::cout << "Running server" << std::endl; 
    timer_->start(100); 
    status_ = true; 
    startButton->setText("Running"); 
  }
  
  
}

//Call io_server's operator() to poll the boost io_service, again probably unnecessary 
void MyForm::timeout_Poll() { 
 server_(); 
}
