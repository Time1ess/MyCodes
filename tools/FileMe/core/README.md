##  Request Usage

### Request Format

|Format|Description
|:---|:---
|`REG host_ip msg_port_num`|Register a `host` with message port `msg_port_num`
|`URE host_ip`|Unregister a `host` from local host
|`PUT -h host_ip -p port_num file_name [-f]`|Request for sending a file named `file_name ` to `host_ip `:`port_num`
|`GET -h host_ip -p port_num file_name [-f]`|Request a file named `file_name` from `host_ip`:`port_num`

### Response Format

|Format|Description
|:---|:---
|`ACK cmd`|Notify client that `cmd` has been acknowledged
|`REJ cmd code reason`|Nofity client that `cmd` has been rejected with reject code `code` and reason `reason`
|`SRG msg_port_num`|Notify client that server messenger is listening at port `msg_port_num`
|`SPT port_num`|Notify client that server is ready to receive file via port `port_num`
|`SGT port_num`|Notify client that server is ready to provide file via port `port_num`
|`CGT port_num`|Notify server that client is about to receive file from server port `port_num`