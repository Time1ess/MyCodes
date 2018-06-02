package main

import "fmt"
import "time"
import "sync/atomic"

func main() {
  var ops uint64

  for i := 0; i < 50; i++ {
    go func() {
      for k := 0; k < 50; k++ {
        atomic.AddUint64(&ops, 1)
        time.Sleep(time.Millisecond)
      }
    }()
  }

  time.Sleep(time.Second)
  opsFinal := atomic.LoadUint64(&ops)
  fmt.Println("ops:", opsFinal)
}
