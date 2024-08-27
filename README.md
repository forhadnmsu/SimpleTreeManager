# Clone the Repository First

```bash
source /exp/seaquest/app/software/osg/software/e1039/this-e1039.sh
cd /path/to/your_working_directory
git clone https://github.com/forhadnmsu/SimpleTreeManager.git
```
# Compilation of Analysis Code
The analysis code is located in AnaSimpleTree/src. The following commands set up the shell environment and compile the code:

```cd AnaSimpleTree
source setup.sh
cmake-this
make-this
```

# Running Simulation
As a test, to generate the MC events and get them in a simplified file called out.root, go to the macro directory and run:

```root -b 'Fun4Sim.C(100)'```
