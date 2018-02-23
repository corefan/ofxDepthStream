#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr

namespace persee {
  class Receiver {

    public:
      Receiver(){}

      Receiver(std::string host, int port) {
        start(host, port);
      }

      ~Receiver();

      void start(std::string host, int port);
      char* getData() { return (char*)(buffer + 4); }
      int getSize() const { return lastPackageSize; }
      bool hasNew() const { return bHasNew; }
      void reset(){ bHasNew = false; }

      void setConnectAttemptInterval(unsigned int interval) { connectAttemptInterval = interval; }

    protected:

      std::ostream& cout() { return std::cout << "[persee::Receiver] "; }
      std::ostream& cerr() { return std::cerr << "[persee::Receiver] "; }
      void error(const char *msg);

      void threadFunc();

      bool connectToServer(std::string address, int port);
      void disconnectFromServer();

      bool receive(size_t size);
      bool receive(char* buffer, size_t size);
      bool send_data(std::string data);

    private:
      std::thread* thread;
      bool bRunning=true;
      bool bConnected=false;
      bool bHasNew=false;

      int sock=-1;
      std::string host;
      int port;
      struct sockaddr_in server;

      static const int BUF_SIZE = (1024*1024*4);
      char buffer[BUF_SIZE];
      // int bufferSize=0;
      int recvSize=0;
      int lastPackageSize=0;

      unsigned int connectAttemptInterval = 3000;
  };
}
