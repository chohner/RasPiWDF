#!/bin/bash

ip_host=$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1')
echo Host IP: $ip_host
# first two bytes
ip_static=${ip_host:0:8}
# third byte
ip_sweep=${ip_host:8:2}

# clear period
if [ "${ip_sweep:1}" = "." ]
  then
    ip_sweep=${ip_sweep:0:1}
fi

# define search range around third byte:
r=1

# search and print
search () {
  # pass IP
  echo "Searching in : "$1
  sudo nmap -sP $1 | awk '/^Nmap/{ip=$NF}/B8:27:EB/{print "Raspberry IP: "ip}'
}

# start with current
s=$ip_static$ip_sweep.0/24
search $s

echo "- start sweeping -"
for ((i=-r; i<=r; i++)); do
  if [ $i -eq 0 ]; then
    # skip current
    i+=1
  fi
  s=$ip_static$((ip_sweep+i)).0/24
  search $s
done
