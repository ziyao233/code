package main

import (
	"fmt"
	"time"
       )

func main() {
	hour := time.Now().Hour()
	switch {
	case hour < 12 : 
		fmt.Println("Good morning")
	case hour < 17 :
		fmt.Println("Good afternoon")
	case hour < 22 :
		fmt.Println("Good evening")
	default:
		fmt.Println("Good night")
	}
}
