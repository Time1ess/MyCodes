// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-08 20:16
// Last modified: 2016-10-08 20:19
// Filename: echo3.go
// Description:
package main

import (
    "fmt"
    "os"
    "strings"
)

func main() {
    fmt.Println(strings.Join(os.Args[1:], " "))
}
