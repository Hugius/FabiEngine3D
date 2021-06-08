# Networking
- `fe3d:network_server_start`(`INT` clients) ---> `NONE`  
  Starts networking server with a maximum amount of **clients**.
- `fe3d:network_server_stop`() ---> `NONE`  
  Stops networking server.
- `fe3d:network_server_is_running`() ---> `BOOL`  
  Returns true if networking server is running.
- `fe3d:network_server_is_client_connected`(`STR` username) ---> `BOOL`  
  Returns true if client with **username** is connected.
- `fe3d:network_server_send_tcp_message`(`STR` username, `STR` message) ---> `NONE`  
  Sends a TCP **message** to client with **username**.
- `fe3d:network_server_send_udp_message`(`STR` username, `STR` message) ---> `NONE`  
  Sends a UDP **message** to client with **username**.
- `fe3d:network_server_broadcast_tcp_message`(`STR` message) ---> `NONE`  
  Sends a TCP **message** to all connected clients.
- `fe3d:network_server_broadcast_udp_message`(`STR` message) ---> `NONE`  
  Sends a UDP **message** to all connected clients.
- `fe3d:network_server_disconnect_client`(`STR` username) ---> `NONE`  
  Disconnects a connected client with **username** from the server.
- `fe3d:network_server_get_connected_ips`() ---> `LIST`  
  Returns the IP addresses of all connected clients.
- `fe3d:network_server_get_connected_ports`() ---> `LIST`  
  Returns the ports of all connected clients.
- `fe3d:network_server_get_connected_usernames`() ---> `LIST`  
  Returns the usernames of all connected clients.
- `fe3d:network_server_get_pending_ips`() ---> `LIST`  
  Returns the corresponding IP addresses of the pending messages from clients.
- `fe3d:network_server_get_pending_ports`() ---> `LIST`  
  Returns the corresponding ports of the pending messages from clients.
- `fe3d:network_server_get_pending_usernames`() ---> `LIST`  
  Returns the corresponding usernames of the pending messages from clients.
- `fe3d:network_server_get_pending_messages`() ---> `LIST`  
  Returns the contents of the pending messages from clients.
