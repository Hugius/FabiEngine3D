# Server
### Setters
- `fe3d:server_start`(`INT` clients) ---> `NONE`  
  Starts networking server with maximum amount of **clients**.
- `fe3d:server_send_tcp_message`(`STR` username, `STR` message) ---> `NONE`  
  Sends TCP **message** to networking client with **username**.
- `fe3d:server_send_udp_message`(`STR` username, `STR` message) ---> `NONE`  
  Sends UDP **message** to networking client with **username**.
- `fe3d:server_broadcast_tcp_message`(`STR` message, `STR` exception) ---> `NONE`  
  Sends TCP **message** to all connected networking clients, except for **exception** (username).
- `fe3d:server_broadcast_udp_message`(`STR` message, `STR` exception) ---> `NONE`  
  Sends UDP **message** to all connected networking clients, except for **exception** (username).
- `fe3d:server_disconnect_client`(`STR` username) ---> `NONE`  
  Disconnects connected networking client with **username** from networking server.
### Getters
- `fe3d:server_is_running`() ---> `BOOL`  
  Returns true if networking server is running.
- `fe3d:server_is_client_connected`(`STR` username) ---> `BOOL`  
  Returns true if networking client with **username** is connected.
- `fe3d:server_get_new_ip`() ---> `STR`  
  Returns IP address of client that just connected.
- `fe3d:server_get_new_port`() ---> `STR`  
  Returns port of client that just connected.
- `fe3d:server_get_new_username`() ---> `STR`  
  Returns username of client that just connected.
- `fe3d:server_get_old_ip`() ---> `STR`  
  Returns IP address of client that just disconnected.
- `fe3d:server_get_old_port`() ---> `STR`  
  Returns port of client that just disconnected.
- `fe3d:server_get_old_username`() ---> `STR`  
  Returns username of client that just disconnected.
- `fe3d:server_get_connected_ips`() ---> `LIST`  
  Returns IP addresses of all connected networking clients.
- `fe3d:server_get_connected_ports`() ---> `LIST`  
  Returns ports of all connected networking clients.
- `fe3d:server_get_connected_usernames`() ---> `LIST`  
  Returns usernames of all connected networking clients.
- `fe3d:server_get_pending_ips`() ---> `LIST`  
  Returns IP addresses of pending messages from networking clients.
- `fe3d:server_get_pending_ports`() ---> `LIST`  
  Returns ports of pending messages from networking clients.
- `fe3d:server_get_pending_usernames`() ---> `LIST`  
  Returns usernames of pending messages from networking clients.
- `fe3d:server_get_pending_protocols`() ---> `LIST`  
  Returns protocols of pending messages from networking clients.
- `fe3d:server_get_pending_contents`() ---> `LIST`  
  Returns contents of pending messages from networking clients.

# Client
### Setters
- `fe3d:client_start`(`STR` username) ---> `NONE`  
  Starts networking client with custom **username**.
- `fe3d:client_stop`() ---> `NONE`  
  Stops networking client.
- `fe3d:client_connect`(`STR` IP) ---> `NONE`  
  Connects to networking server with **IP** address.
- `fe3d:client_disconnect`() ---> `NONE`  
  Disconnects from networking server.
- `fe3d:client_send_tcp_message`(`STR` message) ---> `NONE`  
  Sends TCP **message** to networking server.
- `fe3d:client_send_udp_message`(`STR` message) ---> `NONE`  
  Sends UDP **message** to networking server.
### Getters
- `fe3d:client_is_running`() ---> `BOOL`  
  Returns true if networking client is running.
- `fe3d:client_is_connecting`() ---> `BOOL`  
  Returns true if networking client is connecting to networking server.
- `fe3d:client_is_connected`() ---> `BOOL`  
  Returns true if networking client is connected to networking server.
- `fe3d:client_get_pending_protocols`() ---> `LIST`  
  Returns protocols of pending messages from networking server.
- `fe3d:client_get_pending_contents`() ---> `LIST`  
  Returns contents of pending messages from networking server.
- `fe3d:client_get_ping_latency`() ---> `INT`  
  Returns average round-trip ping latency from networking client to networking server in milliseconds.
- `fe3d:client_get_server_ip`() ---> `STR`  
  Returns IP address of networking server.
- `fe3d:client_get_username`() ---> `STR`  
  Returns username of networking client.
