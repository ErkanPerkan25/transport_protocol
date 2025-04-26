#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define BUFFER_SIZE 50

struct connInfo{
    string hostName;
    int remoteHostPort;
    int localHostPort;
    //char *buffer = new char[BUFFER_SIZE];
    vector<char> *buffer = new vector<char>(BUFFER_SIZE);
};

int main(int argc, char *argv[]){
    map<string, connInfo> connections;

    string command;
    cin >> command;

    while(command != "quit"){
        if (command == "quit") {
            return 1;  
        }
        if (command == "conn") {
            string hostName;
            int remoteHostPort;
            int localHostPort;
            cin >> hostName >> remoteHostPort >> localHostPort;
        
            connInfo connection;
            connection.hostName = hostName;
            connection.remoteHostPort = remoteHostPort;
            connection.localHostPort = localHostPort;
            // needs to be stored some where
            // map or array?
            connections.insert({hostName, connection});

            cout << "ACK" << " " << connection.hostName << " " << connection.remoteHostPort << " " << connection.localHostPort << " " << connection.buffer->size() << endl;
        }
        if(command == "data"){
            string remoteHostName;
            int remoteHostPort;
            int localHostPort;
            int dataSize;
            string data;
            int moreData;
            cin >> remoteHostName >> remoteHostPort >> localHostPort >> dataSize >> data >> moreData;
            
            /*
            char *cbuff = (char *) data.c_str();
            for(int i=0; data.size(); i++){
                connections[remoteHostName].buffer->push_back(cbuff[i]);
            }
            */

            // append data to remoteHos
            //
            cout << remoteHostName << " " << remoteHostPort << " " <<localHostPort << " " << dataSize << " "<< data << " " << moreData << endl;
            // bool
        }

        //conn
        //data
        //ACK
        //consum
        cin >> command;
    }

    return 0;
}
