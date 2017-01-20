#!/bin/bash

cp jaaps_povray.pl /var/www/localhost/cgi-bin/
cp *.inc /var/www/localhost/htdocs/render_data/
cp render_*.txt /var/www/localhost/htdocs/render_data/
cp render_*.sh /var/www/localhost/htdocs/render_data/
cp render_*.png /var/www/localhost/htdocs/render_data/

chown apache:apache /var/www/localhost/cgi-bin/jaaps_povray.pl
chmod 555 /var/www/localhost/cgi-bin/jaaps_povray.pl

chown apache:apache /var/www/localhost/htdocs/render_data/*.sh
chown apache:apache /var/www/localhost/htdocs/render_data/*.inc
chown apache:apache /var/www/localhost/htdocs/render_data/*.txt
chown apache:apache /var/www/localhost/htdocs/render_data/render_cone_apex.png
chown apache:apache /var/www/localhost/htdocs/render_data/render_cone_clipping.png

chmod 555 /var/www/localhost/htdocs/render_data/*.sh
chmod 444 /var/www/localhost/htdocs/render_data/*.inc
chmod 444 /var/www/localhost/htdocs/render_data/*.txt
chmod 444 /var/www/localhost/htdocs/render_data/render_cone_apex.png
chmod 444 /var/www/localhost/htdocs/render_data/render_cone_clipping.png

