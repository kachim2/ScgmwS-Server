#include<SFML/Network.hpp>
#include<iostream>
#include <vector>

struct cldata
{
    sf::Int32 X = 0, Y = 0;
    uint8_t side = 0;
    uint8_t lvlhash[32] = {0};

};


int main(){
    sf::TcpListener listener;
    listener.listen(5300);
    // Create a list to store the future clients
    std::vector<sf::TcpSocket*> clients;
    std::vector<cldata> clientsdata;
    // Create a selector
    sf::SocketSelector selector;
    // Add the listener to the selector
    selector.add(listener);
    // Endless loop that waits for new connections
    while (true)
    {
            
            // Make the selector wait for data on any socket
            if (selector.wait(sf::seconds(3.0f)))
            {
                // Test the listener
                if (selector.isReady(listener))
                {
                    // The listener is ready: there is a pending connection
                    sf::TcpSocket* client = new sf::TcpSocket;
                    if (listener.accept(*client) == sf::Socket::Done)
                    {
                        // Add the new client to the clients list
                        clients.push_back(client);
                        clientsdata.push_back(cldata());
                        // Add the new client to the selector so that we will
                        // be notified when he sends something
                        selector.add(*client);
                    }
                    else
                    {
                        // Error, we won't get a new connection, delete the socket
                        delete client;
                    }
                }
                else
                {
                    // The listener socket is not ready, test all other sockets (the clients)
                    int ri = 0;
                    for (int it = 0; it < clients.size(); ++it)
                    {
                        
                        sf::TcpSocket& client = *clients[it];
                        
                        if (selector.isReady(client))
                        {
                            // The client has sent some data, we can receive it
                            sf::Packet rpacket;
                            sf::TcpSocket::Status State = client.receive(rpacket);
                            if (State == sf::Socket::Done)
                            {
                                rpacket >> clientsdata[it].X >> clientsdata[it].Y >> clientsdata[it].side; 
                                
                                for(int i = 0; i < 32; i++){
                                    rpacket >> clientsdata[it].lvlhash[i];
                                }
                                sf::Int32 one = 1;
                                sf::Int32 playercount = 0;
                                for(int i = 0; i< clientsdata.size(); i++){
                                    bool is = 1;
                                    for(int j = 0; j < 32; j++){
                                        if(clientsdata[i].lvlhash[j] != clientsdata[it].lvlhash[j]){
                                            is = 0;
                                        }
                                    }
                                    if (is) playercount++;
                                     
                                }
                                sf::Packet Spacket;
                                Spacket << playercount-1;
                                client.send(Spacket);
                                sf::Packet Spacket1;
                                for(int i = 0; i< clientsdata.size(); i++){
                                    bool is = 1;
                                    for(int j = 0; j < 32; j++){
                                        if(clientsdata[i].lvlhash[j] != clientsdata[it].lvlhash[j]){
                                            is = 0;
                                        }
                                    }
                                    if (is && it != i){
                                        Spacket1 << clientsdata[i].X << clientsdata[i].Y << clientsdata[i].side;
                                    }
                                     
                                }
                                client.send(Spacket1);


                            }
                            if(State == sf::Socket::Disconnected){
                                
                                clients.erase(clients.begin()+it);
                                selector.remove(client);
                                clientsdata.erase(clientsdata.begin()+it);
                            }
                        }
                        ri++;
                    }
                }
            }
        }
}