import subprocess
import sys
import os

if len(sys.argv) != 2:
	print 'Error: Usage is python launch_firefox.py <profile_num>'
	exit(1)

profileNum = sys.argv[1]
devNull = open(os.devnull, 'w')
subprocess.call(["firefox", "-P", "eecs489profile" + profileNum], stdout=devNull, stderr=devNull)