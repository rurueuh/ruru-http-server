#include "Socket.hpp"
#include "Http.hpp"
#include "Log.hpp"
#include <fstream>

int main(int argc, char **argv)
{
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.

    Socket server(4221);
    server.listen();
    while (1) {
        Socket client = server.accept();
        std::string data = client.recv();
        std::string path = Http::getPath(data);
        Log::save("Request from " + client.getIP() + ": " + path);
        // insert before in path ./www
        path = "../www" + path;
        // check if the file exists
        auto file = std::fstream(path);
        if (file.is_open()) {
            uint file_size = 0;
            file.seekg(0, std::ios::end);
            file_size = file.tellg();
            file.seekg(0, std::ios::beg);
            std::string content = "";
            for (uint i = 0; i < file_size; i++) {
                content += file.get();
            }
            std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(file_size) + "\r\n Content-Type: text/html\r\n\r\n" + content;
            client.send(response);
            continue;
        } else {
            std::string response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n Content-Type: text/html\r\n\r\n";
            client.send(response);
        }
        
    }

    return 1-1;
}
