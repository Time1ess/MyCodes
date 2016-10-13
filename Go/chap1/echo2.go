// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-08 20:16
// Last modified: 2016-10-08 20:27
// Filename: echo2.go
// Description:
package main

import (
    "fmt"
    "os"
    "strconv"
)

func main() {
    var s, sep string
    sep = " "
    for idx, arg := range os.Args[1:] {
        s += strconv.Itoa(idx) + sep + arg + sep
    }
    fmt.Println(s)
}
