# Client Scripting Functions

## Setters

- `fe3d:client_start` (`STR` username) -----> `NONE`
- `fe3d:client_connect` (`STR` ip_address) -----> `NONE`
- `fe3d:client_disconnect` () -----> `NONE`
- `fe3d:client_stop` () -----> `NONE`
- `fe3d:client_send_tcp_message` (`STR` content) -----> `NONE`
- `fe3d:client_send_udp_message` (`STR` content) -----> `NONE`

## Getters

- `fe3d:client_is_valid_ip` (`STR` ip_address) -----> `BOL`
- `fe3d:client_is_running` () -----> `BOL`
- `fe3d:client_is_connecting` () -----> `BOL`
- `fe3d:client_is_connected` () -----> `BOL`
- `fe3d:client_is_accepted` () -----> `BOL`
- `fe3d:server_get_pending_protocols` () -----> `LIST`
- `fe3d:server_get_pending_contents` () -----> `LIST`
- `fe3d:client_get_ping_latency` () -----> `INT`
- `fe3d:client_get_server_ip` () -----> `STR`
- `fe3d:client_get_username` () -----> `STR`
