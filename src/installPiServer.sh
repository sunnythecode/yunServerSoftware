#!/bin/sh
cd ~
sudo apt update
sudo apt install git python-smbus
git clone https://github.com/Saint-Francis-Robotics-Team2367/yunServerSoftware.git

echo "#!/bin/sh
cd /home/pi/
su pi -c 'python /home/pi/yunServerSoftware/src/pi/server.py" > startServer.sh

chmod a+x startServer.sh

echo "[Unit]
Description=Soccer bots
After=multi-user.target

[Service]
Type=idle
ExecStart=/home/pi/startServer.sh

[Install]
WantedBy=multi-user.target" | sudo tee /lib/systemd/system/soccerbots.service

sudo chmod 644 /lib/systemd/system/soccerbots.service
sudo systemctl daemon-reload
sudo systemctl enable soccerbots.service


echo -n "Enter Team Name? "
read name < /dev/tty
echo "[Main]
TeamName = $name" > /home/pi/yunServerSoftware/src/pi/config.ini
