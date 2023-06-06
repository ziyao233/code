package main

import (
	"fmt"
	"runtime"
       )

func main() {
	platform := ""
	switch runtime.GOOS {
		case "darwin" :
			platform = "OS X"
		case "linux" :
			platform = "Linux"
		default:
			platform = runtime.GOOS
	}
	fmt.Printf("Platform is %s\n", platform)
}
