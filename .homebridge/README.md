## To install on a Raspberry PI - Raspbian Stretch Lite

Install NodeJS
```
wget http://node-arm.herokuapp.com/node_latest_armhf.deb
sudo dpkg -i node_latest_armhf.deb
```

If you get the error message
```
compilation terminated.
dns_sd_bindings.target.mk:142: recipe for target 'Release/obj.target/dns_sd_bindings/src/dns_sd.o' failed
make: *** [Release/obj.target/dns_sd_bindings/src/dns_sd.o] Error 1
```

Then you are missing the `dns_sd.o` library, so
```
sudo apt-get install libavahi-compat-libdnssd-dev
```

Note that you may have other missing library errors, but fear not: 99% of the
compilation errors are due to missing library, so try to spot the missing library
(use the previous error message as a reference), and to install the corresponding
library  - usually looking for the error message on Google helps a lot ;)

So, let's install homebridge and the homebridge-http-accessory plugin
```
sudo npm install -g --unsafe-perm homebridge
sudo npm install -g homebridge-http-accessory
```

run homebridge once, to let it create the configuration files directory

```
homebridge

```

and copy `config.json` in `~/.homebridge`

to make hombridge start automatically at the RaspberryPi Boot, edit `/etc/rc.local`
```
sudo nano /etc/rc.local
```

And paste the line  `su pi -c /usr/local/bin/homebridge` right above `exit 0`

Then reboot
