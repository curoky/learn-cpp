# bind and connect use a specific IP address

## Usage

```bash
#!/bin/bash

BIND_IF='eth2'
BIND_ADDR4=$(/sbin/ifconfig $BIND_IF | grep 'inet ' | awk '{print $2}')
⁣BIND_ADDR6=$(/sbin/ifconfig $BIND_IF | grep 'inet6' | grep global | awk '{print $2}')

# BIND_ADDR4=$(ip route | grep $BIND_IF | grep -v default | awk '{print $NF}')

LD_PRELOAD=./bind.so ./main
```
