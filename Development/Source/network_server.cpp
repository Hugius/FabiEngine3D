//#include "network_server.hpp"
//#include "logger.hpp"
//
////#include <ws2tcpip.h>
//
//void NetworkServer::start()
//{
//	// Compose address info hints
//	struct addrinfo hints;
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_INET;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//	hints.ai_flags = AI_PASSIVE;
//
//	// Create address info
//	struct addrinfo* addressInfo = NULL;
//	auto infoResult = getaddrinfo(NULL, SERVER_PORT.c_str(), &hints, &addressInfo);
//	if (infoResult != 0) {
//		Logger::throwError("Server startup failed with error code: ", infoResult);
//		stop();
//		return;
//	}
//
//	// Create socket for listening
//	auto listenSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
//	if (listenSocket == INVALID_SOCKET) {
//		printf("Error at socket(): %ld\n", WSAGetLastError());
//		freeaddrinfo(addressInfo);
//		WSACleanup();
//		return;
//	}
//}
//
//void NetworkServer::stop()
//{
//	WSACleanup();
//}