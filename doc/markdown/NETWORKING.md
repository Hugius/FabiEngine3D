# Networking

<img src="../image/client_server.png" width="75%"/>

## 1. Server

### 1.1 General

- A FabiEngine3D server is a separate application that runs on its own.
- Its only purpose is processing incoming/outgoing messages from/to clients.
- If you export a server project there will be no window display, only the logging console.
- A server is hosted on the IPV4 address of your computer (write `ipconfig` in your Windows command prompt to look it up).
- You can portforward the server in your router settings on port `61205` for both TCP & UDP protocols.
- There can be only 1 server running on the same machine at the same time.
- You can set a maximum amount of clients that can connect to the server.
- An exported server application runs at the maximum update speed possible (overrides the fixed engine updates speed).

### 1.2 Scripting

- Read the [scripting documentation](SCRIPTING.md) first!
- You can only start a server in an initialization script before any other FE3D scripting functions are called.
- Before you can call any other server scripting functions, the server must be started.
- Be careful with performance heavy operations in the server scripts.
- The scripts of a server can only access these `fe3d` functions (`*` means "everything"):
  - `fe3d:server_*`
  - `fe3d:directory_*`
  - `fe3d:file_*`
  - `fe3d:clock_*`
  - `fe3d:application_stop`
  - `fe3d:print`
  - `fe3d:time_interval`

## 2. Client

### 2.1 General

- A FabiEngine3D client exists within a FabiEngine3D application.
- Its only purpose is sending/receiving messages to/from the server.
- When you start a client, you must specify a username that cannot be longer than 16 characters.
- To be able to use the client, you need to be connected to AND accepted by the server.
- The client can only be connected to 1 server at a time.
- You can always retrieve pending messages, because of error messages sent by the server if the connection attempt went wrong.

### 2.2 Scripting

- Read the [scripting documentation](SCRIPTING.md) first!
- Before you can call any other client scripting functions, the client must be started and connected to a server.

### 2.3 Errors

- When connecting to a server fails, the server will send error messages.
- `SERVER_FULL`: the server is currently at maximum client capacity.
- `ALREADY_CONNECTED`: another client with the same username is already connected to the server.
- `DISCONNECTED`: you have been disconnected by the server.

## 3. TCP & UDP

- On top of the IP protocol, there are 2 different protocols for sending data through networking: TCP & UDP.
- TCP stands for "Transmission Control Protocol".
- UDP stands for "User Datagram Protocol".
- TCP is relatively slow, because it guarantees that the sent data will always arrive at the recipient in the same order the data was sent.
- UDP is relatively fast, because it cannot guarantee that the data will always arrive at the recipient in the same order the data was sent.
- TCP example scenario: you need to send chat messages to other players. The chat messages must always arrive (and in the same order).
- UDP example scenario: you need to send your player position to other players. It is no big deal if some data gets lost.
- You can choose which protocol you want to use when sending a message. This gives you more control over performance decisions.

## 4. Messaging

- A network message cannot be longer than 128 characters or contain any semicolons (`;`).
- There is no guarantee that if you send multiple messages right after each other, they will arrive at the same time.
- Every update in either the server or the client, the pending messages will be cleared before receiving new messages.
- Some messages are reserved for the engine: `REQUEST`, `ACCEPT`, `PING`, `SERVER_FULL`, `ALREADY_CONNECTED`, `DISCONNECTED`.
