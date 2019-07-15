# blf_ctrl_go
Its a application in go to control blf sinalization using a sip protocol

Its necessary to connect a server to get a status sinalization of a product application and pass another who will conume cosume this data.

We will work with go routines, TCP sockets and Maps.
This same application has been done in C code.  


Copy release to path 
cp ~/projetos-go/src/github.com/marcovargas74/blf_ctrl_go/blf_ctrl  ~/UNNITI_GIT/packetsAPP/blf_ctrl/zynq/ 

compila para Arm
env GOOS=linux GOARCH=arm GOARM=5 go build 
env GOOS=linux GOARCH=arm go build -o blf_ctrl