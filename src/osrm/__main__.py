import site
import subprocess
import sys

if(len(sys.argv) < 2):
    print("Argument not provided")
    sys.exit(1)

exec = site.getusersitepackages()+"/bin/"

if(sys.argv[1] == "components"):
    exec += "osrm-components"

elif(sys.argv[1] == "contract"):
    exec += "osrm-contract"

elif(sys.argv[1] == "customize"):
    exec += "osrm-customize"

elif(sys.argv[1] == "datastore"):
    exec += "osrm-datastore"

elif(sys.argv[1] == "extract"):
    exec += "osrm-extract"

elif(sys.argv[1] == "partition"):
    exec += "osrm-partition"

elif(sys.argv[1] == "routed"):
    exec += "osrm-routed"

for i in range(2, len(sys.argv)):
    exec += " " + sys.argv[i]

# will stream any output to the shell
# shell=True is safe here and lets people use "~" in paths etc
proc = subprocess.run(exec, encoding="utf-8", shell=True)
sys.exit(proc.returncode)
