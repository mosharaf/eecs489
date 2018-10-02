import subprocess
import sys

if len(sys.argv) != 2:
	print 'Error: Usage is python start_server.py <host_number>'
	exit(1)

conf = sys.argv[1]
if(int(conf) < 1 or int(conf) > 8):
	print 'Error: <host_number> must be between 1 and 8'
	exit(1)
subprocess.call(["/usr/local/apache2/bin/apachectl", "-f", "/home/proj2/.confs/httpd" + conf + ".conf"])