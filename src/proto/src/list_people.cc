// See README.txt for information and build instructions.

#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <boost/foreach.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using yourMOMsdsdsddsds
using namespace std;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const tutorial::AddressBook& address_book) {
  for (int i = 0; i < address_book.person_size(); i++) {
    const tutorial::Person& person = address_book.person(i);

    cout << "Person ID-->: " << person.id() << endl;
    cout << "  Name-->: " << person.name() << endl;
    if (person.has_email()) {
      cout << "  E-mail address: " << person.email() << endl;
    }

    cout << "Status n STUFF: " << person.status() << endl;


    for (int j = 0; j < person.phone_size(); j++) {
      const tutorial::Person::PhoneNumber& phone_number = person.phone(j);

      switch (phone_number.type()) {
        case tutorial::Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case tutorial::Person::HOME:
          cout << "  Home phone #: ";
          break;
        case tutorial::Person::WORK:
          cout << "  Work phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
    cout << "SIZE OF STRUCTURE UP IN HURRR: " << person.ByteSize() << endl;
    cout << "CREATE ARRAY HERE..." << endl;
    char arrayToSend[person.ByteSize()];

    person.SerializeToArray(arrayToSend, person.ByteSize());


    int z =0;
    cout << "printing out send array now..." << endl;
    for(z = 0; z < person.ByteSize(); z++)
    	cout << " " << arrayToSend[z];
    cout << "end printing out send array now..." << endl;


    /*let's send out data here */
    boost::asio::io_service io_serverUDP;

    udp::socket socket(io_serverUDP);

    socket.open(udp::v4());

    boost::system::error_code myError;

    boost::asio::ip::address_v4 targetIP;
    targetIP.from_string("192.168.1.16", myError);

    boost::asio::ip::udp::endpoint xEndPoint;
    xEndPoint.address(targetIP);
    xEndPoint.port(777);

    socket.open(xEndPoint.protocol(), myError);
    socket.bind(xEndPoint, myError);


    //while(1)
    //{
		cout << "sizeof " << sizeof(arrayToSend) << endl;
		socket.send_to(boost::asio::buffer(arrayToSend, sizeof(arrayToSend)), xEndPoint);
		cout << "sending data..." << endl;

		boost::array<char, 128> recv_buf;
		size_t len = socket.receive_from( boost::asio::buffer(recv_buf), xEndPoint);
		cout.write(recv_buf.data(), len);

		/*now let's deseralize*/

		tutorial::Person dePerson;

		dePerson.ParseFromString(recv_buf.data());

		cout << "Done deserialization process..." << endl;
		cout << "Person: " << dePerson.name() << endl;
		cout << "Info: " << dePerson.status() << endl;
		cout << "Phone: " << dePerson.email() << endl;


	//}
	std::string strIt("yoyoyoy");

	BOOST_FOREACH(char c, strIt)
	{
		std::cout << c;
	}

  }


}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  cout << "protbuf version verified" << endl;
  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  tutorial::AddressBook address_book;

  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

  cout << "received address book...now time to list people" << endl;
  ListPeople(address_book);

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
