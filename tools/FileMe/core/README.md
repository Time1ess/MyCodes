## Request Usage

### Request Format

|Format|Description
|:---|:---
|`REG host_ip msg_port_num`|Register a `host` with message port `msg_port_num`
|`URE host_ip`|Unregister a `host` from local host
|`PUT -h host_ip -p port_num -f file_name [-F]`|Request for sending a file named `file_name ` to `host_ip `:`port_num`
|`GET -h host_ip -p port_num -f file_name [-F]`|Request a file named `file_name` from `host_ip`:`port_num`

### Response Format

|Format|Description
|:---|:---
|`ACK cmd`|Notify client that `cmd` has been acknowledged
|`REJ cmd code reason`|Nofity client that `cmd` has been rejected with reject code `code` and reason `reason`
|`SRG msg_port_num host`|Notify client that server `host` messenger is listening at port `msg_port_num`
|`SPT host_ip port_num file_name`|Notify client that server is ready to receive file `file_name` via port `port_num`
|`SGT host_ip port_num file_name`|Notify client that server is ready to provide file `file_name` via port `port_num`
|`DLY cmd host_ip file_name`|Notify client that server will delay transfering file `file_name` on cmd `cmd`

### Code Table

|Reject Code|Description
|:---|:---
|001|Invalid host
|002|Unknown reason
|003|User reject
|101|Local host should not be registered
|102|Host ip doesn't match
|201|Invalid operation
|301|Target host doesn't match
|400|Put session has been created
|401|Port has been used
|402|Master session pool has full, waitting
|403|Unknown error in master put session
|500|Slave put session is ready
|501|No such file session with this host
|502|Local session pool has full, waitting
|600|Master get session is ready
|603|Unknown error in master get session
|700|Slave get session is ready
