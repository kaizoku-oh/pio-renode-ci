#!/bin/sh

# Starts the built Renode image without a GUI
# To attach to it, use Telnet

sh renode --disable-xwt scripts/renode_l4_config --port 33334