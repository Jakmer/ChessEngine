#!/bin/bash

# Run server in the background
EngineStarter &

sleep 5

# Create an expect script to automate the input
expect <<EOF
spawn ClientStarter
expect "Please choose an option:"
send "1\r"
expect eof
EOF