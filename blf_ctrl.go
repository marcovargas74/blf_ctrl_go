package main

import (
	"fmt"

	"github.com/marcovargas74/blf_ctrl_go/includes"
)

func init() {
	fmt.Println("======== Start Aplication blf_control Version " + includes.Version + "========")
}

func testSucces(num int) int {
	return includes.SUCCESS
}

func main() {
	fmt.Println(testSucces(3))
	fmt.Println(includes.Version)
}
