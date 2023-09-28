#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  
  string request = "GET " + path + " HTTP/1.1\r\n" +
                              "Host: " + host + "\r\n" +
                              "Connection: close\r\n\r\n";

  string service = "http";
  // like telnet > telnet cs144.keithw.org http
  TCPSocket tcpSock;
  string output;
  tcpSock.connect(Address{host, service});
  // write datagram
  tcpSock.write(request); 
  tcpSock.read(output);
  cout << output <<endl;
  tcpSock.close();
  
  //cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      // abort() is a function that is part of the C Standard Library
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    // std::span is a C++20 feature that represents a view over a contiguous sequence of elements. It allows you to work with a range of elements without owning or copying them.
    // auto is a keyword in C++ that tells the compiler to automatically deduce the type of a variable based on its initializer. 
    // args is span object
    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
