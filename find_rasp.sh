ip=$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1')
echo Your IP: $ip
sudo nmap -sP $ip/24 | awk '/^Nmap/{ip=$NF}/B8:27:EB/{print ip}'

