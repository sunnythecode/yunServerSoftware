#!/bin/sh
cd ~
git clone https://github.com/Saint-Francis-Robotics-Team2367/yunServerSoftware.git
echo "#!/bin/sh\npython /home/pi/yunServerSoftware/src/pi/server.py" > startServer.sh
chmod a+x startServer.sh
echo "./startServer.sh" >> .bashrc
