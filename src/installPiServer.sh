#!/bin/sh
cd ~
git clone https://github.com/Saint-Francis-Robotics-Team2367/yunServerSoftware.git
echo "#!/bin/sh
python /home/pi/yunServerSoftware/src/pi/server.py" > startServer.sh
chmod a+x startServer.sh
echo "./startServer.sh" >> .bashrc
echo -n "Enter Team Name? "
read name
echo "[Main]
TeamName = $name" > /home/pi/yunServerSoftware/src/pi/config.ini
