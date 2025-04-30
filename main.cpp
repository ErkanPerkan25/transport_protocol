#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define BUFFER_SIZE 50

struct buffer {
    char *buffer = new char[BUFFER_SIZE];
    int nextRead;
    int nextWrite;
    int size;
};

struct connInfo{
    string hostName;
    int remoteHostPort;
    int localHostPort;
    buffer buff;
    //char *buffer = new char[BUFFER_SIZE];
    //vector<char> *buffer = new vector<char>();
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
            connection.buff.nextWrite = 0;
            connection.buff.nextRead = 0;
            connection.buff.size = 0;
            for(int i=0; i < BUFFER_SIZE; i++){
                connection.buff.buffer[i] = ' ';
            }
            // needs to be stored some where
            // map or array?
            connections.insert({hostName, connection});

            cout << "ACK" << " " << connection.hostName << " " << connection.remoteHostPort << " " << connection.localHostPort << " " << BUFFER_SIZE << endl;
        }
        else if(command == "data"){
            string remoteHostName;
            int remoteHostPort;
            int localHostPort;
            int dataSize;
            string data = "";
            int moreData;
            cin >> remoteHostName >> remoteHostPort >> localHostPort >> dataSize >> data >> moreData;

           
            if (connections.find(remoteHostName) != connections.end()) {
                if(data.size() > dataSize){
                    cerr << "too much data" << endl;
                }
                else{
                    for(int i=0; i < dataSize; i++){
                        if (connections[remoteHostName].buff.nextWrite == BUFFER_SIZE) {
                            connections[remoteHostName].buff.nextWrite = 0;
                        }

                        connections[remoteHostName].buff.buffer[connections[remoteHostName].buff.nextWrite] = data[i];
                        connections[remoteHostName].buff.nextWrite++;
                        connections[remoteHostName].buff.size++;

                        if (connections[remoteHostName].buff.size > BUFFER_SIZE) {
                            connections[remoteHostName].buff.size = BUFFER_SIZE;
                        }
                    }
                }
            }
            

            // append data to remoteHos
            cout << data << endl;
            cout << connections[remoteHostName].buff.buffer << endl;
            cout << "ACK " <<remoteHostName << " " << remoteHostPort << " " << localHostPort << " " << BUFFER_SIZE - connections[remoteHostName].buff.size << endl;
            //cout << remoteHostName << " " << remoteHostPort << " " <<localHostPort << " " << dataSize << " "<< data << " " << moreData << endl;
            // bool
        }
        else if(command == "list"){
            for(auto con : connections){
                cout << "               " << con.first << " " << con.second.remoteHostPort << " " << con.second.localHostPort << " ";
                cout << "[" << con.second.buff.buffer;
                cout << "]" << " f=" << con.second.buff.nextRead << " n=" << con.second.buff.size << endl;

            }

        }
        else if(command == "consume"){
            string remoteHostName;
            int remoteHostPort;
            int localPort;
            int dataToRead;
            cin >> remoteHostName >> remoteHostPort >> localPort >> dataToRead;
            
            if (connections.find(remoteHostName) != connections.end()) {
                string removedData; 
                for(int i=0; i < dataToRead; i++){
                    removedData.push_back(connections[remoteHostName].buff.buffer[i]);
                    connections[remoteHostName].buff.buffer[i] = ' ';
                    connections[remoteHostName].buff.size--;
                    connections[remoteHostName].buff.nextRead++;
                }

                //connections[remoteHostName].buff.size -= dataToRead;

                cout << "(READ) " << '"' << removedData << '"' << endl;
                cout << "ACK " << remoteHostName << " " << remoteHostPort << " " << localPort << " " << BUFFER_SIZE - connections[remoteHostName].buff.size << endl;
            } 


        }

        //conn
        //data
        //ACK
        //consum
        cout << endl;
        cin >> command;
    }

    return 0;
}
