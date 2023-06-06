package main

import (
	"fmt"
	"strings"
       )

func wordCount(s string) map[string]int {
	res := make(map[string]int)
	for _, part := range(strings.Fields(s)) {
		_, ok := res[part]
		if !ok {
			res[part] = 1
		} else {
			res[part]++
		}
	}
	return res
}

func main() {
	fmt.Println(wordCount("This is a normal string string is is is"))
}
