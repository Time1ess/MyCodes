// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-08 20:16
// Last modified: 2016-10-08 20:16
// Filename: echo1.go
// Description:
package main

import (
    "fmt"
    "os"
)

func main() {
    var s, sep string
    for i := 1; i < len(os.Args); i++ {
        s += sep + os.Args[i]
        sep = " "
    }
    fmt.Println(s)
}
