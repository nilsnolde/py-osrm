import site
import subprocess
import sys

if(len(sys.argv) < 2):
    print("Argument not provided")
    exit()

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

subprocess.call(args)
