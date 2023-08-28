import site
import subprocess
import sys

if(len(sys.argv) < 2):
    print("Argument not provided")
    sys.exit(1)

execpath = site.getusersitepackages()+"/bin/"

if(sys.argv[1] == "components"):
    execpath += "osrm-components"

elif(sys.argv[1] == "contract"):
    execpath += "osrm-contract"

elif(sys.argv[1] == "customize"):
    execpath += "osrm-customize"

elif(sys.argv[1] == "datastore"):
    execpath += "osrm-datastore"

elif(sys.argv[1] == "extract"):
    execpath += "osrm-extract"

elif(sys.argv[1] == "partition"):
    execpath += "osrm-partition"

elif(sys.argv[1] == "routed"):
    execpath += "osrm-routed"

args = [execpath]

for i in range(2, len(sys.argv)):
    args.append(sys.argv[i])

# will stream any output to the shell
# shell=True is safe here and lets people use "~" in paths etc
proc = subprocess.run(args, encoding="utf-8", capture_output=True, shell=True)
sys.exit(proc.returncode)
