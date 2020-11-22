./cmake.exe --build cmake-build-debug --target lab_MPI -- -j 3
mpiexec -n 4 cmake-build-debug/lab_MPI.exe 

