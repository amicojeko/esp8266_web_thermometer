# To install on a RaspberryPi

cd ~

git clone git@github.com:amicojeko/esp8266_web_thermometer.git

mv esp8266_web_thermometer/homebridge_debugger/ ./

gpg --keyserver hkp://keys.gnupg.net --recv-keys 409B6B1796C275462A1703113804BB82D39DC0E3 7D2BAF1CF37B13E2069D6956105BD0E739499BDB

\curl -sSL https://get.rvm.io | bash -s stable --ruby
(this will take a while)
source /home/pi/.rvm/scripts/rvm

gem install bundler



cd homebridge_debugger



bundler
