# Server Scripting Functions

## Setters

- `fe3d:server_start` (`INT` max_player_count) -----> `NONE`
- `fe3d:server_stop` () -----> `NONE`
- `fe3d:server_send_tcp_message` (`STR` username, `STR` content) -----> `NONE`
- `fe3d:server_send_udp_message` (`STR` username, `STR` content) -----> `NONE`
- `fe3d:server_broadcast_tcp_message` (`STR` content) -----> `NONE`
- `fe3d:server_broadcast_udp_message` (`STR` content) -----> `NONE`
- `fe3d:server_disconnect_client` (`STR` username) -----> `NONE`
- `fe3d:server_disconnect_clients` () -----> `NONE`

## Getters

- `fe3d:server_is_running` () -----> `BOL`
- `fe3d:server_is_client_connected` (`STR` username) -----> `BOL`
- `fe3d:server_get_new_ip` () -----> `STR`
- `fe3d:server_get_new_username` () -----> `STR`
- `fe3d:server_get_old_ip` () -----> `STR`
- `fe3d:server_get_old_username` () -----> `STR`
- `fe3d:server_get_connected_ips` () -----> `LIST`
- `fe3d:server_get_connected_usernames` () -----> `LIST`
- `fe3d:server_get_pending_protocols` () -----> `LIST`
- `fe3d:server_get_pending_usernames` () -----> `LIST`
- `fe3d:server_get_pending_contents` () -----> `LIST`
